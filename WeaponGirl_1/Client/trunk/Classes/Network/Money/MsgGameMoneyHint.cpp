////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameMoneyHint.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/19
////////////////////////////////////////////////////////////////////////
#include "MsgGameMoneyHint.h"
#include "SceneMain\LayerMoneyAddHint.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameMoneyHint::CMsgGameMoneyHint()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_USER_MONEY_HINT;
}

//////////////////////////////////////////////////////////////////////////
CMsgGameMoneyHint::~CMsgGameMoneyHint()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameMoneyHint::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_MONEY_HINT_ACTION_add_hint:
		for (int i = 0; i < m_pInfo->sCount; i++)
		{
			MONEY_HINT_INFO& stInfo = m_pInfo->stInfo[i];
			MoneyAddHint((USER_MONEY_TYPE)stInfo.nType, stInfo.i64Data);
		}
		
		break;
	default:
		break;
	}
}
