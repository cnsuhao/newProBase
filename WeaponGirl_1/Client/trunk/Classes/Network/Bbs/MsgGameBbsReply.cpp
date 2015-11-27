////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameBbsReply.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/04
////////////////////////////////////////////////////////////////////////
#include "MsgGameBbsReply.h"
#include "Mgr\BbsMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameBbsReply::CMsgGameBbsReply()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;

	m_head.usType = _MSG_GAME_BBS_REPLY;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameBbsReply::~CMsgGameBbsReply()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameBbsReply::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_BBS_REPLY_ACTION_querylist:
		{
			if (m_pInfo->nStartFlag != 0)
			{
				BbsMgr::getInstance()->clearReply(m_pInfo->idBbs);
			}

			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				BbsMgr::getInstance()->addReply(m_pInfo->info[i]);
			}

			if (m_pInfo->nEndFlag != 0)
			{
				// 通知数据读取完成
			}
		}
		break;
	case MSG_BBS_REPLY_ACTION_addnew:
		{
			BbsMgr::getInstance()->addReply(m_pInfo->info[0], true);
		}
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameBbsReply::CreateBbsReplyBase(MSG_BBS_REPLY_ACTION eAciton, DB_KEY idBbs)
{
	this->Init();
	m_head.usType = _MSG_GAME_BBS_REPLY;
	m_head.usSize = sizeof(MSG_Info) - sizeof(BBS_REPLY_INFO);

	m_pInfo->sAction = eAciton;
	m_pInfo->sCount = 0;
	m_pInfo->nStartFlag = 0;
	m_pInfo->nEndFlag = 0;
	m_pInfo->idBbs = idBbs;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameBbsReply::AppendBbsReplyInfo(const BBS_REPLY_INFO& rInfo)
{
	CHECKF_NOLOG(sizeof(MSG_Info) + sizeof(BBS_REPLY_INFO) * m_pInfo->sCount < MAX_PACKETSIZE);
	memcpy(&m_pInfo->info[m_pInfo->sCount], &rInfo, sizeof(BBS_REPLY_INFO));
	m_head.usSize = sizeof(MSG_Info) + sizeof(BBS_REPLY_INFO) * m_pInfo->sCount;
	m_pInfo->sCount++;
	return true;
}
