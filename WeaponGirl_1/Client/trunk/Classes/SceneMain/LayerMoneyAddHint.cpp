////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMoneyAddHint.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/19
////////////////////////////////////////////////////////////////////////
#include "LayerMoneyAddHint.h"
#include "Mgr\MoneyMgr.h"

//////////////////////////////////////////////////////////////////////////
LayerMoneyAddHint* LayerMoneyAddHint::create(USER_MONEY_TYPE eType, int64_t addData)
{
	LayerMoneyAddHint* pRet = new(std::nothrow) LayerMoneyAddHint();
	if (pRet && pRet->init(eType, addData))
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
bool LayerMoneyAddHint::init(USER_MONEY_TYPE eType, int64_t addData)
{
	this->setName("LayerMoneyAddHint");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerMoneyAddHint.csb");
	this->addChild(m_pCsbWidget);
	auto action = CSLoader::createTimeline("LayerMoneyAddHint.csb");
	this->runAction(action);
	action->play("animation", false);
	ui::Helper::doLayout(m_pCsbWidget);

	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextMoneyNumber", MoneyMgr::getBigForamt(addData)));
	CHECKF(ui::Helper::setSprite(m_pCsbWidget, "SpriteMoneyType", MoneyMgr::getInstance()->getMoneySpriteFrameName(eType)));

	return true;
}


//////////////////////////////////////////////////////////////////////////
void MoneyAddHint(USER_MONEY_TYPE eType, int64_t addData)
{
	auto scene = Director::getInstance()->getRunningScene();
	auto hint = LayerMoneyAddHint::create(eType, addData);
	CHECK(hint && scene);
	scene->addChild(hint);

	// 淡出效果
	auto delay = DelayTime::create(0.45f);
	auto fadeout = FadeOut::create(0.3f);
	auto remove = CallFunc::create([=](){
		hint->removeFromParent();
	});
	hint->runAction(Sequence::create(delay, fadeout, remove, nullptr));

	int nHintCount = 0;
	for (auto child : scene->getChildren())
	{
		if (child->getName() == "LayerMoneyAddHint")
		{
			nHintCount++;
		}
	}
	hint->setPositionY(hint->getPositionY() - nHintCount * 96);
}
