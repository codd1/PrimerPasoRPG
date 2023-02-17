// TextRPG - 몬스터 툴

#include <iostream>

using namespace std;

#define NAME_SIZE 32

enum MAP_TYPE {
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_END
};

enum MAIN_MENU {
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
};

struct _tagMonster {
	char strName[NAME_SIZE];
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iLevel;
	int iExp;		// 몬스터 처치 시 플레이어 획득 경험치
	int iGoldMin;	// 몬스터 처치 시 플레이어 획득 골드
	int iGoldMax;
};

// 숫자 입력을 받는다. 입력 오류까지 출력해주고 INT_MAX를 리턴하면 입력 오류 발생
int InputInt() {
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;		// INT_MAX가 리턴되면 입력이 잘못됐다는 의미
	}

	return iInput;
}

void AddMonster(_tagMonster* pMonsterArr) {

	int iMap = 0;

	while (true) {
		system("cls");
		cout << "1. 쉬움" << endl;
		cout << "2. 보통" << endl;
		cout << "3. 어려움" << endl;
		cout << "4. 취소" << endl;
		cout << "추가할 난이도를 선택하세요: ";
		iMap = InputInt();

		if (iMap == 4) {
			return;
		}
		else if (iMap < 1 || iMap>4) {
			continue;
		}
		// 1부터 시작이기 때문에 1을 감소시켜야 사냥터 인덱스가 된다.
		// ex) 2. 보통 선택 시 인덱스가 1이어야하므로 iMap--
		iMap--;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	// 몬스터 이름을 입력받는다.
	cout << endl << "몬스터 이름: ";
	cin.getline(pMonsterArr[iMap].strName, NAME_SIZE - 1);

	cout << "최소 공격력: ";
	pMonsterArr[iMap].iAttackMin = InputInt();

	cout << "최대 공격력: ";
	pMonsterArr[iMap].iAttackMax = InputInt();

	cout << "최소 방어력: ";
	pMonsterArr[iMap].iArmorMin = InputInt();

	cout << "최대 방어력: ";
	pMonsterArr[iMap].iArmorMax = InputInt();

	cout << "체력: ";
	pMonsterArr[iMap].iHP = InputInt();
	pMonsterArr[iMap].iHPMax = pMonsterArr[iMap].iHP;

	cout << "마나: ";
	pMonsterArr[iMap].iHP = InputInt();
	pMonsterArr[iMap].iHPMax = pMonsterArr[iMap].iHP;

	cout << "레벨: ";
	pMonsterArr[iMap].iLevel = InputInt();

	cout << "획득 경험치: ";
	pMonsterArr[iMap].iExp = InputInt();

	cout << "획득 최소 골드: ";
	pMonsterArr[iMap].iGoldMin = InputInt();

	cout << "획득 최대 골드: ";
	pMonsterArr[iMap].iGoldMax = InputInt();

	cout << "몬스터 추가 완료" << endl;
	system("pause");
}

bool SaveMonster(_tagMonster* pMonsterArr) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "wb");

	if (pFile) {
		fwrite(pMonsterArr, sizeof(_tagMonster), MT_END, pFile);
		fclose(pFile);

		return true;
	}

	return false;
}

bool LoadMonster(_tagMonster* pMonsterArr) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "rb");

	if (pFile) {
		fread(pMonsterArr, sizeof(_tagMonster), MT_END, pFile);
		fclose(pFile);

		return true;
	}

	return false;
}

void OutputMonster(_tagMonster* pMonster) {
	system("cls");
	cout << "===================== Monster =====================" << endl;
	for (int i = 0; i < MT_END; i++) {
		cout << "이름: " << pMonster[i].strName << "\t레벨: " << pMonster[i].iLevel << endl;
		cout << "공격력: " << pMonster[i].iAttackMin << " - " << pMonster[i].iAttackMax << "\t방어력: " << pMonster[i].iArmorMin << " - " << pMonster[i].iArmorMax << endl;
		cout << "체력: " << pMonster[i].iHP << " / " << pMonster[i].iHPMax << "\t마나: " << pMonster[i].iMP << " / " << pMonster[i].iMPMax << endl;
		cout << "획득 경험치: " << pMonster[i].iExp << "\t획득 골드: " << pMonster[i].iGoldMin << " - " << pMonster[i].iGoldMax << endl << endl;
	}
	system("pause");
}

int main() {

	_tagMonster tMonster[MT_END] = {};

	while (true) {
		system("cls");
		cout << "1. 몬스터 추가" << endl;
		cout << "2. 읽어오기" << endl;
		cout << "3. 저장" << endl;
		cout << "4. 몬스터 목록 출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요: ";

		int iMenu = InputInt();

		if (iMenu == MM_EXIT) {
			break;
		}

		switch (iMenu) {
		case MM_ADD:
			AddMonster(tMonster);
			break;
		case MM_LOAD:
			if (LoadMonster(tMonster)) {
				cout << endl << "읽어오기 성공!" << endl;
				system("pause");
			}
			break;
		case MM_SAVE:
			if (SaveMonster(tMonster)) {
				cout << endl << "저장하기 성공!" << endl;
				system("pause");
			}
			break;
		case MM_OUTPUT:
			OutputMonster(tMonster);
			break;
		}
	}

	// 자동 저장기능. 플레이어가 저장을 하지 않더라도 프로그램이 종료될 때 자동으로 저장되도록 한다.
	SaveMonster(tMonster);

	return 0;
}

