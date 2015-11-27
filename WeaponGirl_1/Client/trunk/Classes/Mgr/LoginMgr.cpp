////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LoginMgr.cpp
// Author: ������(Peng Wenqi)
// Created: 2015/05/26
////////////////////////////////////////////////////////////////////////
#include "LoginMgr.h"
#include "Root.h"
#include "Mgr/LogicDataMgr.h"
#include "SceneLogin\SceneLogin.h"
#include "Network\Login\MsgLoginAction.h"
#include "SceneLogin\LayerLoginLoad.h"
#include "Network\Login\MsgGameLoginQuery.h"
#include "SceneMain\SceneMain.h"
#include "MyCocosCommon\LayerHint.h"
#include "MyCocosCommon\LayerWaitting.h"

LoginMgr* LoginMgr::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
LoginMgr::LoginMgr()
{
	m_bReConnect = false;
}

//////////////////////////////////////////////////////////////////////////
LoginMgr* LoginMgr::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new LoginMgr();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}

////////////////////////////////////////////////////////////////////////
// Description: ���õ�¼����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LoginMgr::setLoginPercent(float fPercent)
{
	fPercent = ::GetValueInRightRange(fPercent, 0.f, 100.f);

	auto sceneLogin = Root::getInstance()->getSceneLogin();
	if (nullptr == sceneLogin)
	{
		return;
	}
	auto layerLoginLoad = (LayerLoginLoad*)sceneLogin->getChildByName("LayerLoginLoad");
	if (nullptr == layerLoginLoad)
	{
		return;
	}
	layerLoginLoad->setPercent(fPercent);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::sendReq(MSG_LOGIN_QUERY_ACTION eAction, MSG_LOGIN_QUERY_RESULT eResult /*= MSG_LOGIN_QUERY_RESULT_SUCC*/, int nParam1 /*= 0*/, int nParam2 /*= 0*/)
{
	CMsgGameLoginQuery msg;
	CHECK(msg.CreateLoginQuery(eAction, eResult, nParam1, nParam2));
	NetworkServe::getInstance()->sendMsg(msg);
}

////////////////////////////////////////////////////////////////////////
// Description: ��¼���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LoginMgr::loginFinish()
{
	auto sceneMain = Root::getInstance()->getSceneMain();
	if (!sceneMain)
	{
		sceneMain = SceneMain::create();
		CHECK(sceneMain);
		Director::getInstance()->replaceScene(sceneMain);
	}
	CHECK(sceneMain);

	this->setLoginPercent(100);
	LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_run);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_CLIENT_LOGIN_OVER);

	if (LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_ReconnectingFlag) != 0)
	{
		std::string strMessageBox = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_RECONNECT_SUCCESS);
		AddHint(strMessageBox);
		LayerWaitting::stopWaitting(sceneMain);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ����ontimer
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LoginMgr::onTimerHeartbeat()
{
	if (LogicDataMgr::getInstance()->getConnectStatus() < CONNECT_STATUS_login)
	{
		return;
	}
	
	// ÿ���Ӹ���һ��
	uint32_t unClientStartSecond = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_heartbeat_client_start);
	uint32_t unNowClientSecond = ::TimeGet(TIME_SECOND);
	if (unNowClientSecond < unClientStartSecond + 60)
	{
		return;
	}

	this->sendReq(MSG_LOGIN_QUERY_ACTION_HEARTBEAT);
}

////////////////////////////////////////////////////////////////////////
// Description: ��������
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LoginMgr::updateHeartbeat(uint32_t unServerUtcSecond)
{
	CHECK(unServerUtcSecond > 0);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_heartbeat_client_start, ::TimeGet(TIME_SECOND));
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_heartbeat_server_start, unServerUtcSecond);
}

////////////////////////////////////////////////////////////////////////
// Description: �������ʱ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: uint32_t
////////////////////////////////////////////////////////////////////////
uint32_t LoginMgr::getHeartbeat() const
{
	uint32_t nowClientSecond = ::TimeGet(TIME_SECOND);
	uint32_t startClientSecond = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_heartbeat_client_start);
	uint32_t startServerSecond = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_heartbeat_server_start);
	IF_NOT(nowClientSecond >= startClientSecond)
	{
		LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_heartbeat_client_start, nowClientSecond); 
	}
	return startServerSecond + nowClientSecond - startClientSecond;
}

////////////////////////////////////////////////////////////////////////
// Description: ������ҿ���
// Arguments:	1. û�п��ս���ע�����
//				2. ֻ��һ����ɫ�Զ�����
//				3. �ж����ɫѡ���ɫ		��ʱ����
// Author: ������(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserSnap()
{
	LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_choose);
	SpriteFrameCache::getInstance()->addSpriteFramesWithZipFile(MERGE_PIC_FILE_NAME, "lookface", MERGE_PIC_FILE_PASSWORD);	// lookface��ͼ

	auto sceneLogin = Root::getInstance()->getSceneLogin();

	if (LogicDataMgr::getInstance()->getLoginSnapSize() == 0)
	{
		CHECK(sceneLogin);
		sceneLogin->popLayerCreateNew();
	}
	else
	{
		// ��¼����ʱ, �������ؽ���
		if (sceneLogin)
		{
			sceneLogin->popLayerLoad();
		}
		
		// �Զ�ѡ���һ��
		USER_LOGIN_SNAP snap = { 0 };
		CMsgLoginAction msg;
		CHECK(LogicDataMgr::getInstance()->queryLoginSnap(0, snap));
		CHECK(msg.CreateChooseUser(snap.nUserID));
		NetworkServe::getInstance()->sendMsg(msg);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ������ҵ�¼��Ϣ
// Arguments:	ʵ�ʵ�¼����1
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserInfo()
{
	LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_login);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main.plist", "main.png", true);

	this->setLoginPercent(30);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_HEARTBEAT);		// ��һ����������
	this->sendReq(MSG_LOGIN_QUERY_ACTION_SERVER_GROUP);			// ��ʼ�𲽵�¼��Ϣ��ȡ
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserServerGroup()
{
	this->setLoginPercent(35);

	// �������л����Դ
	SpriteFrameCache::getInstance()->addSpriteFramesWithZipFile(VAR_PIC_FILE_NAME, "item", VAR_PIC_FILE_PASSWORD);	
	SpriteFrameCache::getInstance()->addSpriteFramesWithZipFile(VAR_PIC_FILE_NAME, "magic", VAR_PIC_FILE_PASSWORD);	
	SpriteFrameCache::getInstance()->addSpriteFramesWithZipFile(VAR_PIC_FILE_NAME, "money", VAR_PIC_FILE_PASSWORD);	
	SpriteFrameCache::getInstance()->addSpriteFramesWithZipFile(VAR_PIC_FILE_NAME, "lookface", VAR_PIC_FILE_PASSWORD);	


	this->sendReq(MSG_LOGIN_QUERY_ACTION_ALL_MONEY);	
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserMoney()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithZipFile(MERGE_PIC_FILE_NAME, "money", MERGE_PIC_FILE_PASSWORD);	// ����ͼ���ͼ

	
	this->setLoginPercent(40);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_MASKINFO);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserMaskInfo()
{
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battle.plist", "battle.png", true);
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common.plist", "common.png", true);

	this->setLoginPercent(45);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_PACKAGE);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserPackage()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithZipFile(MERGE_PIC_FILE_NAME, "item", MERGE_PIC_FILE_PASSWORD);	// ��Ʒͼ���ͼ
	this->setLoginPercent(50);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_ALL_FRIEND);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserFriend()
{
	this->setLoginPercent(55);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_CLIENT_TMPDATA);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserTmpData()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithZipFile(MERGE_PIC_FILE_NAME, "magic", MERGE_PIC_FILE_PASSWORD);	// ħ��ͼ���ͼ
	this->setLoginPercent(60);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_ALL_TASK);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processTask()
{
	this->setLoginPercent(70);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_UNREADMAILCOUNT);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserMail()
{
	this->setLoginPercent(80);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_SIGN);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserSign()
{
	this->setLoginPercent(90);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_ACTIVITES);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_INSTANCE_LIST);
	this->sendReq(MSG_LOGIN_QUERY_ACTION_SELF_SYNDICATE);
}

//////////////////////////////////////////////////////////////////////////
void LoginMgr::processUserSelfSyndicate()
{
	this->loginFinish();	// ��¼���
}
