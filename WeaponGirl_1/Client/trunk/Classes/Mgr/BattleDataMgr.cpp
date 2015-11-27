////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: BattleDataMgr.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-6
////////////////////////////////////////////////////////////////////////
#include "BattleDataMgr.h"
#include "ConstTable\ConstTableMgr.h"
#include "LogicDataMgr.h"
#include "Network\NetworkServe.h"
#include "MyCocosCommon\LayerHint.h"
#include "Root.h"
#include "InstanceMgr.h"

BattleDataMgr* BattleDataMgr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
BattleDataMgr::BattleDataMgr()
{

}

//////////////////////////////////////////////////////////////////////////
BattleDataMgr* BattleDataMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new BattleDataMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void BattleDataMgr::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}

////////////////////////////////////////////////////////////////////////
// Description: 初始化战斗数据
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool BattleDataMgr::initBattleData(E_BATTLE_TYPE eBattleType, IN BATTLE_FIGHTER_INFO& stAttackerInfo, IN BATTLE_FIGHTER_INFO& stDefenderInfo)
{
	CHECKF(eBattleType != E_BATTLE_TYPE_NONE);
	m_eBattleType = eBattleType;
	CopyMemory(&m_stAttackerInfo, &stAttackerInfo, sizeof(BATTLE_FIGHTER_INFO));
	CopyMemory(&m_stDefenderInfo, &stDefenderInfo, sizeof(BATTLE_FIGHTER_INFO));
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 压入战斗回合数据
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
void BattleDataMgr::pushRoundResult(IN BATTLE_ROUND_INFO& stRoundInfo)
{
	m_deqRoundInfo.push_back(stRoundInfo);
}

////////////////////////////////////////////////////////////////////////
// Description: 弹出战斗回合数据
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
bool BattleDataMgr::popRoundResult(OUT BATTLE_ROUND_INFO& stRoundInfo)
{
	if (m_deqRoundInfo.empty())
	{
		return false;
	}

	stRoundInfo = m_deqRoundInfo[0];
	m_deqRoundInfo.pop_front();
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 战斗结束
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
void BattleDataMgr::endBattle(IN BATTLE_ROUND_INFO& stRoundInfo)
{
	auto idWinner = stRoundInfo.idAttacker;
	auto nRound = stRoundInfo.nRound;
	LogSave("========== Battle %s[%u] Attack %s[%u] Begin! ==========", 
		m_stAttackerInfo.szName,
		m_stAttackerInfo.id,
		m_stDefenderInfo.szName,
		m_stDefenderInfo.id);
	LogSave("*** Attacker[%u] : Score[%I64d] Atk[%d] Def[%d] Dodge[%d] King[%d]! ==========",
		m_stAttackerInfo.id,
		m_stAttackerInfo.i64Score,
		m_stAttackerInfo.nAttrAtk,
		m_stAttackerInfo.nAttrDef,
		m_stAttackerInfo.nAttrDodge,
		m_stAttackerInfo.nAttrKing);
	LogSave("*** Defender[%u] : Score[%I64d] Atk[%d] Def[%d] Dodge[%d] King[%d]! ==========",
		m_stDefenderInfo.id,
		m_stDefenderInfo.i64Score,
		m_stDefenderInfo.nAttrAtk,
		m_stDefenderInfo.nAttrDef,
		m_stDefenderInfo.nAttrDodge,
		m_stDefenderInfo.nAttrKing);

	// 测试
	for (int i = 1; i <= nRound; i++)
	{
		BATTLE_ROUND_INFO stInfo = { 0 };
		CHECKC(this->popRoundResult(stInfo));
		LogSave("Round [%d] : RoundCheck[%d] -- Attacker[%u], idMagicType[%u], nHitFlag[%d], i64Damage[%I64d], i64Recover[%I64d]", i,
			stInfo.nRound,
			stInfo.idAttacker,
			stInfo.idMagicType,
			stInfo.nHitFlag,
			stInfo.i64Damage,
			stInfo.i64Recover);
		if (stInfo.idAttacker == m_stAttackerInfo.id)
		{
			m_stAttackerInfo.i64Score += stInfo.i64Recover;
			if (stInfo.nHitFlag > 0)
			{
				m_stDefenderInfo.i64Score -= stInfo.i64Damage;
			}
		}
		else
		{
			m_stDefenderInfo.i64Score += stInfo.i64Recover;
			if (stInfo.nHitFlag > 0)
			{
				m_stAttackerInfo.i64Score -= stInfo.i64Damage;
			}
		}
		LogSave("      Attacker hp[%I64d] ------- Defender hp[%I64d]", m_stAttackerInfo.i64Score, m_stDefenderInfo.i64Score);
	}
	LogSave("============== Battle End！ Winner is [%u]! ==============", idWinner);

	this->processBattleEnd(idWinner == LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_userinfo_user_id));
	this->clearBattleData();
}

////////////////////////////////////////////////////////////////////////
// Description: 处理战斗结束各系统分发
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
void BattleDataMgr::processBattleEnd(bool bWin)
{
	switch (m_eBattleType)
	{
	case E_BATTLE_TYPE_NONE:
		break;
	case E_BATTLE_TYPE_MONSTER:
		break;
	case E_BATTLE_TYPE_FRIENDLY:
		break;
	case E_BATTLE_TYPE_PVP_CHALLENGE:
		break;
	case E_BATTLE_TYPE_PVP_WORLD:
		break;
	case E_BATTLE_TYPE_INSTANCE:
		{
			if (bWin)
			{
				InstanceMgr::getInstance()->winFight();
			}
		}
		break;
	case E_BATTLE_TYPE_SMELT:
		break;
	default:
		break;
	}

	// 测试提示
	if (bWin)
	{
		AddHint("YOU WIN!!!");
	}
	else
	{
		AddHint("YOU FAILD!!!");
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 清理战斗数据
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value:  bool
////////////////////////////////////////////////////////////////////////
void BattleDataMgr::clearBattleData(void)
{
	m_eBattleType = E_BATTLE_TYPE_NONE;
	ZeroMemory(&m_stAttackerInfo, sizeof(BATTLE_FIGHTER_INFO));
	ZeroMemory(&m_stDefenderInfo, sizeof(BATTLE_FIGHTER_INFO));
	m_deqRoundInfo.clear();
}


