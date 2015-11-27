////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameInstanceInfo.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_INSTANCE_INFO_H_
#define _GAMEKERNEL_MSG_GAME_INSTANCE_INFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./Network/NetMsg.h"

enum EMSGINSTANCEACTION				// 消息类型
{
	EMSGINSTANCEA_NONE = 0,
	EMSGINSTANCEA_QUERY_INFO,		// 查询副本信息			C <-> S
	EMSGINSTANCEA_FIGHT,			// 开始战斗				C <-> S

	EMSGINSTANCEA_SEARCHING,		// 开始探索				C <-> S
	EMSGINSTANCEA_SEARCHING_AWARD,	// 获得探索结果			C <-> S
	EMSGINSTANCEA_SEARCHING_COUNT,	// 增加探索次数			C <-> S
};

enum EMSGINSTANCERESULT				// 消息结果类型
{
	EMSGINSTANCER_SUC	= 0,		// 通用成功
	EMSGINSTANCER_FAILD = 1,		// 通用失败
};

class CMsgGameInstanceInfo : public CNetMsg
{
public:
	CMsgGameInstanceInfo();
	virtual ~CMsgGameInstanceInfo();

protected:
	virtual void Process();

public:
	bool CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idInstance);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;
		MSG_NUM_4BIT	idInstance;			// 副本id
		MSG_NUM_4BIT	nFightLeftTime;		// 战斗剩余时间
		MSG_NUM_4BIT	nFightCount;		// 战斗次数
		MSG_NUM_4BIT	nResetTime;			// 消耗重置时间
		MSG_NUM_4BIT	nSearchingLeftTime;	// 探索剩余时间
		MSG_NUM_4BIT	nSearchingCount;	// 探索次数
		MSG_NUM_4BIT	nCommentCount;		// 攻略数
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif