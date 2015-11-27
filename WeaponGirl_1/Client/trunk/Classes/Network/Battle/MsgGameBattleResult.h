////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameBattleResult.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_BATTLE_RESULT_H_
#define _GAMEKERNEL_MSG_GAME_BATTLE_RESULT_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

enum BATTLE_RESULT_ACTION
{
	BATTLE_RESULT_ACTION_LIST	  = 1,	// 战斗回合列表
	BATTLE_RESULT_ACTION_LIST_END = 2,	// 战斗回合结束包
};

class CMsgGameBattleResult : public CNetMsg
{
public:
	CMsgGameBattleResult();
	virtual ~CMsgGameBattleResult();

protected:
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_2BIT		sAction;
		MSG_NUM_2BIT		sBattleType;
		MSG_NUM_4BIT		nRoundCount;
		BATTLE_ROUND_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_BATTLE_RESULT_H_
