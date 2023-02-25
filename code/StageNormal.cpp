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
	// 플레이어를 얻어온다. (플레이어는 하나이므로 복사할 필요x)
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	// 몬스터를 복사한다.
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
				//cout << pPlayer->GetName() << " 이(가) " << pPlayer << "";
				pPlayer->DropGold();
				pPlayer->FullHPMP();

				break;
			case BF_MONSTER_DIE:
				pPlayer->AddExp(pMonster->GetCharacterInfo().iExp);
				cout << pPlayer->GetName() << " 이(가) " << pMonster->GetCharacterInfo().iExp << " 경험치를 획득했습니다." << endl;

				pPlayer->AddGold(pMonster->GetDropGold());
				cout << pPlayer->GetName() << " 이(가) " << pMonster->GetDropGold() << " Gold를 획득했습니다." << endl;

				if (pPlayer->CheckLevelUp()) {

					pPlayer->LevelUp();

					// 직업에 맞춰 능력치 상승
					pPlayer->AddLevelUpStatus(GET_SINGLE(CCore)->GetLevelUpInfo(pPlayer->GetJob()));

					cout << "Level Up!" << endl;
				}

				// 몬스터를 삭제하고 다시 복사해서 생성해준다. (몬스터 리젠)
				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject("Troll");

				break;
			}
			break;
		case MENU_BACK:
			// 생성한 몬스터를 더 이상 사용하지 않으므로 뒤로가기 하기 전에 지워준다. 매번 맵에 들어올 때마다 몬스터를 새로 생성해주고있다.
			SAFE_DELETE(pMonster);
			return;
		}

		system("pause");
	}
}
