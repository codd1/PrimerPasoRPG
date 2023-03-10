#include "ItemPosion.h"
#include "FileStream.h"

CItemPosion::CItemPosion() :
	m_iNumPosion(0)
{
}

CItemPosion::CItemPosion(const CItemPosion& item) :
	CItem(item)
{
	m_iPosion = item.m_iPosion;
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
	cout << "�̸�: " << m_strName << "\t����: " << m_tInfo.strTypeName << "\tX" << m_iNumPosion << endl;
	cout << "ȸ����: " << m_iPosion << endl;
	cout << "���Ű�: " << m_tInfo.iPrice << "\t�ǸŰ�: " << m_tInfo.iSell << endl;
	cout << "������ ����: " << m_tInfo.strDesc << endl;
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
