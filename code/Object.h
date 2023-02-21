#pragma once

#include "value.h"

class CObject
{
protected:
	CObject();
	virtual ~CObject() = 0;

private:
	friend class CObjectManager;

public:
	virtual bool Init();
};

