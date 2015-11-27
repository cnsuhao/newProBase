////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameShop.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#include "./MsgGameShop.h"
#include "Mgr/ShopMgr.h"
#include "MyCocosCommon/LayerHint.h"

CMsgGameShop::CMsgGameShop()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_SHOP;
}

CMsgGameShop::~CMsgGameShop()
{

}

//////////////////////////////////////////////////////////////////////
bool CMsgGameShop::CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idShopGoods)
{
	this->Init();
	m_head.usType = _MSG_GAME_SHOP;
	m_head.usSize = sizeof(MSG_Info);

	m_pInfo->sAction = sAction;
	m_pInfo->sResult = sResult;
	m_pInfo->idShopGoods = idShopGoods;
	return true;
}

void CMsgGameShop::Process()
{
	switch (m_pInfo->sAction)
	{
	case EMSHOPA_BUY:	// 购买商品
		{

		}
		break;
	default:
		break;
	}
}
