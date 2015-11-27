////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerHint.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/7/7
////////////////////////////////////////////////////////////////////////
#include "LayerHint.h"
#include "Root.h"

//////////////////////////////////////////////////////////////////////////
LayerHint* LayerHint::create(const std::string& strHint, Color4B textColor /*= Color4B::WHITE*/)
{
	LayerHint* pRet = new(std::nothrow) LayerHint();
	if (pRet && pRet->init(strHint, textColor))
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
bool LayerHint::init(const std::string& strHint, Color4B textColor)
{
	CHECKF(strHint.size() > 0);
	this->setName("LayerHint");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerHint.csb");
	this->addChild(m_pCsbWidget);
	auto action = CSLoader::createTimeline("LayerHint.csb");
	this->runAction(action);
	action->play("animation", false);
	ui::Helper::doLayout(m_pCsbWidget);

	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextHint", strHint));
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
void LayerHint::runShowAction(LayerHint* layerHint)
{
	CHECK(layerHint);
	Vec2 targetPos = layerHint->getPosition();
//	layerHint->setPositionX(APP_DESIGN_WIDTH + targetPos.x);

	// 淡出效果
	auto delay = DelayTime::create(0.5f);
	auto fadeout = FadeOut::create(0.8f);
	auto remove = CallFunc::create([=](){
		layerHint->removeFromParent();
	});
	layerHint->runAction(Sequence::create(delay, fadeout, remove, nullptr));
}

////////////////////////////////////////////////////////////////////////
// Description: 增加一个hint
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void AddHint(const std::string& strHint, Scene* fatherScene/* = nullptr*/)
{
	auto scene = Director::getInstance()->getRunningScene();
	if (fatherScene)
	{
		scene = fatherScene;
	}

	int nHintCount = 0;
	for (auto child : scene->getChildren())
	{
		if (child->getName() == "LayerHint")
		{
			nHintCount++;
		}
	}

	auto layer = LayerHint::create(strHint);
	CHECK(scene && layer);
	layer->setPositionY(layer->getPositionY() - nHintCount * 96);
	scene->addChild(layer);
	LayerHint::runShowAction(layer);
}
