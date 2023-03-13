#include "ItemPosion.h"
#include "FileStream.h"

CItemPosion::CItemPosion()
	//m_iNumPosion(0)
{
}

CItemPosion::CItemPosion(const CItemPosion& item) :
	CItem(item)
{
	m_iRecoveryValue = item.m_iRecoveryValue;
}

CItemPosion::~CItemPosion()
{
}

void CItemPosion::SetPosion(int iRecoveryValue)
{
	m_iRecoveryValue = iRecoveryValue;
}

//void CItemPosion::SetNumPosion(int iNumPosion)
//{
//	m_iNumPosion = iNumPosion;
//}

bool CItemPosion::Init()
{
	return true;
}

void CItemPosion::Render()
{
	cout << "�̸�: " << m_strName << "\t����: " << m_tInfo.strTypeName << endl;
	cout << "ȸ����: " << m_iRecoveryValue << endl;
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

	pFile->Write(&m_iRecoveryValue, 4);
}

void CItemPosion::Load(CFileStream* pFile)
{
	CItem::Load(pFile);

	pFile->Read(&m_iRecoveryValue, 4);
}
