////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceDrop.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceDrop.h"
#include "Root.h"
#include "mgr/InstanceMgr.h"
#include "../SceneMain.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceDrop::~LayerInstanceDrop()
{
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceDrop::init()
{
	this->setName("LayerInstanceDrop");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceDrop.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerInstanceDrop", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceDrop::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceDrop::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 初始化控件
	// 关闭按钮
	auto pImage = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewClose"));
	CHECKF(pImage);
	pImage->addClickEventListener([=](Ref*){ this->removeFromParent(); });
	pImage->setAutoTouchAction();
	pImage->setTouchEnabled(true);

	// 弹出效果
	this->setPopLayoutMode();
	
	// 背景半透处理
	::AddBlurScreen(this, true);
	return true;
}

// 更新掉落信息
bool LayerInstanceDrop::updateDropInfo(OBJID idInstance)
{
	CHECKF(idInstance);
	for (int nIndex = INSTANCE_DATA_DROP_POKER_TYPE1, i = 1; nIndex <= INSTANCE_DATA_DROP_POKER_TYPE3; nIndex++, i++)
	{
		auto layoutPokerType = dynamic_cast<ui::Layout*>(ui::Helper::seekNodeByName(m_pCsbWidget, StringUtils::format("LayoutPokerType%d", i)));
		CHECKC(layoutPokerType);
		auto nPokerType = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, nIndex);
		CHECKC(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_poker_type, nPokerType));
		auto nColor = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, nPokerType, POKER_TYPE_DATA_color);
		CHECKC(ui::Helper::setImageViewTexturePlist(layoutPokerType, "ImageViewBg", StringUtils::format("res/ColorFrame/ColorFrameBg%d.png", nColor)));		// bg
		CHECKC(ui::Helper::setImageViewTexturePlist(layoutPokerType, "ImageViewFrame", StringUtils::format("res/ColorFrame/ColorFrame%d.png", nColor)));	// frame
		auto nSpineType = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, nPokerType, POKER_TYPE_DATA_spine_type);
		CHECKC(ui::Helper::setImageViewTexturePlist(layoutPokerType, "ImageViewIcon", ::getLookfaceFileName(nSpineType)));	// icon
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceDrop::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceDrop::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}