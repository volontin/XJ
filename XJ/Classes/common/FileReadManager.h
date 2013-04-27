//
//  FileReadManager.h
//  Datang
//
//  Created by 于志鹏 on 13-2-5.
//
//

#ifndef __Datang__FileReadManager__
#define __Datang__FileReadManager__

class FileReadManager{
public:
	FileReadManager(void);
	~FileReadManager(void);
	void readFileData(const char* pszFileName, const char* pszMode);
    int readInt();
    short readShort();
    char readByte();
    bool readBool();
    char * readUTF();
	void setIsPopupNotify(bool bNotify);
	bool getIsPopupNotify();
private:
	unsigned char * pBuffer;
	unsigned long iBufferSize;
	unsigned long iBufferIndex;
};
#endif /* defined(__Datang__FileReadManager__) */