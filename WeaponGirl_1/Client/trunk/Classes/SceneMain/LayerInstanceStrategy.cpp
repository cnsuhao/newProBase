////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceStrategy.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceStrategy.h"
#include "Root.h"
#include "mgr/InstanceMgr.h"
#include "SceneMain.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceStrategy::~LayerInstanceStrategy()
{
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceStrategy::init()
{
	this->setName("LayerInstanceStrategy");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceStrategy.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerInstanceStrategy", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceStrategy::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceStrategy::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 初始化列表
	auto listViewStrategy = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewStrategy"));
	CHECKF(listViewStrategy);
	auto layoutStrategy = dynamic_cast<ui::Layout*>(ui::Helper::seekWidgetByName(listViewStrategy, "LayoutStrategy"));
	CHECKF(layoutStrategy);
	listViewStrategy->setItemModel(layoutStrategy);
	listViewStrategy->removeItem(0);

	// 初始化控件
	// 关闭按钮
	CHECKF(this->initButtonListen("ImageViewClose", [=](Ref*){
		this->removeFromParent();
	}));

	// 发表评论按钮
	CHECKF(this->initButtonListen("ImageViewSend", [=](Ref*){

	}));

	// 背景半透处理
	::AddBlurScreen(this, true);
	return true;
}

// 初始化监听按钮
bool LayerInstanceStrategy::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback)
{
	CHECKF(m_pCsbWidget);
	auto pImage = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, strName));
	CHECKF(pImage);
	pImage->addClickEventListener(callback);
	pImage->setAutoTouchAction(true);
	pImage->setTouchEnabled(true);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceStrategy::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceStrategy::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}