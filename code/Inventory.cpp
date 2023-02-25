#include "Inventory.h"
#include "Item.h"

DEFINITION_SINGLE(CInventory)

CInventory::CInventory():
	m_iInvenMax(10)		// �⺻ 10��
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
	// �κ��丮�� ���� ��� ������ �߰� �Ұ�
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
