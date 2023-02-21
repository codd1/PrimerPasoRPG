#pragma once
#include "Character.h"
class CPlayer :
    public CCharacter
{
private:
    CPlayer();
    CPlayer(const CPlayer& player);
    ~CPlayer();

private:
    friend class CObjectManager;

private:
    JOB m_eJob;
    string m_strJobName;
    int m_iGold;

public:
    virtual bool Init();
    virtual void Render();
    virtual CPlayer* Clone();
};

