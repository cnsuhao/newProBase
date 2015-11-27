////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginKickReason.cpp
// Author: ������(Peng Wenqi)
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
	// ƴ���߳�ԭ���ַ���
	std::string strKickReason = "Be Kick out!";
	switch (m_pInfo->nReason)
	{
	case KICK_REASON_PASSWORD_ERROR:		// �������
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_PASSWORD_ERROR);
		}
		break;
	case KICK_REASON_BE_KICK_ANOTHER:		// ��������
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_BE_KICK_ANOTHER);
		}
		break;
	case KICK_REASON_RELATION_SERVER:		// ��ϵ������ָʾ�㱻����
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_RELATION_SERVER);
		}
		break;
	case KICK_REASON_FULL:					// ��̫��
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_FULL);
		}
		break;
	case KICK_REASON_SYSTEM:				// ����������������� �� GM����	
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_SYSTEM);
		}
		break;
	case KICK_REASON_NOT_ALLOW:				// ������δ������½����
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_NOT_ALLOW);
		}
		break;
	case KICK_REASON_GM_MAC_ERROR:
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_GM_MAC_ERROR);
		}
		break;
	case KICK_REASON_CHECK_SPEED_TOO_FAST:	// ����ٶȹ���					**
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_CHECK_SPEED_TOO_FAST);
		}
		break;
	case KICK_REASON_GMCMD:					// GM�������Լ�	
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_GMCMD);
		}
		break;
	case KICK_REASON_LOGIN_TIMEOUT:			// ��½���̳�ʱ
		{
			strKickReason = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_LOGIN_TIMEOUT);
		}
		break;
	case KICK_REASON_ACCOUNT_STOP_BYTIME:	// �˺���ʱ��ͣ
		{
			std::string strText = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_KICK_REASON_ACCOUNT_STOP_BYTIME);
			strKickReason = StringUtils::format(strText.c_str(), m_pInfo->nParam / 60 / 60 + 1);
		}
		break;
	case KICK_REASON_ACCOUNT_STOP_FOREVER:	// �˺����÷�ͣ
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

	// ������ʾ�����ּ�¼
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_BreakReasonCode, m_pInfo->nReason);
	LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_BreakReason, strKickReason);

	LogSave("KickReason Process [%d]", m_pInfo->nReason);
}

