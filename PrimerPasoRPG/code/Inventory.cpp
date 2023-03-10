#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

DEFINITION_SINGLE(CInventory)

enum INVENTORY_TAB_MENU {
	ITM_NONE,
	ITM_EQUIP,
	ITEM_CONSUMABLE,	// �Ҹ�ǰ
	ITM_BACK
};

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
	// player�� ���´�.
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	while (true) {
		system("cls");
		cout << "==================== Inventory ====================" << endl;
		pPlayer->Render();		// �÷��̾� ���� ���
		cout << endl;

		switch (OutputTab()) {
		case ITM_EQUIP:
			EquipItemTab();
			break;
		case ITEM_CONSUMABLE:
			ConsumableItemTab();
			break;
		case ITM_BACK:
			return;
		}

		for (size_t i = 0; i < m_vecItem.size(); i++) {
			cout << i + 1 << ". ";
			m_vecItem[i]->Render();
			cout << endl;
		}
		cout << m_vecItem.size() + 1 << ". �ڷΰ���" << endl;
		cout << "����(���)�� �������� �����ϼ���: ";
		int iItem = Input<int>();

		if (iItem<1 || iItem>m_vecItem.size() + 1) {
			continue;
		}
		else if (iItem == m_vecItem.size() + 1) {
			return;
		}


	}
}

int CInventory::OutputTab()
{
	system("cls");
	cout << "1. ���" << endl;
	cout << "2. �Ҹ�ǰ" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "�κ��丮 ���� �����ϼ���: ";
	int iMenu = Input<int>();

	if (iMenu <= ITM_NONE || iMenu > ITM_BACK) {
		return ITM_NONE;
	}

	return iMenu;
}

void CInventory::EquipItemTab()
{
}

void CInventory::ConsumableItemTab()
{
}
