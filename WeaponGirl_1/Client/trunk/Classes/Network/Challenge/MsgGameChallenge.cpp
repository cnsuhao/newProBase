////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameChallenge.cpp
// Author: �½���(Chen Jianjun)
// Created: 2015-11-9
////////////////////////////////////////////////////////////////////////
#include "./MsgGameChallenge.h"
#include "mgr/ChallengeMgr.h"

CMsgGameChallenge::CMsgGameChallenge()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_CHALLENGE;
	m_head.usSize = sizeof(MSG_Info)-sizeof(CHALLENGER_INFO);
}

CMsgGameChallenge::~CMsgGameChallenge()
{

}

//////////////////////////////////////////////////////////////////////
bool CMsgGameChallenge::CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idTarget)
{
	this->Init();
	m_pInfo->sAction   = sAction;
	m_pInfo->sResult   = sResult;
	m_pInfo->idTarget  = idTarget;
	m_pInfo->nData1	   = 0;
	m_pInfo->nData2	   = 0;
	m_pInfo->sMsgEnd   = 0;
	m_pInfo->sParamNum = 0;

	m_head.usType = _MSG_GAME_CHALLENGE;
	m_head.usSize = sizeof(MSG_Info)-sizeof(CHALLENGER_INFO);
	return true;
}

void CMsgGameChallenge::Process()
{
	switch (m_pInfo->sAction)
	{
	case EMCHALLENGEA_QUERY_LIST:		// ��ѯ�б�
		{
			for (int i = 0; i < m_pInfo->sParamNum; i++)
			{
				ChallengeMgr::getInstance()->addChallengeInfo(m_pInfo->stInfo[i]);
			}

			if (m_pInfo->sMsgEnd > 0)
			{
				ChallengeMgr::getInstance()->setChallengeData(m_pInfo->nData1, m_pInfo->nData2);
			}
		}
		break;
	case EMCHALLENGEA_FIGHT:			// ��ʼս��
		{

		}
		break;
	case EMCHALLENGEA_QUERY_WORLDRANK_LIST:		// ��ѯpvp������Ϣ
		{
			for (int i = 0; i < m_pInfo->sParamNum; i++)
			{
				ChallengeMgr::getInstance()->addWorldRankInfo(m_pInfo->stInfo[i]);
			}

			if (m_pInfo->sMsgEnd > 0)
			{
				ChallengeMgr::getInstance()->setWorldRankData(m_pInfo->nData1, m_pInfo->nData2);
			}
		}
		break;
	case EMCHALLENGEA_FIGHT_WORLDRANK:			// ��ʼpvp����ս��
		{

		}
		break;
	default:
		break;
	}

}
