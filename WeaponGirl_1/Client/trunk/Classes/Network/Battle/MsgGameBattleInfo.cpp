////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameBattleInfo.cpp
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-3
////////////////////////////////////////////////////////////////////////
#include "./MsgGameBattleInfo.h"
#include "mgr/BattleDataMgr.h"

CMsgGameBattleInfo::CMsgGameBattleInfo()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_BATTLE_INFO;
}

CMsgGameBattleInfo::~CMsgGameBattleInfo()
{

}

void CMsgGameBattleInfo::Process()
{
	CHECK(m_pInfo);
	BattleDataMgr::getInstance()->initBattleData((E_BATTLE_TYPE)m_pInfo->nBattleType, m_pInfo->stAttackerInfo, m_pInfo->stDefenderInfo);
}
