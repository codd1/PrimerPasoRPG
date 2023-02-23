#include "StoreArmor.h"
#include "ItemArmor.h"
#include "Player.h"
#include "ObjectManager.h"

CStoreArmor::CStoreArmor()
{
}

CStoreArmor::~CStoreArmor()
{
}

bool CStoreArmor::Init()
{
    // ÆÇ¸Å ¸ñ·ÏÀ» ¸¸µé¾îÁØ´Ù.
    CItemArmor* pItem = (CItemArmor*)CreateItem("°¡Á× ¿Ê", IT_ARMOR, 1000, 500, "°¡Á×À¸·Î ¸¸µé¾îÁø ¿Ê");
    pItem->SetArmorInfo(5, 10);

    pItem = (CItemArmor*)CreateItem("Ã¶ °©¿Ê", IT_ARMOR, 3000, 1500, "Ã¶·Î ¸¸µé¾îÁø °©¿Ê");
    pItem->SetArmorInfo(20, 30);

    pItem = (CItemArmor*)CreateItem("ÅÂ¾ç ºÒ²É ¸ÁÅä", IT_ARMOR, 25000, 12500, "ÅÂºÒ¸Á");
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
        cout << m_vecItem.size() + 1 << ". µÚ·Î°¡±â" << endl;
        cout << "º¸À¯ ±Ý¾×: " << pPlayer->GetGold() << " Gold" << endl;
        int iInput = Input<int>();

        if (iInput<1 || iInput>m_vecItem.size() + 1) {
            continue;
        }
        else if (iInput == m_vecItem.size() + 1) {
            return;
        }
    }
}
