
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

typedef struct _tagLevelUpInfo {
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iMP;
}LEVELUPINFO, *PLEVELUPINFO;

#define MAX_LEVEL 10

// 경험치를 250000 먹어도 10레벨에 멈춰있고 더 이상 오르지 않는다. (사양)
static int g_iLvUpTable[MAX_LEVEL] = { 4000,10000,20000,35000,52000,72000,90000,130000, 170000,250000 };

// Item Information
typedef struct _tagItemInfo {
	ITEM_TYPE eType;
	string strTypeName;
	int iPrice;
	int iSell;
	string strDesc;		// 아이템 설명
}ITEMINFO, *PITEMINFO;