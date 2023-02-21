#pragma once
#include "Character.h"
class CMonster :
    public CCharacter
{
private:
    CMonster();
    ~CMonster();

private:
    friend class CObjectManager;

public:
    virtual bool Init();
};

