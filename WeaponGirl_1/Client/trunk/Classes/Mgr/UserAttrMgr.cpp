////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: UserAttrMgr.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/16
////////////////////////////////////////////////////////////////////////
#include "UserAttrMgr.h"

UserAttrMgr* UserAttrMgr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
UserAttrMgr* UserAttrMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new UserAttrMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void UserAttrMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
UserAttrMgr::UserAttrMgr()
{

}

//////////////////////////////////////////////////////////////////////////
int64_t UserAttrMgr::getAttr(USER_ATTR eAttr) const
{
	auto iter = m_mapData.find(eAttr);
	if (iter == m_mapData.end())
	{
		return 0;
	}
	return iter->second;
}

//////////////////////////////////////////////////////////////////////////
void UserAttrMgr::updateAttr(USER_ATTR eAttr, int64_t data)
{
	auto iter = m_mapData.find(eAttr);
	if (iter != m_mapData.end())
	{
		iter->second = data;
	}
	else
	{
		m_mapData[eAttr] = data;
	}
}
