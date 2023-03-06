#pragma once

#include "value.h"
#include "conio.h"

class CCore
{
private:
	LEVELUPINFO m_tLevelUpInfo[JOB_END - 1];	// 직업은 총 3개이므로 인덱스계산해 -1
public:
	LEVELUPINFO GetLevelUpInfo(JOB eJob);

public:
	bool Init();
	void Run();
private:
	int OutputMenu();
	void SetLevelUpInfo();
	LEVELUPINFO CreateLevelUpInfo(int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, int iHP, int iMP);
	void OutputGameInfo();
	void CheckExit();

	DECLARE_SINGLE(CCore)
};

