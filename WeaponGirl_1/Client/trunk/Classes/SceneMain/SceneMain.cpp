////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: SceneMain.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-14
////////////////////////////////////////////////////////////////////////
#include "SceneMain.h"
#include "Network/NetworkServe.h"
#include "Root.h"
#include "LayerMain.h"
#include "MyCocosCommon/LayerHint.h"
#include "Network/Login/MsgLoginConnect.h"
#include "MyCocosCommon/LayerWaitting.h"
#include "Instance/LayerInstanceView.h"
#include "Instance/LayerInstanceMap.h"
#include "Home/LayerHomeView.h"
#include "Poker/LayerPokerView.h"
#include "Poker/LayerMyPoker.h"

//////////////////////////////////////////////////////////////////////////
bool SceneMain::init()
{
	if(!Scene::init())
	{
		return false;
	}

	this->setName("SceneMain");
	Root::getInstance()->setSceneMain(this);
	
	auto layerMain = LayerMain::create();
	if (layerMain)
	{
		this->addChild(layerMain);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
SceneMain::~SceneMain()
{
	Root::getInstance()->setSceneMain(nullptr);
}

//////////////////////////////////////////////////////////////////////////
void SceneMain::OnConnectOK()
{

}

//////////////////////////////////////////////////////////////////////////
void SceneMain::OnConnectBreak()
{
	int nBreakCode = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_BreakReasonCode);
	bool bNeedReconnect = Root::getInstance()->isNeedReconnectBreakCode(nBreakCode);
	if (!bNeedReconnect)
	{
		return;
	}

	// 3分钟内可以重连5次
	auto unNowSecond = ::TimeGet(TIME_SECOND);
	uint32_t unReconnectStartTime = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_ReconnectStartTime);
	if (unNowSecond > unReconnectStartTime + 60 * 3)
	{
		LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_ReconnectStartTime, unNowSecond);
		LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_ReconnectCount, 0);
	}

	if (LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_ReconnectCount) >= 5)
	{
		LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_ReconnectingFlag, 0);
		return;
	}
	LogicDataMgr::getInstance()->AddMemoryDataAttr(LOGIC_DATA_ReconnectCount, 1);

	// 延迟开始重连
	std::string strMessageBox = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_RECONNECT_START);
	::AddHint(strMessageBox, this);
	LayerWaitting::startWaitting(this, true);
	this->scheduleOnce(schedule_selector(SceneMain::reconnect), 3.0f);
}

//////////////////////////////////////////////////////////////////////////
LayerMain* SceneMain::getLayerMain() const
{
	return dynamic_cast<LayerMain*>(this->getChildByName("LayerMain"));
}

////////////////////////////////////////////////////////////////////////
// Description: 加载主界面页签
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool SceneMain::loadMainView(const std::string& rLayoutName)
{
	const int MAIN_VIEW_TAG = 5678;

	// 显示沉底
	for (auto child : _children)
	{
		if (MAIN_VIEW_TAG == child->getTag())
		{
			child->setLocalZOrder(-1);
			child->setVisible(false);
		}
	}

	// 弹出新界面
	Layer* childLayer = nullptr;
	if		("LayoutHome" == rLayoutName)
	{
		childLayer = dynamic_cast<Layer*>(this->getChildByName("LayerHomeView"));
		if (!childLayer)
		{
			childLayer = LayerHomeView::create();
			this->addChild(childLayer);
		}
	}
	else if ("LayoutInstance" == rLayoutName)
	{
		childLayer = dynamic_cast<Layer*>(this->getChildByName("LayerInstanceView"));
		if (!childLayer)
		{
			childLayer = LayerInstanceView::create();
			CHECKF(childLayer);
			this->addChild(childLayer);
		}
	}
	else if ("LayerInstanceMap" == rLayoutName)
	{
		childLayer = dynamic_cast<Layer*>(this->getChildByName("LayerInstanceMap"));
		if (!childLayer)
		{
			childLayer = LayerInstanceMap::create();
			CHECKF(childLayer);
			this->addChild(childLayer);
		}
	}
	else if ("LayoutLottery" == rLayoutName)
	{
	}
	else if ("LayoutChallenge" == rLayoutName)
	{
	}
	else if ("LayoutSmelt" == rLayoutName)
	{
	}
	else if ("LayoutPoker" == rLayoutName)
	{
		childLayer = dynamic_cast<Layer*>(this->getChildByName("LayerPokerView"));
		if (!childLayer)
		{
			childLayer = LayerPokerView::create();
			CHECKF(childLayer);
			this->addChild(childLayer);
		}
	}
	else if ("LayoutActivity" == rLayoutName)
	{
	}
	else
	{
		LogSave("error MainView[%s]", rLayoutName.c_str());
		return false;
	}

	// 选中层弹起
	IF_OK (childLayer)
	{
		childLayer->setTag(MAIN_VIEW_TAG);
		childLayer->setLocalZOrder(0);
		childLayer->setVisible(true);
	}	

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 弹出底栏对话框
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
bool SceneMain::popBottomDlg(const std::string& rImageViewName)
{
	if		("ImageViewMail" == rImageViewName)
	{
	}
	else if ("ImageViewAchievement" == rImageViewName)
	{
	}
	else if ("ImageViewFriend" == rImageViewName)
	{
	}
	else if ("ImageViewShop" == rImageViewName)
	{
	}
	else if ("ImageViewNotify" == rImageViewName)
	{
	}
	else if ("ImageViewSetup" == rImageViewName)
	{
	}
	else
	{
		LogSave("error BottomDlg[%s]", rImageViewName.c_str());
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 重连
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void SceneMain::reconnect(float dt)
{
	// 开始重连, 直接连接游戏服
	NetworkServe::getInstance()->closeSocket();

	auto strIP = LogicDataMgr::getInstance()->GetMemoryStringAttr(LOGIC_STRING_GameServerIp);	// 保存游戏服ip
	auto nPort = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_GameServerPort);	// 保存游戏服端口

	NetworkServe::getInstance()->connect(strIP, nPort,
		[=]()	// 连接成功
	{
		// 发送账号验证
		CMsgLoginConnect msg;
		CHECK(msg.CreateAccountConnect(LogicDataMgr::getInstance()->GetMemoryStringAttr(LOGIC_STRING_AccountName).c_str(), LogicDataMgr::getInstance()->GetMemoryStringAttr(LOGIC_STRING_AccountPwd).c_str()));
		NetworkServe::getInstance()->sendMsg(msg);

		LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_reqPwd);	// 状态更新
		LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_ReconnectingFlag, 1);	},
		[=]()	// 连接失败
	{
		LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_none);
		NetworkServe::getInstance()->closeSocket();
		LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_ReconnectingFlag, 0);

		std::string strMessageBox = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_CONNECT_GAME_SERVER_FAILED);
		::AddHint(strMessageBox);
		Root::getInstance()->processConnectFailed();	
	});
}
