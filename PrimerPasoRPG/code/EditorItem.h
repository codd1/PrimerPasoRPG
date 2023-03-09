#pragma once

#include "value.h"

class CEditorItem
{
private:
	// ���� ����, �� ���� �Ǹ� ����� ���� ������ֱ� ���� ���� 2�� ����
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

