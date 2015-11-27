////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameInstanceInfo.cpp
// Author: �½���(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#include "MsgGameInstanceInfo.h"
#include "mgr/InstanceMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameInstanceInfo::CMsgGameInstanceInfo()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_INSTANCE_INFO;
	m_head.usSize = sizeof(MSG_Info);
}

CMsgGameInstanceInfo::~CMsgGameInstanceInfo()
{

}

bool CMsgGameInstanceInfo::CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idInstance)
{
	this->Init();
	m_pInfo->sAction			= sAction;
	m_pInfo->sResult			= sResult;
	m_pInfo->idInstance			= idInstance;
	m_pInfo->nFightLeftTime		= 0;
	m_pInfo->nFightCount		= 0;
	m_pInfo->nResetTime			= 0;
	m_pInfo->nSearchingLeftTime = 0;
	m_pInfo->nSearchingCount	= 0;
	m_pInfo->nCommentCount		= 0;
	m_head.usType = _MSG_GAME_INSTANCE_INFO;
	m_head.usSize = sizeof(MSG_Info);
	return true;
}
//////////////////////////////////////////////////////////////////////////

void CMsgGameInstanceInfo::Process()
{

	switch (m_pInfo->sAction)
	{
	case EMSGINSTANCEA_QUERY_INFO:		// ��ѯ�ؿ���Ϣ
		{
			InstanceMgr::getInstance()->updateInstanceInfo(
				m_pInfo->idInstance,
				m_pInfo->nFightLeftTime,
				m_pInfo->nFightCount,
				m_pInfo->nResetTime,
				m_pInfo->nSearchingLeftTime,
				m_pInfo->nSearchingCount,
				m_pInfo->nCommentCount);
		}
		break;
	case EMSGINSTANCEA_FIGHT:			// ��ʼս��				C <-> S
		{

		}
		break;
	case EMSGINSTANCEA_SEARCHING:		// ��ʼ̽��				C <-> S
		{
			if (m_pInfo->sResult == EMSGINSTANCER_SUC)
			{
				InstanceMgr::getInstance()->updateSearchingPass();
			}
		}
		break;
	case EMSGINSTANCEA_SEARCHING_AWARD:	// ���̽�����			C <-> S
		{
			if (m_pInfo->sResult == EMSGINSTANCER_SUC)
			{
				InstanceMgr::getInstance()->updateSearchingCount();
			}
		}
		break;
	case EMSGINSTANCEA_SEARCHING_COUNT:	// ����̽������			C <-> S
		{
			if (m_pInfo->sResult == EMSGINSTANCER_SUC)
			{
				InstanceMgr::getInstance()->updateMaxSearchingCount();
			}
		}
		break;
	default:
		break;
	}
}