#pragma once
#include "Character.h"
class CPlayer :
	public CCharacter
{
private:
	enum EQUIP {
		EQ_WEAPON,
		EQ_ARMOR,
		EQ_END
	};

private:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

private:
	friend class CObjectManager;

private:
	JOB m_eJob;
	string m_strJobName;
	int m_iGold = 10000;		// ±âº» 10000 Gold
	class CItem* m_pEquip[EQ_END];

public:
	JOB GetJob() const {
		return m_eJob;
	}
	void AddGold(int iGold);
	void DropGold();

	int GetGold() const {
		return m_iGold;
	}
	
	class CItem* GetEquip(EQUIP eq) const {
		return m_pEquip[eq];
	}

	bool CheckMP();

	virtual int GetDamage();
	virtual int GetArmor();

public:
	class CItem* Equip(class CItem* pItem);

public:
	virtual bool Init();
	virtual void Render();
	virtual CPlayer* Clone();

};

