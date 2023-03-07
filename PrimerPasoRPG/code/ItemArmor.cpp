#include "ItemArmor.h"
#include "FileStream.h"

CItemArmor::CItemArmor()
{
}

CItemArmor::CItemArmor(const CItemArmor& item) :
	CItem(item)
{
	m_iArmor = item.m_iArmor;
}

CItemArmor::~CItemArmor()
{
}

void CItemArmor::SetArmor(int iArmor)
{
	m_iArmor = iArmor;
}

bool CItemArmor::Init()
{
	return true;
}

void CItemArmor::Render()
{
	cout << "이름: " << m_strName << "\t종류: " << m_tInfo.strTypeName << endl;
	cout << "방어력: " << m_iArmor << endl;
	cout << "구매가: " << m_tInfo.iPrice << "\t판매가: " << m_tInfo.iSell << endl;
	cout << "아이템 설명: " << m_tInfo.strDesc << endl;
}

CItemArmor* CItemArmor::Clone()
{
	return new CItemArmor(*this);
}

void CItemArmor::Save(CFileStream* pFile)
{
	CItem::Save(pFile);

	pFile->Write(&m_iArmor, 4);
}

void CItemArmor::Load(CFileStream* pFile)
{
	CItem::Load(pFile);

	pFile->Read(&m_iArmor, 4);
}
