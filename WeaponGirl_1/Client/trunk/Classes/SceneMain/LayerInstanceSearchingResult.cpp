////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceSearchingResult.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceSearchingResult.h"
#include "Root.h"
#include "mgr/InstanceMgr.h"
#include "LayerInstanceSearchingBuy.h"
#include "SceneMain.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceSearchingResult::~LayerInstanceSearchingResult()
{
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceSearchingResult::init()
{
	this->setName("LayerInstanceSearchingResult");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceSearchingResult.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerInstanceSearchingResult", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceSearchingResult::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceSearchingResult::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 初始化列表
	auto listViewResult = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewResult"));
	CHECKF(listViewResult);
	auto layoutResult = dynamic_cast<ui::Layout*>(ui::Helper::seekWidgetByName(listViewResult, "LayoutResult"));
	CHECKF(layoutResult);
	listViewResult->setItemModel(layoutResult);
	listViewResult->removeItem(0);
	auto nSearchingMaxCount = InstanceMgr::getInstance()->getSearchingMaxCount();
	auto nSerchingCount = InstanceMgr::getInstance()->getSearchingCount();
	for (int i = 0; i < nSearchingMaxCount - nSerchingCount; i++)
	{
		listViewResult->pushBackDefaultItem();
	}

	// 初始化控件
	// 关闭按钮
	CHECKF(this->initButtonListen("ImageViewClose", [=](Ref*){
		this->removeFromParent();
	}));

	// 探索增加按钮
	CHECKF(this->initButtonListen("ImageViewAdd", [=](Ref*){
		auto sence = Root::getInstance()->getSceneMain();
		CHECK_NOLOG(sence);
		auto layer = LayerInstanceSearchingBuy::create();
		CHECK_NOLOG(layer);
		sence->addChild(layer);
	}));

	// 一键收取按钮
	CHECKF(this->initButtonListen("ImageViewAward", [=](Ref*){

	}));

	// 设置数据
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", nSearchingMaxCount));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingCount", nSerchingCount));

	// 背景半透处理
	::AddBlurScreen(this, true);
	return true;
}

// 初始化监听按钮
bool LayerInstanceSearchingResult::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback)
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
bool LayerInstanceSearchingResult::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceSearchingResult::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}