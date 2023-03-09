#include "Core.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "StoreManager.h"
#include "Inventory.h"
#include "Object.h"

DEFINITION_SINGLE(CCore)

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_PLAYERINFO,
	MM_GAMEINFO,
	MM_EXIT
};

enum GAME_INFO_MENU {
	GIM_NONE,
	GIM_PLAYERJOB,
	GIM_BATTLE,
	GIM_STORE,
	GIM_INVENTORY,
	GIM_DEVELOPER,
	GIM_BACK
};

CCore::CCore() {

}

CCore::~CCore() {
	DESTROY_SINGLE(CObjectManager);
	DESTROY_SINGLE(CStageManager);
	DESTROY_SINGLE(CStoreManager);
	DESTROY_SINGLE(CInventory);
}

LEVELUPINFO CCore::GetLevelUpInfo(JOB eJob)
{
	return m_tLevelUpInfo[eJob - 1];
}

bool CCore::Init()
{
	SetLevelUpInfo();

	// 오브젝트 관리자 초기화
	if (!GET_SINGLE(CObjectManager)->Init()) {
		return false;
	}

	// Stage를 초기화한다.
	if (!GET_SINGLE(CStageManager)->Init()) {
		return false;
	}

	// 상점 관리자 초기화
	if (!GET_SINGLE(CStoreManager)->Init()) {
		return false;
	}

	// 인벤토리를 초기화한다.
	if (!GET_SINGLE(CInventory)->init()) {
		return false;
	}

	return true;
}

void CCore::Run()
{
	while (true) {
		switch (OutputMenu()) {
		case MM_MAP:
			GET_SINGLE(CStageManager)->Run();
			break;
		case MM_STORE:
			GET_SINGLE(CStoreManager)->Run();
			break;
		case MM_INVENTORY:
			GET_SINGLE(CInventory)->Run();
			break;
		case MM_PLAYERINFO:
			system("cls");
			cout << "======================= Player 정보 =======================" << endl;
			GET_SINGLE(CObjectManager)->FindObject("Player")->Render();
			cout << endl;
			system("pause");
			break;
		case MM_GAMEINFO:
			OutputGameInfo();
			break;
		case MM_EXIT:
			CheckExit();
			break;
		}
	}
}

int CCore::OutputMenu()
{
	system("cls");
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 인벤토리" << endl;
	cout << "4. 캐릭터정보" << endl;
	cout << "5. 게임정보" << endl;
	cout << "6. 종료" << endl;
	cout << "메뉴를 선택하세요: ";
	int iMenu = Input<int>();

	if (iMenu <= MM_NONE || iMenu > MM_EXIT) {
		return MM_NONE;
	}

	return iMenu;
}

void CCore::SetLevelUpInfo()
{
	// 레벨업에 필요한 정보 상승 구조체를 만들어준다.
	m_tLevelUpInfo[JOB_KNIGHT - 1] = CreateLevelUpInfo(5, 10, 15, 100, 10);
	m_tLevelUpInfo[JOB_ARCHER - 1] = CreateLevelUpInfo(10, 15, 10, 80, 20);
	m_tLevelUpInfo[JOB_WIZARD - 1] = CreateLevelUpInfo(15, 20, 5, 50, 30);
}

LEVELUPINFO CCore::CreateLevelUpInfo(int iAttackMin, int iAttackMax, int iArmor, int iHP, int iMP)
{
	LEVELUPINFO tInfo = {};

	tInfo.iAttackMin = iAttackMin;
	tInfo.iAttackMax = iAttackMax;
	tInfo.iArmor = iArmor;
	tInfo.iHP = iHP;
	tInfo.iMP = iMP;

	return tInfo;
}

void CCore::OutputGameInfo()
{
	system("cls");

	int iMenu = 0;

	while (iMenu <= GIM_NONE || iMenu > GIM_BACK) {
		cout << "=============== 게임 정보 ===============" << endl;
		cout << "(1) 플레이어 직업 정보" << endl;
		cout << "(2) 전투" << endl;
		cout << "(3) 상점" << endl;
		cout << "(4) 인벤토리" << endl;
		cout << "(5) 개발자 정보" << endl;
		cout << "(6) 뒤로가기" << endl;
		cout << "메뉴를 선택하세요: ";
		iMenu = Input<int>();
	}

	switch (iMenu) {
	case GIM_PLAYERJOB:
		system("cls");
		cout << "(1) 플레이어 직업 정보" << endl << endl;
		cout << "1. 기사" << endl << "- 공격력이 낮은 대신, 방어력이 높은 직업입니다." << endl;
		cout << "2. 궁수" << endl << "- 공격력 보통, 방어력이 보통인 아주 평범한 직업입니다." << endl;
		cout << "3. 마법사" << endl << "- 공격력이 높은 대신, 방어력이 낮은 직업입니다." << endl << endl;
		system("pause");
		break;
	case GIM_BATTLE:
		system("cls");
		cout << "(2) 전투" << endl << endl;
		cout << "- 메인 메뉴의 '1. 맵' 메뉴에서 공격할 몬스터의 난이도를 선택할 수 있습니다." << endl;
		cout << "- 쉬움, 보통, 어려움 단계가 있으며 쉬움에는 1레벨 몬스터, 보통에는 5레벨 몬스터, 어려움에는 10레벨 몬스터가 있습니다." << endl;
		cout << "- 몬스터를 잡아 경험치를 획득할 수 있고, 경험치를 모아 레벨이 오를 경우 레벨에 따라 플레이어의 기본 스탯이 오릅니다." << endl;
		cout << "- 몬스터를 잡아 골드를 획득할 수 있고 골드를 모아 상점에서 아이템을 구매할 수 있습니다." << endl << endl;
		system("pause");
		break;
	case GIM_STORE:
		system("cls");
		cout << "(3) 상점" << endl << endl;
		cout << "- 메인 메뉴의 '2. 상점' 메뉴에서 무기, 방어구 아이템을 구매할 수 있습니다." << endl;
		cout << "- 무기를 구매해 착용 후 몬스터를 공격하면 무기 치명타율에 따라 몬스터에게 치명타를 입힐 수 있습니다. (치명타는 기본 공격의 2배의 데미지를 입힙니다.)" << endl;
		cout << "- 무기를 구매해 착용하면 공격력, 치명타율 스탯이 올라갑니다." << endl;
		cout << "- 방어구를 구매해 착용하면 방어력 스탯이 올라갑니다." << endl;
		cout << "- 골드를 모아 무기, 방어구를 구매해 더 높은 난이도의 몬스터를 잡아보세요!" << endl << endl;
		system("pause");
		break;
	case GIM_INVENTORY:
		system("cls");
		cout << "(4) 인벤토리" << endl << endl;
		cout << "- 아이템을 구매해 착용할 수 있습니다." << endl;
		cout << "- 같은 종류의 아이템을 착용하게 될 경우, 기존 아이템이 장착 해제되고 새로 장착한 아이템의 스탯이 적용됩니다." << endl;
		cout << "- 아이템은 무기 1개, 방어구 1개만 착용 가능합니다." << endl << endl;
		system("pause");
		break;
	case GIM_DEVELOPER:
		system("cls");
		cout << "(5) 개발자 정보" << endl << endl;
		cout << "- 개발자/기획자: 홍채영" << endl;
		cout << "- 참고 강의: 인프런 C++ Let's Make Games" << endl << endl;
		system("pause");
		break;
	case GIM_BACK:
		return;
	}
}

void CCore::CheckExit()
{
	cout << endl << "종료하시겠습니까?(Y/N): " << endl;
	char iYN = 'n';
	while ((iYN = getchar()) != NULL) {
		if (iYN == 'y' || iYN == 'Y') {
			exit(0);
		}
		else if (iYN == 'n' || iYN == 'N') {
			return;
		}
	}
}
