#include "FileStream.h"

CFileStream::CFileStream() :
	m_pFile(NULL),
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
	fopen_s(&m_pFile, pFileName, pMode);

	if (!m_pFile) {
		return false;
	}

	m_bOpen = true;

	if (pMode[0] == 'r' || pMode[0] == 'R') {		// 읽기 모드
		m_eMode = FM_READ;
	}
	else if (pMode[0] == 'w' || pMode[0] == 'W') {	// 쓰기 모드
		m_eMode = FM_WRITE;
	}

	fseek(m_pFile, 0, SEEK_END);	// 맨 뒤로 옮긴다.
	m_iFileSize = ftell(m_pFile);	// 현재 커서의 위치를 가져온다. (=파일크기)
	fseek(m_pFile, 0, SEEK_SET);	// 처음 위치로 돌려놓는다.

	return true;
}

bool CFileStream::Close()
{
	if (!m_bOpen) {
		return false;
	}

	fclose(m_pFile);
	m_pFile = NULL;
	m_bOpen = false;
	m_iFileSize = 0;

	return true;
}

bool CFileStream::Read(void* pData, int iSize)
{
	if (!m_bOpen || m_eMode != FM_READ) {
		return false;
	}
	fread(pData, iSize, 1, m_pFile);

	m_iCurrent += iSize;

	return true;
}

bool CFileStream::ReadLine(void* pData, int* pSize)
{
	if (!m_bOpen || m_eMode != FM_READ) {
		return false;
	}

	char cBuffer = 0;

	vector<char> vec;
	vec.reserve(128);		// 예약공간

	while (feof(m_pFile) == 0) {		// feof가 0일 때는 파일의 끝이 아니다.
		fread(&cBuffer, 1, 1, m_pFile);

		// 한 문장씩 읽는 것이므로 '\n'을 만나면 반복문 종료
		if (cBuffer == '\n') {
			break;
		}

		vec.push_back(cBuffer);
	}
	*pSize = vec.size();

	// 메모리 복사 memcpy 함수
	// memcpy(복사 받을 메모리를 가리키고 있는 포인터, 복사할 메모리를 가리키고 있는 포인터, 복사할 데이터(값)의 크기
	memcpy(pData, &vec[0], vec.size());

	m_iCurrent += vec.size();

	return true;
}

bool CFileStream::Write(void* pData, int iSize)
{
	if (!m_bOpen || m_eMode != FM_WRITE) {
		return false;
	}

	fwrite(pData, iSize, 1, m_pFile);

	return true;
}
