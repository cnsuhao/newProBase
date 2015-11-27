////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: SceneLogin.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-2-4
////////////////////////////////////////////////////////////////////////
#include "SceneLogin\SceneLogin.h"
#include "SceneLogin\LayerLogin.h"
#include "Mgr/LogicDataMgr.h"
#include "Root.h"
#include "LayerInputName.h"
#include "LayerLoginBg.h"
#include "LayerCreateNew.h"
#include "LayerLoginLoad.h"
#include "Network\Login\MsgLoginAction.h"
#include "MyCocosCommon\LayerWaitting.h"
#include "LayerLoginLogo.h"
#include "LayerLoginSelectServer.h"
#include "MyCocosCommon\LayerHint.h"
#include "ConstTable\ConfigNetworkMgr.h"

//////////////////////////////////////////////////////////////////////////
bool SceneLogin::init()
{
	if(!Scene::init())
	{
		return false;
	}

	this->setName("SceneLogin");
	Root::getInstance()->setSceneLogin(this);

	auto layerLoginBg = LayerLoginBg::create();
	this->addChild(layerLoginBg);

	auto layerLogin = LayerLogin::create();
	this->addChild(layerLogin);

	static bool bShowLogo = false;
	if (!bShowLogo)
	{
		auto layerLogo = LayerLoginLogo::create();
		this->addChild(layerLogo);
		bShowLogo = true;
	}

	// 第一次启动读远程配置
	static bool bFirst = true;
	if (bFirst)
	{
		ConfigNetworkMgr::getInstance()->Init();// 网络获取配置
		bFirst = false;
	}
		
	return true;
}

//////////////////////////////////////////////////////////////////////////
SceneLogin::~SceneLogin()
{
	Root::getInstance()->setSceneLogin(nullptr);
}

//////////////////////////////////////////////////////////////////////////
void SceneLogin::OnConnectOK()
{
	if (LogicDataMgr::getInstance()->getConnectStatus() == CONNECT_STATUS_reqLogin)
	{
		auto layerLogin = (LayerLogin*)this->getChildByName("LayerLogin");
		CHECK(layerLogin);
		layerLogin->sendReqLogin();
	}
}

//////////////////////////////////////////////////////////////////////////
void SceneLogin::OnConnectBreak()
{
	this->reInit();
}

////////////////////////////////////////////////////////////////////////
// Description: 还原初始化状态
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SceneLogin::reInit()
{
	std::vector<Node*> vecNeedRemoveNode;
	for (auto child : _children)
	{
		if (child->getName() == "LayerInputName" ||
			child->getName() == "LayerCreateNew" ||
			child->getName() == "LayerLoginLoad" || 
			child->getName() == "LayerWaitting" )
		{
			vecNeedRemoveNode.push_back(child);
		}
	}

	for (auto node : vecNeedRemoveNode)
	{
		node->removeFromParent();
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 回调开始登陆
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SceneLogin::callbackStartLogin(const std::string& accountName, const std::string& accountPassword)
{
	auto layerInputName = (LayerInputName*)this->getChildByName("LayerInputName");
	if (layerInputName)
	{
		this->removeChild(layerInputName);
	}

	// 3秒CD
	static uint32_t clickCD = 0;
	uint32_t nowSecond = ::TimeGet(TIME_SECOND);
	if (clickCD + 3 >= nowSecond)
	{
		::AddHint("try again later, plz");
		return;
	}
	clickCD = nowSecond;

	// 设置账号名与密码
	LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_AccountName, accountName);;
	LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_AccountPwd, accountPassword);

	// 开始网络连接
	auto ip = LogicDataMgr::getInstance()->getLoginServerIp();
	auto port = LogicDataMgr::getInstance()->getLoginServerPort();
	CHECK(NetworkServe::getInstance()->getStatus() != NETWORK_STATUS_CONNECT);
	LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_reqLogin);
	LayerWaitting::startWaitting(this, true);	// 等待界面
	
	NetworkServe::getInstance()->connect(ip, port, 
		[=]()	// 连接成功
	{
		std::deque<int> deqSaveServer;
		for (int i = SAVE_DATA_choose_server_id1; i <= SAVE_DATA_choose_server_id3; i++)
		{
			if (::GetSaveData((SAVE_DATA)i) != 0)
			{
				deqSaveServer.push_back(::GetSaveData((SAVE_DATA)i));
			}
		}

		int newestID = LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_LoginServerId);
		bool bInDeq = false;
		for (auto iter = deqSaveServer.begin(); iter != deqSaveServer.end(); iter++)
		{
			if (newestID == *iter)
			{
				bInDeq = true;
				deqSaveServer.erase(iter);
				break;
			}
		}
		deqSaveServer.push_front(newestID);

		// 清空旧的
		::SetSaveData(SAVE_DATA_choose_server_id1, 0);
		::SetSaveData(SAVE_DATA_choose_server_id2, 0);
		::SetSaveData(SAVE_DATA_choose_server_id3, 0);

		// 保存新的
		int count = 0;
		for (auto iter = deqSaveServer.begin(); iter != deqSaveServer.end() && count < 3; count++, iter++)
		{
			::SetSaveData((SAVE_DATA)(SAVE_DATA_choose_server_id1 + count), *iter);
		}
	}, 
		[=]()	// 连接失败
	{
		LogSave("connect loginServer Failed! ip[%s], port[%u]", NetworkServe::getInstance()->getIp().c_str(), NetworkServe::getInstance()->getPort());
		LogicDataMgr::getInstance()->setConnectStatus(CONNECT_STATUS_none);
		LayerWaitting::stopWaitting(this);
		Root::getInstance()->popMessageBox("connect loginServer Failed!\n try other server!");
	});
}

////////////////////////////////////////////////////////////////////////
// Description: 弹出输入账号名窗口
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SceneLogin::popLayerInputName()
{
	// 默认先开启输入框方式, 以后接sdk, 判断平台弹出其他内容, 回调callbackStartLogin触发登陆
	auto layerInputName = (LayerInputName*)this->getChildByName("LayerInputName");
	if (!layerInputName)
	{
		layerInputName = LayerInputName::create();
		this->addChild(layerInputName);
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 弹出创建新角色界面
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SceneLogin::popLayerCreateNew()
{
	auto layerLogin = this->getChildByName("LayerLogin");
	if (layerLogin)
	{
		this->removeChild(layerLogin);
	}

	auto layerCreateNew = LayerCreateNew::create();
	this->addChild(layerCreateNew);
}

////////////////////////////////////////////////////////////////////////
// Description: 弹出加载界面
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SceneLogin::popLayerLoad()
{
	auto layerLogin = this->getChildByName("LayerLogin");
	if (layerLogin)
	{
		this->removeChild(layerLogin);
	}

	auto layerLoginLoad = this->getChildByName("LayerLoginLoad");
	if (layerLoginLoad)
	{
		this->removeChild(layerLoginLoad);
	}

	auto layerCreateNew = this->getChildByName("LayerCreateNew");
	if (layerCreateNew)
	{
		this->removeChild(layerCreateNew);
	}

	auto layerLoginLoadNew = LayerLoginLoad::create();
	this->addChild(layerLoginLoadNew);
}

////////////////////////////////////////////////////////////////////////
// Description: 弹出服务器列表界面
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void SceneLogin::popLayerServerList()
{
	auto layerLoginSelectServer = dynamic_cast<LayerLoginSelectServer*>(this->getChildByName("LayerLoginSelectServer"));
	if (!layerLoginSelectServer)
	{
		layerLoginSelectServer = LayerLoginSelectServer::create();
		this->addChild(layerLoginSelectServer);
	}
}

