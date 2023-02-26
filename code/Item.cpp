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
		m_tInfo.strTypeName = "무기";
		break;
	case IT_ARMOR:
		m_tInfo.strTypeName = "방어구";
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

	// 이름 길이를 불러온다.
	int iLength = 0;
	pFile->Read(&iLength, 4);

	char* pName = new char[iLength + 1];		// +1은 마지막 NULL
	memset(pName, 0, iLength);

	pFile->Read(pName, iLength);
	pName[iLength] = NULL;			// 마지막에 NULL 문자를 넣어준다. (안 넣어주면 몬스터 이름 뒤에 이상한 문자 출력됨)

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
