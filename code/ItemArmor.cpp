#include "ItemArmor.h"

CItemArmor::CItemArmor()
{
}

CItemArmor::CItemArmor(const CItemArmor& item) :
	CItem(item)
{
	m_iArmorMin = item.m_iArmorMin;
	m_iArmorMax = item.m_iArmorMax;
}

CItemArmor::~CItemArmor()
{
}

void CItemArmor::SetArmorInfo(int iArmorMin, int iArmorMax)
{
	m_iArmorMax = iArmorMax;
	m_iArmorMin = iArmorMin;
}

bool CItemArmor::Init()
{
	return true;
}

void CItemArmor::Render()
{
	cout << "�̸�: " << m_strName << "\t����: " << m_tInfo.strTypeName << endl;
	cout << "����: " << m_iArmorMin << " ~ " << m_iArmorMax << endl;
	cout << "���Ű�: " << m_tInfo.iPrice << "\t�ǸŰ�: " << m_tInfo.iSell << endl;
	cout << "������ ����: " << m_tInfo.strDesc << endl;
}

CItemArmor* CItemArmor::Clone()
{
	return new CItemArmor(*this);
}
