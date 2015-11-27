////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerBookList.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/27
////////////////////////////////////////////////////////////////////////
#include "MsgGamePokerBookList.h"
#include "Mgr\PokerMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGamePokerBookList::CMsgGamePokerBookList()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_POKER_BOOK_LIST;
}

//////////////////////////////////////////////////////////////////////////
CMsgGamePokerBookList::~CMsgGamePokerBookList()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGamePokerBookList::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_POKER_BOOK_LIST_ACTION_queryall:
	case MSG_POKER_BOOK_LIST_ACTION_update:
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				PokerMgr::getInstance()->updateBookData(m_pInfo->stInfo[i].type, m_pInfo->stInfo[i].count);
			}
		}
		break;
	default:
		break;
	}
}
