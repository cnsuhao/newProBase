////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameBattleInfo.h
// Author: �½���(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_BATTLE_INFO_H_
#define _GAMEKERNEL_MSG_GAME_BATTLE_INFO_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

class CBattleFighter;
class CMsgGameBattleInfo : public CNetMsg
{
public:
	CMsgGameBattleInfo();
	virtual ~CMsgGameBattleInfo();

protected:
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_4BIT	nBattleType;		// ս������

		BATTLE_FIGHTER_INFO stAttackerInfo;	// ����������
		BATTLE_FIGHTER_INFO stDefenderInfo;	// ����������
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_BATTLE_INFO_H_
