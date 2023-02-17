// TextRPG - ������ ��

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
	char strDesc[ITEM_DESC_LENGTH];		// ������ ����
};

// ���� �Է��� �޴´�. �Է� �������� ������ְ� INT_MAX�� �����ϸ� �Է� ���� �߻�
int InputInt() {
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;		// INT_MAX�� ���ϵǸ� �Է��� �߸��ƴٴ� �ǹ�
	}

	return iInput;
}

void AddItem(_tagItem* pWeaponStore, _tagItem* pArmorStore) {

	int iStore = 0;

	while (true) {
		system("cls");
		cout << "1. ���� ����" << endl;
		cout << "2. �� ����" << endl;
		cout << "3. ���" << endl;
		cout << "�߰��� ���� ������ �����ϼ���: ";
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
		cout << "1. �ʱ�" << endl;
		cout << "2. �߱�" << endl;
		cout << "3. ���" << endl;
		cout << "4. ���" << endl;
		cout << "�߰��� ������ �ܰ踦 �����ϼ���: ";
		iItemLevel = InputInt();

		if (iItemLevel == 4) {
			return;
		}
		else if (iItemLevel < 1 || iItemLevel>4) {
			continue;
		}
		// 1���� �����̱� ������ 1�� ���ҽ��Ѿ� ������ �ܰ� �ε����� �ȴ�.
		// ex) 2. �߱� ���� �� �ε����� 1�̾���ϹǷ� iItemLevel--
		iItemLevel--;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	_tagItem* pItem = NULL;

	// ���ڷ� ����������� ����� ������ �迭�� �� �������� ����� ������ �迭�� ���� �־��־��� �������� �߰��� ���� �߰��� ������ �����ϰ� �������� ���̵��� �����ߴ�.
	// �׷��Ƿ� ���������� ������ ���⿡�� �߰��� �������� �޸� �ּҸ� ���ͼ� �ű⿡ �߰����־� ���� ó�� �����ϰԲ� �Ѵ�.
	if (iStore == SM_WEAPON) {
		pItem = &pWeaponStore[iItemLevel];
		pItem->eType = IT_WEAPON;
		strcpy_s(pItem->strTypeName, "����");
	}
	else {
		pItem = &pArmorStore[iItemLevel];
		pItem->eType = IT_ARMOR;
		strcpy_s(pItem->strTypeName, "��");
	}

	// ������ �̸��� �Է¹޴´�.
	cout << endl << "������ �̸�: ";
	cin.getline(pItem->strName, NAME_SIZE - 1);

	cout << "������ ����: ";
	cin.getline(pItem->strDesc, ITEM_DESC_LENGTH - 1);

	cout << "�ּ� �ɷ�ġ: ";
	pItem->iMin = InputInt();

	cout << "�ִ� �ɷ�ġ: ";
	pItem->iMax = InputInt();

	cout << "���� ����: ";
	pItem->iPrice = InputInt();

	cout << "�Ǹ� ����: ";
	pItem->iSell = InputInt();

	cout << "������ �߰� �Ϸ�" << endl;
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
	// �Ǹ� ����� �����ش�.
	for (int i = 0; i < STORE_WEAPON_MAX; i++) {
		cout << "Weapon " << i + 1 << ": " << pWeapon[i].strName << endl;
		cout << "������ Ÿ�� : " << pWeapon[i].strTypeName << endl;
		cout << "�ɷ�ġ: " << pWeapon[i].iMin << " - " << pWeapon[i].iMax << endl;
		cout << "���Ű���: " << pWeapon[i].iPrice << " Gold\t�ǸŰ���: " << pWeapon[i].iSell << " Gold" << endl;
		cout << "������ ����: " << pWeapon[i].strDesc << endl << endl;
	}

	cout << "===================== Armor =====================" << endl;
	// �Ǹ� ����� �����ش�.
	for (int i = 0; i < STORE_ARMOR_MAX; i++) {
		cout << "Armor " << i + 1 << ": " << pArmor[i].strName << endl;
		cout << "������ Ÿ�� : " << pArmor[i].strTypeName << endl;
		cout << "�ɷ�ġ: " << pArmor[i].iMin << " - " << pArmor[i].iMax << endl;
		cout << "���Ű���: " << pArmor[i].iPrice << " Gold\t�ǸŰ���: " << pArmor[i].iSell << " Gold" << endl;
		cout << "������ ����: " << pArmor[i].strDesc << endl << endl;
	}

	system("pause");
}

int main() {

	_tagItem tWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tArmor[STORE_ARMOR_MAX] = {};

	while (true) {
		system("cls");
		cout << "1. ������ �߰�" << endl;
		cout << "2. �о����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ������ ��� ���" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ���: ";

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
				cout << endl << "�о���� ����!" << endl;
				system("pause");
			}
			break;
		case MM_SAVE:
			if (SaveStore(tWeapon, tArmor)) {
				cout << endl << "�����ϱ� ����!" << endl;
				system("pause");
			}
			break;
		case MM_OUTPUT:
			OutputStore(tWeapon, tArmor);
			break;
		}
	}

	// �ڵ� ������. �÷��̾ ������ ���� �ʴ��� ���α׷��� ����� �� �ڵ����� ����ǵ��� �Ѵ�.
	SaveStore(tWeapon, tArmor);

	return 0;
}