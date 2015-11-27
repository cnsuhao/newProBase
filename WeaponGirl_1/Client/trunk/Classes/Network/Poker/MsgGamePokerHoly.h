////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGamePokerHoly.h
// Author: ������(Peng Wenqi)
// Created: 2015/11/09
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_MsgGamePokerHoly_H_
#define _GAMESERVER_MSG_MsgGamePokerHoly_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_POKER_HOLY_ACTION
{
	MSG_POKER_HOLY_ACTION_query = 1,	// ����				C <-> S
	MSG_POKER_HOLY_ACTION_buy,			// ����				C <-> S
};

enum MSG_POKER_HOLY_RESULT
{
	MSG_POKER_HOLY_RESULT_success = 0,
	MSG_POKER_HOLY_RESULT_failed,
};

class CMsgGamePokerHoly : public CNetMsg
{
public:
	CMsgGamePokerHoly();
	virtual ~CMsgGamePokerHoly();
	virtual void Process();

public:
	bool CreateHolyMsg(MSG_POKER_HOLY_ACTION eAction, int nCanBuyTime = 0);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	nCanBuyTime;	// �´ι���utcʱ��
		MSG_NUM_4BIT	nRefreshTime;	// �´�ˢ��utcʱ��
		MSG_NUM_4BIT	nPokerType[POKER_HOLY_COUNT];	// ��������
		MSG_NUM_4BIT	nPokerPrice[POKER_HOLY_COUNT];	// ���Ƽ۸�
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif	// end of _GAMESERVER_MSG_MsgGamePokerHoly_H_