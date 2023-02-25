#include "Object.h"
#include "FileStream.h"

CObject::CObject()
{
}

CObject::CObject(const CObject& obj)
{
	m_strName = obj.m_strName;
	m_eType = obj.m_eType;
}

CObject::~CObject()
{
}

OBJECT_TYPE CObject::GetObjectType() const
{
	return m_eType;
}

bool CObject::Init()
{
	return true;
}

void CObject::Render()
{
}

void CObject::Save(CFileStream* pFile)
{
	// enum의 크기는 항상 4byte이다.
	pFile->Write(&m_eType, sizeof(OBJECT_TYPE));

	int iLength = m_strName.length();

	// 이름 길이를 저장한다.
	pFile->Write(&iLength, 4);

	// 이름을 저장한다.
	pFile->Write((void*)m_strName.c_str(), iLength);
}

void CObject::Load(CFileStream* pFile)
{
	pFile->Read(&m_eType, sizeof(OBJECT_TYPE));

	// 이름 길이를 불러온다.
	int iLength = 0;
	pFile->Read(&iLength, 4);

	char* pName = new char[iLength + 1];		// +1은 마지막 NULL
	memset(pName, 0, iLength);

	pFile->Read(pName, iLength);
	pName[iLength] = NULL;			// 마지막에 NULL 문자를 넣어준다. (안 넣어주면 몬스터 이름 뒤에 이상한 문자 출력됨)

	m_strName = pName;

	// 다 썼으면 동적 배열 메모리 해제
	SAFE_DELETE_ARRAY(pName);
}
