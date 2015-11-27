////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerAskToUpdate.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/19
////////////////////////////////////////////////////////////////////////
#include "LayerAskToUpdate.h"

//////////////////////////////////////////////////////////////////////////
LayerAskToUpdate* LayerAskToUpdate::create(int totalSize, const UpdateListener& listen)
{
	LayerAskToUpdate* pRet = new(std::nothrow) LayerAskToUpdate();
	if (pRet && pRet->init(totalSize, listen))
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
bool LayerAskToUpdate::init(int totalSize, const UpdateListener& listen)
{
	this->setName("LayerAskToUpdate");

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerAskToUpdate.csb");
	CHECKF(m_pCsbWidget);
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 推荐服务器按钮
	auto cancelButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewCancel"));
	CHECKF(cancelButton);
	cancelButton->setTouchEnabled(true);
	cancelButton->setAutoTouchChangeRenderer(true);
	cancelButton->addClickEventListener(CC_CALLBACK_1(LayerAskToUpdate::clickCancel, this));

	// 全部服务器按钮
	auto okButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewOK"));
	CHECKF(okButton);
	okButton->setTouchEnabled(true);
	okButton->setAutoTouchChangeRenderer(true);
	okButton->addClickEventListener(CC_CALLBACK_1(LayerAskToUpdate::clickOK, this));

	m_listener = listen;

	float sizeMB = totalSize / 1024.f / 1024.f;
	std::string strSize = StringUtils::format("%.2f", sizeMB);
	ui::Helper::setStringText(m_pCsbWidget, "TextUpdateSizeData", strSize);

	this->setLocalZOrder(999);

	return true;

}

//////////////////////////////////////////////////////////////////////////
void LayerAskToUpdate::clickCancel(Ref* pSender)
{
	Director::getInstance()->end();
}

//////////////////////////////////////////////////////////////////////////
void LayerAskToUpdate::clickOK(Ref* pSender)
{
	CHECK(m_listener);
	m_listener();
	this->removeFromParent();
}
