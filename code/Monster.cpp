#include "Monster.h"

CMonster::CMonster()
{
	m_eType = OT_MONSTER;
}

CMonster::CMonster(const CMonster& monster) :
	CCharacter(monster)
{
	m_iGoldMin = monster.m_iGoldMin;
	m_iGoldMax = monster.m_iGoldMax;
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	return true;
}

void CMonster::Render()
{
	cout << "�̸�: " << m_strName << endl;
	cout << "����: " << m_tInfo.iLevel << "\t\tȹ�� ����ġ: " << m_tInfo.iExp << endl;
	cout << "���ݷ�: " << m_tInfo.iAttackMin << " - " << m_tInfo.iAttackMax << "\t����: " << m_tInfo.iArmorMin << " - " << m_tInfo.iArmorMax << endl;
	cout << "ü��: " << m_tInfo.iHP << "\t����: " << m_tInfo.iMP << endl;
	cout << "ȹ�� �ݾ�: " << m_iGoldMin << " - " << m_iGoldMax << " Gold" << endl << endl;
}

CMonster* CMonster::Clone()
{
	// this�� �ڱ��ڽ��� �������̴�. �ڱ��ڽ��� �����͸� �������ϸ� �ڱ��ڽ� ��ü�� �ȴ�.
	// �׷��� ���� �Ҵ��ϴ� �÷��̾� ��ü�� �ڱ��ڽ��� �Ѱ��ְ� �ڱ��ڽ��� �����ϴ� �����ڸ� ȣ���Ͽ� �����ϵ��� ������ش�.
	// �̷��� ���ָ� "�� ��ü�� ������ ���ο� ��ü�� �����Ҵ��Ͽ� �� �޸� �ּҸ� ��ȯ"���ְ� �ȴ�.
	return new CMonster(*this);
}

