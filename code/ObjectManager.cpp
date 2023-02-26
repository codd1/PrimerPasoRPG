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
	// �÷��̾ �����Ѵ�.
	CObject* pPlayer = CreateObject("Player", OT_PLAYER);

	//CObject* pPlayer1 = pPlayer->Clone();

	// ���� ��� ������ �о�´�.
	CFileStream file("MonsterList.mtl", "rb");

	if (file.GetOpen()) {		// ������ ���� ���
		int iMonsterCount = 0;

		file.Read(&iMonsterCount, 4);

		for (int i = 0; i < iMonsterCount; i++) {
			CMonster* pMonster = new CMonster;
			pMonster->Load(&file);

			m_mapObj.insert(make_pair(pMonster->GetName(), pMonster));
		}
	}
	else {		// ������ ���� ��� (�⺻ ��)
		// CreateObject �Լ��� ���͸� �����ϰ� CObject* Ÿ���� �����Ѵ�.
		// �׷��� ������ �⺻ �������� Monster Ŭ������ Character Ŭ������ ������ �����Ƿ� ���� Ŭ������ ����ȯ�Ͽ� �����صΰ� ����� ����Ѵ�.
		CMonster* pMonster = (CMonster*)CreateObject("Goblin", OT_MONSTER);
		pMonster->SetName("���");
		pMonster->SetCharacterInfo(10, 20, 3, 5, 100, 10, 1, 1000);
		pMonster->SetGold(1000, 2000);

		pMonster = (CMonster*)CreateObject("Troll", OT_MONSTER);
		pMonster->SetName("Ʈ��");
		pMonster->SetCharacterInfo(50, 80, 40, 60, 2000, 300, 5, 7000);
		pMonster->SetGold(5000, 10000);

		pMonster = (CMonster*)CreateObject("Dragon", OT_MONSTER);
		pMonster->SetName("�巡��");
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

	// ���� key�� value�� �̿��ؼ� �����͸� �����ϱ� ������
	// make_pair�� �̿��� key�� value�� pair(��)���� ���� �־��ش�.
	m_mapObj.insert(make_pair(strKey, pObj));

	return pObj;
}

CObject* CObjectManager::FindObject(const string& strKey) {
	// map�� find �Լ��� �������ش�. find �Լ��� key�� �־��ָ� �ش� Ű�� Ž���Ͽ� Ű�� ���� ��� �ش� Ű�� iterator�� ��ȯ�ϰ� ���� ��� end()�� ��ȯ�Ѵ�.
	unordered_map<string, CObject*>::iterator iter = m_mapObj.find(strKey);

	// end()�� ���� ã�� ���ߴٴ� ���̴�.
	if (iter == m_mapObj.end()) {
		return NULL;
	}
	return iter->second;
}

// ���ڷ� ������ Ű�� �̿��ؼ� ��ü�� ã�� �Ŀ� �ش� ��ü�� �����ؼ� ������ �� ��ȯ���ִ� �Լ�
CObject* CObjectManager::CloneObject(const string& strKey) {

	// ������ ���� ��ü�� ã�´�.
	CObject* pOrigin = FindObject(strKey);

	// ã�� ���ߴٸ�
	if (!pOrigin) {
		return NULL;
	}

	// ���� ã�Ҵٸ� ���� ��ü�� ������ ���ο� ��ü�� ���� ��ȯ�Ѵ�.
	return pOrigin->Clone();
}

CObject* CObjectManager::CloneObject(STAGE_TYPE eType) {

	vector<CMonster*> vecMonster;

	unordered_map<string, CObject*>::iterator iter;

	for (iter = m_mapObj.begin(); iter != m_mapObj.end(); iter++) {
		if (iter->second->GetObjectType() == OT_MONSTER) {
			// iter�� CObject* Ÿ���̹Ƿ� CMonster*�� ĳ����
			CMonster* pMonster = (CMonster*)iter->second;

			if (pMonster->GetStageType() == eType) {
				vecMonster.push_back(pMonster);
			}
		}
	}

	// ��ϵ� ���Ͱ� ���� ���
	if (vecMonster.empty()) {
		return NULL;
	}

	int idx = rand() % vecMonster.size();

	// ��ϵǾ��ִ� ���� �� ������ ���͸� ������ ����
	return vecMonster[idx]->Clone();
}