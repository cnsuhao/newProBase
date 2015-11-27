////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameBbs.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/04
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MsgGameBbs_H_
#define _GAMEKERNEL_MsgGameBbs_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_BBS_ACTION
{
	MSG_BBS_ACTION_querylist = 1,		// 查询列表		C <-> S
	MSG_BBS_ACTION_addnew = 2,			// 发帖			C <-> S
};

class CMsgGameBbs : public CNetMsg
{
public:
	CMsgGameBbs();
	virtual ~CMsgGameBbs();

	virtual void Process();

public:
	bool CreateBbsBase(MSG_BBS_ACTION eAciton);
	bool AppendBbsInfo(const BBS_INFO& rInfo);

private:
	typedef struct
	{
		int16_t sAction;
		int16_t	sCount;
		int16_t nStartFlag;
		int16_t nEndFlag;
		BBS_INFO info[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // end of _GAMEKERNEL_MsgGameBbs_H_