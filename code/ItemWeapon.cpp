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
	cout << "�̸�: " << m_strName << "\t����: " << m_tInfo.strTypeName << endl;
	cout << "���ݷ�: " << m_iAttackMin << " ~ " << m_iAttackMax << "\tġ��Ÿ��: " << m_fCritical << endl;
	cout << "���Ű�: " << m_tInfo.iPrice << "\t�ǸŰ�: " << m_tInfo.iSell << endl;
	cout << "������ ����: " << m_tInfo.strDesc << endl;
}

CItemWeapon* CItemWeapon::Clone()
{
	return new CItemWeapon(*this);
}
