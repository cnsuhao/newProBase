////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLoginLogo.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/12
////////////////////////////////////////////////////////////////////////
#include "LayerLoginLogo.h"

//////////////////////////////////////////////////////////////////////////
bool LayerLoginLogo::init()
{
	this->setName("LayerLoginLogo");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerLoginLogo.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerLoginLogo", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerLoginLogo::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	this->runAction(Sequence::create(DelayTime::create(1 * 0.618f), FadeOut::create(0.618f), CallFunc::create([=](){
		this->removeFromParent();
	}), nullptr));

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerLoginLogo::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}
