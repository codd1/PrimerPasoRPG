#pragma once

#include "value.h"

enum STAGE_TYPE {
	ST_NONE,
	ST_EASY,
	ST_NORMAL,
	ST_HARD,
	ST_BACK
};

class CStageManager
{
private:
	vector<class CStage*> m_vecStage;

	enum MENU {
		MENU_NONE,
		MENU_EASY,
		MENU_NORMAL,
		MENU_HARD,
		MENU_BACK
	};
public:
	bool Init();
	void Run();

private:
	bool CreateStage(STAGE_TYPE eType);
	int OutputMenu();

	DECLARE_SINGLE(CStageManager)
};

