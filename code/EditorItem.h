#pragma once

#include "value.h"

class CEditorItem
{
private:
	// ���� ����, �� ���� �Ǹ� ����� ���� ������ֱ� ���� ���� 2�� ����
	vector<class CItem*> m_vecWeapon;
	vector<class CItem*> m_vecArmor;

public:
	bool Init();
	void Run();

private:
	int OutputMenu();
	void InsertItem();
	void OutputItemList();
	void SaveItem();
	void LoadItem();


	DECLARE_SINGLE(CEditorItem)
};

