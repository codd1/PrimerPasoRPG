#pragma once
#include "Store.h"

class CStorePosion :
    public CStore
{
private:
	CStorePosion();
	~CStorePosion();

private:
	friend class CStoreManager;

public:
	virtual bool Init();
	virtual void Run();
};

