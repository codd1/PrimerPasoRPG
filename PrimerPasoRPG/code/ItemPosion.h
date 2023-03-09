#pragma once
#include "Item.h"
class CItemPosion :
    public CItem
{
protected:
	CItemPosion();
	CItemPosion(const CItemPosion& item);
	virtual ~CItemPosion();

private:
	friend class CEditorItem;

private:
	int m_iPosion;

public:
	int GetRecovery() const {
		return m_iPosion;
	}

public:
	void SetPosion(int iPosion);

public:
	virtual bool Init();
	virtual void Render();
	virtual CItemPosion* Clone();
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

