#include "Object.h"

CObject::CObject()
{
}

CObject::CObject(const CObject& obj)
{
	m_strName = obj.m_strName;
	m_eType = obj.m_eType;
}

CObject::~CObject()
{
}

OBJECT_TYPE CObject::GetObjectType() const
{
	return m_eType;
}

bool CObject::Init()
{
	return true;
}

void CObject::Render()
{
}
