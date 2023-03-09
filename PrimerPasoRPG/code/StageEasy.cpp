#include "StageEasy.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"

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
	CMonster* pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_EASY);

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
				pPlayer->DropGold();
				pPlayer->FullHPMP();

				break;
			case BF_MONSTER_DIE:
				cout << endl << "[�ý���] " << pPlayer->GetName() << " ��(��) " << pMonster->GetName() << "�� óġ�߽��ϴ�." << endl << endl;
				pPlayer->AddExp(pMonster->GetCharacterInfo().iExp);
				cout << "[�ý���] " << pMonster->GetCharacterInfo().iExp << " ����ġ ȹ��" << endl;

				pPlayer->AddGold(pMonster->GetDropGold());
				cout << "[�ý���] " << pMonster->GetDropGold() << " Gold ȹ��" << endl << endl;

				// ������ ������ �����ϸ� true ��ȯ �� ������
				if (pPlayer->CheckLevelUp()) {

					pPlayer->LevelUp();

					// ������ ���� �ɷ�ġ ���
					pPlayer->AddLevelUpStatus(GET_SINGLE(CCore)->GetLevelUpInfo(pPlayer->GetJob()));

					cout << "[�ý���] Level Up!" << endl << endl;
				}

				// ���͸� �����ϰ� �ٽ� �����ؼ� �������ش�. (���� ����)
				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_EASY);

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
