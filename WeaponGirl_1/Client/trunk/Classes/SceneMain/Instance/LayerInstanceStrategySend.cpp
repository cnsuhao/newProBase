////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceStrategySend.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-26
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceStrategySend.h"
#include "Root.h"
#include "mgr/InstanceMgr.h"
#include "../SceneMain.h"
#include "Network\Comment\MsgCommentList.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceStrategySend::~LayerInstanceStrategySend()
{
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceStrategySend::init()
{
	this->setName("LayerInstanceStrategySend");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceStrategySend.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerInstanceStrategySend", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceStrategySend::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceStrategySend::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 初始化输入框
	auto textFieldStrategy = dynamic_cast<ui::TextField*>(ui::Helper::seekNodeByName(m_pCsbWidget, "TextFieldStrategy"));
	CHECKF(textFieldStrategy);
	textFieldStrategy->setString(InstanceMgr::getInstance()->getStrategyText());
	textFieldStrategy->addEventListener([=](Ref* pSender, cocos2d::ui::TextField::EventType type) {
		auto textField = (ui::TextField*)pSender;
		CHECK(textField);
		switch (type)
		{
		case cocos2d::ui::TextField::EventType::INSERT_TEXT:		 // 写入事件
		case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:	 // 回退事件
			{
				ui::Helper::setDataText(m_pCsbWidget, "TextNum", textFieldStrategy->getMaxLength() - textField->getStringLength());
			}
			break;
		default: break;
		}
	});
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextNum", textFieldStrategy->getMaxLength() - textFieldStrategy->getStringLength()));

	// 初始化控件
	// 取消按钮
	CHECKF(this->initButtonListen("ImageViewCancel", [=](Ref*){
		auto textFieldStrategy = dynamic_cast<ui::TextField*>(ui::Helper::seekNodeByName(m_pCsbWidget, "TextFieldStrategy"));
		if (textFieldStrategy)
		{
			InstanceMgr::getInstance()->setStrategyText(textFieldStrategy->getString());
		}
		this->removeFromParent();
	}, true));

	// 发表评论按钮
	CHECKF(this->initButtonListen("ImageViewSend", [=](Ref*){ 
		auto textFieldStrategy = dynamic_cast<ui::TextField*>(ui::Helper::seekNodeByName(m_pCsbWidget, "TextFieldStrategy"));
		CHECK_NOLOG(textFieldStrategy);
		if (textFieldStrategy->getStringLength() > 0)
		{
			CMsgCommentList msg;
			CHECK_NOLOG(msg.CreateNewComment(InstanceMgr::getInstance()->getidCurInstance(), textFieldStrategy->getString().c_str()));
			NetworkServe::getInstance()->sendMsg(msg);
			InstanceMgr::getInstance()->setStrategyText("");
			this->removeFromParent();
		}
	}, true));

	// 弹出效果
	this->setPopLayoutMode();

	// 背景半透处理
	::AddBlurScreen(this, true);
	return true;
}

// 初始化监听按钮
bool LayerInstanceStrategySend::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback, bool bLight/* = false*/)
{
	CHECKF(m_pCsbWidget);
	auto pImage = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, strName));
	CHECKF(pImage);
	pImage->setAutoTouchChangeRenderer(bLight);
	pImage->addClickEventListener(callback);
	pImage->setAutoTouchAction();
	pImage->setTouchEnabled(true);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceStrategySend::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceStrategySend::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		auto textFieldStrategy = dynamic_cast<ui::TextField*>(ui::Helper::seekNodeByName(m_pCsbWidget, "TextFieldStrategy"));
		if (textFieldStrategy)
		{
			InstanceMgr::getInstance()->setStrategyText(textFieldStrategy->getString());
		}
		this->removeFromParent();
		return;
	}
}