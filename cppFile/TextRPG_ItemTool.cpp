// TextRPG - 아이템 툴

#include <iostream>

using namespace std;

#define NAME_SIZE 32
#define ITEM_DESC_LENGTH	512
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3

enum MAIN_MENU {
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

struct _tagItem {
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int iMin;
	int iMax;
	int iPrice;
	int iSell;
	char strDesc[ITEM_DESC_LENGTH];		// 아이템 설명
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

void AddItem(_tagItem* pWeaponStore, _tagItem* pArmorStore) {

	int iStore = 0;

	while (true) {
		system("cls");
		cout << "1. 무기 상점" << endl;
		cout << "2. 방어구 상점" << endl;
		cout << "3. 취소" << endl;
		cout << "추가할 상점 유형을 선택하세요: ";
		iStore = InputInt();

		if (iStore == 3) {
			return;
		}
		else if (iStore < 1 || iStore>3) {
			continue;
		}
		
		//iStore--;
		break;
	}

	int iItemLevel = 0;
	while (true) {
		system("cls");
		cout << "1. 초급" << endl;
		cout << "2. 중급" << endl;
		cout << "3. 고급" << endl;
		cout << "4. 취소" << endl;
		cout << "추가할 아이템 단계를 선택하세요: ";
		iItemLevel = InputInt();

		if (iItemLevel == 4) {
			return;
		}
		else if (iItemLevel < 1 || iItemLevel>4) {
			continue;
		}
		// 1부터 시작이기 때문에 1을 감소시켜야 아이템 단계 인덱스가 된다.
		// ex) 2. 중급 선택 시 인덱스가 1이어야하므로 iItemLevel--
		iItemLevel--;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	_tagItem* pItem = NULL;

	// 인자로 무기상점에서 사용할 아이템 배열과 방어구 상점에서 사용할 아이템 배열을 따로 넣어주었고 아이템을 추가할 때도 추가할 상점을 선택하고 아이템의 난이도를 선택했다.
	// 그러므로 복잡해지기 때문에 여기에서 추가할 아이템의 메모리 주소를 얻어와서 거기에 추가해주어 쉽게 처리 가능하게끔 한다.
	if (iStore == SM_WEAPON) {
		pItem = &pWeaponStore[iItemLevel];
		pItem->eType = IT_WEAPON;
		strcpy_s(pItem->strTypeName, "무기");
	}
	else {
		pItem = &pArmorStore[iItemLevel];
		pItem->eType = IT_ARMOR;
		strcpy_s(pItem->strTypeName, "방어구");
	}

	// 아이템 이름을 입력받는다.
	cout << endl << "아이템 이름: ";
	cin.getline(pItem->strName, NAME_SIZE - 1);

	cout << "아이템 설명: ";
	cin.getline(pItem->strDesc, ITEM_DESC_LENGTH - 1);

	cout << "최소 능력치: ";
	pItem->iMin = InputInt();

	cout << "최대 능력치: ";
	pItem->iMax = InputInt();

	cout << "구매 가격: ";
	pItem->iPrice = InputInt();

	cout << "판매 가격: ";
	pItem->iSell = InputInt();

	cout << "아이템 추가 완료" << endl;
	system("pause");
}

bool SaveStore(_tagItem* pWeapon, _tagItem* pArmor) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Store.str", "wb");

	if (pFile) {
		fwrite(pWeapon, sizeof(_tagItem), STORE_WEAPON_MAX, pFile);
		fwrite(pArmor, sizeof(_tagItem), STORE_ARMOR_MAX, pFile);

		fclose(pFile);

		return true;
	}

	return false;
}

bool LoadStore(_tagItem* pWeapon, _tagItem* pArmor) {
	FILE* pFile = NULL;

	fopen_s(&pFile, "Store.str", "rb");

	if (pFile) {
		fread(pWeapon, sizeof(_tagItem), STORE_WEAPON_MAX, pFile);
		fread(pArmor, sizeof(_tagItem), STORE_ARMOR_MAX, pFile);

		fclose(pFile);

		return true;
	}

	return false;
}

void OutputStore(_tagItem* pWeapon, _tagItem* pArmor) {
	system("cls");
	cout << "===================== Store =====================" << endl << endl;
	cout << "===================== Weapon =====================" << endl;
	// 판매 목록을 보여준다.
	for (int i = 0; i < STORE_WEAPON_MAX; i++) {
		cout << "Weapon " << i + 1 << ": " << pWeapon[i].strName << endl;
		cout << "아이템 타입 : " << pWeapon[i].strTypeName << endl;
		cout << "능력치: " << pWeapon[i].iMin << " - " << pWeapon[i].iMax << endl;
		cout << "구매가격: " << pWeapon[i].iPrice << " Gold\t판매가격: " << pWeapon[i].iSell << " Gold" << endl;
		cout << "아이템 설명: " << pWeapon[i].strDesc << endl << endl;
	}

	cout << "===================== Armor =====================" << endl;
	// 판매 목록을 보여준다.
	for (int i = 0; i < STORE_ARMOR_MAX; i++) {
		cout << "Armor " << i + 1 << ": " << pArmor[i].strName << endl;
		cout << "아이템 타입 : " << pArmor[i].strTypeName << endl;
		cout << "능력치: " << pArmor[i].iMin << " - " << pArmor[i].iMax << endl;
		cout << "구매가격: " << pArmor[i].iPrice << " Gold\t판매가격: " << pArmor[i].iSell << " Gold" << endl;
		cout << "아이템 설명: " << pArmor[i].strDesc << endl << endl;
	}

	system("pause");
}

int main() {

	_tagItem tWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tArmor[STORE_ARMOR_MAX] = {};

	while (true) {
		system("cls");
		cout << "1. 아이템 추가" << endl;
		cout << "2. 읽어오기" << endl;
		cout << "3. 저장" << endl;
		cout << "4. 아이템 목록 출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요: ";

		int iMenu = InputInt();

		if (iMenu == MM_EXIT) {
			break;
		}

		switch (iMenu) {
		case MM_ADD:
			AddItem(tWeapon, tArmor);
			break;
		case MM_LOAD:
			if (LoadStore(tWeapon, tArmor)) {
				cout << endl << "읽어오기 성공!" << endl;
				system("pause");
			}
			break;
		case MM_SAVE:
			if (SaveStore(tWeapon, tArmor)) {
				cout << endl << "저장하기 성공!" << endl;
				system("pause");
			}
			break;
		case MM_OUTPUT:
			OutputStore(tWeapon, tArmor);
			break;
		}
	}

	// 자동 저장기능. 플레이어가 저장을 하지 않더라도 프로그램이 종료될 때 자동으로 저장되도록 한다.
	SaveStore(tWeapon, tArmor);

	return 0;
}