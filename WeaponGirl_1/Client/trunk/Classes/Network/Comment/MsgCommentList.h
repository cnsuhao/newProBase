////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgCommentList.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/03
////////////////////////////////////////////////////////////////////////

#ifndef _COMMENTKERNEL_MsgCommentList_H_
#define _COMMENTKERNEL_MsgCommentList_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_COMMENT_LIST_ACTION
{
	MSG_COMMENT_LIST_ACTION_alllist = 1,	// 返回全部list信息		C <-- S
	MSG_COMMENT_LIST_ACTION_new = 2,		// 新的信息				C <-> S
};

class CMsgCommentList : public CNetMsg
{
public:
	CMsgCommentList();
	virtual ~CMsgCommentList();

	virtual void Process();

public:
	bool CreateNewComment(OBJID idCommentType, const char* pszText);

private:
	typedef struct
	{
		int16_t sAction;
		int16_t	sCount;
		int32_t nCommentType;
		int16_t nStartFlag;
		int16_t nEndFlag;
		COMMENT_INFO info[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // end of _COMMENTKERNEL_MsgCommentList_H_