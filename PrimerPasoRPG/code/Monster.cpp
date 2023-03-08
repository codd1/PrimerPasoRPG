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
	m_eStageType = monster.m_eStageType;
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
	cout << "�̸�: " << m_strName;
	switch (m_eStageType) {
	case ST_EASY:
		cout << "\t���̵�: Easy" << endl;
		break;
	case ST_NORMAL:
		cout << "\t���̵�: Normal" << endl;
		break;
	case ST_HARD:
		cout << "\t���̵�: Hard" << endl;
		break;
	}
	cout << "����: " << m_tInfo.iLevel << "\t\tü��: " << m_tInfo.iHP << " / " << m_tInfo.iHPMax << endl;
	cout << "���ݷ�: " << m_tInfo.iAttackMin << " - " << m_tInfo.iAttackMax;
	cout << "\t����: " << m_tInfo.iArmor;
	cout << "\tġ��Ÿ��: " << m_tInfo.fCritical << endl;
	cout << "ȹ�� ����ġ : " << m_tInfo.iExp << "\t\tȹ�� �ݾ� : " << m_iGoldMin << " - " << m_iGoldMax << " Gold" << endl << endl;
}

CMonster* CMonster::Clone()
{
	// this�� �ڱ��ڽ��� �������̴�. �ڱ��ڽ��� �����͸� �������ϸ� �ڱ��ڽ� ��ü�� �ȴ�.
	// �׷��� ���� �Ҵ��ϴ� �÷��̾� ��ü�� �ڱ��ڽ��� �Ѱ��ְ� �ڱ��ڽ��� �����ϴ� �����ڸ� ȣ���Ͽ� �����ϵ��� ������ش�.
	// �̷��� ���ָ� "�� ��ü�� ������ ���ο� ��ü�� �����Ҵ��Ͽ� �� �޸� �ּҸ� ��ȯ"���ְ� �ȴ�.
	return new CMonster(*this);
}

void CMonster::Save(CFileStream* pFile)
{
	// �θ� Ŭ������ �Լ��� Ÿ�� Ÿ�� �Ѿ�� ������ ���� Ŭ�������� �� �� �ִ� ���� ���� Ŭ�������� �ϵ����Ͽ�,
	// �θ� Ŭ�������� �ߴ� ���� �ʿ��� ���� �θ�Ŭ������ ȣ���ϸ� �ǵ����ϱ� ���ؼ��̴�. (���߿� ����)
	CCharacter::Save(pFile);

	// ���� ����� �߰��Ѵ�.
	pFile->Write(&m_iGoldMin, 4);
	pFile->Write(&m_iGoldMax, 4);
	pFile->Write(&m_eStageType, 4);
}

void CMonster::Load(CFileStream* pFile)
{
	CCharacter::Load(pFile);

	pFile->Read(&m_iGoldMin, 4);
	pFile->Read(&m_iGoldMax, 4);
	pFile->Read(&m_eStageType, 4);
}

