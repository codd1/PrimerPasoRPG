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
	//friend class CInventory;

private:
	int m_iRecoveryValue;	// 물약 회복량
	//int m_iNumPosion;		// 물약 갯수

public:
	int GetRecoveryValue() const {
		return m_iRecoveryValue;
	}
	/*int GetNumPosion() const {
		return m_iNumPosion;
	}*/

public:
	void SetPosion(int iRecoveryValue);
	//void SetNumPosion(int iNumPosion);

public:
	virtual bool Init();
	virtual void Render();
	virtual CItemPosion* Clone();
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

