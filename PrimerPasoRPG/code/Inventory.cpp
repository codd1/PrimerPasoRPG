#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

DEFINITION_SINGLE(CInventory)

enum INVENTORY_TAB_MENU {
	ITM_NONE,
	ITM_EQUIP,
	ITEM_CONSUMABLE,	// 소모품
	ITM_BACK
};

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
	// player를 얻어온다.
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	while (true) {
		system("cls");
		cout << "==================== Inventory ====================" << endl;
		pPlayer->Render();		// 플레이어 정보 출력
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
		cout << m_vecItem.size() + 1 << ". 뒤로가기" << endl;
		cout << "장착(사용)할 아이템을 선택하세요: ";
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
	cout << "1. 장비" << endl;
	cout << "2. 소모품" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "인벤토리 탭을 선택하세요: ";
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
