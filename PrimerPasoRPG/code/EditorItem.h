#pragma once

#include "value.h"

class CEditorItem
{
private:
	// 무기 상점, 방어구 상점 판매 목록을 따로 만들어주기 위해 변수 2개 선언
	vector<class CItem*> m_vecWeapon;
	vector<class CItem*> m_vecArmor;
	vector<class CItem*> m_vecPosion;

public:
	bool Init();
	void Run();

private:
	int OutputMenu();
	void InsertItem();
	void ModifyItem();
	void DeleteItem();
	void OutputWeaponList();
	void OutputArmorList();
	void OutputPosionList();
	void OutputItemList();
	void SaveItem();
	void LoadItem();


	DECLARE_SINGLE(CEditorItem)
};

