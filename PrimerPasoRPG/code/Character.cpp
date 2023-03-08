#include "Character.h"
#include "FileStream.h"

CCharacter::CCharacter()
{
}

// Object 복사생성자를 먼저 호출하여 Object의 값을 복사하고 character의 값을 복사한다.
CCharacter::CCharacter(const CCharacter& character) :
	CObject(character)
{
	m_tInfo = character.m_tInfo;
}

CCharacter::~CCharacter()
{
}

void CCharacter::SetAttackMin(int iAttackMin)
{
	m_tInfo.iAttackMin = iAttackMin;
}

void CCharacter::SetAttackMax(int iAttackMax)
{
	m_tInfo.iAttackMax = iAttackMax;
}

void CCharacter::SetCritical(float fCritical)
{
	m_tInfo.fCritical = fCritical;
}

void CCharacter::SetArmor(int iArmor)
{
	m_tInfo.iArmor = iArmor;
}

void CCharacter::SetHP(int iHP)
{
	m_tInfo.iHP = iHP;
}

void CCharacter::SetMPUse(int iMPUse)
{
	m_tInfo.iMPUse = iMPUse;
}

void CCharacter::SetMP(int iMP)
{
	m_tInfo.iMP = iMP;
}

void CCharacter::SetLevel(int iLevel)
{
	m_tInfo.iLevel = iLevel;
}

void CCharacter::SetExp(int iExp)
{
	m_tInfo.iExp = iExp;
}

void CCharacter::SetCharacterInfo(int iAtMin, int iAtMax, float fCritical, int iArmor, int iHP, int iMPUse, int iMP, int iLevel, int iExp)
{
	m_tInfo.iAttackMin = iAtMin;
	m_tInfo.iAttackMax = iAtMax;
	m_tInfo.fCritical = fCritical;
	m_tInfo.iArmor = iArmor;
	m_tInfo.iHP = iHP;
	m_tInfo.iHPMax = iHP;
	m_tInfo.iMPUse = iMPUse;
	m_tInfo.iMP = iMP;
	m_tInfo.iMPMax = iMP;
	m_tInfo.iLevel = iLevel;
	m_tInfo.iExp = iExp;
}

bool CCharacter::Damage(int iDamage)
{
	m_tInfo.iHP -= iDamage;

	// 캐릭터 사망 시 true (iHP <= 0)
	return m_tInfo.iHP <= 0;
}

bool CCharacter::AddExp(int iExp)
{
	m_tInfo.iExp += iExp;

	// false 리턴 시에는 레벨업 X
	return false;
}

bool CCharacter::CheckLevelUp()
{
	if (g_iLvUpTable[m_tInfo.iLevel - 1] <= m_tInfo.iExp) {
		return true;
	}
	
	return false;
}

void CCharacter::DropExp()
{
	// 갖고 있던 경험치를 10% 떨군다.
	m_tInfo.iExp -= m_tInfo.iExp * 0.1f;
}

void CCharacter::FullHPMP()
{
	m_tInfo.iHP = m_tInfo.iHPMax;
	m_tInfo.iMP = m_tInfo.iMPMax;
}

void CCharacter::LevelUp()
{
	// 레벨업테이블에 입력되어있는만큼 경험치 감소
	m_tInfo.iExp -= g_iLvUpTable[m_tInfo.iLevel - 1];

	// 레벨업
	m_tInfo.iLevel++;
}

void CCharacter::AddLevelUpStatus(const LEVELUPINFO& tInfo)
{
	m_tInfo.iAttackMin += tInfo.iAttackMin;
	m_tInfo.iAttackMax += tInfo.iAttackMax;
	m_tInfo.iArmor += tInfo.iArmor;

	// 레벨업 했으므로 최대 체력, 마나를 바꾸고 체력과 마나를 풀로 채워준다.
	m_tInfo.iHPMax += tInfo.iHP;
	m_tInfo.iHP = m_tInfo.iHPMax;
	m_tInfo.iMPMax += tInfo.iMP;
	m_tInfo.iMP = m_tInfo.iMPMax;
}

bool CCharacter::Init()
{
	return true;
}

void CCharacter::Render()
{
}

void CCharacter::Save(CFileStream* pFile)
{
	CObject::Save(pFile);

	pFile->Write(&m_tInfo, sizeof(m_tInfo));
}

void CCharacter::Load(CFileStream* pFile)
{
	CObject::Load(pFile);

	pFile->Read(&m_tInfo, sizeof(m_tInfo));
}
