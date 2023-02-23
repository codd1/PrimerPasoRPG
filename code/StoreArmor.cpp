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
    // �Ǹ� ����� ������ش�.
    CItemArmor* pItem = (CItemArmor*)CreateItem("���� ��", IT_ARMOR, 1000, 500, "�������� ������� ��");
    pItem->SetArmorInfo(5, 10);

    pItem = (CItemArmor*)CreateItem("ö ����", IT_ARMOR, 3000, 1500, "ö�� ������� ����");
    pItem->SetArmorInfo(20, 30);

    pItem = (CItemArmor*)CreateItem("�¾� �Ҳ� ����", IT_ARMOR, 25000, 12500, "�ºҸ�");
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
        cout << m_vecItem.size() + 1 << ". �ڷΰ���" << endl;
        cout << "���� �ݾ�: " << pPlayer->GetGold() << " Gold" << endl;
        int iInput = Input<int>();

        if (iInput<1 || iInput>m_vecItem.size() + 1) {
            continue;
        }
        else if (iInput == m_vecItem.size() + 1) {
            return;
        }
    }
}
