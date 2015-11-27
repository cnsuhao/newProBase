////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameFriend.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-2
////////////////////////////////////////////////////////////////////////
#include "./MsgGameFriend.h"
#include "Mgr/FriendMgr.h"
#include "MyCocosCommon/LayerHint.h"

CMsgGameFriend::CMsgGameFriend()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_FRIEND;
}

CMsgGameFriend::~CMsgGameFriend()
{

}

//////////////////////////////////////////////////////////////////////
bool CMsgGameFriend::CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idFriend/* = ID_NONE*/)
{
	this->Init();
	m_head.usType = _MSG_GAME_FRIEND;
	m_head.usSize = sizeof(MSG_Info)-sizeof(ST_FRIEDN_INFO);

	m_pInfo->sAction = sAction;
	m_pInfo->sResult = sResult;
	m_pInfo->idFriend = 0;
	m_pInfo->nParamNum = 0;
	return true;
}

void CMsgGameFriend::Process()
{
	switch (m_pInfo->sAction)
	{
	case EMFA_SYN_FRIEND_LIST:	// 同步好友列表			C <-- S
	case EMFA_UPDATE_FRIEND:	// 更新好友信息			C <-- S
		{
			for (int i = 0; i < m_pInfo->nParamNum; i++)
			{
				FriendMgr::getInstance()->updateFriendInfo(m_pInfo->stInfo[i]);
			}
		}
		break;
	case EMFA_SYN_REQUST_LIST:	// 同步申请列表			C <-- S
	case EMFA_UPDATE_REQUEST:	// 更新申请信息			C <-- S
		{
			for (int i = 0; i < m_pInfo->nParamNum; i++)
			{
				FriendMgr::getInstance()->updateRequestInfo(m_pInfo->stInfo[i]);
			}
		}
		break;
	case EMFA_SEARCH:	// 搜索好友			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_REQUEST:	// 申请好友			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_AGREE:	// 同意好友			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_REFUSE:	// 拒绝好友			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_DELETE:	// 删除好友			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_SENDGIFT:	// 送礼好友			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_FIGHT_FRIENDLY:	// 切磋好友			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	default:
		break;
	}
}

void CMsgGameFriend::ProcessFaildHint()
{
	switch (m_pInfo->sResult)
	{
	case EMFR_SUC:					// 通用成功
		{
			AddHint("123");
		}
		break;
	case EMFR_FAILD:				// 通用失败
		{
				AddHint("123");
		}
		break;
	case EMFR_IS_FRIEND:			// 已经是好友了
		{
			AddHint("123");
		}
		break;
	case EMFR_SELF_FRIEND_FULL:		// 自己好友满了
		{
			AddHint("123");
		}
		break;
	case EMFR_TARGET_FRIEND_FULL:	// 对方好友满了
		{
			AddHint("123");
		}
		break;
	case EMFR_IS_REQUEST:			// 已经申请过了
		{
			AddHint("123");
		}
		break;
	case EMFR_ID_ERRO:				// ID不存在
		{
			AddHint("123");
		}
		break;
	default:
		break;
	}
}
