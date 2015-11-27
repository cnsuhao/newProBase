////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginKickReason.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#include "./MsgKickReason.h"
#include "ConstTable/ConstTableMgr.h"
#include "Mgr/LogicDataMgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMsgKickReason::CMsgKickReason()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_KICK_REASON;
	m_head.usSize = sizeof(MSG_Info);
}

CMsgKickReason::~CMsgKickReason()
{
	
}

//////////////////////////////////////////////////////////////////////////
void CMsgKickReason::Process()
{
	// 拼接踢出原因字符串
	std::string strKickReason = "Be Kick out!";
	switch (m_pInfo->nReason)
	{
	case KICK_REASON_PASSWORD_ERROR:		// 密码错误
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_PASSWORD_ERROR);
		}
		break;
	case KICK_REASON_BE_KICK_ANOTHER:		// 被别人踢
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_BE_KICK_ANOTHER);
		}
		break;
	case KICK_REASON_RELATION_SERVER:		// 关系服务器指示你被踢了
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_RELATION_SERVER);
		}
		break;
	case KICK_REASON_FULL:					// 人太多
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_FULL);
		}
		break;
	case KICK_REASON_SYSTEM:				// 服务器控制面板踢人 或 GM踢人	
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_SYSTEM);
		}
		break;
	case KICK_REASON_NOT_ALLOW:				// 服务器未开启登陆允许
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_NOT_ALLOW);
		}
		break;
	case KICK_REASON_GM_MAC_ERROR:
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_GM_MAC_ERROR);
		}
		break;
	case KICK_REASON_CHECK_SPEED_TOO_FAST:	// 检测速度过快					**
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_CHECK_SPEED_TOO_FAST);
		}
		break;
	case KICK_REASON_GMCMD:					// GM命令踢自己	
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_GMCMD);
		}
		break;
	case KICK_REASON_LOGIN_TIMEOUT:			// 登陆过程超时
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_LOGIN_TIMEOUT);
		}
		break;
	case KICK_REASON_ACCOUNT_STOP_BYTIME:	// 账号临时封停
		{
			std::string strText = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_ACCOUNT_STOP_BYTIME);
			strKickReason = StringUtils::format(strText.c_str(), m_pInfo->nParam / 60 / 60 + 1);
		}
		break;
	case KICK_REASON_ACCOUNT_STOP_FOREVER:	// 账号永久封停
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_ACCOUNT_STOP_FOREVER);
		}
		break;
	default:
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_DEFAULT);
		}
		break;
	} // end of switch

	// 弹出提示框文字记录
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_BreakReasonCode, m_pInfo->nReason);
	LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_BreakReason, strKickReason);

	LogSave("KickReason Process [%d]", m_pInfo->nReason);
}

