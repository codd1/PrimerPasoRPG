#pragma once

#include "value.h"

class CStore
{
protected:
	CStore();

public:
	virtual ~CStore();

private:
	friend class CStoreManager;

protected:
	vector<class CItem*> m_vecItem;

protected:
	CItem* CreateItem(const char* strName, ITEM_TYPE eType, int iPrice, int iSell, const char* pDesc);
	void OutputItemList();
	void OutputTag(const char* pStoreName);

public:
	virtual bool Init() = 0;
	virtual void Run() = 0;
};

