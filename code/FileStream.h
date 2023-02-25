#pragma once

#include "value.h"

class CFileStream
{
public:
	CFileStream();
	CFileStream(const char* pFileName, const char* pMode);
	~CFileStream();

private:
	enum FILE_MODE {
		FM_READ,
		FM_WRITE
	};

private:
	FILE* m_pFIle;
	bool m_bOpen;
	FILE_MODE m_eMode;
	int m_iFileSize;
	int m_iCurrent;

public:
	bool GetOpen() const {
		return m_bOpen;
	}

	int GetFileSize() const {
		return m_iFileSize;
	}

public:
	bool Open(const char* pFileName, const char* pMode);
	bool Close();
	bool Read(void* pData, int iSize);
	bool ReadLine(void* pData, int* pSize);
	bool Write(void* pData, int iSize);
};

