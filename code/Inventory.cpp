#include "Inventory.h"
#include "Item.h"

DEFINITION_SINGLE(CInventory)

CInventory::CInventory():
	m_iInvenMax(10)		// 기본 10개
{
}

CInventory::~CInventory()
{
	Safe_Delete_VecList(m_vecItem);
}

bool CInventory::init()
{
	return true;
}

void CInventory::Additem(CItem* pItem)
{
	// 인벤토리가 꽉찰 경우 아이템 추가 불가
	if (m_iInvenMax == m_vecItem.size()) {
		return;
	}

	m_vecItem.push_back(pItem);
}

void CInventory::Run()
{
	for (size_t i = 0; i < m_vecItem.size(); i++) {
		cout << i + 1 << ". ";
		m_vecItem[i]->Render();
		cout << endl;
	}

	system("pause");
}
