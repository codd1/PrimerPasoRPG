
#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <time.h>

using namespace std;

// 사용자정의 헤더
#include "defines.h"
#include "Flags.h"

template <typename T>
T Input() {
	T data;
	cin >> data;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return 0;
	}
	return data;
}

template <typename T>
void Safe_Delete_VecList(T &p) {
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++) {
		SAFE_DELETE(*iter);
	}
	p.clear();
}

template <typename T>
void Safe_Delete_Map(T& p) {
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++) {
		SAFE_DELETE(iter->second);		// first: key, second: value
	}
	p.clear();
}

//enum JOB {
//	JOB_NONE,
//	JOB_KNIGHT,
//	JOB_ARCHER,
//	JOB_WIZARD,
//	JOB_END
//};

// Character Information
typedef struct _tagCharacterInfo
{
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
}CHARACTERINFO, * PCHARACTERINFO;

// Item Information
typedef struct _tagItemInfo {
	ITEM_TYPE eType;
	string strTypeName;
	int iPrice;
	int iSell;
	string strDesc;		// 아이템 설명
}ITEMINFO, *PITEMINFO;