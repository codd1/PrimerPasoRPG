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
	friend class CStore;
	friend class CEditorItem;
	friend class CStorePosion;

private:
	int m_iPosion;
	int m_iNumPosion;

public:
	int GetPosion() const {
		return m_iPosion;
	}
	int GetNumPosion() const {
		return m_iNumPosion;
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

