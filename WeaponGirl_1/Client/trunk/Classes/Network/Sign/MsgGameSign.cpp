////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameSign.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-30
////////////////////////////////////////////////////////////////////////
#include "./MsgGameSign.h"
#include "Mgr/SignMgr.h"
#include "MyCocosCommon/LayerHint.h"

CMsgGameSign::CMsgGameSign()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_SIGN;
}

CMsgGameSign::~CMsgGameSign()
{

}

//////////////////////////////////////////////////////////////////////
bool CMsgGameSign::CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult)
{
	this->Init();
	m_head.usType = _MSG_GAME_SIGN;
	m_head.usSize = sizeof(MSG_Info)-sizeof(ST_SIGN_AWARD_INFO);

	m_pInfo->sAction   = sAction;
	m_pInfo->sResult   = sResult;
	m_pInfo->nParamNum = 0;
	return true;
}

void CMsgGameSign::Process()
{
	switch (m_pInfo->sAction)
	{
	case EMSA_QUERY_SIGN_INFO:	// 查询签到信息
		{
			for (int i = 0; i < m_pInfo->nParamNum; i++)
			{
				SignMgr::getInstance()->addSignAwardInfo(m_pInfo->stInfo[i]);
			}
		}
		break;
	case EMSA_SIGN:				// 签到
		{
			if (EMSR_SUC == m_pInfo->sResult)
			{
				// 签到成功
				SignMgr::getInstance()->signSuc();
			}
			else if (EMSR_FAILD == m_pInfo->sResult)
			{
				// 通用失败
				AddHint("123");
			}
			else if (EMSR_ALREADY_SIGN == m_pInfo->sResult)
			{
				// 已经签到过
				AddHint("123");
			}
			else if (EMSR_NOT_ENOUGH == m_pInfo->sResult)
			{
				// 条件不足
				AddHint("123");
			}
			else if (EMSR_PACKFULL == m_pInfo->sResult)
			{
				// 背包已满
				AddHint("123");
			}
		}
		break;
	default:
		break;
	}
}
