#include "StoreWeapon.h"
#include "ItemWeapon.h"
#include "Player.h"
#include "ObjectManager.h"

CStoreWeapon::CStoreWeapon()
{
}

CStoreWeapon::~CStoreWeapon()
{
}

bool CStoreWeapon::Init()
{
	// 판매 목록을 만들어준다.
	CItemWeapon* pItem = (CItemWeapon*)CreateItem("목검", IT_WEAPON, 1000, 500, "나무로 만든 검");
	pItem->SetWeaponInfo(5, 10, 10.f);

	pItem = (CItemWeapon*)CreateItem("철검", IT_WEAPON, 3000, 1500, "철로 만든 검");
	pItem->SetWeaponInfo(20, 30, 20.f);

	pItem = (CItemWeapon*)CreateItem("그림자 검", IT_WEAPON, 25000, 12500, "방관 꿀템");
	pItem->SetWeaponInfo(70, 100, 35.f);

	return true;
}

void CStoreWeapon::Run()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	while (true) {
		system("cls");
		OutputTag("Weapon Store");
		OutputItemList();
		cout << m_vecItem.size() + 1 << ". 뒤로가기" << endl << endl;
		cout << "보유 금액: " << pPlayer->GetGold() << " Gold" << endl;
		int iInput = Input<int>();

		if (iInput<1 || iInput>m_vecItem.size() + 1) {
			continue;
		}
		else if (iInput == m_vecItem.size() + 1) {		// 뒤로가기일 경우
			return;
		}

		// 아이템을 구매한다.
	}
}
