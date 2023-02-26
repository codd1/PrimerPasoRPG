#pragma once
#include "Object.h"
class CItem :
    public CObject
{
protected:
	CItem();
	CItem(const CItem& item);

public:			// 소멸자를 public으로 해놓는 이유는 Safe_Delete_VecList 때문이다
	virtual ~CItem();

private:
	friend class CStore;

protected:
	ITEMINFO m_tInfo;
	friend class CEditorItem;

public:
	void SetItemInfo(ITEM_TYPE eType, int iPrice, int iSell, const char* pDesc);

	ITEMINFO GetItemInfo() const {
		return m_tInfo;
	}
public:
	virtual bool Init();
	virtual void Render();
	virtual CItem* Clone() = 0;
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

