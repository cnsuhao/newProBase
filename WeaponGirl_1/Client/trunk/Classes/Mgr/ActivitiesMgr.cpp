////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ActivitiesMgr.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/05
////////////////////////////////////////////////////////////////////////
#include "ActivitiesMgr.h"
#include "LoginMgr.h"

ActivitiesMgr* ActivitiesMgr::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
ActivitiesMgr* ActivitiesMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ActivitiesMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void ActivitiesMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
ActivitiesMgr::ActivitiesMgr()
{

}

//////////////////////////////////////////////////////////////////////////
void ActivitiesMgr::updateActivity(const Activity_Info& info)
{
	auto eType = (ACTIVITY_CONFIG_TYPE)info.nType;
	m_mapData[eType] = info;
}

//////////////////////////////////////////////////////////////////////////
void ActivitiesMgr::deleteActivity(ACTIVITY_CONFIG_TYPE eType)
{
	auto iter = m_mapData.find(eType);
	if (iter == m_mapData.end())
	{
		return;
	}
	m_mapData.erase(iter);
}

//////////////////////////////////////////////////////////////////////////
bool ActivitiesMgr::isActivityRunning(ACTIVITY_CONFIG_TYPE eType) const
{
	auto iter = m_mapData.find(eType);
	if (iter == m_mapData.end())
	{
		return false;
	}

	auto nowTime = LoginMgr::getInstance()->getHeartbeat();
	if (nowTime < iter->second.nStartSecond || nowTime > iter->second.nEndSecond)
	{
		return false;
	}
	
	return true;
}

