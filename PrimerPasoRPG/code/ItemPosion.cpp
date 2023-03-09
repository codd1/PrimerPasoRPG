#include "ItemPosion.h"
#include "FileStream.h"

CItemPosion::CItemPosion()
{
}

CItemPosion::CItemPosion(const CItemPosion& item)
{
}

CItemPosion::~CItemPosion()
{
}

void CItemPosion::SetPosion(int iPosion)
{
	m_iPosion = iPosion;
}

bool CItemPosion::Init()
{
	return true;
}

void CItemPosion::Render()
{
	cout << "이름: " << m_strName << "\t종류: " << m_tInfo.strTypeName << endl;
	cout << "회복량: " << m_iPosion << endl;
	cout << "구매가: " << m_tInfo.iPrice << "\t판매가: " << m_tInfo.iSell << endl;
	cout << "아이템 설명: " << m_tInfo.strDesc << endl;
}

CItemPosion* CItemPosion::Clone()
{
	return new CItemPosion(*this);
}

void CItemPosion::Save(CFileStream* pFile)
{
	CItem::Save(pFile);

	pFile->Write(&m_iPosion, 4);
}

void CItemPosion::Load(CFileStream* pFile)
{
	CItem::Load(pFile);

	pFile->Read(&m_iPosion, 4);
}
