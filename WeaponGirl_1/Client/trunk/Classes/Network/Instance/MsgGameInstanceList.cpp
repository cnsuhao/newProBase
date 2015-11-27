////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameInstanceList.cpp
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#include "MsgGameInstanceList.h"
#include "mgr/InstanceMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameInstanceList::CMsgGameInstanceList()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_INSTANCE_LIST;
	m_head.usSize = sizeof(MSG_Info)-sizeof(ST_INSTANCE_LIST_INFO);
}

CMsgGameInstanceList::~CMsgGameInstanceList()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameInstanceList::Process()
{
	for (int i = 0; i < m_pInfo->nInfoCount; i++)
	{
		InstanceMgr::getInstance()->addInstanceInfo(m_pInfo->stInfo[i]);
	}
}