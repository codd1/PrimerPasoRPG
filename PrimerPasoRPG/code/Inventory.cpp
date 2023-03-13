#include "Inventory.h"
#include "Item.h"
#include "ItemPosion.h"
#include "Player.h"
#include "ObjectManager.h"

DEFINITION_SINGLE(CInventory)

//enum INVENTORY_TAB_MENU {
//	ITM_NONE,
//	ITM_EQUIP,
//	ITEM_CONSUMABLE,	// �Ҹ�ǰ
//	ITM_BACK
//};

CInventory::CInventory() :
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
		cout << "==================== Player Information ====================" << endl;
		pPlayer->Render();		// �÷��̾� ���� ���
		cout << endl << endl;

		cout << "==================== Inventory ====================" << endl;
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
	// iItem�� 1������ �����ϱ� ������ 1�� ������Ѵ�. (�ε���)
	CItem* pEquip = pPlayer->Equip(m_vecItem[iItem - 1]);

	if (pEquip) {
		// ���� �ϰ��ִ� �������� ���� ���,
		// �޾ƿͼ� ������ �������� �����ϰ� �ִ� �����۰� ��ü���ش�.
		m_vecItem[iItem - 1] = pEquip;
	}
	else {
		// ���� �ϰ��ִ� �������� ���� ��� �ش� ������ ĭ�� �����ش�.
		// begin + �ε����� ���༭ ������ �������� iterator�� �����ش�.
		vector<CItem*>::iterator iter = m_vecItem.begin() + (iItem - 1);

		// iter�� ����鼭 �ڵ����� �� ĭ�� ����ش�.
		m_vecItem.erase(iter);
	}
}

void CInventory::HPPosionItem(CPlayer* pPlayer, int iItem)
{
	CItemPosion* pPosion = (CItemPosion*)m_vecItem[iItem - 1]->Clone();
	int iRecoveryValue = pPosion->GetRecoveryValue();		// ȸ����ġ

	int iSetHP = pPlayer->GetCharacterInfo().iHP + iRecoveryValue;

	// �ִ�HP�� �ʰ��� ��� �ִ�HP������ ȸ��
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
	int iRecoveryValue = pPosion->GetRecoveryValue();		// ȸ����ġ
	
	int iSetMP = pPlayer->GetCharacterInfo().iMP + iRecoveryValue;
	// �ִ�MP�� �ʰ��� ��� �ִ�MP������ ȸ��
	if (iSetMP > pPlayer->GetCharacterInfo().iMPMax) {
		pPlayer->SetMP(pPlayer->GetCharacterInfo().iMPMax);
	}
	else {
		pPlayer->SetMP(iSetMP);
	}

	vector<CItem*>::iterator iter = m_vecItem.begin() + (iItem - 1);
	m_vecItem.erase(iter);
}
