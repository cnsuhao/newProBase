////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgCommentOpt.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/03
////////////////////////////////////////////////////////////////////////

#ifndef _COMMENTKERNEL_MsgCommentOpt_H_
#define _COMMENTKERNEL_MsgCommentOpt_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_COMMENT_OPT_ACTION
{
	MSG_COMMENT_OPT_ACTION_querylist = 1,	// 查询列表		C --> S
	MSG_COMMENT_OPT_ACTION_click_good = 2,	// 点击赞按钮	C --> S
	MSG_COMMENT_OPT_ACTION_add_good = 3,	// 点赞			C <-- S
	MSG_COMMENT_OPT_ACTION_dec_good = 4,	// 取消点赞		C <-- S
};

class CMsgCommentOpt : public CNetMsg
{
public:
	CMsgCommentOpt();
	virtual ~CMsgCommentOpt();

	virtual void Process();

public:
	bool CreateCommentOpt(MSG_COMMENT_OPT_ACTION eAciton, OBJID idCommentType, int64_t idComment);


private:
	typedef struct
	{
		int32_t nAction;
		int32_t	idCommentType;
		int64_t idComment;
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // end of _COMMENTKERNEL_MsgCommentOpt_H_