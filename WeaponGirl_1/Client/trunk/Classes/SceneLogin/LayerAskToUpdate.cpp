////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerAskToUpdate.cpp
// Author: ������(Peng Wenqi)
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

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerAskToUpdate.csb");
	CHECKF(m_pCsbWidget);
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// �Ƽ���������ť
	auto cancelButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewCancel"));
	CHECKF(cancelButton);
	cancelButton->setTouchEnabled(true);
	cancelButton->setAutoTouchChangeRenderer(true);
	cancelButton->addClickEventListener(CC_CALLBACK_1(LayerAskToUpdate::clickCancel, this));

	// ȫ����������ť
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
