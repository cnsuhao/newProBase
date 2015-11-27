////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameShop.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_SHOP_H_
#define _GAMEKERNEL_MSG_GAME_SHOP_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

enum EMSGSHOPACTION				// 消息类型
{
	EMSHOPA_NONE		= 0,
	EMSHOPA_BUY			= 1,	// 购买商品
};

enum EMSGSHOPRESULT				// 消息结果类型
{
	EMSHOPR_SUC			= 0,	// 签到成功
	EMSHOPR_FAILD		= 1,	// 通用失败
	EMSHOPR_PACKFULL	= 2,	// 背包已满
};

class CMsgGameShop : public CNetMsg
{
public:
	CMsgGameShop();
	virtual ~CMsgGameShop();

protected:
	virtual void Process();

public:
	bool	CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idShopGoods);

private:
	typedef struct{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;
		MSG_NUM_4BIT	idShopGoods;
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_SHOP_H_
