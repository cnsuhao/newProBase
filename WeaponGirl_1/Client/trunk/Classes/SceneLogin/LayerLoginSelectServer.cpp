////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLoginSelectServer.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/10
////////////////////////////////////////////////////////////////////////
#include "LayerLoginSelectServer.h"
#include "WidgetServerSeparator.h"
#include "SaveData\SaveData.h"
#include "WidgetServerInfo.h"
#include "ConstTable\ConstTableMgr.h"
#include "Mgr/LogicDataMgr.h"
#include "Root.h"
#include "SceneLogin.h"
#include "LayerLogin.h"

//////////////////////////////////////////////////////////////////////////
bool LayerLoginSelectServer::init()
{
	this->setName("LayerLoginSelectServer");
	m_pCsbNodeServerSeparator = nullptr;
	m_pCsbNodeServerInfo = nullptr;

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerLoginSelectServer.csb");
	CHECKF(m_pCsbWidget);
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);
	m_pCsbNodeServerSeparator = CSLoader::createNode("NodeServerSeparator.csb");
	m_pCsbNodeServerInfo = CSLoader::createNode("NodeServerInfo.csb");
	CHECKF(m_pCsbNodeServerSeparator && m_pCsbNodeServerInfo);
	m_pCsbNodeServerSeparator->retain();
	m_pCsbNodeServerInfo->retain();

	// 加入触摸优先级
	if (this->initTouchPriority("LayerLoginSelectServer", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerLoginSelectServer::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 关闭按钮
	auto closeButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewClose"));
	CHECKF(closeButton);
	closeButton->setTouchEnabled(true);
	closeButton->setAutoTouchChangeRenderer(true);
	closeButton->addClickEventListener(CC_CALLBACK_1(LayerLoginSelectServer::clickClose, this));

	// 推荐服务器按钮
	auto recommandButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewRecommand"));
	CHECKF(recommandButton);
	recommandButton->setTouchEnabled(true);
	recommandButton->setAutoTouchChangeRenderer(true);
	recommandButton->addClickEventListener(CC_CALLBACK_1(LayerLoginSelectServer::clickRecommond, this));

	// 全部服务器按钮
	auto allButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewAll"));
	CHECKF(allButton);
	allButton->setTouchEnabled(true);
	allButton->setAutoTouchChangeRenderer(true);
	allButton->addClickEventListener(CC_CALLBACK_1(LayerLoginSelectServer::clickAll, this));

	// 服务器列表时间监听
	auto serverListView = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewServerList"));
	CHECKF(serverListView);
	serverListView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(LayerLoginSelectServer::selectedServerListEvent, this));

	// 默认打开推荐服务器列表
	this->clickRecommond(nullptr);

	return true;
}

//////////////////////////////////////////////////////////////////////////
LayerLoginSelectServer::~LayerLoginSelectServer()
{
	CC_SAFE_RELEASE(m_pCsbNodeServerSeparator);
	CC_SAFE_RELEASE(m_pCsbNodeServerInfo);
}

////////////////////////////////////////////////////////////////////////
// Description: 选择服务器
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerLoginSelectServer::selectedServerListEvent(Ref* pSender, ui::ListView::EventType type)
{
	if (type != cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END)
	{
		return;
	}

	auto serverList = dynamic_cast<ui::ListView*>(pSender);
	CHECK(serverList);

	auto serverInfo = dynamic_cast<WidgetServerInfo*>(serverList->getItem(serverList->getCurSelectedIndex()));
	if (!serverInfo)
	{
		return;
	}
	
	OBJID idServer = serverInfo->getServerID();
	CHECK(idServer);
	LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_LoginServerId, idServer);
	auto sceneLogin = Root::getInstance()->getSceneLogin();
	CHECK(sceneLogin);
	auto layerLogin = dynamic_cast<LayerLogin*>(sceneLogin->getChildByName("LayerLogin"));
	CHECK(layerLogin);
	layerLogin->updateLoginServerName();

	// 下一帧关闭
	this->scheduleOnce([=](float){this->removeFromParent(); }, 0.f, "close LayerLoginSelectServer");
}

//////////////////////////////////////////////////////////////////////////
bool LayerLoginSelectServer::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerLoginSelectServer::clickRecommond(Ref* pSender)
{
	CHECK(m_pCsbWidget);
	auto serverListView = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewServerList"));
	CHECK(serverListView);

	auto imageviewRecommand = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewRecommand"));
	auto imageviewAll = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewAll"));
	CHECK(imageviewRecommand && imageviewAll);

	if (MY_SHADER_EFFECT_BLACK_AND_WHITE == imageviewRecommand->getShaderEffect())
	{
		return;
	}

	imageviewRecommand->setShaderEffect(MY_SHADER_EFFECT_BLACK_AND_WHITE);
	imageviewAll->setShaderEffect(MY_SHADER_EFFECT_NONE);

	// 清空列表
	serverListView->removeAllItems();

	// 分隔符
	std::string strTitle = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_USER_NEWEST_SERVER);
	auto sep1 = WidgetServerSeparator::create(m_pCsbNodeServerSeparator, strTitle);
	CHECK(sep1);
	serverListView->pushBackCustomItem(sep1);

	// 最新服务器
	OBJID idNewestServer = ConstTableMgr::getInstance()->GetNewestServerID();
	if (idNewestServer)
	{
		auto serverInfo = WidgetServerInfo::create(m_pCsbNodeServerInfo, idNewestServer);
		if (serverInfo)
		{
			serverListView->pushBackCustomItem(serverInfo);
		}
	}


	// 分隔符
	strTitle = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_USER_LOGINED_SERVER);
	auto sep2 = WidgetServerSeparator::create(m_pCsbNodeServerSeparator, strTitle);
	CHECK(sep2);
	serverListView->pushBackCustomItem(sep2);

	// 上次登陆服务器
	for (int i = SAVE_DATA_choose_server_id1; i <= SAVE_DATA_choose_server_id3; i++)
	{
		OBJID idServer = ::GetSaveData((SAVE_DATA)i);
		if (idServer)
		{
			auto serverInfo = WidgetServerInfo::create(m_pCsbNodeServerInfo, idServer);
			if (serverInfo)
			{
				serverListView->pushBackCustomItem(serverInfo);
			}
		}
	}

	serverListView->scrollToTop(0, true);
}

//////////////////////////////////////////////////////////////////////////
void LayerLoginSelectServer::clickAll(Ref* pSender)
{
	CHECK(m_pCsbWidget);
	auto serverListView = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewServerList"));
	CHECK(serverListView);

	auto imageviewRecommand = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewRecommand"));
	auto imageviewAll = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewAll"));
	CHECK(imageviewRecommand && imageviewAll);
	if (MY_SHADER_EFFECT_BLACK_AND_WHITE == imageviewAll->getShaderEffect())
	{
		return;
	}
	imageviewRecommand->setShaderEffect(MY_SHADER_EFFECT_NONE);
	imageviewAll->setShaderEffect(MY_SHADER_EFFECT_BLACK_AND_WHITE);

	// 清空列表
	serverListView->removeAllItems();

	// 分隔符
	std::string strTitle = ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_USER_ALL_SERVER);
	auto sep = WidgetServerSeparator::create(m_pCsbNodeServerSeparator, strTitle);
	CHECK(sep);
	serverListView->pushBackCustomItem(sep);

	// 全部服务器
	VEC_DB_KEY vec;
	CHECK(ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_server_list, vec));
	std::sort(vec.begin(), vec.end(), [this](const int64_t& l, const int64_t& r)->bool{
		return l > r;
	});
	for (auto id : vec)
	{
		auto serverInfo = WidgetServerInfo::create(m_pCsbNodeServerInfo, id);
		if (serverInfo)
		{
			serverListView->pushBackCustomItem(serverInfo);
		}
	}

	serverListView->scrollToTop(0, true);
}
