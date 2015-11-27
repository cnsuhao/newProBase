////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerList.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/26
////////////////////////////////////////////////////////////////////////
#include "MsgGamePokerList.h"
#include "Mgr\PokerMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGamePokerList::CMsgGamePokerList()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_POKER_LIST;
}

//////////////////////////////////////////////////////////////////////////
CMsgGamePokerList::~CMsgGamePokerList()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGamePokerList::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_POKER_LIST_ACTION_queryall:	// 查询更新全部		C <-- S
	case MSG_POKER_LIST_ACTION_update:		// 单张更新			C <-- S
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				PokerMgr::getInstance()->updatePokerData(m_pInfo->stInfo[i]);
			}
		}
		break;
	case MSG_POKER_LIST_ACTION_award:		// 增加				C <-- S
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				PokerMgr::getInstance()->updatePokerData(m_pInfo->stInfo[i]);
			}

			// 通知播放抽卡动画, 此时图鉴数据还未处理, 可以判断是否为第一次抽卡
			// .....
		}
		break;
	case MSG_POKER_LIST_ACTION_delete:		// 删除				C <-- S
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				PokerMgr::getInstance()->deletePoker(m_pInfo->stInfo[i].idPoker);
			}
		}
		break;
	case MSG_POKER_LIST_ACTION_changesort:	// 修改出战顺序		C <-> S
		break;
	default:
		LogSave("CMsgGamePokerList::Process error action[%d]", m_pInfo->sAction);
		break;
	}

}
