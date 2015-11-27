////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: BattleDataMgr.h
// Author: �½���(Chen Jianjun)
// Created: 2015-11-6
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_BATTLE_DATA_H_
#define _JYP_BATTLE_DATA_H_

#include "Global/Global.h"

struct MyStruct
{

};

class BattleDataMgr : public Ref
{
public:
	static BattleDataMgr*	getInstance();
	static void				destroyInstance();
private:
	BattleDataMgr();
	static BattleDataMgr*	m_pInstance;

public:
	bool	initBattleData	(E_BATTLE_TYPE eBattleType, IN BATTLE_FIGHTER_INFO& stAttackerInfo, IN BATTLE_FIGHTER_INFO& stDefenderInfo);
	void	pushRoundResult	(IN BATTLE_ROUND_INFO& stRoundInfo);
	bool	popRoundResult	(OUT BATTLE_ROUND_INFO& stRoundInfo);
	void	endBattle		(IN BATTLE_ROUND_INFO& stRoundInfo);
	
	void	clearBattleData	(void);

	void	processBattleEnd(bool bWin);

private:
	std::deque<BATTLE_ROUND_INFO>	m_deqRoundInfo;

	CC_SYNTHESIZE_READONLY(E_BATTLE_TYPE,		m_eBattleType,		BattleType);	// ս������
	CC_SYNTHESIZE_READONLY(BATTLE_FIGHTER_INFO,	m_stAttackerInfo,	AttackerInfo);	// ��������Ϣ
	CC_SYNTHESIZE_READONLY(BATTLE_FIGHTER_INFO,	m_stDefenderInfo,	DefenderInfo);	// ��������Ϣ
};

#endif // end of _JYP_BATTLE_DATA_H_