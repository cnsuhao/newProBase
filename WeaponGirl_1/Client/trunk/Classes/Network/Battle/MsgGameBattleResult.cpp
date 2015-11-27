////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameBattleResult.cpp
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#include "./MsgGameBattleResult.h"
#include "mgr/BattleDataMgr.h"

CMsgGameBattleResult::CMsgGameBattleResult()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_BATTLE_RESULT;
}

CMsgGameBattleResult::~CMsgGameBattleResult()
{

}

void CMsgGameBattleResult::Process()
{
	CHECK(m_pInfo);
	if (m_pInfo->sBattleType != BattleDataMgr::getInstance()->getBattleType())
	{
		return;
	}

	if (m_pInfo->sAction == BATTLE_RESULT_ACTION_LIST)
	{
		for (int i = 0; i < m_pInfo->nRoundCount; i++)
		{
			BattleDataMgr::getInstance()->pushRoundResult(m_pInfo->stInfo[i]);
		}
		return;
	}

	if (m_pInfo->sAction == BATTLE_RESULT_ACTION_LIST_END)
	{
		BattleDataMgr::getInstance()->endBattle(m_pInfo->stInfo[0]);
	}
}