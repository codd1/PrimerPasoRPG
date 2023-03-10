#pragma once

#include "value.h"

class CInventory
{
private:
	vector<class CItem*> m_vecItem;
	int m_iInvenMax;

public:
	void SetInvenMax(int iMax) {
		m_iInvenMax = iMax;
	}
	int GetInvenMax() const {
		return m_iInvenMax;
	}
	bool InvenFull() const {
		return m_iInvenMax == m_vecItem.size();
	}

public:
	bool init();
	void Additem(class CItem* pItem);
	void Run();
	
public:
	int OutputTab();
	void EquipItemTab();
	void ConsumableItemTab();

	DECLARE_SINGLE(CInventory)
};

