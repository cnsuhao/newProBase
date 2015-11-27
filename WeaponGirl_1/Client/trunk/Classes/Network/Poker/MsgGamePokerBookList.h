////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerBookList.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/27
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_MsgGamePokerBookList_H_
#define _GAMESERVER_MSG_MsgGamePokerBookList_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"


enum MSG_POKER_BOOK_LIST_ACTION
{
	MSG_POKER_BOOK_LIST_ACTION_queryall = 1,	// 查询更新全部		C <-- S
	MSG_POKER_BOOK_LIST_ACTION_update	= 2,	// 部分更新			C <-- S
};

class CMsgGamePokerBookList : public CNetMsg
{
public:
	CMsgGamePokerBookList();
	virtual ~CMsgGamePokerBookList();
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sCount;

		MSG_POKER_BOOK_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif	// end of _GAMESERVER_MSG_MsgGamePokerBookList_H_