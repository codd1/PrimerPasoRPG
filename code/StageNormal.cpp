#include "StageNormal.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"

CStageNormal::CStageNormal()
{
}

CStageNormal::~CStageNormal()
{
}

bool CStageNormal::Init()
{
	return true;
}

void CStageNormal::Run()
{
	// �÷��̾ ���´�. (�÷��̾�� �ϳ��̹Ƿ� ������ �ʿ�x)
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	// ���͸� �����Ѵ�.
	CMonster* pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject("Troll");

	while (true) {
		system("cls");
		OutputStageName("Normal");

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

				if (pPlayer->CheckLevelUp()) {

					pPlayer->LevelUp();

					// ������ ���� �ɷ�ġ ���
					pPlayer->AddLevelUpStatus(GET_SINGLE(CCore)->GetLevelUpInfo(pPlayer->GetJob()));

					cout << "Level Up!" << endl;
				}

				// ���͸� �����ϰ� �ٽ� �����ؼ� �������ش�. (���� ����)
				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject("Troll");

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
