#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"

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
