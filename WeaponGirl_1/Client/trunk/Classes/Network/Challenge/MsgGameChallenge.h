////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameChallenge.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_CHALLENGE_H_
#define _GAMEKERNEL_MSG_GAME_CHALLENGE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

enum EMSGCHALLENGEACTION					// 消息类型
{
	EMCHALLENGEA_NONE = 0,
	EMCHALLENGEA_QUERY_LIST,				// 查询列表				C <-> S
	EMCHALLENGEA_FIGHT,						// 开始挑战				C <-> S

	EMCHALLENGEA_QUERY_WORLDRANK_LIST,		// 查询世界榜列表		C <-> S
	EMCHALLENGEA_FIGHT_WORLDRANK,			// 开始世界挑战			C <-> S
};

enum EMSGCHALLENGERESULT					// 消息结果类型
{
	EMCHALLENGER_SUC = 0,					// 签到成功
	EMCHALLENGER_FAILD = 1,					// 通用失败
};

class CMsgGameChallenge : public CNetMsg
{
public:
	CMsgGameChallenge();
	virtual ~CMsgGameChallenge();

protected:
	virtual void Process();

public:
	bool	CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idTarget);

private:
	typedef struct{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	idTarget;
		MSG_NUM_4BIT	nData1;
		MSG_NUM_4BIT	nData2;

		MSG_NUM_2BIT	sMsgEnd;
		MSG_NUM_2BIT	sParamNum;
		CHALLENGER_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_CHALLENGE_H_
