#include "EditorItem.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "ItemPosion.h"
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

enum MODIFY_POSION_MENU {
	MPM_NONE,
	MPM_NAME,
	MPM_ITEMTYPE,
	MPM_POSION,
	MPM_PRICE,
	MPM_SELL,
	MPM_DESC,
	MPM_BACK
};

enum POSION_TYPE {
	PT_NONE,
	PT_HP,
	PT_MP
};

CEditorItem::CEditorItem()
{
}

CEditorItem::~CEditorItem()
{
	Safe_Delete_VecList(m_vecWeapon);
	Safe_Delete_VecList(m_vecArmor);
	Safe_Delete_VecList(m_vecPosion);
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
	int iPosionType = 0;
	while (iItemType <= 0 || iItemType > IT_MAX) {
		cout << "1. 무기" << endl;
		cout << "2. 방어구" << endl;
		cout << "3. 물약" << endl;
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
	case IT_HP_POSION:
	case IT_MP_POSION:
		pItem = new CItemPosion;
		cout << endl;
		while (iPosionType <= PT_NONE || iPosionType > PT_MP + 1) {
			cout << "1. 체력 물약 / 2. 마나 물약" << endl;
			cout << "물약 타입을 선택하세요: ";
			iPosionType = Input<int>();
		}
		switch (iPosionType) {
		case PT_HP:
			iPosionType = IT_HP_POSION;
			break;
		case PT_MP:
			iPosionType = IT_MP_POSION;
			break;
		}
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
		int iArmor;
		cout << "방어력: ";
		iArmor = Input<int>();

		((CItemArmor*)pItem)->SetArmor(iArmor);

		break;
	case IT_HP_POSION:
	case IT_MP_POSION:
		int iPosion;
		cout << "회복량: ";
		iPosion = Input<int>();

		// 포션 타입 저장 (체력/마나 물약)
		// SetItemInfo에서 iItemType -1을 하기 때문에 1을 더해준다.
		iItemType = iPosionType + 1;

		((CItemPosion*)pItem)->SetPosion(iPosion);

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
	case IT_HP_POSION:
	case IT_MP_POSION:
		m_vecPosion.push_back(pItem);
		break;
	}
}

void CEditorItem::ModifyItem()
{
	CItem* pItem = NULL;

	system("cls");
	cout << "=================== 아이템 수정 ===================" << endl;
	int iItemType = 0;
	while (iItemType <= 0 || iItemType > IT_MAX) {
		cout << "1. 무기" << endl;
		cout << "2. 방어구" << endl;
		cout << "3. 물약" << endl;
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
	case IT_HP_POSION:
	case IT_MP_POSION:
		pItem = new CItemPosion;
		break;
	}

	if (!pItem->Init()) {
		SAFE_DELETE(pItem);
		return;
	}

	int iChooseItem;
	char strName[256] = {};
	int iAttackMin, iAttackMax, iArmor, iPosion;
	float fCritical;
	int iPrice, iSell;
	char strDesc[512] = {};

	switch (iItemType - 1) {
	case IT_WEAPON:
		OutputWeaponList();

		while (true) {
			cout << "수정하려는 아이템을 선택하세요: ";
			iChooseItem = Input<int>();

			// 뒤로가기 선택
			if (iChooseItem == m_vecWeapon.size() + 1) {
				return;
			}
			else if (iChooseItem >= 1 && iChooseItem <= m_vecWeapon.size()) {
				break;
			}
		}

		while (true) {
			cout << endl << endl;
			cout << "1. 이름\t\t2. 종류(무기↔방어구)" << endl;
			cout << "3. 최소 공격력\t4. 최대 공격력\t5. 치명타율" << endl;
			cout << "6. 구매가\t7. 판매가\t8. 아이템 설명" << endl;
			cout << "9. 뒤로가기" << endl;
			cout << "수정할 항목을 입력하세요: ";

			int iModifyMenu = Input<int>();

			if (iModifyMenu <= MWM_NONE || iModifyMenu > MWM_BACK) {
				continue;
			}

			switch (iModifyMenu) {
			case MWM_NAME:
				cout << "이름: ";

				cin.ignore(1024, '\n');
				cin.getline(strName, 255);

				m_vecWeapon[iChooseItem - 1]->SetName(strName);
				break;
			case MWM_ITEMTYPE:
				m_vecWeapon[iChooseItem - 1]->SetItemType(IT_ARMOR);
				cout << "아이템 종류가 '방어구'로 변경되었습니다. (아이템 정보는 수정 불가)" << endl;
				m_vecArmor.push_back(m_vecWeapon[iChooseItem - 1]);
				m_vecWeapon.erase(m_vecWeapon.begin() + (iChooseItem - 1));
				break;
			case MWM_ATTACKMIN:
				cout << "최소 공격력: ";
				cin >> iAttackMin;
				((CItemWeapon*)m_vecWeapon[iChooseItem - 1])->SetAttackMin(iAttackMin);
				break;
			case MWM_ATTACKMAX:
				cout << "최대 공격력: ";
				cin >> iAttackMax;
				((CItemWeapon*)m_vecWeapon[iChooseItem - 1])->SetAttackMax(iAttackMax);
				break;
			case MWM_CRITICAL:
				cout << "치명타: ";
				cin >> fCritical;
				((CItemWeapon*)m_vecWeapon[iChooseItem - 1])->SetCritical(fCritical);
				break;
			case MWM_PRICE:
				cout << "구매가: ";
				cin >> iPrice;
				m_vecWeapon[iChooseItem - 1]->SetPrice(iPrice);
				break;
			case MWM_SELL:
				cout << "판매가: ";
				cin >> iSell;
				m_vecWeapon[iChooseItem - 1]->SetSell(iSell);
				break;
			case MWM_DESC:
				cout << "아이템 설명: ";
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
			cout << "수정하려는 아이템을 선택하세요: ";
			iChooseItem = Input<int>();

			// 뒤로가기 선택
			if (iChooseItem == m_vecArmor.size() + 1) {
				return;
			}
			else if (iChooseItem >= 1 && iChooseItem <= m_vecArmor.size()) {
				break;
			}
		}

		while (true) {
			cout << endl << endl;
			cout << "1. 이름\t\t2. 종류(무기↔방어구)" << endl;
			cout << "3. 방어력" << endl;
			cout << "4. 구매가\t5. 판매가\t6. 아이템 설명" << endl;
			cout << "7. 뒤로가기" << endl;
			cout << "수정할 항목을 입력하세요: ";

			int iModifyMenu = Input<int>();

			if (iModifyMenu <= MAM_NONE || iModifyMenu > MAM_BACK) {
				continue;
			}

			switch (iModifyMenu) {
			case MAM_NAME:
				cout << "이름: ";

				cin.ignore(1024, '\n');
				cin.getline(strName, 255);

				m_vecArmor[iChooseItem - 1]->SetName(strName);
				break;
			case MAM_ITEMTYPE:
				m_vecArmor[iChooseItem - 1]->SetItemType(IT_WEAPON);
				cout << "아이템 종류가 '무기'로 변경되었습니다. (아이템 정보는 수정 불가)" << endl;
				m_vecWeapon.push_back(m_vecArmor[iChooseItem - 1]);
				m_vecArmor.erase(m_vecArmor.begin() + (iChooseItem - 1));
				/*cout << "최소 공격력: ";
				cin >> iAttackMin;
				((CItemWeapon*)m_vecWeapon[m_vecWeapon.size() - 1])->SetAttackMin(iAttackMin);
				cout << "최대 공격력: ";
				cin >> iAttackMax;
				((CItemWeapon*)m_vecWeapon[m_vecWeapon.size() - 1])->SetAttackMax(iAttackMax);
				cout << "치명타: ";
				cin >> fCritical;
				((CItemWeapon*)m_vecWeapon[m_vecWeapon.size() - 1])->SetCritical(fCritical);*/
				break;
			case MAM_ARMOR:
				cout << "방어력: ";
				cin >> iArmor;
				((CItemArmor*)m_vecArmor[iChooseItem - 1])->SetArmor(iArmor);
				break;
			case MAM_PRICE:
				cout << "구매가: ";
				cin >> iPrice;
				m_vecArmor[iChooseItem - 1]->SetPrice(iPrice);
				break;
			case MAM_SELL:
				cout << "판매가: ";
				cin >> iSell;
				m_vecArmor[iChooseItem - 1]->SetSell(iSell);
				break;
			case MAM_DESC:
				cout << "아이템 설명: ";
				cin.ignore(1024, '\n');
				cin.getline(strDesc, 255);
				m_vecArmor[iChooseItem - 1]->SetDesc(strDesc);
				break;
			case MAM_BACK:
				return;
			}
		}
	case IT_HP_POSION:
	case IT_MP_POSION:
		OutputPosionList();

		while (true) {
			cout << "수정하려는 아이템을 선택하세요: ";
			iChooseItem = Input<int>();

			// 뒤로가기 선택
			if (iChooseItem == m_vecPosion.size() + 1) {
				return;
			}
			else if (iChooseItem >= 1 && iChooseItem <= m_vecPosion.size()) {
				break;
			}
		}

		while (true) {
			cout << endl << endl;
			cout << "1. 이름\t\t2. 종류" << endl;
			cout << "3. 회복량" << endl;
			cout << "4. 구매가\t5. 판매가\t6. 아이템 설명" << endl;
			cout << "7. 뒤로가기" << endl;
			cout << "수정할 항목을 입력하세요: ";

			int iModifyMenu = Input<int>();

			if (iModifyMenu <= MAM_NONE || iModifyMenu > MAM_BACK) {
				continue;
			}

			switch (iModifyMenu) {
			case MPM_NAME:
				cout << "이름: ";

				cin.ignore(1024, '\n');
				cin.getline(strName, 255);

				m_vecPosion[iChooseItem - 1]->SetName(strName);
				break;
			case MPM_ITEMTYPE:
				/*m_vecPosion[iChooseItem - 1]->SetItemType(IT_WEAPON);
				cout << "아이템 종류가 '무기'로 변경되었습니다. (아이템 정보는 수정 불가)" << endl;
				m_vecWeapon.push_back(m_vecPosion[iChooseItem - 1]);
				m_vecPosion.erase(m_vecPosion.begin() + (iChooseItem - 1));*/
				cout << "설계(기획) 필요" << endl;
				break;
			case MPM_POSION:
				cout << "회복량: ";
				cin >> iPosion;
				((CItemPosion*)m_vecPosion[iChooseItem - 1])->SetPosion(iPosion);
				break;
			case MPM_PRICE:
				cout << "구매가: ";
				cin >> iPrice;
				m_vecPosion[iChooseItem - 1]->SetPrice(iPrice);
				break;
			case MPM_SELL:
				cout << "판매가: ";
				cin >> iSell;
				m_vecPosion[iChooseItem - 1]->SetSell(iSell);
				break;
			case MPM_DESC:
				cout << "아이템 설명: ";
				cin.ignore(1024, '\n');
				cin.getline(strDesc, 255);
				m_vecPosion[iChooseItem - 1]->SetDesc(strDesc);
				break;
			case MPM_BACK:
				return;
			}
		}
		break;
	}
}

void CEditorItem::DeleteItem()
{
	system("cls");
	cout << "=================== 아이템 삭제 ===================" << endl;
	int iItemType = 0;
	while (iItemType <= 0 || iItemType > IT_MAX) {
		cout << "1. 무기" << endl;
		cout << "2. 방어구" << endl;
		cout << "3. 물약" << endl;
		cout << "아이템 종류를 선택하세요: ";
		iItemType = Input<int>();
	}

	int iChooseItem = 0;

	switch (iItemType - 1) {
	case IT_WEAPON:
		OutputWeaponList();
		while (iChooseItem <= 0 || iChooseItem > m_vecWeapon.size() + 1) {
			cout << m_vecWeapon.size() + 1 << ". 뒤로가기" << endl;
			cout << "삭제할 아이템을 선택하세요: ";
			iChooseItem = Input<int>();
		}

		if (iChooseItem == m_vecWeapon.size() + 1) {
			return;
		}

		cout << endl << m_vecWeapon[iChooseItem - 1]->GetName() << " 아이템이 삭제되었습니다." << endl;
		m_vecWeapon.erase(m_vecWeapon.begin() + (iChooseItem - 1));
		break;
	case IT_ARMOR:
		OutputArmorList();
		while (iChooseItem <= 0 || iChooseItem > m_vecArmor.size() + 1) {
			cout << m_vecArmor.size() + 1 << ". 뒤로가기" << endl;
			cout << "삭제할 아이템을 선택하세요: ";
			iChooseItem = Input<int>();
		}

		if (iChooseItem == m_vecArmor.size() + 1) {
			return;
		}

		cout << endl << m_vecArmor[iChooseItem - 1]->GetName() << " 아이템이 삭제되었습니다." << endl;
		m_vecArmor.erase(m_vecArmor.begin() + (iChooseItem - 1));
		break;
	case IT_HP_POSION:
	case IT_MP_POSION:
		OutputPosionList();
		while (iChooseItem <= 0 || iChooseItem > m_vecPosion.size() + 1) {
			cout << m_vecPosion.size() + 1 << ". 뒤로가기" << endl;
			cout << "삭제할 아이템을 선택하세요: ";
			iChooseItem = Input<int>();
		}

		if (iChooseItem == m_vecPosion.size() + 1) {
			return;
		}

		cout << endl << m_vecPosion[iChooseItem - 1]->GetName() << " 아이템이 삭제되었습니다." << endl;
		m_vecPosion.erase(m_vecPosion.begin() + (iChooseItem - 1));

		break;
	}

	system("pause");
}

void CEditorItem::OutputWeaponList()
{
	cout << "================== 무기 상점 ==================" << endl;
	for (size_t i = 0; i < m_vecWeapon.size(); i++) {
		cout << i + 1 << ". ";
		m_vecWeapon[i]->Render();
		cout << endl;
	}
}

void CEditorItem::OutputArmorList()
{
	cout << "================== 방어구 상점 ==================" << endl;
	for (size_t i = 0; i < m_vecArmor.size(); i++) {
		cout << i + 1 << ". ";
		m_vecArmor[i]->Render();
		cout << endl;
	}
}

void CEditorItem::OutputPosionList()
{
	cout << "================== 물약 상점 ==================" << endl;
	for (size_t i = 0; i < m_vecPosion.size(); i++) {
		cout << i + 1 << ". ";
		m_vecPosion[i]->Render();
		cout << endl;
	}
}

void CEditorItem::OutputItemList()
{
	system("cls");

	OutputWeaponList();
	OutputArmorList();
	OutputPosionList();

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

	// 물약 상점 저장
	if (file.Open("StorePosion.sps", "wb")) {
		size_t iCount = m_vecPosion.size();

		file.Write(&iCount, 4);

		for (size_t i = 0; i < iCount; i++) {
			m_vecPosion[i]->Save(&file);
		}
		file.Close();
	}

	cout << endl << "파일 저장 완료" << endl;
	system("pause");
}

void CEditorItem::LoadItem()
{
	Safe_Delete_VecList(m_vecWeapon);
	Safe_Delete_VecList(m_vecArmor);
	Safe_Delete_VecList(m_vecPosion);

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

	// 물약 상점 읽어오기
	if (file.Open("StorePosion.sps", "rb")) {
		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; i++) {

			CItem* pItem = new CItemPosion;

			if (!pItem->Init()) {
				SAFE_DELETE(pItem);
				return;
			}
			pItem->Load(&file);

			m_vecPosion.push_back(pItem);
		}

		file.Close();
	}

	cout << endl << "파일 불러오기 완료" << endl;
	system("pause");
}
