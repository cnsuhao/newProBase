////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerOpt.h
// Author: ������(Peng Wenqi)
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
	MSG_POKER_OPT_ACTION_uplev = 1,			// ����				C <-> S
	MSG_POKER_OPT_ACTION_upstar,			// ����				C <-> S
	MSG_POKER_OPT_ACTION_strengthen,		// ǿ��				C <-> S
	MSG_POKER_OPT_ACTION_breakthrough,		// ͻ��				C <-> S
	MSG_POKER_OPT_ACTION_makeweapon,		// ��������			C <-> S
	MSG_POKER_OPT_ACTION_changeweapon,		// ����������		C <-> S
	MSG_POKER_OPT_ACTION_addscore,			// �����Ӿ���		C <-> S
	MSG_POKER_OPT_ACTION_distractability,	// ת������			C <-> S
	MSG_POKER_OPT_ACTION_goup,				// ����				C <-> S
	MSG_POKER_OPT_ACTION_godown,			// ����				C <-> S
	MSG_POKER_OPT_ACTION_setfightgroup,		// �������ݱ��		C <-> S
	MSG_POKER_OPT_ACTION_recall,			// �����ٻ�			C <-> S
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