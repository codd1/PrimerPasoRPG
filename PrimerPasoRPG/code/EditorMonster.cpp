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

enum MODIFY_MONSTER_MENU {
	MMM_NONE,
	MMM_NAME,
	MMM_STAGETYPE,
	MMM_ATTACKMIN,
	MMM_ATTACKMAX,
	MMM_ARMORMIN,
	MMM_ARMORMAX,
	MMM_HP,
	MMM_MP,
	MMM_GOLD,
	MMM_LEVEL,
	MMM_EXP,
	MMM_BACK
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
			ModifyMonster();
			break;
		case EMM_DELETE:
			DeleteMonster();
			break;
		case EMM_OUTPUT:
			system("cls");
			OutputMonsterList();
			system("pause");
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
	float fCritical;
	cout << "최소 공격력: ";
	cin >> iAttackMin;
	cout << "최대 공격력: ";
	cin >> iAttackMax;
	cout << "치명타율: ";
	cin >> fCritical;
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

	pMonster->SetCharacterInfo(iAttackMin, iAttackMax, fCritical, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp);

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

void CEditorMonster::ModifyMonster()
{
	system("cls");
	cout << "=================== 몬스터 목록 ===================" << endl;

	// 몬스터 목록에 몬스터가 없을 경우
	if (m_vecMonster.size() == 0) {
		cout << endl << "수정 가능한 몬스터가 없습니다." << endl;
		system("pause");
		return;
	}

	OutputMonsterList();
	cout << m_vecMonster.size() + 1 << ". 뒤로가기" << endl;

	int iChooseMonster;

	while (true) {
		cout << "수정하려는 몬스터를 선택하세요: ";
		iChooseMonster = Input<int>();

		// 뒤로가기 선택
		if (iChooseMonster == m_vecMonster.size() + 1) {
			return;
		}
		else if (iChooseMonster >= 1 && iChooseMonster <= m_vecMonster.size()) {
			break;
		}
	}

	while (true) {

		cout << endl << endl;
		cout << "1. 이름\t\t2. 난이도" << endl;
		cout << "3. 최소 공격력\t4. 최대 공격력" << endl;
		cout << "5. 최소 방어력\t6. 최대 방어력" << endl;
		cout << "7. HP\t\t8. MP" << endl;
		cout << "9. 처치 시 획득 골드" << endl;
		cout << "10. 레벨\t11. 경험치" << endl;
		cout << "12. 뒤로가기" << endl;
		cout << "수정할 항목을 입력하세요: ";
		// 수정할 항목을 입력 받고, 기존 정보 지운 후 새로운 정보 새로 입력
		int iModifyMenu = Input<int>();

		// 몬스터 정보: iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp; iGoldMin, iGoldMax;
		if (iModifyMenu <= MMM_NONE || iModifyMenu > MMM_BACK) {
			continue;
		}
		int iInput;
		char strName[256] = {};
		int iGoldMin, iGoldMax;

		cout << endl;
		switch (iModifyMenu) {
		case MMM_NAME:
			cout << "이름: ";

			cin.ignore(1024, '\n');
			cin.getline(strName, 255);

			m_vecMonster[iChooseMonster - 1]->SetName(strName);

			break;
		case MMM_STAGETYPE:
			cout << endl;
			cout << "======== 난이도 선택 ========" << endl;
			cout << "1. Easy / 2. Normal / 3. Hard" << endl;
			cout << "난이도: ";
			iInput = Input<int>();

			m_vecMonster[iChooseMonster - 1]->SetStageType((STAGE_TYPE)iInput);
			break;
		case MMM_ATTACKMIN:
			cout << "최소 공격력: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetAttackMin(iInput);
			break;
		case MMM_ATTACKMAX:
			cout << "최대 공격력: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetAttackMax(iInput);
			break;
		case MMM_ARMORMIN:
			cout << "최소 방어력: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetArmorMin(iInput);
			break;
		case MMM_ARMORMAX:
			cout << "최대 방어력: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetArmorMax(iInput);
			break;
		case MMM_HP:
			cout << "HP: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetHP(iInput);
			break;
		case MMM_MP:
			cout << "MP: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetMP(iInput);
			break;
		case MMM_GOLD:
			cout << "최소 획득 골드: ";
			iGoldMin = Input<int>();
			cout << "최대 획득 골드: ";
			iGoldMax = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetGold(iGoldMin, iGoldMax);
			break;
		case MMM_LEVEL:
			cout << "레벨: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetLevel(iInput);
			break;
		case MMM_EXP:
			cout << "획득 경험치: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetExp(iInput);
			break;
		case MMM_BACK:
			return;
		}
	}
}

void CEditorMonster::DeleteMonster()
{
	system("cls");
	cout << "=================== 아이템 삭제 ===================" << endl;

	int iChooseMonster = 0;

	OutputMonsterList();
	while (iChooseMonster <= 0 || iChooseMonster > m_vecMonster.size() + 1) {
		cout << m_vecMonster.size() + 1 << ". 뒤로가기" << endl;
		cout << "삭제할 몬스터를 선택하세요: ";
		iChooseMonster = Input<int>();
	}

	if (iChooseMonster == m_vecMonster.size() + 1) {
		return;
	}

	cout << endl << m_vecMonster[iChooseMonster - 1]->GetName() << " 몬스터가 삭제되었습니다." << endl;
	m_vecMonster.erase(m_vecMonster.begin() + (iChooseMonster - 1));

	system("pause");
}

void CEditorMonster::OutputMonsterList()
{
	cout << "=================== 몬스터 목록 ===================" << endl;

	for (size_t i = 0; i < m_vecMonster.size(); i++) {
		cout << i + 1 << ". ";
		m_vecMonster[i]->Render();
		cout << endl;
	}

}

void CEditorMonster::SaveMonster()
{
	CFileStream file("MonsterList.mtl", "wb");

	// 몬스터 수를 저장한다.
	// size_t: unsigned int를 typedef 해놓은 것
	size_t iMonsterCount = m_vecMonster.size();

	file.Write(&iMonsterCount, 4);

	for (size_t i = 0; i < iMonsterCount; i++) {
		m_vecMonster[i]->Save(&file);
	}

	file.Close();

	cout << endl << "파일 저장 완료" << endl;
	system("pause");
}

void CEditorMonster::LoadMonster()
{
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

	file.Close();

	cout << endl << "파일 불러오기 완료" << endl;
	system("pause");
}
