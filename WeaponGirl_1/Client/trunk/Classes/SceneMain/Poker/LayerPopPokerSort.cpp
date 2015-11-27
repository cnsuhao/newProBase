////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerPopPokerSort.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/24
////////////////////////////////////////////////////////////////////////
#include "LayerPopPokerSort.h"
#include "Mgr\PokerMgr.h"
#include "Root.h"
#include "..\SceneMain.h"

//////////////////////////////////////////////////////////////////////////
bool LayerPopPokerSort::init()
{
	this->setName("LayerPopPokerSort");

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerPopPokerSort.csb");
	this->addChild(m_pCsbWidget);
	auto action = CSLoader::createTimeline("LayerPopPokerSort.csb");
	this->runAction(action);
	action->play("animation", false);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerPopPokerSort", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerPopPokerSort::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerPopPokerSort::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 排序文字背景高亮
	switch (PokerMgr::getInstance()->getMyPokerSort())
	{
	case POKER_SORT_TYPE_color:
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnColor", "res/Common/Common.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnLevel", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnStar", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnScore", "res/Common/Cancel.png");
		break;
	case POKER_SORT_TYPE_level:
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnColor", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnLevel", "res/Common/Common.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnStar", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnScore", "res/Common/Cancel.png");
		break;
	case POKER_SORT_TYPE_upstar:
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnColor", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnLevel", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnStar", "res/Common/Common.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnScore", "res/Common/Cancel.png");
		break;
	case POKER_SORT_TYPE_score:
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnColor", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnLevel", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnStar", "res/Common/Cancel.png");
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortBtnScore", "res/Common/Common.png");
		break;
	default:
		break;
	}

	auto btnColor = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewSortBtnColor"));
	CHECKF(btnColor);
	btnColor->addClickEventListener([=](Ref*){
		PokerMgr::getInstance()->setMyPokerSort(POKER_SORT_TYPE_color);
		this->removeFromParent();
	});
	btnColor->setAutoTouchChangeRenderer(true);
	btnColor->setAutoTouchAction();
	btnColor->setTouchEnabled(true);

	auto btnLevel = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewSortBtnLevel"));
	CHECKF(btnLevel);
	btnLevel->addClickEventListener([=](Ref*){
		PokerMgr::getInstance()->setMyPokerSort(POKER_SORT_TYPE_level);
		this->removeFromParent();
	});
	btnLevel->setAutoTouchChangeRenderer(true);
	btnLevel->setAutoTouchAction();
	btnLevel->setTouchEnabled(true);

	auto btnUpstar = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewSortBtnStar"));
	CHECKF(btnUpstar);
	btnUpstar->addClickEventListener([=](Ref*){
		PokerMgr::getInstance()->setMyPokerSort(POKER_SORT_TYPE_upstar);
		this->removeFromParent();
	});
	btnUpstar->setAutoTouchChangeRenderer(true);
	btnUpstar->setAutoTouchAction();
	btnUpstar->setTouchEnabled(true);

	auto btnScore = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewSortBtnScore"));
	CHECKF(btnScore);
	btnScore->addClickEventListener([=](Ref*){
		PokerMgr::getInstance()->setMyPokerSort(POKER_SORT_TYPE_score);
		this->removeFromParent();
	});
	btnScore->setAutoTouchChangeRenderer(true);
	btnScore->setAutoTouchAction();
	btnScore->setTouchEnabled(true);

	::AddBlurScreen(this, true);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerPopPokerSort::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerPopPokerSort::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}
