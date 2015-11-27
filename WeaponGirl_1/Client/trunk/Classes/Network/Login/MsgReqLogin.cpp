////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgReqLogin.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#include "MsgReqLogin.h"
#include "Mgr/LogicDataMgr.h"
#include "..\NetworkServe.h"
#include "MsgLoginConnect.h"
#include "MyCocosCommon\LayerMessageBox.h"
#include "ConstTable\ConstTableMgr.h"
#include "Root.h"
#include "MyCocosCommon\LayerWaitting.h"
#include "SceneLogin/SceneLogin.h"
#include "MyCocosCommon\LayerHint.h"

//////////////////////////////////////////////////////////////////////////
CMsgReqLogin::CMsgReqLogin()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_head.usType = _MSG_RL_SERVER_REQ_LOGIN;
	m_head.usSize = sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgReqLogin::~CMsgReqLogin()
{

}

//////////////////////////////////////////////////////////////////////////
void CMsgReqLogin::Process()
{
	if (CONNECT_STATUS_reqLogin == LogicDataMgr::getInstance()->getConnectStatus())
	{
		// 没有开启的服务器
		if (0 == m_pInfo->nLine)
		{
			LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_none);
			NetworkServe::getInstance()->closeSocket();
			
			std::string strMessageBox = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_NOT_GAME_SERVER);
			::AddHint(strMessageBox);
			Root::getInstance()->processConnectFailed();
			return;
		}
		
		NetworkServe::getInstance()->closeSocket();

		NetworkServe::getInstance()->connect(m_pInfo->szAccIp, m_pInfo->nAccPort,
			[=]()	// 连接成功
		{
			auto accIP = NetworkServe::getInstance()->getIp();
			auto accPort = NetworkServe::getInstance()->getPort();
			LayerWaitting::stopWaitting(Root::getInstance()->getSceneLogin());	// 移除等待界面

			LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_GameServerIp, accIP);	// 保存游戏服ip
			LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_GameServerPort, accPort);	// 保存游戏服端口

			// 发送账号验证
			CMsgLoginConnect msg;
			CHECK(msg.CreateAccountConnect(LogicDataMgr::getInstance()->GetMemoryStringAttr(LOGIC_STRING_AccountName).c_str(), LogicDataMgr::getInstance()->GetMemoryStringAttr(LOGIC_STRING_AccountPwd).c_str()));
			NetworkServe::getInstance()->sendMsg(msg);

			LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_reqPwd);	// 状态更新
		},
			[=]()	// 连接失败
		{
			LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_none);
			NetworkServe::getInstance()->closeSocket();

			std::string strMessageBox = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_CONNECT_GAME_SERVER_FAILED);
			::AddHint(strMessageBox);
			Root::getInstance()->processConnectFailed();
		});
	}
	else
	{
		LogSave("CMsgReqLogin::Process connect status [%d] error!", LogicDataMgr::getInstance()->getConnectStatus());
	}
}

//////////////////////////////////////////////////////////////////////////
bool CMsgReqLogin::CreateEmpty()
{
	this->Init();

	m_head.usType	= _MSG_RL_SERVER_REQ_LOGIN;
	m_head.usSize	= sizeof(MSG_Info);

	return true;
}
