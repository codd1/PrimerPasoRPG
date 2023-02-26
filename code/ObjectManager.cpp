#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "FileStream.h"

DEFINITION_SINGLE(CObjectManager)

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	// 플레이어를 생성한다.
	CObject* pPlayer = CreateObject("Player", OT_PLAYER);

	//CObject* pPlayer1 = pPlayer->Clone();

	// 몬스터 목록 파일을 읽어온다.
	CFileStream file("MonsterList.mtl", "rb");

	if (file.GetOpen()) {		// 파일이 있을 경우
		int iMonsterCount = 0;

		file.Read(&iMonsterCount, 4);

		for (int i = 0; i < iMonsterCount; i++) {
			CMonster* pMonster = new CMonster;
			pMonster->Load(&file);

			m_mapObj.insert(make_pair(pMonster->GetName(), pMonster));
		}
	}
	else {		// 파일이 없을 경우 (기본 값)
		// CreateObject 함수는 몬스터를 생성하고 CObject* 타입을 리턴한다.
		// 그런데 몬스터의 기본 변수들은 Monster 클래스나 Character 클래스가 가지고 있으므로 몬스터 클래스로 형변환하여 저장해두고 기능을 사용한다.
		CMonster* pMonster = (CMonster*)CreateObject("Goblin", OT_MONSTER);
		pMonster->SetName("고블린");
		pMonster->SetCharacterInfo(10, 20, 3, 5, 100, 10, 1, 1000);
		pMonster->SetGold(1000, 2000);

		pMonster = (CMonster*)CreateObject("Troll", OT_MONSTER);
		pMonster->SetName("트롤");
		pMonster->SetCharacterInfo(50, 80, 40, 60, 2000, 300, 5, 7000);
		pMonster->SetGold(5000, 10000);

		pMonster = (CMonster*)CreateObject("Dragon", OT_MONSTER);
		pMonster->SetName("드래곤");
		pMonster->SetCharacterInfo(150, 250, 150, 250, 10000, 10000, 10, 25000);
		pMonster->SetGold(30000, 50000);
	}

	return true;
}

CObject* CObjectManager::CreateObject(const string& strKey, OBJECT_TYPE eType)
{
	CObject* pObj = NULL;

	switch (eType) {
	case OT_PLAYER:
		pObj = new CPlayer;
		break;
	case OT_MONSTER:
		pObj = new CMonster;
		break;
	}

	if (!pObj->Init()) {
		SAFE_DELETE(pObj);
		return NULL;
	}

	// 맵은 key와 value를 이용해서 데이터를 관리하기 때문에
	// make_pair를 이용해 key와 value를 pair(쌍)으로 만들어서 넣어준다.
	m_mapObj.insert(make_pair(strKey, pObj));

	return pObj;
}

CObject* CObjectManager::FindObject(const string& strKey) {
	// map은 find 함수를 제공해준다. find 함수에 key를 넣어주면 해당 키를 탐색하여 키가 있을 경우 해당 키의 iterator를 반환하고 없을 경우 end()를 반환한다.
	unordered_map<string, CObject*>::iterator iter = m_mapObj.find(strKey);

	// end()일 경우는 찾지 못했다는 것이다.
	if (iter == m_mapObj.end()) {
		return NULL;
	}
	return iter->second;
}

// 인자로 들어오는 키를 이용해서 객체를 찾은 후에 해당 객체를 복사해서 생성한 후 반환해주는 함수
CObject* CObjectManager::CloneObject(const string& strKey) {

	// 복사할 원본 객체를 찾는다.
	CObject* pOrigin = FindObject(strKey);

	// 찾지 못했다면
	if (!pOrigin) {
		return NULL;
	}

	// 만약 찾았다면 원본 객체를 복사한 새로운 객체를 만들어서 반환한다.
	return pOrigin->Clone();
}

CObject* CObjectManager::CloneObject(STAGE_TYPE eType) {

	vector<CMonster*> vecMonster;

	unordered_map<string, CObject*>::iterator iter;

	for (iter = m_mapObj.begin(); iter != m_mapObj.end(); iter++) {
		if (iter->second->GetObjectType() == OT_MONSTER) {
			// iter는 CObject* 타입이므로 CMonster*로 캐스팅
			CMonster* pMonster = (CMonster*)iter->second;

			if (pMonster->GetStageType() == eType) {
				vecMonster.push_back(pMonster);
			}
		}
	}

	// 등록된 몬스터가 없을 경우
	if (vecMonster.empty()) {
		return NULL;
	}

	int idx = rand() % vecMonster.size();

	// 등록되어있는 몬스터 중 랜덤한 몬스터를 복사해 리턴
	return vecMonster[idx]->Clone();
}