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
	// 플레이어를 얻어온다. (플레이어는 하나이므로 복사할 필요x)
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	// 몬스터를 복사한다.
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
				//cout << pPlayer->GetName() << " 이(가) " << pPlayer << "";
				pPlayer->DropGold();
				pPlayer->FullHPMP();

				break;
			case BF_MONSTER_DIE:
				pPlayer->AddExp(pMonster->GetCharacterInfo().iExp);
				cout << pPlayer->GetName() << " 이(가) " << pMonster->GetCharacterInfo().iExp << " 경험치를 획득했습니다." << endl;
				
				pPlayer->AddGold(pMonster->GetDropGold());
				cout << pPlayer->GetName() << " 이(가) " << pMonster->GetDropGold() << " Gold를 획득했습니다." << endl;

				// 레벨업 조건을 만족하면 true 반환 후 레벨업
				if (pPlayer->CheckLevelUp()) {

				}

				// 몬스터를 삭제하고 다시 복사해서 생성해준다. (몬스터 리젠)
				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject("Goblin");

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
