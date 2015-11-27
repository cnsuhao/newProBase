////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerList.cpp
// Author: ������(Peng Wenqi)
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
	case MSG_POKER_LIST_ACTION_queryall:	// ��ѯ����ȫ��		C <-- S
	case MSG_POKER_LIST_ACTION_update:		// ���Ÿ���			C <-- S
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				PokerMgr::getInstance()->updatePokerData(m_pInfo->stInfo[i]);
			}
		}
		break;
	case MSG_POKER_LIST_ACTION_award:		// ����				C <-- S
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				PokerMgr::getInstance()->updatePokerData(m_pInfo->stInfo[i]);
			}

			// ֪ͨ���ų鿨����, ��ʱͼ�����ݻ�δ����, �����ж��Ƿ�Ϊ��һ�γ鿨
			// .....
		}
		break;
	case MSG_POKER_LIST_ACTION_delete:		// ɾ��				C <-- S
		{
			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				PokerMgr::getInstance()->deletePoker(m_pInfo->stInfo[i].idPoker);
			}
		}
		break;
	case MSG_POKER_LIST_ACTION_changesort:	// �޸ĳ�ս˳��		C <-> S
		break;
	default:
		LogSave("CMsgGamePokerList::Process error action[%d]", m_pInfo->sAction);
		break;
	}

}
