#pragma once
#include "Character.h"
class CMonster :
    public CCharacter
{
private:
    CMonster();
    CMonster(const CMonster& monster);
public:
    ~CMonster();

private:
    friend class CObjectManager;

private:
    int m_iGoldMin;
    int m_iGoldMax;

public:
    void SetGold(int iMin, int iMax) {
        m_iGoldMin = iMin;
        m_iGoldMax = iMax;
    }

public:
    // 멤버함수 뒤에 const를 붙이면 이 함수 내에서 멤버변수의 값을 변경할 수 없다. 
    int GetGoldMin()    const {
        return m_iGoldMin;
    }
    int GetGoldMax()    const {
        return m_iGoldMax;
    }

public:
    virtual bool Init();
    virtual void Render();
    virtual CMonster* Clone();
};

