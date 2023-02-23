#include "ItemWeapon.h"

CItemWeapon::CItemWeapon()
{
}

CItemWeapon::CItemWeapon(const CItemWeapon& item) :
	CItem(item)
{
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
