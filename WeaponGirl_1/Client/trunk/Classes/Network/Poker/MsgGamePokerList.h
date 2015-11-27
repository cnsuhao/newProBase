////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerList.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/26
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_MsgGamePokerList_H_
#define _GAMESERVER_MSG_MsgGamePokerList_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"


enum MSG_POKER_LIST_ACTION
{
	MSG_POKER_LIST_ACTION_queryall = 1,	// 查询更新全部		C <-- S
	MSG_POKER_LIST_ACTION_update,		// 单张更新			C <-- S
	MSG_POKER_LIST_ACTION_award,		// 增加				C <-- S
	MSG_POKER_LIST_ACTION_delete,		// 删除				C <-- S
	MSG_POKER_LIST_ACTION_changesort,	// 修改出战顺序		C <-> S
};

class CMsgGamePokerList : public CNetMsg
{
public:
	CMsgGamePokerList();
	virtual ~CMsgGamePokerList();
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sCount;

		MSG_POKER_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif	// end of _GAMESERVER_MSG_MsgGamePokerList_H_