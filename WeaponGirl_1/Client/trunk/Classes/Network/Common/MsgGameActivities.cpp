////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: CMsgGameActivities.cpp
// Author: 
// Created: 2014-11-13
////////////////////////////////////////////////////////////////////////
#include "MsgGameActivities.h"
#include "Mgr\ActivitiesMgr.h"

CMsgGameActivities::CMsgGameActivities(void)
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_ACTIVITIES;
	m_head.usSize = sizeof(MSG_Info);
}

CMsgGameActivities::~CMsgGameActivities(void)
{
}

////////////////////////////////////////////////////////////////////////
// Description：处理客户端发来的消息
// Arguments: 
// Author: 
// Date: 20141114
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CMsgGameActivities::Process()
{
	switch(m_pInfo->sAction)
	{
	case MSG_ACTIVITY_ACTION_BROADCAST_START:
		{
			ActivitiesMgr::getInstance()->updateActivity(m_pInfo->stActivity[0]);
		}
		break;
	case MSG_ACTIVITY_ACTION_BROADCAST_OVER:
		{
			for (int i = 0; i < m_pInfo->nCount; i++)
			{
				ActivitiesMgr::getInstance()->deleteActivity((ACTIVITY_CONFIG_TYPE)m_pInfo->stActivity[i].nType);
			}
		}
		break;
	case MSG_ACTIVITY_ACTION_QUERY_RUN_ACTIVITIES:
		{
			for (int i = 0; i < m_pInfo->nCount; i++)
			{
				ActivitiesMgr::getInstance()->updateActivity(m_pInfo->stActivity[i]);
			}
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameActivities::createQueryAll()
{
	m_pInfo->nCount = 0;
	m_pInfo->sAction = MSG_ACTIVITY_ACTION_QUERY_ALL_ACTIVITIES;
	m_pInfo->sResult = MSG_ACTIVITY_RESULT_TYPE_SUCC;
	m_head.usType = _MSG_GAME_ACTIVITIES;
	m_head.usSize = sizeof(MSG_Info) - sizeof(Activity_Info);
	return true;
}
