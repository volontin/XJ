//
//  FileReadManager.cpp
//  Datang
//
//  Created by 于志鹏 on 13-2-5.
//
//

#include "FileReadManager.h"

#include "cocos2d.h"
#include "platform/CCFileUtils.h"
USING_NS_CC;

FileReadManager::FileReadManager(void)
:pBuffer(NULL)
,iBufferSize(0)
,iBufferIndex(-1)
{
}


FileReadManager::~FileReadManager(void)
{
    CC_SAFE_DELETE(pBuffer);
}

static bool s_bPopupNotify = true;

void FileReadManager::setIsPopupNotify(bool bNotify)
{
    s_bPopupNotify = bNotify;
}

bool FileReadManager::getIsPopupNotify()
{
    return s_bPopupNotify;
}
void FileReadManager::readFileData(const char* pszFileName, const char* pszMode)
{
    const char *filepath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFileName).c_str();
    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(filepath, pszMode, &iBufferSize);
    iBufferIndex = 0;
}
int FileReadManager::readInt()
{
    if (iBufferIndex + 4 < iBufferSize) {
    	unsigned char temp[4];
        memcpy(&temp,pBuffer+iBufferIndex,4);
        iBufferIndex += 4;
        return temp[0]<<24|temp[1]<<16|temp[2]<<8|temp[3];
    }else{
        const char* str = "read Int error because of out of range";
        printf("%s",str);
        throw str;
    }
    
}
short FileReadManager::readShort()
{
    if (iBufferIndex + 2 < iBufferSize) {
        unsigned char temp[2];
        memcpy(&temp,pBuffer + iBufferIndex,2);
        iBufferIndex += 2;
        return temp[0]<<8|temp[1];
    }else{
        const char* str = "read Short error because of out of range";
        printf("%s",str);
        throw str;
    }
}
char FileReadManager::readByte()
{
    if (iBufferIndex + 1 < iBufferSize) {
        unsigned char temp;
        memcpy(&temp,pBuffer + iBufferIndex,1);
        iBufferIndex++;
        return temp;
    }else{
        const char* str = "read Byte error because of out of range";
        printf("%s",str);
        throw str;
    }
}
bool FileReadManager::readBool()
{
    if (iBufferIndex + 1 < iBufferSize) {
        bool temp;
        memcpy(&temp,pBuffer + iBufferIndex,1);
        iBufferIndex++;
        return temp;
    }else{
        const char* str = "read Bool error because of out of range";
        printf("%s",str);
        throw str;
    }
}
char* FileReadManager::readUTF()
{
    //utf 8字符串 ，前2字节（16位）表示字符串的长度
	unsigned char temp[2];
	memcpy(&temp,pBuffer + iBufferIndex,2);
	iBufferIndex += 2;
    short length = temp[0]<<8|temp[1];
    if (iBufferIndex + length < iBufferSize) {
        char * str = new char[length];
        memcpy(str,pBuffer + iBufferIndex,length);
        iBufferIndex += length;
        return str;
    }else{
        const char* str = "read UTF error because of out of range";
        printf("%s",str);
        throw str;
    }
}