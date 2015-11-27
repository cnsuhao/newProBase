////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameGift.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/05
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MsgGameGift_H_
#define _GAMEKERNEL_MsgGameGift_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_GIFT_ACTION
{
	MSG_GIFT_ACTION_querylist	= 1,	// 查询列表		C <-> S
	MSG_GIFT_ACTION_getgift		= 2,	// 获取礼物		C <-> S
};

class CMsgGameGift : public CNetMsg
{
public:
	CMsgGameGift();
	virtual ~CMsgGameGift();

	virtual void Process();

public:
	bool CreateGiftBase(MSG_GIFT_ACTION eAciton);
	bool AppendGiftInfo(const GIFT_INFO& rInfo);

private:
	typedef struct
	{
		int16_t sAction;
		int16_t	sCount;
		int16_t nStartFlag;
		int16_t nEndFlag;
		GIFT_INFO info[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // end of _GAMEKERNEL_MsgGameBbs_H_