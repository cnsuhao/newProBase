////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerOpt.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/26
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_MsgGamePokerOpt_H_
#define _GAMESERVER_MSG_MsgGamePokerOpt_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_POKER_OPT_ACTION
{
	MSG_POKER_OPT_ACTION_uplev = 1,			// 升级				C <-> S
	MSG_POKER_OPT_ACTION_upstar,			// 升星				C <-> S
	MSG_POKER_OPT_ACTION_strengthen,		// 强化				C <-> S
	MSG_POKER_OPT_ACTION_breakthrough,		// 突破				C <-> S
	MSG_POKER_OPT_ACTION_makeweapon,		// 武器打造			C <-> S
	MSG_POKER_OPT_ACTION_changeweapon,		// 主卡换武器		C <-> S
	MSG_POKER_OPT_ACTION_addscore,			// 主卡加经验		C <-> S
	MSG_POKER_OPT_ACTION_distractability,	// 转移能力			C <-> S
	MSG_POKER_OPT_ACTION_goup,				// 上阵				C <-> S
	MSG_POKER_OPT_ACTION_godown,			// 下阵				C <-> S
	MSG_POKER_OPT_ACTION_setfightgroup,		// 设置阵容编号		C <-> S
	MSG_POKER_OPT_ACTION_recall,			// 卡牌召回			C <-> S
};

enum MSG_POKER_OPT_RESULT
{
	MSG_POKER_OPT_RESULT_success = 0,	
	MSG_POKER_OPT_RESULT_failed,
};


class CMsgGamePokerOpt : public CNetMsg
{
public:
	CMsgGamePokerOpt();
	virtual ~CMsgGamePokerOpt();
	virtual void Process();

public:
	bool CreatePokerOpt(MSG_POKER_OPT_ACTION sAction, MSG_POKER_OPT_RESULT sResult, int64_t idPoker, int64_t data1 = 0, int64_t data2 = 0);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_8BIT	idPoker;
		MSG_NUM_8BIT	data1;
		MSG_NUM_8BIT	data2;
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif	// end of _GAMESERVER_MSG_MsgGamePokerOpt_H_