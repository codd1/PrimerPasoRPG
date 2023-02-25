#pragma once
#include "Character.h"
class CPlayer :
	public CCharacter
{
private:
	enum JOB {
		JOB_NONE,
		JOB_KNIGHT,
		JOB_ARCHER,
		JOB_WIZARD,
		JOB_END
	};

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
	int m_iGold = 10000;		// �⺻ 10000 Gold
	class CItem* m_pEquip[EQ_END];

public:
	void AddGold(int iGold);
	void DropGold();

	int GetGold() const {
		return m_iGold;
	}
	
	class CItem* GetEquip(EQUIP eq) const {
		return m_pEquip[eq];
	}

	virtual int GetDamage();
	virtual int GetArmor();

public:
	class CItem* Equip(class CItem* pItem);

public:
	virtual bool Init();
	virtual void Render();
	virtual CPlayer* Clone();

};

