////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ChallengeMgr.cpp
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-10
////////////////////////////////////////////////////////////////////////
#include "ChallengeMgr.h"

ChallengeMgr* ChallengeMgr::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
ChallengeMgr* ChallengeMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ChallengeMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void ChallengeMgr::destroyInstance()
{

}

//////////////////////////////////////////////////////////////////////////
ChallengeMgr::ChallengeMgr()
{

}

bool ChallengeMgr::addChallengeInfo(CHALLENGER_INFO& stInfo)
{
	m_vecChallengeInfo.push_back(stInfo);
	return true;
}

bool ChallengeMgr::setChallengeData(int nChallengeLastRefreshTime, int nChallengeCount)
{
	m_nChallengeLastRefreshTime = nChallengeLastRefreshTime;
	m_nChallengeCount			= nChallengeCount;
	return true;
}

bool ChallengeMgr::addWorldRankInfo(CHALLENGER_INFO& stInfo)
{
	m_vecPvpWorldRankInfo.push_back(stInfo);
	return true;
}

bool ChallengeMgr::setWorldRankData(int nWorldRankLastFIghtTime, int nWorldRankFightCount)
{
	m_nWorldRankLastFIghtTime = nWorldRankLastFIghtTime;
	m_nWorldRankFightCount    = nWorldRankFightCount;
	return true;
}
