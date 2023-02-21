#pragma once

#include "value.h"

class CCore
{
public:
	bool Init();
	void Run();
private:
	int OutputMenu();

	DECLARE_SINGLE(CCore)
};

