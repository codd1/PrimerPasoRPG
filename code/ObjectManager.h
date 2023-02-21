#pragma once

#include "value.h"

class CObject;
class CObjectManager
{
private:
	// map�� �⺻������ key, value�� �����Ǿ��ִ�.
	// ù ��° template Ÿ���� key, �� ��° template Ÿ���� value�̴�.
	// �׷��� Ÿ�� 2���� �������ְ� key�� �̿��ؼ� Ž���� �ϰ� �ȴ�.
	// ���� ���� value�� �����ϴ� ���̴�. (������ Ÿ���� ��)
	unordered_map<string, CObject*> m_mapObj;
public:
	bool Init();
	CObject* CreateObject(const string& strKey, OBJECT_TYPE eType);

	DECLARE_SINGLE(CObjectManager)
};

