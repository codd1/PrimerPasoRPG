#include "Character.h"

CCharacter::CCharacter()
{
}

// Object ��������ڸ� ���� ȣ���Ͽ� Object�� ���� �����ϰ� character�� ���� �����Ѵ�.
CCharacter::CCharacter(const CCharacter& character):
	CObject(character)
{
	m_tInfo = character.m_tInfo;
}

CCharacter::~CCharacter()
{
}

void CCharacter::SetCharacterInfo(int iAtMin, int iAtMax, int iArMin, int iArMax, int iHP, int iMP, int iLevel, int iExp)
{
	m_tInfo.iAttackMin = iAtMin;
	m_tInfo.iAttackMax = iAtMax;
	m_tInfo.iArmorMin = iArMin;
	m_tInfo.iArmorMax = iArMax;
	m_tInfo.iHP = iHP;
	m_tInfo.iHPMax = iHP;
	m_tInfo.iMP = iMP;
	m_tInfo.iMPMax = iMP;
	m_tInfo.iLevel = iLevel;
	m_tInfo.iExp = iExp;
}

bool CCharacter::Damage(int iDamage)
{
	m_tInfo.iHP -= iDamage;

	// ĳ���� ��� �� true (iHP <= 0)
	return m_tInfo.iHP <= 0;
}

bool CCharacter::AddExp(int iExp)
{
	m_tInfo.iExp += iExp;
	
	// false ���� �ÿ��� ������ X
	return false;
}

bool CCharacter::CheckLevelUp()
{
	return false;
}

void CCharacter::DropExp()
{
	// ���� �ִ� ����ġ�� 10% ������.
	m_tInfo.iExp -= m_tInfo.iExp * 0.1f;
}

void CCharacter::FullHPMP()
{
	m_tInfo.iHP = m_tInfo.iHPMax;
	m_tInfo.iMP = m_tInfo.iMPMax;
}

bool CCharacter::Init()
{
	return true;
}

void CCharacter::Render()
{
}