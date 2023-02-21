#pragma once

#include "value.h"

class CObject;
class CObjectManager
{
private:
	// map은 기본적으로 key, value로 구성되어있다.
	// 첫 번째 template 타입이 key, 두 번째 template 타입이 value이다.
	// 그래서 타입 2개를 지정해주고 key를 이용해서 탐색을 하게 된다.
	// 실제 값은 value에 저장하는 것이다. (지정된 타입의 값)
	unordered_map<string, CObject*> m_mapObj;
public:
	bool Init();
	CObject* CreateObject(const string& strKey, OBJECT_TYPE eType);

	DECLARE_SINGLE(CObjectManager)
};

