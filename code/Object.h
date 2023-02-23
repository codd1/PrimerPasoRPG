#pragma once

#include "value.h"

class CObject
{
protected:
	CObject();
	CObject(const CObject& obj);
	virtual ~CObject() = 0;

private:
	friend class CObjectManager;

protected:
	string m_strName;
	OBJECT_TYPE m_eType;

public:
	OBJECT_TYPE GetObjectType() const;

public:
	void SetName(const char* pName) {
		m_strName = pName;
	}

	string GetName() const {
		return m_strName;
	}

public:
	virtual bool Init();
	virtual void Render();
	virtual CObject* Clone() = 0;
};

