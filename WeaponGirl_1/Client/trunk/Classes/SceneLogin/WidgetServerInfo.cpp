////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetServerInfo.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/10
////////////////////////////////////////////////////////////////////////
#include "WidgetServerInfo.h"
#include "ConstTable\ConstTableMgr.h"

//////////////////////////////////////////////////////////////////////////
WidgetServerInfo::WidgetServerInfo()
{
	m_idServer = ID_NONE;
}

//////////////////////////////////////////////////////////////////////////
WidgetServerInfo::~WidgetServerInfo()
{

}

//////////////////////////////////////////////////////////////////////////
WidgetServerInfo* WidgetServerInfo::create(Node* pCsbNode, OBJID idServer)
{
	WidgetServerInfo* pRet = new(std::nothrow) WidgetServerInfo();
	if (pRet && pRet->init(pCsbNode, idServer))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
bool WidgetServerInfo::init(Node* pCsbNode, OBJID idServer)
{
	CHECKF(pCsbNode && idServer && ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_server_list, idServer));
	auto csbLayout = (ui::Widget*)pCsbNode->getChildByName("Layout");
	CHECKF(csbLayout);

	bool bOpen = !!ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_open);
	bool bSee = !!ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_see);
	bool bDebug = !!ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_debug);

	// 不可见不创建
	if (!bSee)
	{
		return false;
	}

	// 调试服务器, 在非调试版本不显示
#ifndef COCOS2D_DEBUG
	if (bDebug)
	{
		return false;
	}
#endif

	this->copyProperties(csbLayout);
	this->copyClonedWidgetChildren(csbLayout);

	
	// 名字与附加内容设置
	std::string strServerName = StringUtils::format("%s-%s",
		ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_short_name).c_str(),
		ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_name).c_str());
	ui::Helper::setStringText(this, "TextServerName", strServerName);
	ui::Helper::setStringText(this, "TextServerDetail", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_explain));

	// 停止标记
	if (!bOpen)
	{
		auto image = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(this, "ImageBg"));
		image->setShaderEffect(MY_SHADER_EFFECT_BLACK_AND_WHITE);	
	}
	
	m_idServer = idServer;
	return true;
}
