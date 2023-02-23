#pragma once

#include "Item.h"

class CItemArmor :
    public CItem
{
protected:
	CItemArmor();
	CItemArmor(const CItemArmor& item);
	virtual ~CItemArmor();

private:
	friend class CStore;
	friend class CStoreArmor;

private:
	int m_iArmorMin;
	int m_iArmorMax;

public:
	void SetArmorInfo(int iArmorMin, int iArmorMax);

public:
	virtual bool Init();
	virtual void Render();
	virtual CItemArmor* Clone();
};

