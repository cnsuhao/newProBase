////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerPokerView.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/24
////////////////////////////////////////////////////////////////////////
#include "LayerPokerView.h"
#include "Root.h"
#include "../SceneMain.h"
#include "LayerMyPoker.h"

//////////////////////////////////////////////////////////////////////////
LayerPokerView::~LayerPokerView()
{

}

//////////////////////////////////////////////////////////////////////////
bool LayerPokerView::init()
{
	this->setName("LayerPokerView");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerPokerView.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerPokerView", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerPokerView::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 按钮监听
	auto pImageViewMyPoker = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewMyPokerBg"));
	CHECKF(pImageViewMyPoker);
	pImageViewMyPoker->addClickEventListener(CC_CALLBACK_1(LayerPokerView::clickMyPoker, this));
	pImageViewMyPoker->setAutoTouchChangeRenderer();
	pImageViewMyPoker->setAutoTouchAction();
	pImageViewMyPoker->setTouchEnabled(true);

	auto pImageViewFightGroup = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewFightGroupBg"));
	CHECKF(pImageViewFightGroup);
	pImageViewFightGroup->addClickEventListener(CC_CALLBACK_1(LayerPokerView::clickFightGroup, this));
	pImageViewFightGroup->setAutoTouchChangeRenderer();
	pImageViewFightGroup->setAutoTouchAction();
	pImageViewFightGroup->setTouchEnabled(true);

	auto pImageViewDistractAbility = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewDistractAbilityBg"));
	CHECKF(pImageViewDistractAbility);
	pImageViewDistractAbility->addClickEventListener(CC_CALLBACK_1(LayerPokerView::clickDistractAbility, this));
	pImageViewDistractAbility->setAutoTouchChangeRenderer();
	pImageViewDistractAbility->setAutoTouchAction();
	pImageViewDistractAbility->setTouchEnabled(true);

	auto pImageViewDelete = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewDeleteBg"));
	CHECKF(pImageViewDelete);
	pImageViewDelete->addClickEventListener(CC_CALLBACK_1(LayerPokerView::clickDelete, this));
	pImageViewDelete->setAutoTouchChangeRenderer();
	pImageViewDelete->setAutoTouchAction();
	pImageViewDelete->setTouchEnabled(true);

	auto pImageViewBossWeapon = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewBossWeaponBg"));
	CHECKF(pImageViewBossWeapon);
	pImageViewBossWeapon->addClickEventListener(CC_CALLBACK_1(LayerPokerView::clickBossWeapon, this));
	pImageViewBossWeapon->setAutoTouchChangeRenderer();
	pImageViewBossWeapon->setAutoTouchAction();
	pImageViewBossWeapon->setTouchEnabled(true);

	return true;
}

//////////////////////////////////////////////////////////////////////////
void LayerPokerView::clickMyPoker(Ref* pSender)
{
	auto layer = LayerMyPoker::create();
	CHECK(layer);
	this->getFather()->addChild(layer);
}

//////////////////////////////////////////////////////////////////////////
void LayerPokerView::clickFightGroup(Ref* pSender)
{

}

//////////////////////////////////////////////////////////////////////////
void LayerPokerView::clickDistractAbility(Ref* pSender)
{

}

//////////////////////////////////////////////////////////////////////////
void LayerPokerView::clickDelete(Ref* pSender)
{

}

//////////////////////////////////////////////////////////////////////////
void LayerPokerView::clickBossWeapon(Ref* pSender)
{

}
