////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetServerInfo.cpp
// Author: ������(Peng Wenqi)
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

	// ���ɼ�������
	if (!bSee)
	{
		return false;
	}

	// ���Է�����, �ڷǵ��԰汾����ʾ
#ifndef COCOS2D_DEBUG
	if (bDebug)
	{
		return false;
	}
#endif

	this->copyProperties(csbLayout);
	this->copyClonedWidgetChildren(csbLayout);

	
	// �����븽����������
	std::string strServerName = StringUtils::format("%s-%s",
		ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_short_name).c_str(),
		ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_name).c_str());
	ui::Helper::setStringText(this, "TextServerName", strServerName);
	ui::Helper::setStringText(this, "TextServerDetail", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_server_list, idServer, SERVER_LIST_DATA_explain));

	// ֹͣ���
	if (!bOpen)
	{
		auto image = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(this, "ImageBg"));
		image->setShaderEffect(MY_SHADER_EFFECT_BLACK_AND_WHITE);	
	}
	
	m_idServer = idServer;
	return true;
}
