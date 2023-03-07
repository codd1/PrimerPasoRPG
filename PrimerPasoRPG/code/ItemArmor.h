#pragma once

#include "Item.h"

class CItemArmor :
    public CItem
{
protected:
	CItemArmor();
	CItemArmor(const CItemArmor& item);
	virtual ~CItemArmor();

private:
	friend class CStore;
	friend class CStoreArmor;
	friend class CEditorItem;

private:
	int m_iArmor;

public:
	int GetArmor() const {
		return m_iArmor;
	}

public:
	void SetArmor(int iArmor);

public:
	virtual bool Init();
	virtual void Render();
	virtual CItemArmor* Clone();
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

