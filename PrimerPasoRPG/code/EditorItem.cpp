#include "EditorItem.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "FileStream.h"

DEFINITION_SINGLE(CEditorItem)

enum EDIT_ITEM_MENU {
	EIM_NONE,
	EIM_INSERT,
	EIM_MODIFY,
	EIM_DELETE,
	EIM_OUTPUT,
	EIM_SAVE,
	EIM_LOAD,
	EIM_BACK
};

enum MODIFY_WEAPON_MENU {
	MWM_NONE,
	MWM_NAME,
	MWM_ITEMTYPE,
	MWM_ATTACKMIN,
	MWM_ATTACKMAX,
	MWM_CRITICAL,
	MWM_PRICE,
	MWM_SELL,
	MWM_DESC,
	MWM_BACK
};

enum MODIFY_ARMOR_MENU {
	MAM_NONE,
	MAM_NAME,
	MAM_ITEMTYPE,
	MAM_ARMOR,
	MAM_PRICE,
	MAM_SELL,
	MAM_DESC,
	MAM_BACK
};

CEditorItem::CEditorItem()
{
}

CEditorItem::~CEditorItem()
{
	Safe_Delete_VecList(m_vecWeapon);
	Safe_Delete_VecList(m_vecArmor);
}

bool CEditorItem::Init()
{
	return true;
}

void CEditorItem::Run()
{
	while (true) {
		switch (OutputMenu()) {
		case EIM_INSERT:
			InsertItem();
			break;
		case EIM_MODIFY:
			ModifyItem();
			break;
		case EIM_DELETE:
			DeleteItem();
			break;
		case EIM_OUTPUT:
			OutputItemList();
			break;
		case EIM_SAVE:
			SaveItem();
			break;
		case EIM_LOAD:
			LoadItem();
			break;
		case EIM_BACK:
			return;
		}
	}
}

int CEditorItem::OutputMenu()
{
	system("cls");
	cout << "1. ������ �߰�" << endl;
	cout << "2. ������ ����" << endl;
	cout << "3. ������ ����" << endl;
	cout << "4. ������ ���" << endl;
	cout << "5. ����" << endl;
	cout << "6. �ҷ�����" << endl;
	cout << "7. �ڷΰ���" << endl;
	cout << "�޴��� �����ϼ���: ";
	int iMenu = Input<int>();

	if (iMenu <= EIM_NONE || iMenu > EIM_BACK) {
		return EIM_NONE;
	}

	return iMenu;
}

void CEditorItem::InsertItem()
{
	CItem* pItem = NULL;

	system("cls");
	cout << "=================== ������ �߰� ===================" << endl;
	int iItemType = 0;
	while (iItemType <= 0 || iItemType > IT_MAX) {
		cout << "1. ����" << endl;
		cout << "2. ��" << endl;
		cout << "������ ������ �����ϼ���: ";
		iItemType = Input<int>();
	}

	switch (iItemType - 1) {
	case IT_WEAPON:
		pItem = new CItemWeapon;
		break;
	case IT_ARMOR:
		pItem = new CItemArmor;
		break;
	}

	if (!pItem->Init()) {
		SAFE_DELETE(pItem);
		return;
	}

	cin.ignore(1024, '\n');
	cout << "�̸�: ";
	char strName[256] = {};
	cin.getline(strName, 255);

	pItem->SetName(strName);

	int iPrice, iSell;
	cout << "���Ű�: ";
	cin >> iPrice;
	cout << "�ǸŰ�: ";
	cin >> iSell;

	switch (iItemType - 1) {
	case IT_WEAPON:
		int iAttackMin, iAttackMax;
		float fCritical;

		cout << "�ּ� ���ݷ�: ";
		iAttackMin = Input<int>();

		cout << "�ִ� ���ݷ�: ";
		iAttackMax = Input<int>();

		cout << "ġ��Ÿ��: ";
		fCritical = Input<float>();

		((CItemWeapon*)pItem)->SetWeaponInfo(iAttackMin, iAttackMax, fCritical);

		break;

	case IT_ARMOR:
		int iArmor;
		cout << "����: ";
		iArmor = Input<int>();

		((CItemArmor*)pItem)->SetArmor(iArmor);

		break;
	}

	char strDesc[256] = {};
	// ������ ���� �Է� �޴ٰ� �Ʒ��� ���ڿ� �Է� ������ ���� ���� �� �����Ƿ� ignore ���
	cin.ignore(1024, '\n');
	cout << "������ ����: ";
	cin.getline(strDesc, 255);

	pItem->SetItemInfo((ITEM_TYPE)(iItemType - 1), iPrice, iSell, strDesc);

	switch (iItemType - 1) {
	case IT_WEAPON:
		m_vecWeapon.push_back(pItem);
		break;
	case IT_ARMOR:
		m_vecArmor.push_back(pItem);
		break;
	}
}

void CEditorItem::ModifyItem()
{
	CItem* pItem = NULL;

	system("cls");
	cout << "=================== ������ ���� ===================" << endl;
	int iItemType = 0;
	while (iItemType <= 0 || iItemType > IT_MAX) {
		cout << "1. ����" << endl;
		cout << "2. ��" << endl;
		cout << "������ ������ �����ϼ���: ";
		iItemType = Input<int>();
	}
	switch (iItemType - 1) {
	case IT_WEAPON:
		pItem = new CItemWeapon;
		break;
	case IT_ARMOR:
		pItem = new CItemArmor;
		break;
	}

	if (!pItem->Init()) {
		SAFE_DELETE(pItem);
		return;
	}

	int iChooseItem;
	char strName[256] = {};
	int iAttackMin, iAttackMax, iArmor;
	float fCritical;
	int iPrice, iSell;
	char strDesc[512] = {};

	switch (iItemType - 1) {
	case IT_WEAPON:
		OutputWeaponList();

		while (true) {
			cout << "�����Ϸ��� �������� �����ϼ���: ";
			iChooseItem = Input<int>();

			// �ڷΰ��� ����
			if (iChooseItem == m_vecWeapon.size() + 1) {
				return;
			}
			else if (iChooseItem >= 1 && iChooseItem <= m_vecWeapon.size()) {
				break;
			}
		}

		while (true) {
			cout << endl << endl;
			cout << "1. �̸�\t\t2. ����(������)" << endl;
			cout << "3. �ּ� ���ݷ�\t4. �ִ� ���ݷ�\t5. ġ��Ÿ��" << endl;
			cout << "6. ���Ű�\t7. �ǸŰ�\t8. ������ ����" << endl;
			cout << "9. �ڷΰ���" << endl;
			cout << "������ �׸��� �Է��ϼ���: ";

			int iModifyMenu = Input<int>();

			if (iModifyMenu <= MWM_NONE || iModifyMenu > MWM_BACK) {
				continue;
			}

			switch (iModifyMenu) {
			case MWM_NAME:
				cout << "�̸�: ";

				cin.ignore(1024, '\n');
				cin.getline(strName, 255);

				m_vecWeapon[iChooseItem - 1]->SetName(strName);
				break;
			case MWM_ITEMTYPE:
				m_vecWeapon[iChooseItem - 1]->SetItemType(IT_ARMOR);
				cout << "������ ������ '��'�� ����Ǿ����ϴ�. (������ ������ ���� �Ұ�)" << endl;
				m_vecArmor.push_back(m_vecWeapon[iChooseItem - 1]);
				m_vecWeapon.erase(m_vecWeapon.begin() + (iChooseItem - 1));
				break;
			case MWM_ATTACKMIN:
				cout << "�ּ� ���ݷ�: ";
				cin >> iAttackMin;
				((CItemWeapon*)m_vecWeapon[iChooseItem - 1])->SetAttackMin(iAttackMin);
				break;
			case MWM_ATTACKMAX:
				cout << "�ִ� ���ݷ�: ";
				cin >> iAttackMax;
				((CItemWeapon*)m_vecWeapon[iChooseItem - 1])->SetAttackMax(iAttackMax);
				break;
			case MWM_CRITICAL:
				cout << "ġ��Ÿ: ";
				cin >> fCritical;
				((CItemWeapon*)m_vecWeapon[iChooseItem - 1])->SetCritical(fCritical);
				break;
			case MWM_PRICE:
				cout << "���Ű�: ";
				cin >> iPrice;
				m_vecWeapon[iChooseItem - 1]->SetPrice(iPrice);
				break;
			case MWM_SELL:
				cout << "�ǸŰ�: ";
				cin >> iSell;
				m_vecWeapon[iChooseItem - 1]->SetSell(iSell);
				break;
			case MWM_DESC:
				cout << "������ ����: ";
				cin.ignore(1024, '\n');
				cin.getline(strDesc, 255);
				m_vecWeapon[iChooseItem - 1]->SetDesc(strDesc);
				break;
			case MWM_BACK:
				return;
			}
		}

	case IT_ARMOR:
		OutputArmorList();

		while (true) {
			cout << "�����Ϸ��� �������� �����ϼ���: ";
			iChooseItem = Input<int>();

			// �ڷΰ��� ����
			if (iChooseItem == m_vecArmor.size() + 1) {
				return;
			}
			else if (iChooseItem >= 1 && iChooseItem <= m_vecArmor.size()) {
				break;
			}
		}

		while (true) {
			cout << endl << endl;
			cout << "1. �̸�\t\t2. ����(������)" << endl;
			cout << "3. ����" << endl;
			cout << "4. ���Ű�\t5. �ǸŰ�\t6. ������ ����" << endl;
			cout << "7. �ڷΰ���" << endl;
			cout << "������ �׸��� �Է��ϼ���: ";

			int iModifyMenu = Input<int>();

			if (iModifyMenu <= MAM_NONE || iModifyMenu > MAM_BACK) {
				continue;
			}

			switch (iModifyMenu) {
			case MAM_NAME:
				cout << "�̸�: ";

				cin.ignore(1024, '\n');
				cin.getline(strName, 255);

				m_vecArmor[iChooseItem - 1]->SetName(strName);
				break;
			case MAM_ITEMTYPE:
				m_vecArmor[iChooseItem - 1]->SetItemType(IT_WEAPON);
				cout << "������ ������ '����'�� ����Ǿ����ϴ�. (������ ������ ���� �Ұ�)" << endl;
				m_vecWeapon.push_back(m_vecArmor[iChooseItem - 1]);
				m_vecArmor.erase(m_vecArmor.begin() + (iChooseItem - 1));
				/*cout << "�ּ� ���ݷ�: ";
				cin >> iAttackMin;
				((CItemWeapon*)m_vecWeapon[m_vecWeapon.size() - 1])->SetAttackMin(iAttackMin);
				cout << "�ִ� ���ݷ�: ";
				cin >> iAttackMax;
				((CItemWeapon*)m_vecWeapon[m_vecWeapon.size() - 1])->SetAttackMax(iAttackMax);
				cout << "ġ��Ÿ: ";
				cin >> fCritical;
				((CItemWeapon*)m_vecWeapon[m_vecWeapon.size() - 1])->SetCritical(fCritical);*/
				break;
			case MAM_ARMOR:
				cout << "����: ";
				cin >> iArmor;
				((CItemArmor*)m_vecArmor[iChooseItem - 1])->SetArmor(iArmor);
				break;
			case MAM_PRICE:
				cout << "���Ű�: ";
				cin >> iPrice;
				m_vecArmor[iChooseItem - 1]->SetPrice(iPrice);
				break;
			case MAM_SELL:
				cout << "�ǸŰ�: ";
				cin >> iSell;
				m_vecArmor[iChooseItem - 1]->SetSell(iSell);
				break;
			case MAM_DESC:
				cout << "������ ����: ";
				cin.ignore(1024, '\n');
				cin.getline(strDesc, 255);
				m_vecArmor[iChooseItem - 1]->SetDesc(strDesc);
				break;
			case MAM_BACK:
				return;
			}
		}
	}
}

void CEditorItem::DeleteItem()
{
	system("cls");
	cout << "=================== ������ ���� ===================" << endl;
	int iItemType = 0;
	while (iItemType <= 0 || iItemType > IT_MAX) {
		cout << "1. ����" << endl;
		cout << "2. ��" << endl;
		cout << "������ ������ �����ϼ���: ";
		iItemType = Input<int>();
	}

	int iChooseItem = 0;

	switch (iItemType - 1) {
	case IT_WEAPON:
		OutputWeaponList();
		while (iChooseItem <= 0 || iChooseItem > m_vecWeapon.size() + 1) {
			cout << m_vecWeapon.size() + 1 << ". �ڷΰ���" << endl;
			cout << "������ �������� �����ϼ���: ";
			iChooseItem = Input<int>();
		}

		if (iChooseItem == m_vecWeapon.size() + 1) {
			return;
		}

		cout << endl << m_vecWeapon[iChooseItem - 1]->GetName() << " �������� �����Ǿ����ϴ�." << endl;
		m_vecWeapon.erase(m_vecWeapon.begin() + (iChooseItem - 1));
		break;
	case IT_ARMOR:
		OutputArmorList();
		while (iChooseItem <= 0 || iChooseItem > m_vecArmor.size() + 1) {
			cout << m_vecArmor.size() + 1 << ". �ڷΰ���" << endl;
			cout << "������ �������� �����ϼ���: ";
			iChooseItem = Input<int>();
		}

		if (iChooseItem == m_vecArmor.size() + 1) {
			return;
		}

		cout << endl << m_vecArmor[iChooseItem - 1]->GetName() << " �������� �����Ǿ����ϴ�." << endl;
		m_vecArmor.erase(m_vecArmor.begin() + (iChooseItem - 1));
		break;
	}

	system("pause");
}

void CEditorItem::OutputWeaponList()
{
	cout << "================== ���� ���� ==================" << endl;
	for (size_t i = 0; i < m_vecWeapon.size(); i++) {
		cout << i + 1 << ". ";
		m_vecWeapon[i]->Render();
		cout << endl;
	}
}

void CEditorItem::OutputArmorList()
{
	cout << "================== �� ���� ==================" << endl;
	for (size_t i = 0; i < m_vecArmor.size(); i++) {
		cout << i + 1 << ". ";
		m_vecArmor[i]->Render();
		cout << endl;
	}
}

void CEditorItem::OutputItemList()
{
	system("cls");

	OutputWeaponList();
	OutputArmorList();

	system("pause");
}

void CEditorItem::SaveItem()
{
	CFileStream file("StoreWeapon.swp", "wb");

	// ���� ���� ����
	if (file.GetOpen()) {
		size_t iCount = m_vecWeapon.size();

		file.Write(&iCount, 4);

		for (size_t i = 0; i < iCount; i++) {
			m_vecWeapon[i]->Save(&file);
		}
		file.Close();
	}

	// �� ���� ����
	if (file.Open("StoreArmor.sar", "wb")) {
		size_t iCount = m_vecArmor.size();

		file.Write(&iCount, 4);

		for (size_t i = 0; i < iCount; i++) {
			m_vecArmor[i]->Save(&file);
		}
		file.Close();
	}

	/*CFileStream file("StoreWeapon.swp", "wb");

	size_t iCount = m_vecWeapon.size();

	file.Write(&iCount, 4);

	for (size_t i = 0; i < iCount; i++) {
		m_vecWeapon[i]->Save(&file);
	}


	CFileStream file2("StoreArmor.sar", "wb");

	iCount = m_vecArmor.size();

	file2.Write(&iCount, 4);

	for (size_t i = 0; i < iCount; i++) {
		m_vecArmor[i]->Save(&file2);
	}*/

	cout << endl << "���� ���� �Ϸ�" << endl;
	system("pause");
}

void CEditorItem::LoadItem()
{
	Safe_Delete_VecList(m_vecWeapon);
	Safe_Delete_VecList(m_vecArmor);

	CFileStream file("StoreWeapon.swp", "rb");

	if (file.GetOpen()) {
		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; i++) {
			CItem* pItem = new CItemWeapon;
			if (!pItem->Init()) {
				SAFE_DELETE(pItem);
				return;
			}
			pItem->Load(&file);

			m_vecWeapon.push_back(pItem);
		}
		file.Close();
	}

	//// ���� ���� �о����
	//CFileStream file("StoreWeapon.swp", "rb");

	//size_t iWeaponCount = 0;

	//file.Read(&iWeaponCount, 4);

	//for (size_t i = 0; i < iWeaponCount; i++) {

	//	CItem* pItem = new CItemWeapon;

	//	if (!pItem->Init()) {
	//		SAFE_DELETE(pItem);
	//		return;
	//	}
	//	pItem->Load(&file);

	//	m_vecWeapon.push_back(pItem);
	//}

	//CFileStream file2("StoreArmor.sar", "rb");

	//// �� ���� �о����
	//size_t iArmorCount = 0;

	//file2.Read(&iArmorCount, 4);

	//for (size_t i = 0; i < iArmorCount; i++) {

	//	CItem* pItem = new CItemArmor;

	//	if (!pItem->Init()) {
	//		SAFE_DELETE(pItem);
	//		return;
	//	}
	//	pItem->Load(&file2);

	//	m_vecArmor.push_back(pItem);
	//}


	// �� ���� �о����
	if (file.Open("StoreArmor.sar", "rb")) {
		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; i++) {

			CItem* pItem = new CItemArmor;

			if (!pItem->Init()) {
				SAFE_DELETE(pItem);
				return;
			}
			pItem->Load(&file);

			m_vecArmor.push_back(pItem);
		}

		file.Close();
	}

	cout << endl << "���� �ҷ����� �Ϸ�" << endl;
	system("pause");
}
