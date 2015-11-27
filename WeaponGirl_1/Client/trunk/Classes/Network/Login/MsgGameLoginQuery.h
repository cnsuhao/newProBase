////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameLoginQuery.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_LOGIN_QUERY_H_
#define _GAMEKERNER_MSG_GAME_LOGIN_QUERY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

// 登录action枚举, 对应sAction
enum MSG_LOGIN_QUERY_ACTION
{
	MSG_LOGIN_QUERY_ACTION_HEARTBEAT					= 1,	// 心跳				C <-> S
	MSG_LOGIN_QUERY_ACTION_CLIENT_LOGIN_OVER			= 2,	// 客户端登陆完成	C --> S


	MSG_LOGIN_QUERY_ACTION_AUTOBACK_BEGIN				= 100,	// 自动回包开始	以下全部 C <-> S
	MSG_LOGIN_QUERY_ACTION_ALL_MONEY					= 101,	// 查询全部金钱		
	MSG_LOGIN_QUERY_ACTION_MASKINFO						= 102,	// 查询掩码		
	MSG_LOGIN_QUERY_ACTION_PACKAGE						= 103,	// 查询背包
	MSG_LOGIN_QUERY_ACTION_ALL_FRIEND					= 104,	// 查询好友
	MSG_LOGIN_QUERY_ACTION_CLIENT_TMPDATA				= 105,	// 查询客户端自定义TmpData
	MSG_LOGIN_QUERY_ACTION_ALL_TASK						= 106,	// 查询任务列表
	MSG_LOGIN_QUERY_ACTION_UNREADMAILCOUNT				= 107,	// 查询未读邮件数量
	MSG_LOGIN_QUERY_ACTION_SIGN							= 108,	// 查询签到
	MSG_LOGIN_QUERY_ACTION_SELF_SYNDICATE				= 109,	// 查询自己帮派信息
	MSG_LOGIN_QUERY_ACTION_ACTIVITES					= 110,	// 查询所有活动
	MSG_LOGIN_QUERY_ACTION_INSTANCE_LIST				= 111,	// 查询副本列表

	MSG_LOGIN_QUERY_ACTION_SERVER_GROUP					= 113,	// 查询服务器组信息
};

// 错误码枚举, 对应sResult
enum MSG_LOGIN_QUERY_RESULT
{
	MSG_LOGIN_QUERY_RESULT_SUCC		= 0,
	MSG_LOGIN_QUERY_RESULT_ERROR	= 1,
};

class CMsgGameLoginQuery : public CNetMsg
{
public:
	CMsgGameLoginQuery();
	virtual ~CMsgGameLoginQuery();

	virtual void Process();

public:
	bool CreateLoginQuery(MSG_LOGIN_QUERY_ACTION eAction, MSG_LOGIN_QUERY_RESULT eResult = MSG_LOGIN_QUERY_RESULT_SUCC, int nParam1 = 0, int nParam2 = 0);

private:
	void ProcessHeartbeat(void);

private:
	typedef struct  
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	nParam1;
		MSG_NUM_4BIT	nParam2;
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMEKERNER_MSG_GAME_LOGIN_QUERY_H_