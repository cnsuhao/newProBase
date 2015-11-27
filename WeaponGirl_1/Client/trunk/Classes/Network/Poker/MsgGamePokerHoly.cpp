////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerHoly.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/09
////////////////////////////////////////////////////////////////////////
#include "MsgGamePokerHoly.h"
#include "Mgr\PokerMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGamePokerHoly::CMsgGamePokerHoly()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_POKER_HOLY;
}

//////////////////////////////////////////////////////////////////////////
CMsgGamePokerHoly::~CMsgGamePokerHoly()
{

}
//////////////////////////////////////////////////////////////////////////
void CMsgGamePokerHoly::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_POKER_HOLY_ACTION_query:
		PokerMgr::getInstance()->updateHolyData(m_pInfo->nRefreshTime, m_pInfo->nCanBuyTime, (OBJID*)m_pInfo->nPokerType, (uint32_t*)m_pInfo->nPokerPrice);
		break;
	case MSG_POKER_HOLY_ACTION_buy:
		PokerMgr::getInstance()->updateHolyData(m_pInfo->nRefreshTime, m_pInfo->nCanBuyTime, (OBJID*)m_pInfo->nPokerType, (uint32_t*)m_pInfo->nPokerPrice);
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGamePokerHoly::CreateHolyMsg(MSG_POKER_HOLY_ACTION eAction, int nCanBuyTime /*= 0*/)
{
	this->Init();
	m_head.usType = _MSG_GAME_POKER_HOLY;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = eAction;
	m_pInfo->sResult = MSG_POKER_HOLY_RESULT_success;

	m_pInfo->nCanBuyTime = nCanBuyTime;	// 用来表示购买序号

	return true;
}


