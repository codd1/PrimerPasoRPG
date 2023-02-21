#pragma once
#include "Object.h"
class CCharacter :
	public CObject
{
protected:
	CCharacter();
	CCharacter(const CCharacter& character);
	virtual ~CCharacter() = 0;

protected:
	CHARACTERINFO m_tInfo;
public:
	CHARACTERINFO GetCharacterInfo() const {
		return m_tInfo;
	}

	void SetCharacterInfo(int iAtMin, int iAtMax, int iArMin, int iArMax, int iHP, int iMP, int iLevel, int iExp);
public:
	virtual bool Init();
	virtual void Render();
};

