#include "StoreArmor.h"
#include "ItemArmor.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Inventory.h"

CStoreArmor::CStoreArmor()
{
}

CStoreArmor::~CStoreArmor()
{
}

bool CStoreArmor::Init()
{
    // 판매 목록을 만들어준다.
    CItemArmor* pItem = (CItemArmor*)CreateItem("가죽 옷", IT_ARMOR, 1000, 500, "가죽으로 만들어진 옷");
    pItem->SetArmorInfo(5, 10);

    pItem = (CItemArmor*)CreateItem("철 갑옷", IT_ARMOR, 3000, 1500, "철로 만들어진 갑옷");
    pItem->SetArmorInfo(20, 30);

    pItem = (CItemArmor*)CreateItem("태양 불꽃 망토", IT_ARMOR, 25000, 12500, "태불망");
    pItem->SetArmorInfo(70, 100);

    return true;
}

void CStoreArmor::Run()
{
    CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");
    
    while (true) {
        system("cls");
        OutputTag("Armor Store");
        OutputItemList();
        cout << m_vecItem.size() + 1 << ". 뒤로가기" << endl;
        cout << "보유 금액: " << pPlayer->GetGold() << " Gold" << endl;
        int iInput = Input<int>();

        if (iInput<1 || iInput>m_vecItem.size() + 1) {
            continue;
        }
        else if (iInput == m_vecItem.size() + 1) {
            return;
        }

        // 아이템을 구매한다. 가방이 꽉 찼을 경우 구매 불가
        if (GET_SINGLE(CInventory)->InvenFull()) {
            cout << "인벤토리에 빈 공간이 없습니다." << endl;
            system("pause");
            continue;
        }
        // 돈이 부족할 경우를 체크한다.
        else if (pPlayer->GetGold() < m_vecItem[iInput - 1]->GetItemInfo().iPrice) {
            cout << "소지금이 부족합니다." << endl;
            system("pause");
            continue;
        }

        CItem* pItem = m_vecItem[iInput - 1]->Clone();

        GET_SINGLE(CInventory)->Additem(pItem);

        // 구매 시 아이템 가격만큼 차감 (AddGold 함수를 이용해 -값을 넣어줌)
        pPlayer->AddGold(-pItem->GetItemInfo().iPrice);
    }	
}
