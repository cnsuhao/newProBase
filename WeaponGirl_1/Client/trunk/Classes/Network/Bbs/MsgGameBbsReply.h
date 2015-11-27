////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameBbsReply.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/04
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MsgGameBbsReply_H_
#define _GAMEKERNEL_MsgGameBbsReply_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_BBS_REPLY_ACTION
{
	MSG_BBS_REPLY_ACTION_querylist = 1,		// 查询回帖列表	C <-> S
	MSG_BBS_REPLY_ACTION_addnew = 2,		// 回帖			C <-> S
};

class CMsgGameBbsReply : public CNetMsg
{
public:
	CMsgGameBbsReply();
	virtual ~CMsgGameBbsReply();

	virtual void Process();

public:
	bool CreateBbsReplyBase(MSG_BBS_REPLY_ACTION eAciton, DB_KEY idBbs);
	bool AppendBbsReplyInfo(const BBS_REPLY_INFO& rInfo);

private:
	typedef struct
	{
		int16_t sAction;
		int16_t	sCount;
		int16_t nStartFlag;
		int16_t nEndFlag;
		int64_t idBbs;
		BBS_REPLY_INFO info[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // end of _GAMEKERNEL_MsgGameBbsReply_H_