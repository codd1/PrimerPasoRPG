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
        cout << m_vecItem.size() + 1 << ". �ڷΰ���" << endl;
        cout << "���� �ݾ�: " << pPlayer->GetGold() << " Gold" << endl;
        int iInput = Input<int>();

        if (iInput<1 || iInput>m_vecItem.size() + 1) {
            continue;
        }
        else if (iInput == m_vecItem.size() + 1) {
            return;
        }

        // �������� �����Ѵ�. ������ �� á�� ��� ���� �Ұ�
        if (GET_SINGLE(CInventory)->InvenFull()) {
            cout << "�κ��丮�� �� ������ �����ϴ�." << endl;
            system("pause");
            continue;
        }
        // ���� ������ ��츦 üũ�Ѵ�.
        else if (pPlayer->GetGold() < m_vecItem[iInput - 1]->GetItemInfo().iPrice) {
            cout << "�������� �����մϴ�." << endl;
            system("pause");
            continue;
        }

        CItem* pItem = m_vecItem[iInput - 1]->Clone();

        GET_SINGLE(CInventory)->Additem(pItem);

        // ���� �� ������ ���ݸ�ŭ ���� (AddGold �Լ��� �̿��� -���� �־���)
        pPlayer->AddGold(-pItem->GetItemInfo().iPrice);
    }
}
