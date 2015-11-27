////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: Root.cpp
// Author: ������(Peng Wenqi)
// Created: 2015-1-20
////////////////////////////////////////////////////////////////////////
#include "Root.h"
#include "Global/Global.h"
#include "SceneMain/SceneMain.h"
#include "SceneLogin/SceneLogin.h"
#include "SceneBattle/SceneBattle.h"
#include "MyCocosCommon/LayerMessageBox.h"
#include "Mgr/LoginMgr.h"
#include "MyCocosCommon/LayerHint.h"
#include "MyCocosCommon/LayerWaitting.h"
#include "ConstTable/ConfigNetworkMgr.h"
#include "Mgr/MoneyMgr.h"

Root* Root::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////////
Root* Root::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new Root();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void Root::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}

//////////////////////////////////////////////////////////////////////////
bool Root::init()
{
	m_pSceneMain = nullptr;
	m_pSceneLogin = nullptr;
	m_pSceneBattle = nullptr;

	// �豸����
	Device::setAccelerometerEnabled(true);	// �������ټ�
	Device::setKeepScreenOn(true);			// ��Ļ����

	ConstTableMgr::getInstance()->Init();	// �������һ��Ԥ��

	// ��Ŀ¼����
	FileUtils::getInstance()->addSearchPath("ui");

	// ��������ϵͳ
	NetworkServe::getInstance();					// �����߳�����

	// �����߼����ݳ�ʼ��
	LogicDataMgr::getInstance();						// �߼�����
	BattleDataMgr::getInstance();						// ս������

	// ����ʱ���ص�����
	auto schedulea = Director::getInstance()->getScheduler();
	schedulea->schedule(schedule_selector(Root::onTimerFastest), this, 0.05f, false);
	schedulea->schedule(schedule_selector(Root::onTimerSecond), this, 1.f, false);
	schedulea->schedule(schedule_selector(Root::onTimerMinute), this, 60.f, false);


	return true;
}

//////////////////////////////////////////////////////////////////////////
void Root::release()
{
	NetworkServe::destroyInstance();
	SpineCache::destroyInstance();
}

////////////////////////////////////////////////////////////////////////
// Description: ���ٶ�ʱ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Root::onTimerFastest( float dt )
{
	if (LogicDataMgr::getInstance()->getConnectStatus() != CONNECT_STATUS_none)
	{
		NetworkServe::getInstance()->recvMsg();	// ������Ϣ����
	}
	this->OnConnectBreak();					// �Ͽ�������Ϣ
}

////////////////////////////////////////////////////////////////////////
// Description: �뼶��ʱ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Root::onTimerSecond( float dt )
{
	LoginMgr::getInstance()->onTimerHeartbeat();
	SpineCache::getInstance()->onTimerProloadCache();
	NetworkServe::getInstance()->onTimer(0);
}

////////////////////////////////////////////////////////////////////////
// Description: ���Ӽ���ʱ��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Root::onTimerMinute( float dt )
{
	this->autoClearCache();
}

void Root::OnConnectOK()
{
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_BreakReasonCode, KICK_REASON_DEFAULT);
	LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_BreakReason, "");

	if (m_pSceneLogin)	
		m_pSceneLogin->OnConnectOK();

	if (m_pSceneMain)	
		m_pSceneMain->OnConnectOK();

	if (m_pSceneBattle)	
		m_pSceneBattle->OnConnectOK();
}

////////////////////////////////////////////////////////////////////////
// Description: ����Ͽ����߳���Ӧ
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void Root::OnConnectBreak()
{
	if (LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_NeedProcessNetBreak) == 0)
	{
		return;
	}
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_NeedProcessNetBreak, 0);
	NetworkServe::getInstance()->recvMsgBreak();
	LogSave("Root::OnConnectBreak");

	auto breakReason = LogicDataMgr::getInstance()->GetMemoryStringAttr(LOGIC_STRING_BreakReason);
	int nBreakCode = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_BreakReasonCode);
	bool bNeedReconnect = Root::getInstance()->isNeedReconnectBreakCode(nBreakCode);
	if (breakReason.size() > 0)
	{
		if (bNeedReconnect)
		{
			::AddHint(breakReason);
		}
		else
		{
			this->popMessageBox(breakReason, "", MESSAGE_BOX_MODE_OK, false, [=](cocos2d::Ref*, MESSAGE_BOX_CLICK){
				auto oldLoginScene = Root::getInstance()->getSceneLogin();
				if (!oldLoginScene)
				{
					auto scene = SceneLogin::create();
					Director::getInstance()->replaceScene(scene);
				}
			});
		}
		
	}

	if (m_pSceneBattle)
		m_pSceneBattle->OnConnectBreak();

	if (m_pSceneMain)
		m_pSceneMain->OnConnectBreak();

	if (m_pSceneLogin)
		m_pSceneLogin->OnConnectBreak();
}

////////////////////////////////////////////////////////////////////////
// Description: �Ƿ���Ҫ�����ĶϿ���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Root::isNeedReconnectBreakCode(int nBreakCode)
{
	switch (nBreakCode)
	{
	case KICK_REASON_DEFAULT:
	case KICK_REASON_LOGIN_TIMEOUT:

	// ����ʱ�����߻�����
#ifdef COCOS2D_DEBUG
	case KICK_REASON_GMCMD:
#endif
		return true;
		break;
	default:
		return false;
		break;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: �����Զ�����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Root::autoClearCache()
{
	if (Director::getInstance()->getOpenGLView())
	{
		SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
		Director::getInstance()->getTextureCache()->removeUnusedTextures();
		log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ����MessageBox
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Root::popMessageBox(const std::string& message, const std::string& title /*= ""*/, MESSAGE_BOX_MODE mode /*= MESSAGE_BOX_MODE_OK*/, bool bCloseByBg /*= false*/, MessageBoxClickCallback callback /*= nullptr*/, Ref* pRef /*= nullptr*/)
{
	auto scene = Director::getInstance()->getRunningScene();
	CHECK(scene);
	auto layer = LayerMessageBox::createWithMessage(message, title, mode, bCloseByBg, callback, pRef);
	CHECK(layer);
	scene->addChild(layer);
}

////////////////////////////////////////////////////////////////////////
// Description: ����ʧ�ܴ���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Root::processConnectFailed()
{
	if (m_pSceneLogin)
	{
		m_pSceneLogin->reInit();
	}
	else
	{
		auto scene = SceneLogin::create();
		Director::getInstance()->replaceScene(scene);
	}
}
