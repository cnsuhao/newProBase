////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameBbs.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/04
////////////////////////////////////////////////////////////////////////
#include "MsgGameBbs.h"
#include "Mgr\BbsMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameBbs::CMsgGameBbs()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_BBS;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameBbs::~CMsgGameBbs()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameBbs::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_BBS_ACTION_querylist:
		{
			if (m_pInfo->nStartFlag != 0)
			{
				BbsMgr::getInstance()->clearBBS();
			}

			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				BbsMgr::getInstance()->addBBS(m_pInfo->info[i]);
			}

			if (m_pInfo->nEndFlag != 0)
			{
				// 通知数据读取完成
			}
		}
		break;
	case MSG_BBS_ACTION_addnew:
		{
			BbsMgr::getInstance()->addBBS(m_pInfo->info[0], true);
		}
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameBbs::CreateBbsBase(MSG_BBS_ACTION eAciton)
{
	this->Init();
	m_head.usType = _MSG_GAME_BBS;
	m_head.usSize = sizeof(MSG_Info) - sizeof(BBS_INFO);

	m_pInfo->sAction = eAciton;
	m_pInfo->sCount = 0;
	m_pInfo->nStartFlag = 0;
	m_pInfo->nEndFlag = 0;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameBbs::AppendBbsInfo(const BBS_INFO& rInfo)
{
	CHECKF_NOLOG(sizeof(MSG_Info) + sizeof(BBS_INFO) * m_pInfo->sCount < MAX_PACKETSIZE);
	memcpy(&m_pInfo->info[m_pInfo->sCount], &rInfo, sizeof(BBS_INFO));
	m_head.usSize = sizeof(MSG_Info) + sizeof(BBS_INFO) * m_pInfo->sCount;
	m_pInfo->sCount++;
	return true;
}
