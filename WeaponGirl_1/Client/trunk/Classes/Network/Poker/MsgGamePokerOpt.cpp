////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerOpt.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/26
////////////////////////////////////////////////////////////////////////
#include "MsgGamePokerOpt.h"

//////////////////////////////////////////////////////////////////////////
CMsgGamePokerOpt::CMsgGamePokerOpt()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType= _MSG_GAME_POKER_OPT;
}

//////////////////////////////////////////////////////////////////////////
CMsgGamePokerOpt::~CMsgGamePokerOpt()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGamePokerOpt::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_POKER_OPT_ACTION_uplev:
		break;
	case MSG_POKER_OPT_ACTION_upstar:
		break;
	case MSG_POKER_OPT_ACTION_strengthen:
		break;
	case MSG_POKER_OPT_ACTION_breakthrough:
		break;
	case MSG_POKER_OPT_ACTION_makeweapon:
		break;
	case MSG_POKER_OPT_ACTION_changeweapon:
		break;
	case MSG_POKER_OPT_ACTION_distractability:
		break;
	case MSG_POKER_OPT_ACTION_goup:
		break;
	case MSG_POKER_OPT_ACTION_godown:
		break;
	case MSG_POKER_OPT_ACTION_setfightgroup:
		break;
	case MSG_POKER_OPT_ACTION_recall:
		break;
	default:
		LogSave("CMsgGamePokerOpt::Process error action[%d]", m_pInfo->sAction);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGamePokerOpt::CreatePokerOpt(MSG_POKER_OPT_ACTION sAction, MSG_POKER_OPT_RESULT sResult, int64_t idPoker, int64_t data1 /*= 0*/, int64_t data2 /*= 0*/)
{
	this->Init();
	m_head.usType = _MSG_GAME_POKER_OPT;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = sAction;
	m_pInfo->sResult = sResult;
	m_pInfo->idPoker = idPoker;
	m_pInfo->data1 = data1;
	m_pInfo->data2 = data2;

	return true;
}
