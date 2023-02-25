#include "Item.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& item):
	CObject(item)
{
	m_tInfo = item.m_tInfo;
}

CItem::~CItem()
{
}

void CItem::SetItemInfo(ITEM_TYPE eType, int iPrice, int iSell, const char* pDesc)
{
	m_tInfo.eType = eType;

	switch (eType) {
	case IT_WEAPON:
		m_tInfo.strTypeName = "무기";
		break;
	case IT_ARMOR:
		m_tInfo.strTypeName = "방어구";
		break;
	}

	m_tInfo.iPrice = iPrice;
	m_tInfo.iSell = iSell;
	m_tInfo.strDesc = pDesc;
}

bool CItem::Init()
{
	return true;
}

void CItem::Render()
{
}