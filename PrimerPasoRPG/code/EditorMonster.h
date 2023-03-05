#pragma once

#include "value.h"

class CEditorMonster
{
private:
	vector<class CMonster*> m_vecMonster;
public:
	bool Init();
	void Run();

private:
	int OutputMenu();
	void InsertMonster();
	void ModifyMonster();
	void DeleteMonster();
	void OutputMonsterList();
	void SaveMonster();
	void LoadMonster();

	DECLARE_SINGLE(CEditorMonster)
};

