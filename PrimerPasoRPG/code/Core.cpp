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

	// ������Ʈ ������ �ʱ�ȭ
	if (!GET_SINGLE(CObjectManager)->Init()) {
		return false;
	}

	// Stage�� �ʱ�ȭ�Ѵ�.
	if (!GET_SINGLE(CStageManager)->Init()) {
		return false;
	}

	// ���� ������ �ʱ�ȭ
	if (!GET_SINGLE(CStoreManager)->Init()) {
		return false;
	}

	// �κ��丮�� �ʱ�ȭ�Ѵ�.
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
			cout << "======================= Player ���� =======================" << endl;
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
	cout << "1. ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. �κ��丮" << endl;
	cout << "4. ĳ��������" << endl;
	cout << "5. ��������" << endl;
	cout << "6. ����" << endl;
	cout << "�޴��� �����ϼ���: ";
	int iMenu = Input<int>();

	if (iMenu <= MM_NONE || iMenu > MM_EXIT) {
		return MM_NONE;
	}

	return iMenu;
}

void CCore::SetLevelUpInfo()
{
	// �������� �ʿ��� ���� ��� ����ü�� ������ش�.
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
		cout << "=============== ���� ���� ===============" << endl;
		cout << "(1) �÷��̾� ���� ����" << endl;
		cout << "(2) ����" << endl;
		cout << "(3) ����" << endl;
		cout << "(4) �κ��丮" << endl;
		cout << "(5) ������ ����" << endl;
		cout << "(6) �ڷΰ���" << endl;
		cout << "�޴��� �����ϼ���: ";
		iMenu = Input<int>();
	}

	switch (iMenu) {
	case GIM_PLAYERJOB:
		system("cls");
		cout << "(1) �÷��̾� ���� ����" << endl << endl;
		cout << "1. ���" << endl << "- ���ݷ��� ���� ���, ������ ���� �����Դϴ�." << endl;
		cout << "2. �ü�" << endl << "- ���ݷ� ����, ������ ������ ���� ����� �����Դϴ�." << endl;
		cout << "3. ������" << endl << "- ���ݷ��� ���� ���, ������ ���� �����Դϴ�." << endl << endl;
		system("pause");
		break;
	case GIM_BATTLE:
		system("cls");
		cout << "(2) ����" << endl << endl;
		cout << "- ���� �޴��� '1. ��' �޴����� ������ ������ ���̵��� ������ �� �ֽ��ϴ�." << endl;
		cout << "- ����, ����, ����� �ܰ谡 ������ ���򿡴� 1���� ����, ���뿡�� 5���� ����, ����򿡴� 10���� ���Ͱ� �ֽ��ϴ�." << endl;
		cout << "- ���͸� ��� ����ġ�� ȹ���� �� �ְ�, ����ġ�� ��� ������ ���� ��� ������ ���� �÷��̾��� �⺻ ������ �����ϴ�." << endl;
		cout << "- ���͸� ��� ��带 ȹ���� �� �ְ� ��带 ��� �������� �������� ������ �� �ֽ��ϴ�." << endl << endl;
		system("pause");
		break;
	case GIM_STORE:
		system("cls");
		cout << "(3) ����" << endl << endl;
		cout << "- ���� �޴��� '2. ����' �޴����� ����, �� �������� ������ �� �ֽ��ϴ�." << endl;
		cout << "- ���⸦ ������ ���� �� ���͸� �����ϸ� ���� ġ��Ÿ���� ���� ���Ϳ��� ġ��Ÿ�� ���� �� �ֽ��ϴ�. (ġ��Ÿ�� �⺻ ������ 2���� �������� �����ϴ�.)" << endl;
		cout << "- ���⸦ ������ �����ϸ� ���ݷ�, ġ��Ÿ�� ������ �ö󰩴ϴ�." << endl;
		cout << "- ���� ������ �����ϸ� ���� ������ �ö󰩴ϴ�." << endl;
		cout << "- ��带 ��� ����, ���� ������ �� ���� ���̵��� ���͸� ��ƺ�����!" << endl << endl;
		system("pause");
		break;
	case GIM_INVENTORY:
		system("cls");
		cout << "(4) �κ��丮" << endl << endl;
		cout << "- �������� ������ ������ �� �ֽ��ϴ�." << endl;
		cout << "- ���� ������ �������� �����ϰ� �� ���, ���� �������� ���� �����ǰ� ���� ������ �������� ������ ����˴ϴ�." << endl;
		cout << "- �������� ���� 1��, �� 1���� ���� �����մϴ�." << endl << endl;
		system("pause");
		break;
	case GIM_DEVELOPER:
		system("cls");
		cout << "(5) ������ ����" << endl << endl;
		cout << "- ������/��ȹ��: ȫä��" << endl;
		cout << "- ���� ����: ������ C++ Let's Make Games" << endl << endl;
		system("pause");
		break;
	case GIM_BACK:
		return;
	}
}

void CCore::CheckExit()
{
	cout << endl << "�����Ͻðڽ��ϱ�?(Y/N): " << endl;
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
