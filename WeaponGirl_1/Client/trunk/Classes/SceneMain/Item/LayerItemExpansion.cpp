////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerItemExpansion.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-10-28
////////////////////////////////////////////////////////////////////////
#include "LayerItemExpansion.h"
#include "Root.h"
#include "Network\Item\MsgGameItem.h"

//////////////////////////////////////////////////////////////////////////
LayerItemExpansion* LayerItemExpansion::create()
{
	LayerItemExpansion* pRet = new(std::nothrow) LayerItemExpansion();
	if (pRet && pRet->init())
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
bool LayerItemExpansion::init()
{
	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerItemExpansion.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerItemExpansion", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerItemExpansion::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerItemExpansion::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 初始化控件
	auto imageViewOk = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewOk"));
	CHECKF(imageViewOk);
	imageViewOk->addClickEventListener([=](Ref*){
		CMsgGameItem msg;
		CHECK(msg.CreateMsgItem(MSG_ITEM_ACTION_EXPANSION, MSG_ITEM_RESULT_SUCC, 0, 0));
		NetworkServe::getInstance()->sendMsg(msg);
		this->removeFromParent();
	});

	auto imageViewCancel = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewCancel"));
	CHECKF(imageViewCancel);
	imageViewCancel->addClickEventListener([=](Ref*){
		this->removeFromParent();
	});

	auto imageViewClose = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewClose"));
	CHECKF(imageViewClose);
	imageViewClose->addClickEventListener([=](Ref*){
		this->removeFromParent();
	});

	// 背景半透处理
	::AddBlurScreen(this, true);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerItemExpansion::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerItemExpansion::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}

