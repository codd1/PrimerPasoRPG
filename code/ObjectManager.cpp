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
	// �÷��̾ �����Ѵ�.
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

	// ���� key�� value�� �̿��ؼ� �����͸� �����ϱ� ������
	// make_pair�� �̿��� key�� value�� pair(��)���� ���� �־��ش�.
	m_mapObj.insert(make_pair(strKey, pObj));

	return pObj;
}
