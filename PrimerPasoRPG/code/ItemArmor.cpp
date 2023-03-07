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
	cout << "�̸�: " << m_strName << "\t����: " << m_tInfo.strTypeName << endl;
	cout << "����: " << m_iArmor << endl;
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

	pFile->Write(&m_iArmor, 4);
}

void CItemArmor::Load(CFileStream* pFile)
{
	CItem::Load(pFile);

	pFile->Read(&m_iArmor, 4);
}
