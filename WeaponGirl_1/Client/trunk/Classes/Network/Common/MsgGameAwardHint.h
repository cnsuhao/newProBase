////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameAwardHint.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_AWARD_HINT_H_
#define _GAMEKERNEL_MSG_GAME_AWARD_HINT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./Network/NetMsg.h"

enum E_HITN_TYPE							// 提示类型
{
	E_HITN_TYPE_NONE,
	E_HITN_TYPE_CHALLENGE			= 1,	// pvp挑战榜	
	E_HITN_TYPE_INSTANCE_FIGHT		= 2,	// 副本通关
	E_HITN_TYPE_INSTANCE_SEARCHING	= 3,	// 副本探索
};

class CMsgGameAwardHint : public CNetMsg
{
public:
	CMsgGameAwardHint();
	virtual ~CMsgGameAwardHint();

protected:
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_4BIT	nHintType;
		MSG_NUM_4BIT	nData1;
		MSG_NUM_4BIT	nData2;

		MSG_NUM_4BIT	nInfoCount;
		ST_AWARD_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif