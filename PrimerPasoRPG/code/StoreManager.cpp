#include "StoreManager.h"
#include "StoreWeapon.h"
#include "StoreArmor.h"
#include "StorePosion.h"

DEFINITION_SINGLE(CStoreManager)

CStoreManager::CStoreManager() {

}

CStoreManager::~CStoreManager() {
	Safe_Delete_VecList(m_vecStore);
}

bool CStoreManager::Init()
{
	// ������� ����
	CStore* pStore = CreateStore(STR_WEAPON);

	// ������ ����
	pStore = CreateStore(STR_ARMOR);

	// ������� ����
	pStore = CreateStore(STR_POSION);

	return true;
}

void CStoreManager::Run()
{
	while (true) {
		int iMenu = OutputMenu();

		if (iMenu == STR_NONE) {
			continue;
		}
		else if (iMenu == STR_BACK) {
			break;
		}

		m_vecStore[iMenu - 1]->Run();
	}
}

CStore* CStoreManager::CreateStore(STORE_TYPE eType)
{
	CStore* pStore = NULL;
	
	switch (eType) {
	case STR_WEAPON:
		pStore = new CStoreWeapon;
		break;
	case STR_ARMOR:
		pStore = new CStoreArmor;
		break;
	case STR_POSION:
		pStore = new CStorePosion;
		break;
	}

	if (!pStore->Init()) {
		SAFE_DELETE(pStore);
		return NULL;
	}

	m_vecStore.push_back(pStore);

	return pStore;
}

int CStoreManager::OutputMenu()
{
	system("cls");
	cout << "1. ���� ����" << endl;
	cout << "2. �� ����" << endl;
	cout << "3. ���� ����" << endl;
	cout << "4. �ڷΰ���" << endl;
	cout << "������ �����ϼ���: ";
	int iStore = Input<int>();

	if (iStore <= STR_NONE || iStore > STR_BACK) {
		return STR_NONE;
	}

	return iStore;
}
