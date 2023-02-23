#include "StageEasy.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"

CStageEasy::CStageEasy()
{
}

CStageEasy::~CStageEasy()
{
}

bool CStageEasy::Init()
{
	return true;
}

void CStageEasy::Run()
{
	// �÷��̾ ���´�. (�÷��̾�� �ϳ��̹Ƿ� ������ �ʿ�x)
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	// ���͸� �����Ѵ�.
	CMonster* pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject("Goblin");

	while (true) {
		system("cls");
		OutputStageName("Easy");

		pPlayer->Render();
		cout << endl;

		pMonster->Render();
		cout << endl;

		switch (OutputMenu()) {
		case MENU_ATTACK:
			switch (BattleAttack(pPlayer, pMonster)) {
			case BF_PLAYER_DIE:
				pPlayer->DropExp();
				//cout << pPlayer->GetName() << " ��(��) " << pPlayer << "";
				pPlayer->DropGold();
				pPlayer->FullHPMP();

				break;
			case BF_MONSTER_DIE:
				pPlayer->AddExp(pMonster->GetCharacterInfo().iExp);
				cout << pPlayer->GetName() << " ��(��) " << pMonster->GetCharacterInfo().iExp << " ����ġ�� ȹ���߽��ϴ�." << endl;
				
				pPlayer->AddGold(pMonster->GetDropGold());
				cout << pPlayer->GetName() << " ��(��) " << pMonster->GetDropGold() << " Gold�� ȹ���߽��ϴ�." << endl;

				// ������ ������ �����ϸ� true ��ȯ �� ������
				if (pPlayer->CheckLevelUp()) {

				}

				// ���͸� �����ϰ� �ٽ� �����ؼ� �������ش�. (���� ����)
				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject("Goblin");

				break;
			}
			break;
		case MENU_BACK:
			// ������ ���͸� �� �̻� ������� �����Ƿ� �ڷΰ��� �ϱ� ���� �����ش�. �Ź� �ʿ� ���� ������ ���͸� ���� �������ְ��ִ�.
			SAFE_DELETE(pMonster);
			return;
		}

		system("pause");
	}

}
