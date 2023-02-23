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

public:
	virtual bool Init() = 0;
	virtual void Run() = 0;
};

