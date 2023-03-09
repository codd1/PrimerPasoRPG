#include "StorePosion.h"
#include "ItemPosion.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "FileStream.h"

CStorePosion::CStorePosion()
{
}

CStorePosion::~CStorePosion()
{
}

bool CStorePosion::Init()
{
    return true;
}

void CStorePosion::Run()
{
    CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

    while (true) {
        system("cls");
        OutputTag("Posion Store");
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
