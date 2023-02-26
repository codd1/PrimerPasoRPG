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
			break;
		case EIM_DELETE:
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
	cout << "1. 아이템 추가" << endl;
	cout << "2. 아이템 수정" << endl;
	cout << "3. 아이템 삭제" << endl;
	cout << "4. 아이템 목록" << endl;
	cout << "5. 저장" << endl;
	cout << "6. 불러오기" << endl;
	cout << "7. 뒤로가기" << endl;
	cout << "메뉴를 선택하세요: ";
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
	cout << "=================== 아이템 추가 ===================" << endl;
	int iItemType = 0;
	while (iItemType <= 0 || iItemType > IT_MAX) {
		cout << "1. 무기" << endl;
		cout << "2. 방어구" << endl;
		cout << "아이템 종류를 선택하세요: ";
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
	cout << "이름: ";
	char strName[256] = {};
	cin.getline(strName, 255);

	pItem->SetName(strName);

	int iPrice, iSell;
	cout << "구매가: ";
	cin >> iPrice;
	cout << "판매가: ";
	cin >> iSell;

	switch (iItemType - 1) {
	case IT_WEAPON:
		int iAttackMin, iAttackMax;
		float fCritical;

		cout << "최소 공격력: ";
		iAttackMin = Input<int>();

		cout << "최대 공격력: ";
		iAttackMax = Input<int>();

		cout << "치명타율: ";
		fCritical = Input<float>();

		((CItemWeapon*)pItem)->SetWeaponInfo(iAttackMin, iAttackMax, fCritical);

		break;

	case IT_ARMOR:
		int iArmorMin, iArmorMax;
		cout << "최소 방어력: ";
		iArmorMin = Input<int>();

		cout << "최대 방어력: ";
		iArmorMax = Input<int>();

		((CItemArmor*)pItem)->SetArmorInfo(iArmorMin, iArmorMax);

		break;
	}

	char strDesc[256] = {};
	// 위에서 숫자 입력 받다가 아래서 문자열 입력 받으면 문제 생길 수 있으므로 ignore 사용
	cin.ignore(1024, '\n');
	cout << "아이템 설명: ";
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

void CEditorItem::OutputItemList()
{
	system("cls");
	cout << "================== 무기 상점 ==================" << endl;
	for (size_t i = 0; i < m_vecWeapon.size(); i++) {
		cout << i + 1 << ". ";
		m_vecWeapon[i]->Render();
		cout << endl;
	}

	cout << "================== 방어구 상점 ==================" << endl;
	for (size_t i = 0; i < m_vecArmor.size(); i++) {
		cout << i + 1 << ". ";
		m_vecArmor[i]->Render();
		cout << endl;
	}

	system("pause");
}

void CEditorItem::SaveItem()
{
	CFileStream file("StoreWeapon.swp", "wb");
	
	// 무기 상점 저장
	if (file.GetOpen()) {
		size_t iCount = m_vecWeapon.size();

		file.Write(&iCount, 4);

		for (size_t i = 0; i < iCount; i++) {
			m_vecWeapon[i]->Save(&file);
		}
		file.Close();
	}

	// 방어구 상점 저장
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

	cout << "파일 저장 완료" << endl;
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

	//// 무기 상점 읽어오기
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

	//// 방어구 상점 읽어오기
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


	// 방어구 상점 읽어오기
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

	cout << "파일 불러오기 완료" << endl;
	system("pause");
}
