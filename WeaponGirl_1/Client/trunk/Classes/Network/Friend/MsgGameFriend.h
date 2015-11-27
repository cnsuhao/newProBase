////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameFriend.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-2
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_FRIEND_H_
#define _GAMEKERNEL_MSG_GAME_FRIEND_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

enum EMSGFRIENDACTION			// 消息类型
{
	EMFA_NONE				= 0,
	EMFA_SYN_FRIEND_LIST	= 1,	// 同步好友列表		C <-- S
	EMFA_SYN_REQUST_LIST	= 2,	// 同步申请列表		C <-- S
	EMFA_UPDATE_FRIEND		= 3,	// 更新好友信息		C <-- S
	EMFA_UPDATE_REQUEST		= 4,	// 更新申请信息		C <-- S
	EMFA_SEARCH				= 5,	// 搜索好友			C <-> S
	EMFA_REQUEST			= 6,	// 申请好友			C <-> S
	EMFA_AGREE				= 7,	// 同意好友			C <-> S
	EMFA_REFUSE				= 8,	// 拒绝好友			C <-> S
	EMFA_DELETE				= 9,	// 删除好友			C <-> S
	EMFA_SENDGIFT			= 10,	// 送礼好友			C <-> S
	EMFA_FIGHT_FRIENDLY		= 11,	// 切磋战斗			C <-> S
};

enum EMSGFRIENDRESULT				// 消息结果类型
{
	EMFR_SUC				= 0,	// 通用成功
	EMFR_FAILD				= 1,	// 通用失败
	EMFR_IS_FRIEND			= 2,	// 已经是好友了
	EMFR_SELF_FRIEND_FULL	= 3,	// 自己好友满了
	EMFR_TARGET_FRIEND_FULL = 4,	// 对方好友满了
	EMFR_IS_REQUEST			= 5,	// 已经申请过了
	EMFR_ID_ERRO			= 6,	// ID不存在
};

class CMsgGameFriend : public CNetMsg
{
public:
	CMsgGameFriend();
	virtual ~CMsgGameFriend();

protected:
	virtual void Process();
	void	ProcessFaildHint();

public:
	bool	CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idFriend = ID_NONE);

private:
	typedef struct{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	idFriend;
		MSG_STR_32BIT	strSearch;

		MSG_NUM_4BIT	nParamNum;
		ST_FRIEDN_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_FRIEND_H_
