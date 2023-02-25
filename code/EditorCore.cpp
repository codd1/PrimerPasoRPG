#include "EditorCore.h"
#include "EditorMonster.h"

DEFINITION_SINGLE(CEditorCore)

enum EDIT_MENU {
	EM_NONE,
	EM_MONSTER,
	EM_ITEM,
	EM_EXIT
};

CEditorCore::CEditorCore()
{
}

CEditorCore::~CEditorCore()
{
	DESTROY_SINGLE(CEditorMonster);
}

bool CEditorCore::Init()
{
	if (!GET_SINGLE(CEditorMonster)->Init()) {
		return false;
	}
	return true;
}

void CEditorCore::Run()
{
	while (true) {
		switch (OutputMenu()) {
		case EM_MONSTER:
			GET_SINGLE(CEditorMonster)->Run();
			break;
		case EM_ITEM:
			break;
		case EM_EXIT:
			return;
		}

	}
}

int CEditorCore::OutputMenu()
{
	system("cls");
	cout << "1. 몬스터 설정" << endl;
	cout << "2. 아이템 설정" << endl;
	cout << "3. 종료" << endl;
	cout << "메뉴를 선택하세요: ";
	int iMenu = Input<int>();

	if (iMenu <= EM_NONE || iMenu > EM_EXIT) {
		return EM_NONE;
	}

	return iMenu;
}
