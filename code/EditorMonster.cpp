#include "EditorMonster.h"
#include "Monster.h"
#include "FileStream.h"

DEFINITION_SINGLE(CEditorMonster)

enum EDIT_MONSTER_MENU {
	EMM_NONE,
	EMM_INSERT,
	EMM_MODIFY,
	EMM_DELETE,
	EMM_OUTPUT,
	EMM_SAVE,
	EMM_LOAD,
	EMM_BACK
};

CEditorMonster::CEditorMonster()
{
}

CEditorMonster::~CEditorMonster()
{
	Safe_Delete_VecList(m_vecMonster);
}

bool CEditorMonster::Init()
{
	return true;
}

void CEditorMonster::Run()
{
	while (true) {
		switch (OutputMenu()) {
		case EMM_INSERT:
			InsertMonster();
			break;
		case EMM_MODIFY:
			break;
		case EMM_DELETE:
			break;
		case EMM_OUTPUT:
			OutputMonsterList();
			break;
		case EMM_SAVE:
			SaveMonster();
			break;
		case EMM_LOAD:
			LoadMonster();
			break;
		case EMM_BACK:
			return;
		}
	}
}

int CEditorMonster::OutputMenu()
{
	system("cls");
	cout << "1. 몬스터 추가" << endl;
	cout << "2. 몬스터 수정" << endl;
	cout << "3. 몬스터 삭제" << endl;
	cout << "4. 몬스터 목록" << endl;
	cout << "5. 저장" << endl;
	cout << "6. 불러오기" << endl;
	cout << "7. 뒤로가기" << endl;
	cout << "메뉴를 선택하세요: ";
	int iMenu = Input<int>();

	if (iMenu <= EMM_NONE || iMenu > EMM_BACK) {
		return EMM_NONE;
	}

	return iMenu;
}

void CEditorMonster::InsertMonster()
{
	CMonster* pMonster = new CMonster;

	if (!pMonster->Init()) {
		SAFE_DELETE(pMonster);
		return;
	}

	system("cls");
	cout << "=================== 몬스터 추가 ===================" << endl;
	cin.ignore(1024, '\n');
	cout << "이름: ";
	char strName[256] = {};
	cin.getline(strName, 255);

	pMonster->SetName(strName);

	int iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp;
	cout << "최소 공격력: ";
	cin >> iAttackMin;
	cout << "최대 공격력: ";
	cin >> iAttackMax;
	cout << "최소 방어력: ";
	cin >> iArmorMin;
	cout << "최대 방어력: ";
	cin >> iArmorMax;
	cout << "체력: ";
	cin >> iHP;
	cout << "마나: ";
	cin >> iMP;
	cout << "레벨: ";
	cin >> iLevel;
	cout << "획득 경험치: ";
	cin >> iExp;

	pMonster->SetCharacterInfo(iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp);

	int iGoldMin, iGoldMax;
	cout << "최소 골드: ";
	cin >> iGoldMin;
	cout << "최대 골드: ";
	cin >> iGoldMax;

	pMonster->SetGold(iGoldMin, iGoldMax);

	// 난이도를 선택한다.
	int iStage = ST_NONE;
	while (iStage <= ST_NONE || iStage >= ST_BACK) {
		cout << endl;
		cout << "1. Easy" << endl;
		cout << "2. Normal" << endl;
		cout << "3. Hard" << endl;
		cout << "난이도를 선택하세요: ";
		iStage = Input<int>();
	}
	pMonster->SetStageType((STAGE_TYPE)iStage);

	m_vecMonster.push_back(pMonster);
}

void CEditorMonster::OutputMonsterList()
{
	system("cls");
	cout << "=================== 몬스터 목록 ===================" << endl;

	for (size_t i = 0; i < m_vecMonster.size(); i++) {
		cout << i + 1 << ". ";
		m_vecMonster[i]->Render();
		cout << endl;
	}

	system("pause");
}

void CEditorMonster::SaveMonster()
{
	system("cls");
	cout << "=================== 파일 저장 ===================" << endl;

	CFileStream file("MonsterList.mtl", "wb");

	// 몬스터 수를 저장한다.
	// size_t: unsigned int를 typedef 해놓은 것
	size_t iMonsterCount = m_vecMonster.size();

	file.Write(&iMonsterCount, 4);

	for (size_t i = 0; i < iMonsterCount; i++) {
		m_vecMonster[i]->Save(&file);
	}

	cout << "파일 저장 완료" << endl;
	system("pause");
}

void CEditorMonster::LoadMonster()
{
	system("cls");
	cout << "=================== 파일 불러오기 ===================" << endl;

	// 기존 몬스터 정보를 읽어오기 전에 전의 vector list를 지운다.
	Safe_Delete_VecList(m_vecMonster);

	CFileStream file("MonsterList.mtl", "rb");

	// 몬스터 수를 읽어온다.
	// size_t: unsigned int를 typedef 해놓은 것
	size_t iMonsterCount = 0;

	file.Read(&iMonsterCount, 4);

	for (size_t i = 0; i < iMonsterCount; i++) {

		CMonster* pMonster = new CMonster;

		if (!pMonster->Init()) {
			SAFE_DELETE(pMonster);
			return;
		}
		pMonster->Load(&file);

		m_vecMonster.push_back(pMonster);
	}

	cout << "파일 불러오기 완료" << endl;
	system("pause");
}
