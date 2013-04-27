//
//  ODSocket.h
//  Datang
//
//  Created by 于志鹏 on 13-2-18.
//
//

#ifndef __Datang__ODSocket__
#define __Datang__ODSocket__
#ifdef WIN32
#include <winsock.h>
typedef int				socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "cocos2d.h"
typedef int				SOCKET;

//#pragma region define win32 const variable in linux
#define INVALID_SOCKET	-1
#define SOCKET_ERROR	-1
//#pragma endregion
#endif

class SocketReciever{
public:
    virtual void receivedMessage(const char * strings){
        CC_UNUSED_PARAM(strings);
    }
};

class ODSocket{

    CC_SYNTHESIZE(SocketReciever *, delegate, Delegate);
private:
    bool _isConnected;
    
public:
	ODSocket(SOCKET sock = INVALID_SOCKET);
	~ODSocket();
    
    static ODSocket * sharedODSocket();
    
    bool isConnected();//是否已经连接
    
	// Create socket object for snd/recv data
	bool Create(int af, int type, int protocol = 0);
    
	// Connect socket
	bool Connect(const char* ip, unsigned short port);
	//#region server
	// Bind socket
	bool Bind(unsigned short port);
    
	// Listen socket
	bool Listen(int backlog = 5);
    
	// Accept socket
	bool Accept(ODSocket& s, char* fromip = NULL);
	//#endregion
	
	// Send socket
	int Send(const char* buf, int len, int flags = 0);
    
	// Recv socket
	int Recv(char* buf, int len, int flags = 0);
	
	// Close socket
	int Close();
    
	// Get errno
	int GetError();
	
	//#pragma region just for win32
	// Init winsock DLL
	static int Init();
	// Clean winsock DLL
	static int Clean();
	//#pragma endregion
    
	// Domain parse
	static bool DnsParse(const char* domain, char* ip);
    
	ODSocket& operator = (SOCKET s);
    
	operator SOCKET ();
    
    void gameloop();

protected:
	SOCKET m_sock;
};
void startRequestThread();
#endif /* defined(__Datang__ODSocket__) */
