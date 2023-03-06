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
	cout << "1. ���� �߰�" << endl;
	cout << "2. ���� ����" << endl;
	cout << "3. ���� ����" << endl;
	cout << "4. ���� ���" << endl;
	cout << "5. ����" << endl;
	cout << "6. �ҷ�����" << endl;
	cout << "7. �ڷΰ���" << endl;
	cout << "�޴��� �����ϼ���: ";
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
	cout << "=================== ���� �߰� ===================" << endl;
	cin.ignore(1024, '\n');
	cout << "�̸�: ";
	char strName[256] = {};
	cin.getline(strName, 255);

	pMonster->SetName(strName);

	int iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp;
	float fCritical;
	cout << "�ּ� ���ݷ�: ";
	cin >> iAttackMin;
	cout << "�ִ� ���ݷ�: ";
	cin >> iAttackMax;
	cout << "ġ��Ÿ��: ";
	cin >> fCritical;
	cout << "�ּ� ����: ";
	cin >> iArmorMin;
	cout << "�ִ� ����: ";
	cin >> iArmorMax;
	cout << "ü��: ";
	cin >> iHP;
	cout << "����: ";
	cin >> iMP;
	cout << "����: ";
	cin >> iLevel;
	cout << "ȹ�� ����ġ: ";
	cin >> iExp;

	pMonster->SetCharacterInfo(iAttackMin, iAttackMax, fCritical, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp);

	int iGoldMin, iGoldMax;
	cout << "�ּ� ���: ";
	cin >> iGoldMin;
	cout << "�ִ� ���: ";
	cin >> iGoldMax;

	pMonster->SetGold(iGoldMin, iGoldMax);

	// ���̵��� �����Ѵ�.
	int iStage = ST_NONE;
	while (iStage <= ST_NONE || iStage >= ST_BACK) {
		cout << endl;
		cout << "1. Easy" << endl;
		cout << "2. Normal" << endl;
		cout << "3. Hard" << endl;
		cout << "���̵��� �����ϼ���: ";
		iStage = Input<int>();
	}
	pMonster->SetStageType((STAGE_TYPE)iStage);

	m_vecMonster.push_back(pMonster);
}

void CEditorMonster::ModifyMonster()
{
	system("cls");
	cout << "=================== ���� ��� ===================" << endl;

	// ���� ��Ͽ� ���Ͱ� ���� ���
	if (m_vecMonster.size() == 0) {
		cout << endl << "���� ������ ���Ͱ� �����ϴ�." << endl;
		system("pause");
		return;
	}

	OutputMonsterList();
	cout << m_vecMonster.size() + 1 << ". �ڷΰ���" << endl;

	int iChooseMonster;

	while (true) {
		cout << "�����Ϸ��� ���͸� �����ϼ���: ";
		iChooseMonster = Input<int>();

		// �ڷΰ��� ����
		if (iChooseMonster == m_vecMonster.size() + 1) {
			return;
		}
		else if (iChooseMonster >= 1 && iChooseMonster <= m_vecMonster.size()) {
			break;
		}
	}

	while (true) {

		cout << endl << endl;
		cout << "1. �̸�\t\t2. ���̵�" << endl;
		cout << "3. �ּ� ���ݷ�\t4. �ִ� ���ݷ�" << endl;
		cout << "5. �ּ� ����\t6. �ִ� ����" << endl;
		cout << "7. HP\t\t8. MP" << endl;
		cout << "9. óġ �� ȹ�� ���" << endl;
		cout << "10. ����\t11. ����ġ" << endl;
		cout << "12. �ڷΰ���" << endl;
		cout << "������ �׸��� �Է��ϼ���: ";
		// ������ �׸��� �Է� �ް�, ���� ���� ���� �� ���ο� ���� ���� �Է�
		int iModifyMenu = Input<int>();

		// ���� ����: iAttackMin, iAttackMax, iArmorMin, iArmorMax, iHP, iMP, iLevel, iExp; iGoldMin, iGoldMax;
		if (iModifyMenu <= MMM_NONE || iModifyMenu > MMM_BACK) {
			continue;
		}
		int iInput;
		char strName[256] = {};
		int iGoldMin, iGoldMax;

		cout << endl;
		switch (iModifyMenu) {
		case MMM_NAME:
			cout << "�̸�: ";

			cin.ignore(1024, '\n');
			cin.getline(strName, 255);

			m_vecMonster[iChooseMonster - 1]->SetName(strName);

			break;
		case MMM_STAGETYPE:
			cout << endl;
			cout << "======== ���̵� ���� ========" << endl;
			cout << "1. Easy / 2. Normal / 3. Hard" << endl;
			cout << "���̵�: ";
			iInput = Input<int>();

			m_vecMonster[iChooseMonster - 1]->SetStageType((STAGE_TYPE)iInput);
			break;
		case MMM_ATTACKMIN:
			cout << "�ּ� ���ݷ�: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetAttackMin(iInput);
			break;
		case MMM_ATTACKMAX:
			cout << "�ִ� ���ݷ�: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetAttackMax(iInput);
			break;
		case MMM_ARMORMIN:
			cout << "�ּ� ����: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetArmorMin(iInput);
			break;
		case MMM_ARMORMAX:
			cout << "�ִ� ����: ";
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
			cout << "�ּ� ȹ�� ���: ";
			iGoldMin = Input<int>();
			cout << "�ִ� ȹ�� ���: ";
			iGoldMax = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetGold(iGoldMin, iGoldMax);
			break;
		case MMM_LEVEL:
			cout << "����: ";
			iInput = Input<int>();
			m_vecMonster[iChooseMonster - 1]->SetLevel(iInput);
			break;
		case MMM_EXP:
			cout << "ȹ�� ����ġ: ";
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
	cout << "=================== ������ ���� ===================" << endl;

	int iChooseMonster = 0;

	OutputMonsterList();
	while (iChooseMonster <= 0 || iChooseMonster > m_vecMonster.size() + 1) {
		cout << m_vecMonster.size() + 1 << ". �ڷΰ���" << endl;
		cout << "������ ���͸� �����ϼ���: ";
		iChooseMonster = Input<int>();
	}

	if (iChooseMonster == m_vecMonster.size() + 1) {
		return;
	}

	cout << endl << m_vecMonster[iChooseMonster - 1]->GetName() << " ���Ͱ� �����Ǿ����ϴ�." << endl;
	m_vecMonster.erase(m_vecMonster.begin() + (iChooseMonster - 1));

	system("pause");
}

void CEditorMonster::OutputMonsterList()
{
	cout << "=================== ���� ��� ===================" << endl;

	for (size_t i = 0; i < m_vecMonster.size(); i++) {
		cout << i + 1 << ". ";
		m_vecMonster[i]->Render();
		cout << endl;
	}

}

void CEditorMonster::SaveMonster()
{
	CFileStream file("MonsterList.mtl", "wb");

	// ���� ���� �����Ѵ�.
	// size_t: unsigned int�� typedef �س��� ��
	size_t iMonsterCount = m_vecMonster.size();

	file.Write(&iMonsterCount, 4);

	for (size_t i = 0; i < iMonsterCount; i++) {
		m_vecMonster[i]->Save(&file);
	}

	file.Close();

	cout << endl << "���� ���� �Ϸ�" << endl;
	system("pause");
}

void CEditorMonster::LoadMonster()
{
	// ���� ���� ������ �о���� ���� ���� vector list�� �����.
	Safe_Delete_VecList(m_vecMonster);

	CFileStream file("MonsterList.mtl", "rb");

	// ���� ���� �о�´�.
	// size_t: unsigned int�� typedef �س��� ��
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

	cout << endl << "���� �ҷ����� �Ϸ�" << endl;
	system("pause");
}
