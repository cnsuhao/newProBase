////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerWaitting.cpp
// Author: 李梦松(MengSong Lee)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#include "LayerWaitting.h"
#include "Root.h"

LayerWaitting::LayerWaitting()
{

}

LayerWaitting::~LayerWaitting()
{

}

LayerWaitting* LayerWaitting::create()
{
	auto scene = Director::getInstance()->getRunningScene();
	CHECKF(scene);
	auto pLayerWaitting = scene->getChildByName("LayerWaitting");
	if (pLayerWaitting)
	{
		return nullptr;
	}

	// 创建一个Node
	auto pNode = new(std::nothrow) LayerWaitting();
	if (pNode && pNode->init())
	{
		pNode->autorelease();
		return pNode;
	}
	else
	{
		delete pNode;
		pNode = NULL;
		return NULL;
	}
	return pNode;
}

//////////////////////////////////////////////////////////////////////////
bool LayerWaitting::init()
{
	this->setName("LayerWaitting");

	// 加入触摸优先级
	if (this->initTouchPriority("LayerWaitting", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerWaitting::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerWaitting::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerWaitting.csb");
	auto pWidget = this->getCsbWidget();
	CHECKF(pWidget);
	this->addChild(pWidget);

	//加载动画： 
	auto action = CSLoader::createTimeline("LayerWaitting.csb");
	this->runAction(action);
	action->play("animationWatting", true);
	ui::Helper::doLayout(pWidget);
	
	return true;
}

void LayerWaitting::startWaitting(Scene* fatherScene/* = nullptr*/, bool bMaskLayer/* = false*/)
{
	auto scene = Director::getInstance()->getRunningScene();
	if (fatherScene)
	{
		scene = fatherScene;
	}
	CHECK(scene);
	auto layer = LayerWaitting::create();
	if (layer)
	{
		scene->addChild(layer);

		if (bMaskLayer)
		{
			auto color = LayerColor::create(Color4B(0, 0, 0, 192));
			color->setLocalZOrder(-1);
			layer->addChild(color);
		}
	}
}

void LayerWaitting::stopWaitting(Scene* fatherScene/* = nullptr*/)
{
	auto scene = Director::getInstance()->getRunningScene();
	if (fatherScene)
	{
		scene = fatherScene;
	}
	CHECK(scene);
	auto pLayerWaitting = scene->getChildByName("LayerWaitting");
	if (pLayerWaitting)
	{
		pLayerWaitting->removeFromParent();
	}
}

////////////////////////////////////////////////////////////////////////
// Description: 根据场景清理等待层
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerWaitting::clearWaitting(Scene* fatherScene)
{
	CHECK(fatherScene);
	std::vector<Node*> vecNeedRemoveNode;
	for (auto child : fatherScene->getChildren())
	{
		if (child->getName() == "LayerWaitting")
		{
			vecNeedRemoveNode.push_back(child);
		}
	}

	for (auto node : vecNeedRemoveNode)
	{
		node->removeFromParent();
	}
}

bool LayerWaitting::onTouchBegan(Touch *touch, Event *unused_event)
{
	return false;
}

void LayerWaitting::onTouchEnded(Touch *touch, Event *unused_event)
{
	
}

