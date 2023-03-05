#include "ItemArmor.h"
#include "FileStream.h"

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

void CItemArmor::SetArmorMin(int iArmorMin)
{
	m_iArmorMin = iArmorMin;
}

void CItemArmor::SetArmorMax(int iArmorMax)
{
	m_iArmorMax = iArmorMax;
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

void CItemArmor::Save(CFileStream* pFile)
{
	CItem::Save(pFile);

	pFile->Write(&m_iArmorMin, 4);
	pFile->Write(&m_iArmorMax, 4);
}

void CItemArmor::Load(CFileStream* pFile)
{
	CItem::Load(pFile);

	pFile->Read(&m_iArmorMin, 4);
	pFile->Read(&m_iArmorMax, 4);
}
