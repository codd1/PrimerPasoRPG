#pragma once
#include "Object.h"
class CItem :
    public CObject
{
protected:
	CItem();
	CItem(const CItem& item);

public:			// �Ҹ��ڸ� public���� �س��� ������ Safe_Delete_VecList �����̴�
	virtual ~CItem();

private:
	friend class CStore;

protected:
	ITEMINFO m_tInfo;

public:
	void SetItemInfo(ITEM_TYPE eType, int iPrice, int iSell, const char* pDesc);

	ITEMINFO GetItemInfo() const {
		return m_tInfo;
	}
public:
	virtual bool Init();
	virtual void Render();
	virtual CItem* Clone() = 0;
};

