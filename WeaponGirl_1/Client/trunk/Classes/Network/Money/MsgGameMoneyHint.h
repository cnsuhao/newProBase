////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameMoneyHint.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/19
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_GAME_MONEY_HINT_H_
#define _GAMESERVER_MSG_GAME_MONEY_HINT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_MONEY_HINT_ACTION
{
	MSG_MONEY_HINT_ACTION_add_hint = 1,	// Ôö¼Óhint
};

struct MONEY_HINT_INFO
{
	MSG_NUM_4BIT	nType;
	MSG_NUM_8BIT	i64Data;
};


class CMsgGameMoneyHint : public CNetMsg
{
public:
	CMsgGameMoneyHint();
	virtual ~CMsgGameMoneyHint();
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sCount;

		MONEY_HINT_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMESERVER_MSG_GAME_MONEY_HINT_H_