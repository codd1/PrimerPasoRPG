#include "ItemWeapon.h"
#include "FileStream.h"

CItemWeapon::CItemWeapon()
{
}

CItemWeapon::CItemWeapon(const CItemWeapon& item) :
	CItem(item)
{
	m_iAttackMin = item.m_iAttackMin;
	m_iAttackMax = item.m_iAttackMax;
	m_fCritical = item.m_fCritical;
}

CItemWeapon::~CItemWeapon()
{
}

void CItemWeapon::SetWeaponInfo(int iAttackMin, int iAttackMax, float fCritical)
{
	m_iAttackMin = iAttackMin;
	m_iAttackMax = iAttackMax;
	m_fCritical = fCritical;
}

void CItemWeapon::SetAttackMin(int iAttackMin)
{
	m_iAttackMin = iAttackMin;
}

void CItemWeapon::SetAttackMax(int iAttackMax)
{
	m_iAttackMax = iAttackMax;
}

void CItemWeapon::SetCritical(float fCritical)
{
	m_fCritical = fCritical;
}

bool CItemWeapon::Init()
{
	return true;
}

void CItemWeapon::Render()
{
	cout << "이름: " << m_strName << "\t종류: " << m_tInfo.strTypeName << endl;
	cout << "공격력: " << m_iAttackMin << " ~ " << m_iAttackMax << "\t치명타율: " << m_fCritical << endl;
	cout << "구매가: " << m_tInfo.iPrice << "\t판매가: " << m_tInfo.iSell << endl;
	cout << "아이템 설명: " << m_tInfo.strDesc << endl;
}

CItemWeapon* CItemWeapon::Clone()
{
	return new CItemWeapon(*this);
}

void CItemWeapon::Save(CFileStream* pFile)
{
	CItem::Save(pFile);

	pFile->Write(&m_iAttackMin, 4);
	pFile->Write(&m_iAttackMax, 4);
	pFile->Write(&m_fCritical, 4);
}

void CItemWeapon::Load(CFileStream* pFile)
{
	CItem::Load(pFile);

	pFile->Read(&m_iAttackMin, 4);
	pFile->Read(&m_iAttackMax, 4);
	pFile->Read(&m_fCritical, 4);
}
