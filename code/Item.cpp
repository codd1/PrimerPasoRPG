#include "Item.h"
#include "FileStream.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& item):
	CObject(item)
{
	m_tInfo = item.m_tInfo;
}

CItem::~CItem()
{
}

void CItem::SetItemInfo(ITEM_TYPE eType, int iPrice, int iSell, const char* pDesc)
{
	m_tInfo.eType = eType;

	switch (eType) {
	case IT_WEAPON:
		m_tInfo.strTypeName = "����";
		break;
	case IT_ARMOR:
		m_tInfo.strTypeName = "��";
		break;
	}

	m_tInfo.iPrice = iPrice;
	m_tInfo.iSell = iSell;
	m_tInfo.strDesc = pDesc;
}

bool CItem::Init()
{
	return true;
}

void CItem::Render()
{
}

void CItem::Save(CFileStream* pFile)
{
	CObject::Save(pFile);
	//pFile->Write(&m_tInfo, sizeof(m_tInfo));

	pFile->Write(&m_tInfo.eType, 4);

	int iLength = m_tInfo.strTypeName.length();
	pFile->Write(&iLength, 4);

	pFile->Write((void*)m_tInfo.strTypeName.c_str(), iLength);

	pFile->Write(&m_tInfo.iPrice, 4);
	pFile->Write(&m_tInfo.iSell, 4);
	
	iLength = m_tInfo.strDesc.length();
	pFile->Write(&iLength, 4);

	pFile->Write((void*)m_tInfo.strDesc.c_str(), iLength);
}

void CItem::Load(CFileStream* pFile)
{
	CObject::Load(pFile);
	
	//pFile->Read(&m_tInfo, sizeof(m_tInfo));

	pFile->Read(&m_tInfo.eType, 4);

	// �̸� ���̸� �ҷ��´�.
	int iLength = 0;
	pFile->Read(&iLength, 4);

	char* pName = new char[iLength + 1];		// +1�� ������ NULL
	memset(pName, 0, iLength);

	pFile->Read(pName, iLength);
	pName[iLength] = NULL;			// �������� NULL ���ڸ� �־��ش�. (�� �־��ָ� ���� �̸� �ڿ� �̻��� ���� ��µ�)

	m_tInfo.strTypeName = pName;
	SAFE_DELETE_ARRAY(pName);

	pFile->Read(&m_tInfo.iPrice, 4);
	pFile->Read(&m_tInfo.iSell, 4);

	iLength = 0;
	pFile->Read(&iLength, 4);

	pName = new char[iLength + 1];
	memset(pName, 0, iLength);

	pFile->Read(pName, iLength);
	pName[iLength] = NULL;

	m_tInfo.strDesc = pName;
	SAFE_DELETE_ARRAY(pName);
}
