#pragma once
#include "Object.h"
class CCharacter :
	public CObject
{
protected:
	CCharacter();
	CCharacter(const CCharacter& character);
	virtual ~CCharacter() = 0;

public:
	CHARACTERINFO m_tInfo;

public:
	void SetAttackMin(int iAttackMin);
	void SetAttackMax(int iAttackMax);
	void SetCritical(float fCritical);
	void SetArmor(int iArmor);
	void SetHP(int iHP);
	void SetMP(int iMP);
	void SetLevel(int iLevel);
	void SetExp(int iExp);
public:
	CHARACTERINFO GetCharacterInfo() const {
		return m_tInfo;
	}

	void SetCharacterInfo(int iAtMin, int iAtMax, float fCritical, int iArmor, int iHP, int iMP, int iLevel, int iExp);

	virtual int GetDamage() {
		// iAttackMin ~ iAttackMax 사이의 랜덤한 값 리턴
		return rand() % (m_tInfo.iAttackMax - m_tInfo.iAttackMin + 1) + m_tInfo.iAttackMin;
	}
	virtual int GetArmor() {
		return m_tInfo.iArmor;
	}

	bool Damage(int iDamage);
	bool AddExp(int iExp);
	bool CheckLevelUp();
	void DropExp();
	void FullHPMP();
	void LevelUp();
	void AddLevelUpStatus(const LEVELUPINFO& tInfo);
public:
	virtual bool Init();
	virtual void Render();
	virtual CCharacter* Clone() = 0;
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

