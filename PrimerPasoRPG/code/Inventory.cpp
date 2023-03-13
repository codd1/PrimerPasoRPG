#include "Inventory.h"
#include "Item.h"
#include "ItemPosion.h"
#include "Player.h"
#include "ObjectManager.h"

DEFINITION_SINGLE(CInventory)

//enum INVENTORY_TAB_MENU {
//	ITM_NONE,
//	ITM_EQUIP,
//	ITEM_CONSUMABLE,	// 소모품
//	ITM_BACK
//};

CInventory::CInventory() :
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
		cout << "==================== Player Information ====================" << endl;
		pPlayer->Render();		// 플레이어 정보 출력
		cout << endl << endl;

		cout << "==================== Inventory ====================" << endl;
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

		ITEM_TYPE eType = m_vecItem[iItem - 1]->GetItemInfo().eType;

		switch (eType) {
		case IT_WEAPON:
		case IT_ARMOR:
			EquipItem(pPlayer, iItem);
			break;
		case IT_HP_POSION:
			HPPosionItem(pPlayer, iItem);
			break;
		case IT_MP_POSION:
			MPPosionItem(pPlayer, iItem);
			break;
		}
	}
}

void CInventory::EquipItem(CPlayer* pPlayer, int iItem)
{
	// iItem은 1번부터 선택하기 때문에 1을 빼줘야한다. (인덱스)
	CItem* pEquip = pPlayer->Equip(m_vecItem[iItem - 1]);

	if (pEquip) {
		// 장착 하고있던 아이템이 있을 경우,
		// 받아와서 선택한 아이템을 장착하고 있던 아이템과 교체해준다.
		m_vecItem[iItem - 1] = pEquip;
	}
	else {
		// 장착 하고있던 아이템이 없을 경우 해당 아이템 칸을 지워준다.
		// begin + 인덱스를 해줘서 장착한 아이템의 iterator를 구해준다.
		vector<CItem*>::iterator iter = m_vecItem.begin() + (iItem - 1);

		// iter를 지우면서 자동으로 한 칸씩 당겨준다.
		m_vecItem.erase(iter);
	}
}

void CInventory::HPPosionItem(CPlayer* pPlayer, int iItem)
{
	CItemPosion* pPosion = (CItemPosion*)m_vecItem[iItem - 1]->Clone();
	int iRecoveryValue = pPosion->GetRecoveryValue();		// 회복수치

	int iSetHP = pPlayer->GetCharacterInfo().iHP + iRecoveryValue;

	// 최대HP를 초과할 경우 최대HP까지만 회복
	if (iSetHP > pPlayer->GetCharacterInfo().iHPMax) {
		pPlayer->SetHP(pPlayer->GetCharacterInfo().iHPMax);
	}
	else {
		pPlayer->SetHP(iSetHP);
	}

	vector<CItem*>::iterator iter = m_vecItem.begin() + (iItem - 1);
	m_vecItem.erase(iter);
}

void CInventory::MPPosionItem(CPlayer* pPlayer, int iItem)
{
	CItemPosion* pPosion = (CItemPosion*)m_vecItem[iItem - 1]->Clone();
	int iRecoveryValue = pPosion->GetRecoveryValue();		// 회복수치
	
	int iSetMP = pPlayer->GetCharacterInfo().iMP + iRecoveryValue;
	// 최대MP를 초과할 경우 최대MP까지만 회복
	if (iSetMP > pPlayer->GetCharacterInfo().iMPMax) {
		pPlayer->SetMP(pPlayer->GetCharacterInfo().iMPMax);
	}
	else {
		pPlayer->SetMP(iSetMP);
	}

	vector<CItem*>::iterator iter = m_vecItem.begin() + (iItem - 1);
	m_vecItem.erase(iter);
}
