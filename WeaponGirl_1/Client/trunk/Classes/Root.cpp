////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: Root.cpp
// Author: 彭文奇(Peng Wenqi)
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

	// 设备设置
	Device::setAccelerometerEnabled(true);	// 重力加速计
	Device::setKeepScreenOn(true);			// 屏幕常亮

	ConstTableMgr::getInstance()->Init();	// 常量表第一次预读

	// 子目录搜索
	FileUtils::getInstance()->addSearchPath("ui");

	// 各个数据系统
	NetworkServe::getInstance();					// 网络线程启动

	// 本地逻辑数据初始化
	LogicDataMgr::getInstance();						// 逻辑数据
	BattleDataMgr::getInstance();						// 战斗数据

	// 根定时器回调设置
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
// Description: 飞速定时器
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Root::onTimerFastest( float dt )
{
	if (LogicDataMgr::getInstance()->getConnectStatus() != CONNECT_STATUS_none)
	{
		NetworkServe::getInstance()->recvMsg();	// 接收消息处理
	}
	this->OnConnectBreak();					// 断开后处理消息
}

////////////////////////////////////////////////////////////////////////
// Description: 秒级定时器
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Root::onTimerSecond( float dt )
{
	LoginMgr::getInstance()->onTimerHeartbeat();
	SpineCache::getInstance()->onTimerProloadCache();
	NetworkServe::getInstance()->onTimer(0);
}

////////////////////////////////////////////////////////////////////////
// Description: 分钟级定时器
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description: 网络断开主线程响应
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description: 是否需要重连的断开码
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool Root::isNeedReconnectBreakCode(int nBreakCode)
{
	switch (nBreakCode)
	{
	case KICK_REASON_DEFAULT:
	case KICK_REASON_LOGIN_TIMEOUT:

	// 调试时命令踢会重连
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
// Description: 缓存自动清理
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description: 弹出MessageBox
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
// Description: 连接失败处理
// Arguments:
// Author: 彭文奇(Peng Wenqi)
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
