////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameGift.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/05
////////////////////////////////////////////////////////////////////////
#include "MsgGameGift.h"
#include "Mgr\GiftMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameGift::CMsgGameGift()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_GIFT;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameGift::~CMsgGameGift()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgGameGift::Process()
{
	switch (m_pInfo->sAction)
	{
	case MSG_GIFT_ACTION_querylist:
		{
			if (m_pInfo->nStartFlag != 0)
			{
				GiftMgr::getInstance()->clear();
			}

			for (int i = 0; i < m_pInfo->sCount; i++)
			{
				GiftMgr::getInstance()->addInfo(m_pInfo->info[i]);
			}

			if (m_pInfo->nEndFlag != 0)
			{
				// 通知数据读取完成
			}
		}
		break;
	case MSG_GIFT_ACTION_getgift:
		{
			GiftMgr::getInstance()->notifyGetGift(m_pInfo->info[0].idGift);
		}
		break;
	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameGift::CreateGiftBase(MSG_GIFT_ACTION eAciton)
{
	this->Init();
	m_head.usType  = _MSG_GAME_GIFT;
	m_head.usSize  = sizeof(MSG_Info) - sizeof(GIFT_INFO);

	m_pInfo->sAction = eAciton;
	m_pInfo->sCount = 0;
	m_pInfo->nStartFlag = 0;
	m_pInfo->nEndFlag = 0;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgGameGift::AppendGiftInfo(const GIFT_INFO& rInfo)
{
	CHECKF_NOLOG(sizeof(MSG_Info) + sizeof(GIFT_INFO) * m_pInfo->sCount < MAX_PACKETSIZE);
	memcpy(&m_pInfo->info[m_pInfo->sCount], &rInfo, sizeof(GIFT_INFO));
	m_head.usSize = sizeof(MSG_Info) + sizeof(GIFT_INFO) * m_pInfo->sCount;
	m_pInfo->sCount++;
	return true;
}
