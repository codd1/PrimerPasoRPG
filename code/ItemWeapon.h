#pragma once

#include "Item.h"

class CItemWeapon :
    public CItem
{
protected:
	CItemWeapon();
	CItemWeapon(const CItemWeapon& item);
	virtual ~CItemWeapon();

private:
	// friend class = 나(CItemWeapon)는 CStore의 친구니까 private여도 멤버에 접근 가능해
	friend class CStore;
	friend class CStoreWeapon;

private:
	int m_iAttackMin;
	int m_iAttackMax;
	float m_fCritical;

public:
	int GetAttackMin() const {
		return m_iAttackMin;
	}
	int GetAttackMax() const {
		return m_iAttackMax;
	}
	float GetCritical() const {
		return m_fCritical;
	}

public:
	void SetWeaponInfo(int iAttackMin, int iAttackMax, float fCritical);

public:
	virtual bool Init();
	virtual void Render();
	virtual CItemWeapon* Clone();
};

