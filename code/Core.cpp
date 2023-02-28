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
	MM_INFORMATION,
	MM_EXIT
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
		case MM_INFORMATION:
			system("cls");
			cout << "======================= Player ���� =======================" << endl;
			GET_SINGLE(CObjectManager)->FindObject("Player")->Render();
			cout << endl;
			system("pause");
			break;
		case MM_EXIT:
			exit(0);
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
	cout << "5. ����" << endl;
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
	m_tLevelUpInfo[JOB_KNIGHT - 1] = CreateLevelUpInfo(5, 10, 15, 20, 100, 10);
	m_tLevelUpInfo[JOB_ARCHER - 1] = CreateLevelUpInfo(10, 15, 10, 15, 80, 30);
	m_tLevelUpInfo[JOB_WIZARD - 1] = CreateLevelUpInfo(15, 20, 5, 10, 50, 50);
}

LEVELUPINFO CCore::CreateLevelUpInfo(int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, int iHP, int iMP)
{
	LEVELUPINFO tInfo = {};

	tInfo.iAttackMin = iAttackMin;
	tInfo.iAttackMax = iAttackMax;
	tInfo.iArmorMin = iArmorMin;
	tInfo.iArmorMax = iArmorMax;
	tInfo.iHP = iHP;
	tInfo.iMP = iMP;

	return tInfo;
}
