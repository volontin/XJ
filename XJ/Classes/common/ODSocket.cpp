//
//  ODSocket.cpp
//  Datang
//
//  Created by 于志鹏 on 13-2-18.
//
//

#include "ODSocket.h"
#include "../common/Common.h"

#include <errno.h>
#ifdef WIN32
#pragma comment(lib, "wsock32")
#endif

USING_NS_CC;

ODSocket::ODSocket(SOCKET sock)
:_isConnected(false)
{
	m_sock = sock;
}

ODSocket::~ODSocket()
{
}

static ODSocket * singleSocket;

ODSocket * ODSocket::sharedODSocket(){
    if (singleSocket == NULL) {
        singleSocket = new ODSocket();
        
    }
    return singleSocket;
}

bool ODSocket::isConnected(){
    return _isConnected;
}

int ODSocket::Init()
{
#ifdef WIN32
	/*
     http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx
     
     typedef struct WSAData {
     WORD wVersion;								//winsock version
     WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
     char szDescription[WSADESCRIPTION_LEN+1];
     char szSystemStatus[WSASYSSTATUS_LEN+1];
     unsigned short iMaxSockets;
     unsigned short iMaxUdpDg;
     char FAR * lpVendorInfo;
     }WSADATA, *LPWSADATA;
     */
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8))
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret ) {
        //		cerr << "Initilize winsock error !" << endl;
		return -1;
	}
#endif
	
	return 0;
}
//this is just for windows
int ODSocket::Clean()
{
#ifdef WIN32
    return (WSACleanup());
#endif
    return 0;
}

ODSocket& ODSocket::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

ODSocket::operator SOCKET ()
{
	return m_sock;
}
//create a socket object win/lin is the same
// af:
bool ODSocket::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if ( m_sock == INVALID_SOCKET ) {
		return false;
	}
	return true;
}

bool ODSocket::Connect(const char* ip, unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip);
	svraddr.sin_port = htons(port);
	int ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
    _isConnected = true;
    startRequestThread();
	return true;
}

bool ODSocket::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);
    
	int opt =  1;
	if ( setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0 )
		return false;
    
	int ret = bind(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}
//for server
bool ODSocket::Listen(int backlog)
{
	int ret = listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

bool ODSocket::Accept(ODSocket& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR ) {
		return false;
	}
    
	s = sock;
	if ( fromip != NULL )
		CCLOG(fromip, "%s", inet_ntoa(cliaddr.sin_addr));
    
	return true;
}

int ODSocket::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count = 0;
    CCLog("send::%s",buf);
	while ( count < len ) {
		bytes = send(m_sock, buf + count, len - count, flags);
        CCLog("send bytes=%d",bytes);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	}
	return count;
}

int ODSocket::Recv(char* buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}

int ODSocket::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

int ODSocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

bool ODSocket::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
    
    CCLOG(ip,
          "%u.%u.%u.%u",
          (unsigned char)p->h_addr_list[0][0],
          (unsigned char)p->h_addr_list[0][1],
          (unsigned char)p->h_addr_list[0][2],
          (unsigned char)p->h_addr_list[0][3]);
	
	return true;
}
int sock_read (int fd, char *buf, int bufsize)
{
    int res;
    do
        res = read (fd, buf, bufsize);
    while (res == -1);
    return res;
}

void * unUsed;

void *threadProcessFunction(void *ptr)
{
    //    CCThread thread;
    //    thread.createAutoreleasePool();
    char * temp = (char *)malloc(sizeof(char)* 3072);//若接收的信息不以'\n'结尾，则临时保存至temp
    char * buffer = (char *)malloc(sizeof(char)*3072);
    bool isTemp = false;

//    char *recvBuf = (char *)malloc(sizeof(char)*1049);
    while (ODSocket::sharedODSocket()->isConnected()) {
        //do thread thing
    char recvBuf[1049] = "\0";
        int bytesRead = ODSocket::sharedODSocket()->Recv(recvBuf,sizeof(recvBuf)-1,0);
//        printf("recvBuf=%s",recvBuf);
//        printf("\n");
        if ( bytesRead > 0 ) {
            if (*recvBuf == -1) {//过滤socket连接建立后服务器返回的9字节无用信息，首字节值为-1
                continue;
            }
            recvBuf[bytesRead]='\0';
            if (isTemp) {
                buffer = strcat(temp, recvBuf);
                isTemp = false;
//                printf("buffer1=%s",buffer);
//                printf("\n");
            }else{
                memcpy(buffer, recvBuf,bytesRead+1);
//                printf("buffer2=%s",buffer);
//                printf("\n");
            }

            int length = strlen(buffer);
            if (buffer[length-1] != '\n') {//接收的信息不以'\n'结尾，则临时保存至temp
                memcpy(temp, buffer,length+1);
                isTemp = true;
//                printf("temp=%s",temp);
//                printf("\n");
            }else{//以'\n'结尾，发送至游戏信息池进行处理
                isTemp = false;
                ODSocket::sharedODSocket()->getDelegate()->receivedMessage(buffer);
            }
//            int index = length;
//            while (index > 0 && buffer[index - 1] != '\n') {
//                index --;
//            }
//            if (index > 0) {
//                memcpy(temp, buffer,index);
//                printf("receivedMessage::%s",temp);
//                printf("\n");
//                ODSocket::sharedODSocket()->getDelegate()->receivedMessage(temp);
//                if (index < length) {
//                    isTemp = true;
//                    memcpy(temp, buffer + index, length - index + 1);
//                    printf("temp=%s",temp);
//                    printf("\n");
//                }else{
//                    isTemp = false;
//                }
//            }
        }
    }
    CC_SAFE_FREE(buffer);
    CC_SAFE_FREE(temp);
    return NULL;
}
void startRequestThread()
{
    // Create the thread using POSIX routines.
    pthread_attr_t attr;
    pthread_t posixThreadID;
    int returnVal;
    returnVal = pthread_attr_init(&attr);
    assert(!returnVal);
    returnVal = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    assert(!returnVal);
    int threadError = 0;
    
    threadError = pthread_create(&posixThreadID, &attr, &threadProcessFunction, (void*)unUsed);
    returnVal = pthread_attr_destroy(&attr);
    assert(!returnVal);
    if (threadError != 0)
    {
        printf("create thread error");
    }
}

