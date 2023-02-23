#include "Player.h"

//enum JOB {
//	JOB_NONE,
//	JOB_KNIGHT,
//	JOB_ARCHER,
//	JOB_WIZARD,
//	JOB_END
//};

CPlayer::CPlayer()
{
	m_eType = OT_PLAYER;
}

CPlayer::CPlayer(const CPlayer& player) :
	CCharacter(player)
{
	m_eJob = player.m_eJob;
	m_strJobName = player.m_strJobName;
	m_iGold = player.m_iGold;
}

CPlayer::~CPlayer()
{
}

void CPlayer::AddGold(int iGold)
{
	m_iGold += iGold;
}

void CPlayer::DropGold()
{
	m_iGold -= m_iGold * 0.1f;
}

bool CPlayer::Init()
{
	cout << "이름을 입력하세요: ";
	char strName[31];
	cin.getline(strName, 31);
	SetName(strName);

	int iJob;

	while (true) {
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요: ";
		iJob = Input<int>();

		if (iJob < JOB_KNIGHT || iJob >= JOB_END) {
			continue;
		}
		break;
	}

	m_eJob = (JOB)iJob;

	switch (m_eJob) {
	case JOB_KNIGHT:
		m_strJobName = "기사";
		SetCharacterInfo(10, 15, 15, 20, 500, 100, 1, 0);
		break;
	case JOB_ARCHER:
		m_strJobName = "궁수";
		SetCharacterInfo(15, 20, 10, 15, 400, 200, 1, 0);
		break;
	case JOB_WIZARD:
		m_strJobName = "마법사";
		SetCharacterInfo(20, 25, 5, 10, 300, 300, 1, 0);
		break;
	}

	return true;
}

void CPlayer::Render()
{
	cout << "이름: " << m_strName << "\t직업: " << m_strJobName << endl;
	cout << "레벨: " << m_tInfo.iLevel << "\t\t경험치: " << m_tInfo.iExp << endl;
	cout << "공격력: " << m_tInfo.iAttackMin << " - " << m_tInfo.iAttackMax << "\t방어력: " << m_tInfo.iArmorMin << " - " << m_tInfo.iArmorMax << endl;
	cout << "체력: " << m_tInfo.iHP << " / " << m_tInfo.iHPMax << "\t마나: " << m_tInfo.iMP << " / " << m_tInfo.iMPMax << endl;
	cout << "보유 금액: " << m_iGold << " Gold" << endl << endl;

}

CPlayer* CPlayer::Clone()
{
	// this는 자기자신의 포인터이다. 자기자신의 포인터를 역참조하면 자기자신 자체가 된다.
	// 그래서 새로 할당하는 플레이어 객체에 자기자신을 넘겨주고 자기자신을 복사하는 생성자를 호출하여 생성하도록 만들어준다.
	// 이렇게 해주면 "이 객체를 복사한 새로운 객체를 동적할당하여 그 메모리 주소를 반환"해주게 된다.
	return new CPlayer(*this);
}
