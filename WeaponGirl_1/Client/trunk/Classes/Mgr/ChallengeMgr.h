////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ChallengeMgr.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_CHALLENGE_MGR_H_
#define _JYP_CHALLENGE_MGR_H_

#include "Global/Global.h"

class ChallengeMgr : public Ref
{
public:
	static ChallengeMgr*	getInstance();
	static void				destroyInstance();
private:
	ChallengeMgr();
	static ChallengeMgr*	m_pInstance;

public:
	bool	addChallengeInfo		(CHALLENGER_INFO& stInfo);
	bool	setChallengeData		(int nChallengeLastRefreshTime, int nChallengeCount);
	const std::vector<CHALLENGER_INFO>* getChallengeInfo() { return &m_vecChallengeInfo; }

	bool	addWorldRankInfo		(CHALLENGER_INFO& stInfo);
	bool	setWorldRankData		(int nWorldRankLastFIghtTime, int nWorldRankFightCount);
	const std::vector<CHALLENGER_INFO>* getWorldRankInfo() { return &m_vecPvpWorldRankInfo; }

protected:
	CC_SYNTHESIZE_READONLY(int,		m_nChallengeLastRefreshTime,	ChallengeLastRefreshTime);	// pvp挑战上次刷新时间
	CC_SYNTHESIZE_READONLY(int,		m_nChallengeCount,				ChallengeCount);			// pvp挑战次数
	std::vector<CHALLENGER_INFO>	m_vecChallengeInfo;											// pvp挑战榜信息

	CC_SYNTHESIZE_READONLY(int,		m_nWorldRankLastFIghtTime,		WorldRankLastFightTime);	// pvp世界榜上次挑战时间
	CC_SYNTHESIZE_READONLY(int,		m_nWorldRankFightCount,			WorldRankFightCount);		// pvp世界榜挑战次数
	std::vector<CHALLENGER_INFO>	m_vecPvpWorldRankInfo;										// pvp世界榜信息
};

#endif // end of _JYP_CHALLENGE_MGR_H_