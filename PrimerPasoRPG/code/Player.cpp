#include "Player.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"

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
	// ������ ���� �迭 2��¥���� 0���� �ʱ�ȭ�Ѵ�.
	// EQ_END�� 2�̹Ƿ� ������ ����ũ�� 4*2�� �Ǿ� 8����Ʈ�� 0���� �ʱ�ȭ�Ѵ�.
	// ��, ������ ���� 2���� NULL �����ͷ� �ʱ�ȭ�ϴ� ���̴�.
	memset(m_pEquip, NULL, sizeof(CItem*) * EQ_END);
}

CPlayer::CPlayer(const CPlayer& player) :
	CCharacter(player)
{
	m_eJob = player.m_eJob;
	m_strJobName = player.m_strJobName;
	m_iGold = player.m_iGold;
	memset(m_pEquip, NULL, sizeof(CItem*) * EQ_END);
}

CPlayer::~CPlayer()
{
	// ����� �� �޸� ����
	for (int i = 0; i < EQ_END; i++) {
		SAFE_DELETE(m_pEquip[i]);
	}
}

void CPlayer::AddGold(int iGold)
{
	m_iGold += iGold;
}

void CPlayer::DropGold()
{
	m_iGold -= m_iGold * 0.1f;
}

bool CPlayer::CheckMP()
{
	if (m_tInfo.iMP < m_tInfo.iMPUse) {
		return false;
	}
	return true;
}

int CPlayer::GetDamage()
{
	int iMin = m_tInfo.iAttackMin;
	int iMax = m_tInfo.iAttackMax;

	if (m_pEquip[EQ_WEAPON]) {
		iMin += ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetAttackMin();
		iMax += ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetAttackMax();

		// 0~99 ������ ���� ���� ġ��Ÿ�� ���պ��� ������ ġ��Ÿ ����
		if (rand() % 9901 / 100.f <= ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetCritical() + m_tInfo.fCritical) {
			cout << endl << "[�ý���] " << "Critical!" << endl;
			iMin *= 2;
			iMax *= 2;
		}
	}

	// iAttackMin ~ iAttackMax ������ ������ �� ����
	return rand() % (iMax - iMin + 1) + iMin;
}

int CPlayer::GetArmor()
{
	int iArmor = m_tInfo.iArmor;

	if (m_pEquip[EQ_ARMOR]) {
		iArmor += ((CItemArmor*)m_pEquip[EQ_ARMOR])->GetArmor();
	}
	return iArmor;
}

// �����ϰ� �ִ°� ������ �����ϰ� �ִ� �������� ����, ������ NULL ����
class CItem* CPlayer::Equip(CItem* pItem)
{
	// �����ϰ����ϴ� �������� Ÿ�Կ� ���� ���� ������ �޶������Ѵ�.
	EQUIP eq;

	switch (pItem->GetItemInfo().eType) {
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	}

	// �����ϰ��ִ� �������� ���� ��� �����ϰ� �ִ� �������� �������ش�.
	if (m_pEquip[eq]) {
		CItem* pEquip = m_pEquip[eq];
		m_pEquip[eq] = pItem;

		// �����ϰ� �ִ� �������� �����Ѵ�.
		return pEquip;
	}
	m_pEquip[eq] = pItem;

	return NULL;
}

bool CPlayer::Init()
{
	system("cls");
	cout << "============= [PrimerPasoRPG]�� ���� ���� ȯ���մϴ�. =============" << endl;
	cin.ignore(1024, '\n');

	cout << endl;
	cout << "�̸��� �Է��ϼ���: ";
	char strName[31];
	cin.getline(strName, 31);
	SetName(strName);

	int iJob;

	while (true) {
		cout << endl;
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ���: ";
		iJob = Input<int>();

		if (iJob < JOB_KNIGHT || iJob >= JOB_END) {
			continue;
		}
		break;
	}

	m_eJob = (JOB)iJob;

	switch (m_eJob) {
	case JOB_KNIGHT:
		m_strJobName = "���";
		SetCharacterInfo(5, 10, 5.0f, 15, 500, 5, 100, 1, 0);
		break;
	case JOB_ARCHER:
		m_strJobName = "�ü�";
		SetCharacterInfo(10, 15, 5.0f, 10, 400, 10, 125, 1, 0);
		break;
	case JOB_WIZARD:
		m_strJobName = "������";
		SetCharacterInfo(15, 20, 5.0f, 5, 300, 15, 150, 1, 0);
		break;
	}

	return true;
}

void CPlayer::Render()
{
	float fCriticalSum = m_tInfo.fCritical;

	cout << "�̸�: " << m_strName << "\t����: " << m_strJobName << endl;
	cout << "����: " << m_tInfo.iLevel << "\t\t����ġ: " << m_tInfo.iExp << endl;
	cout << "���ݷ�: ";
	// ���� �������� �����ϰ� ���� ���
	if (m_pEquip[EQ_WEAPON]) {
		cout << m_tInfo.iAttackMin << " + " << ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetAttackMin() << " ~ " << m_tInfo.iAttackMax << " + " << ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetAttackMax();
		fCriticalSum += ((CItemWeapon*)m_pEquip[EQ_WEAPON])->GetCritical();
	}
	else {		// ���� �������� �����ϰ� ���� ���� ���
		cout << m_tInfo.iAttackMin << " - " << m_tInfo.iAttackMax;
	}

	cout << "\t����: ";

	// �� �������� �����ϰ� ���� ���
	if (m_pEquip[EQ_ARMOR]) {
		cout << m_tInfo.iArmor << " + " << ((CItemArmor*)m_pEquip[EQ_ARMOR])->GetArmor();
	}
	else {		// �� �������� �����ϰ� ���� ���� ���
		cout << m_tInfo.iArmor;
	}

	cout << "\tġ��Ÿ��: " << fCriticalSum << endl;

	cout << "ü��: " << m_tInfo.iHP << " / " << m_tInfo.iHPMax << "\t����: " << m_tInfo.iMP << " / " << m_tInfo.iMPMax << endl;
	cout << "���� �ݾ�: " << m_iGold << " Gold" << endl << endl;

	cout << "���� ����: ";
	if (m_pEquip[EQ_WEAPON]) {
		cout << m_pEquip[EQ_WEAPON]->GetName();
	}
	else {
		cout << "����";
	}

	cout << "\t/ ���� ��: ";
	if (m_pEquip[EQ_ARMOR]) {
		cout << m_pEquip[EQ_ARMOR]->GetName() << endl;
	}
	else {
		cout << "����" << endl;
	}
}

CPlayer* CPlayer::Clone()
{
	// this�� �ڱ��ڽ��� �������̴�. �ڱ��ڽ��� �����͸� �������ϸ� �ڱ��ڽ� ��ü�� �ȴ�.
	// �׷��� ���� �Ҵ��ϴ� �÷��̾� ��ü�� �ڱ��ڽ��� �Ѱ��ְ� �ڱ��ڽ��� �����ϴ� �����ڸ� ȣ���Ͽ� �����ϵ��� ������ش�.
	// �̷��� ���ָ� "�� ��ü�� ������ ���ο� ��ü�� �����Ҵ��Ͽ� �� �޸� �ּҸ� ��ȯ"���ְ� �ȴ�.
	return new CPlayer(*this);
}