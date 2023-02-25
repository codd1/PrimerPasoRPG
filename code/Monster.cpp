#include "Monster.h"
#include "FileStream.h"

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
	cout << "이름: " << m_strName << endl;
	cout << "레벨: " << m_tInfo.iLevel << "\t\t획득 경험치: " << m_tInfo.iExp << endl;
	cout << "공격력: " << m_tInfo.iAttackMin << " - " << m_tInfo.iAttackMax << "\t방어력: " << m_tInfo.iArmorMin << " - " << m_tInfo.iArmorMax << endl;
	cout << "체력: " << m_tInfo.iHP << " / " << m_tInfo.iHPMax << "\t마나: " << m_tInfo.iMP << " / " << m_tInfo.iMPMax << endl;
	cout << "획득 금액: " << m_iGoldMin << " - " << m_iGoldMax << " Gold" << endl << endl;
}

CMonster* CMonster::Clone()
{
	// this는 자기자신의 포인터이다. 자기자신의 포인터를 역참조하면 자기자신 자체가 된다.
	// 그래서 새로 할당하는 플레이어 객체에 자기자신을 넘겨주고 자기자신을 복사하는 생성자를 호출하여 생성하도록 만들어준다.
	// 이렇게 해주면 "이 객체를 복사한 새로운 객체를 동적할당하여 그 메모리 주소를 반환"해주게 된다.
	return new CMonster(*this);
}

void CMonster::Save(CFileStream* pFile)
{
	// 부모 클래스의 함수로 타고 타고 넘어가는 이유는 하위 클래스에서 할 수 있는 일은 하위 클래스에서 하도록하여,
	// 부모 클래스에서 했던 일이 필요할 때는 부모클래스만 호출하면 되도록하기 위해서이다. (나중에 편리함)
	CCharacter::Save(pFile);

	// 나의 기능을 추가한다.
	pFile->Write(&m_iGoldMin, 4);
	pFile->Write(&m_iGoldMax, 4);
}

void CMonster::Load(CFileStream* pFile)
{
	CCharacter::Load(pFile);

	pFile->Read(&m_iGoldMin, 4);
	pFile->Read(&m_iGoldMax, 4);
}

