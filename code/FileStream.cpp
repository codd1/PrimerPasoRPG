#include "FileStream.h"

CFileStream::CFileStream() :
	m_pFIle(NULL),
	m_bOpen(false),
	m_iFileSize(0),
	m_iCurrent(0)
{
}

CFileStream::CFileStream(const char* pFileName, const char* pMode)
{
	Open(pFileName, pMode);
}

CFileStream::~CFileStream()
{
	Close();
}

bool CFileStream::Open(const char* pFileName, const char* pMode)
{
	fopen_s(&m_pFIle, pFileName, pMode);

	if (!m_pFIle) {
		return false;
	}

	m_bOpen = true;

	if (pMode[0] == 'r' || pMode[0] == 'R') {		// �б� ���
		m_eMode = FM_READ;
	}
	else if (pMode[0] == 'w' || pMode[0] == 'W') {	// ���� ���
		m_eMode = FM_WRITE;
	}

	fseek(m_pFIle, 0, SEEK_END);	// �� �ڷ� �ű��.
	m_iFileSize = ftell(m_pFIle);	// ���� Ŀ���� ��ġ�� �����´�. (=����ũ��)
	fseek(m_pFIle, 0, SEEK_SET);	// ó�� ��ġ�� �������´�.

	return true;
}

bool CFileStream::Close()
{
	if (!m_bOpen) {
		return false;
	}

	fclose(m_pFIle);
	m_pFIle = NULL;
	m_bOpen = false;
	m_iFileSize = 0;

	return true;
}

bool CFileStream::Read(void* pData, int iSize)
{
	return true;
}

bool CFileStream::ReadLine(void* pData, int* pSize)
{
	return true;
}

bool CFileStream::Write(void* pData, int iSize)
{
	return true;
}
