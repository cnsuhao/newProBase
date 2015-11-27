////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginCreateNewUser.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#include "./MsgLoginCreateNewUser.h"
#include "Root.h"
#include "SceneLogin/SceneLogin.h"
#include "MsgLoginAction.h"
#include "MyCocosCommon/LayerHint.h"

//////////////////////////////////////////////////////////////////////////
CMsgLoginCreateNewUser::CMsgLoginCreateNewUser()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_LOGIN_CREATE_NEW_USER;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgLoginCreateNewUser::~CMsgLoginCreateNewUser()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgLoginCreateNewUser::Process()
{
	if (MSG_LOGIN_CREATE_NEW_USER_RESULT_SUCCESS != m_pInfo->nResult)
	{
		std::string strMessageBox = "Create Error";
		switch (m_pInfo->nResult)
		{
			case MSG_LOGIN_CREATE_NEW_USER_RESULT_NAME_CHECK:
				{
					strMessageBox = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_NAME_CHECK_ERROR);
					
				}
				break;
// 			case MSG_LOGIN_CREATE_NEW_USER_RESULT_CODE_REPEAT:
// 				{
// 					strMessageBox = "Name repeat";
// 					ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_NAME_REPEAT, strMessageBox);
// 				}
// 				break;
			case MSG_LOGIN_CREATE_NEW_USER_RESULT_COUNT_FULL:
				{
					strMessageBox = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_CAN_NOT_MORE_PLAYER);
				}
				break;
			default:
				{
					strMessageBox = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_CREATE_FAILED);
				}
				break;
		}
		::AddHint(strMessageBox);
		return;
	}

	// 保存角色数据
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_sex, m_pInfo->nSex);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_lookface, m_pInfo->nLookface);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_userinfo_user_id, m_pInfo->nUserID);
	LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_UserName, m_pInfo->szName);

	// 关闭创建界面, 打开载入界面
	auto sceneLogin = Root::getInstance()->getSceneLogin();
	CHECK(sceneLogin);
	sceneLogin->popLayerLoad();

	// 选择角色
	CMsgLoginAction msg;
	CHECK(msg.CreateChooseUser(m_pInfo->nUserID));
	NetworkServe::getInstance()->sendMsg(msg);
}

////////////////////////////////////////////////////////////////////////
// Description: 创建新角色消息创建
// Arguments:	性别在服务器写死
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool CMsgLoginCreateNewUser::createCreateNewPlayer(const char* pszName, int nLookface, int nJob)
{
	CHECKF(pszName);
	this->Init();

	::SafeCopy(m_pInfo->szName, pszName, sizeof(m_pInfo->szName));

	m_pInfo->nJob = nJob;
	m_pInfo->nLookface = nLookface;
	m_pInfo->nResult = MSG_LOGIN_CREATE_NEW_USER_RESULT_SUCCESS;

	m_head.usType = _MSG_LOGIN_CREATE_NEW_USER;
	m_head.usSize = sizeof(MSG_Info);

	return true;
}

