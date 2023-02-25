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
	// enum�� ũ��� �׻� 4byte�̴�.
	pFile->Write(&m_eType, sizeof(OBJECT_TYPE));

	int iLength = m_strName.length();

	// �̸� ���̸� �����Ѵ�.
	pFile->Write(&iLength, 4);

	// �̸��� �����Ѵ�.
	pFile->Write((void*)m_strName.c_str(), iLength);
}

void CObject::Load(CFileStream* pFile)
{
	pFile->Read(&m_eType, sizeof(OBJECT_TYPE));

	// �̸� ���̸� �ҷ��´�.
	int iLength = 0;
	pFile->Read(&iLength, 4);

	char* pName = new char[iLength + 1];		// +1�� ������ NULL
	memset(pName, 0, iLength);

	pFile->Read(pName, iLength);
	pName[iLength] = NULL;			// �������� NULL ���ڸ� �־��ش�. (�� �־��ָ� ���� �̸� �ڿ� �̻��� ���� ��µ�)

	m_strName = pName;

	// �� ������ ���� �迭 �޸� ����
	SAFE_DELETE_ARRAY(pName);
}
