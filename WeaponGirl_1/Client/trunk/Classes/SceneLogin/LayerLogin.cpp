////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLogin.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#include "LayerLogin.h"
#include "Root.h"
#include "SceneLogin.h"
#include "Network\Login\MsgReqLogin.h"
#include "ConstTable\ConfigNetworkMgr.h"
#include "Spine\SpineModel.h"

//////////////////////////////////////////////////////////////////////////
bool LayerLogin::init()
{
	this->setName("LayerLogin");

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerLogin.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerLogin", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerLogin::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 控件监听
	auto chooseServerButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewChooseServer"));
	CHECKF(chooseServerButton);
	chooseServerButton->setAutoTouchChangeRenderer(true);
	chooseServerButton->setAutoTouchAction();
	chooseServerButton->addClickEventListener(CC_CALLBACK_1(LayerLogin::clickChooseServer, this));

	auto loginButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewLogin"));
	CHECKF(loginButton);
	loginButton->setAutoTouchChangeRenderer(true);
	loginButton->addClickEventListener(CC_CALLBACK_1(LayerLogin::clickLogin, this));

	m_bActiveButton = false;	// 初始化时按钮不激活

	// 开启定时
	this->scheduleUpdate();

	// 广告码返回前, 先将本地缓存的填进去
	ui::Helper::setStringText(m_pCsbWidget, "TextShortNotify", ::GetSaveStr(SAVE_DATA_notify_short));

	// 请求广告码
	std::string url = ConfigNetworkMgr::getInstance()->getBaseUrl() + "notify_short.txt";
	network::HttpRequest* request = new network::HttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(LayerLogin::recvHttp, this));
	request->setTag("notify_short");
	network::HttpClient::getInstance()->send(request);
	request->release();

	// 读取上一次登陆服务器名字, 没有则自动显示最新的
	if (::GetSaveData(SAVE_DATA_choose_server_id1) != 0)
	{
		LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_LoginServerId, ::GetSaveData(SAVE_DATA_choose_server_id1));
		this->updateLoginServerName();
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
void LayerLogin::clickChooseServer( Ref* pSender )
{
	// 弹出选服界面
	getFather()->popLayerServerList();
}

//////////////////////////////////////////////////////////////////////////
void LayerLogin::clickLogin( Ref* pSender )
{
	auto idLoginServer = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_LoginServerId);
	CHECK(idLoginServer);

	// 弹出输入层
	getFather()->popLayerInputName();
}

//////////////////////////////////////////////////////////////////////////
bool LayerLogin::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: 接收广告
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerLogin::recvHttp(network::HttpClient* client, network::HttpResponse* response)
{
	CHECK(response);

	if (!response->isSucceed())
	{
		LogSave("response failed");
		LogSave("error buffer: %s", response->getErrorBuffer());
		return;
	}

	LogSave("ConfigNetworkMgr::recvHttp [%s] completed", response->getHttpRequest()->getTag());

	std::vector<char> *buffer = response->getResponseData();
	std::string strData(buffer->begin(), buffer->end());
	std::string load_str = FileUtils::getInstance()->getRemoveBomStringData(strData.c_str(), strData.size());
	::SetSaveStr(SAVE_DATA_notify_short, load_str);
	ui::Helper::setStringText(m_pCsbWidget, "TextShortNotify", load_str);
}

////////////////////////////////////////////////////////////////////////
// Description: 更新登录服务器名称
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerLogin::updateLoginServerName()
{
	CHECK(m_pCsbWidget);
	auto idLoginServer = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_LoginServerId);
	if (ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_server_list, idLoginServer))
	{
		std::string strServerName = StringUtils::format("%s-%s",
			ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idLoginServer, SERVER_LIST_DATA_short_name).c_str(),
			ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idLoginServer, SERVER_LIST_DATA_name).c_str());
		ui::Helper::setStringText(m_pCsbWidget, "TextServerName", strServerName);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 完成网络数据接收处理
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerLogin::finishConfigNetworkData()
{
	// 如果没有选择服务器, 选择最新的服务器
	if (LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_LoginServerId) == ID_NONE)
	{
		OBJID idNewestServer = ConstTableMgr::getInstance()->GetNewestServerID();
		CHECK(idNewestServer);
		LogicDataMgr::getInstance()->SetMemoryDataAttr(LOGIC_DATA_LoginServerId, idNewestServer);
	}

	this->updateLoginServerName();
}

//////////////////////////////////////////////////////////////////////////
void LayerLogin::update(float delta)
{
	Layer::update(delta);

	// 逻辑每秒检查2次
	static int64_t lastMS = 0;
	int64_t nowMS = ::GetUtcMillisecond();
	if (nowMS < lastMS + 500)
	{
		return;
	}
	lastMS = nowMS;

	CHECK(m_pCsbWidget);

	if (!ConfigNetworkMgr::getInstance()->isInitFinish())
	{
		ui::Helper::setVisable(m_pCsbWidget, "TextLoading", true);

		auto chooseServerButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewChooseServer"));
		auto loginButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewLogin"));
		CHECK(chooseServerButton && loginButton);
		chooseServerButton->setTouchEnabled(false);
		chooseServerButton->setShaderEffect(MY_SHADER_EFFECT_BLACK_AND_WHITE);
		loginButton->setTouchEnabled(false);
		loginButton->setShaderEffect(MY_SHADER_EFFECT_BLACK_AND_WHITE);
	
	}
	else if (!m_bActiveButton)
	{
		ui::Helper::setVisable(m_pCsbWidget, "TextLoading", false);

		auto chooseServerButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewChooseServer"));
		auto loginButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewLogin"));
		CHECK(chooseServerButton && loginButton);
		chooseServerButton->setTouchEnabled(true);
		chooseServerButton->setShaderEffect(MY_SHADER_EFFECT_NONE);
		loginButton->setTouchEnabled(true);
		loginButton->setShaderEffect(MY_SHADER_EFFECT_NONE);

		m_bActiveButton = true;
	}
	
}

//////////////////////////////////////////////////////////////////////////
void LayerLogin::sendReqLogin()
{
	CMsgReqLogin msg;
	IF_OK (msg.CreateEmpty())
	{
		NetworkServe::getInstance()->sendMsg(msg);
	}
}

