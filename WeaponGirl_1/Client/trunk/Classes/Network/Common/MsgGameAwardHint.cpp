////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameAwardHint.cpp
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#include "MsgGameAwardHint.h"
#include "mgr/InstanceMgr.h"
#include "MyCocosCommon/LayerHint.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameAwardHint::CMsgGameAwardHint()
{
	Init();
	m_pInfo = (MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_GAME_AWARD_HINT;
	m_head.usSize = sizeof(MSG_Info)-sizeof(ST_AWARD_INFO);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameAwardHint::~CMsgGameAwardHint()
{

}

void CMsgGameAwardHint::Process()
{
	std::vector<ST_AWARD_INFO> vecAwardInfo;
	for (int i = 0; i < m_pInfo->nInfoCount; i++)
	{
		vecAwardInfo.push_back(m_pInfo->stInfo[i]);
	}

	switch ((E_HITN_TYPE)m_pInfo->nHintType)
	{
	case E_HITN_TYPE_CHALLENGE:
	case E_HITN_TYPE_INSTANCE_FIGHT:
		{

		}
		break;
	case E_HITN_TYPE_INSTANCE_SEARCHING:
		{
			InstanceMgr::getInstance()->updateSearchingResult(vecAwardInfo);
		}
		break;
	default:
		break;
	}
}