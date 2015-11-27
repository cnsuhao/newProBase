////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameLoginQuery.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#include "./MsgGameLoginQuery.h"
#include "Mgr/LoginMgr.h"


//////////////////////////////////////////////////////////////////////////
CMsgGameLoginQuery::CMsgGameLoginQuery()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_LOGIN_QUERY;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameLoginQuery::~CMsgGameLoginQuery()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameLoginQuery::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_LOGIN_QUERY_ACTION_HEARTBEAT:
		{
			LoginMgr::getInstance()->updateHeartbeat(m_pInfo->nParam1); 
		}
		break;

	case MSG_LOGIN_QUERY_ACTION_SERVER_GROUP:
		{
			LoginMgr::getInstance()->processUserServerGroup();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_ALL_MONEY:
		{
			LoginMgr::getInstance()->processUserMoney();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_MASKINFO:
		{
			LoginMgr::getInstance()->processUserMaskInfo();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_PACKAGE:
		{
			LoginMgr::getInstance()->processUserPackage();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_ALL_FRIEND:
		{
			LoginMgr::getInstance()->processUserFriend();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_CLIENT_TMPDATA:
		{
			LoginMgr::getInstance()->processUserTmpData();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_ALL_TASK:
		{
			LoginMgr::getInstance()->processTask();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_UNREADMAILCOUNT:
		{
			LoginMgr::getInstance()->processUserMail();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_SIGN:
		{	
			LoginMgr::getInstance()->processUserSign();
		}
		break;
	case MSG_LOGIN_QUERY_ACTION_SELF_SYNDICATE:
		{
			LoginMgr::getInstance()->processUserSelfSyndicate();
		}
		break;
	default:
		LogSave("CMsgGameLoginQuery::Process unkonw action[%d]", m_pInfo->sAction);
		break;
	}

}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameLoginQuery::CreateLoginQuery( MSG_LOGIN_QUERY_ACTION eAction, MSG_LOGIN_QUERY_RESULT eResult /*= MSG_LOGIN_QUERY_RESULT_SUCC*/, int nParam1 /*= 0*/, int nParam2 /*= 0*/ )
{
	this->Init();
	m_head.usType = _MSG_GAME_LOGIN_QUERY;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = (MSG_NUM_2BIT)eAction;
	m_pInfo->sResult = (MSG_NUM_2BIT)eResult;
	m_pInfo->nParam1 = nParam1;
	m_pInfo->nParam2 = nParam2;

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 心跳包
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CMsgGameLoginQuery::ProcessHeartbeat( void )
{

}


