////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLogin.cpp
// Author: ������(Peng Wenqi)
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

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerLogin.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// ���봥�����ȼ�
	if (this->initTouchPriority("LayerLogin", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerLogin::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// �ؼ�����
	auto chooseServerButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewChooseServer"));
	CHECKF(chooseServerButton);
	chooseServerButton->setAutoTouchChangeRenderer(true);
	chooseServerButton->setAutoTouchAction();
	chooseServerButton->addClickEventListener(CC_CALLBACK_1(LayerLogin::clickChooseServer, this));

	auto loginButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewLogin"));
	CHECKF(loginButton);
	loginButton->setAutoTouchChangeRenderer(true);
	loginButton->addClickEventListener(CC_CALLBACK_1(LayerLogin::clickLogin, this));

	m_bActiveButton = false;	// ��ʼ��ʱ��ť������

	// ������ʱ
	this->scheduleUpdate();

	// ����뷵��ǰ, �Ƚ����ػ�������ȥ
	ui::Helper::setStringText(m_pCsbWidget, "TextShortNotify", ::GetSaveStr(SAVE_DATA_notify_short));

	// ��������
	std::string url = ConfigNetworkMgr::getInstance()->getBaseUrl() + "notify_short.txt";
	network::HttpRequest* request = new network::HttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(LayerLogin::recvHttp, this));
	request->setTag("notify_short");
	network::HttpClient::getInstance()->send(request);
	request->release();

	// ��ȡ��һ�ε�½����������, û�����Զ���ʾ���µ�
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
	// ����ѡ������
	getFather()->popLayerServerList();
}

//////////////////////////////////////////////////////////////////////////
void LayerLogin::clickLogin( Ref* pSender )
{
	auto idLoginServer = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_LoginServerId);
	CHECK(idLoginServer);

	// ���������
	getFather()->popLayerInputName();
}

//////////////////////////////////////////////////////////////////////////
bool LayerLogin::onTouchBegan(Touch *touch, Event *unused_event)
{
	// �̵����ٴ��������е��¼�
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: ���չ��
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description: ���µ�¼����������
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description: ����������ݽ��մ���
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerLogin::finishConfigNetworkData()
{
	// ���û��ѡ�������, ѡ�����µķ�����
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

	// �߼�ÿ����2��
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

