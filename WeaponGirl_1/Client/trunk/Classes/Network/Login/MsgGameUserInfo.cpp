////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameUserInfo.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#include "MsgGameUserInfo.h"
#include "Mgr/LogicDataMgr.h"
#include "Root.h"
#include "Mgr\LoginMgr.h"

//////////////////////////////////////////////////////////////////////////
CMsgGameUserInfo::CMsgGameUserInfo()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_USER_INFO;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgGameUserInfo::~CMsgGameUserInfo()
{

}

////////////////////////////////////////////////////////////////////////
// Description: 接收到角色信息
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void CMsgGameUserInfo::Process( )
{
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_user_id, m_pInfo->nUserID);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_account_id, m_pInfo->nAccountID);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_account_type, m_pInfo->nAccountType);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_exit_time, m_pInfo->nExitTime);

	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_sex, m_pInfo->nSex);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_lookface, m_pInfo->nLookface);
// 	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_lev, m_pInfo->nLev);
// 	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_exp, m_pInfo->i64Exp);

	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_server_group, m_pInfo->nServerGroup);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_server_line, m_pInfo->nServerLine);

	LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_UserName, m_pInfo->szUserName);
	LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_UserCode, m_pInfo->szCode);

	LoginMgr::getInstance()->processUserInfo();
}
