#pragma once
#include "Object.h"
class CCharacter :
	public CObject
{
protected:
	CCharacter();
	virtual ~CCharacter() = 0;

public:
	virtual bool Init();
};

