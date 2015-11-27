////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMessageBox.cpp
// Author: 李梦松(MengSong Lee)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#include "LayerMessageBox.h"
#include "Root.h"

//////////////////////////////////////////////////////////////////////////
LayerMessageBox::LayerMessageBox() :	m_callbackMessageBoxClick(nullptr),
										m_pClickCallBackRef(nullptr),
										m_pLayerTouchListener(nullptr),
										m_pWidget(nullptr),
										m_bCloseByBg(false)										
{

}

LayerMessageBox::~LayerMessageBox()
{
	if (m_pLayerTouchListener)
	{
		_eventDispatcher->removeEventListener(m_pLayerTouchListener);
	}
	LogicDataMgr::getInstance()->delMessageBox(m_strMessage);
}

LayerMessageBox* LayerMessageBox::createWithMessage(const std::string& message, const std::string& title/* = "" */,
													MESSAGE_BOX_MODE mode/*  = MESSAGE_BOX_MODE_OK */, bool bCloseByBg/* = false */, MessageBoxClickCallback callback /* = nullptr */, Ref* pRef/* = nullptr */)
{

	// 创建一个Layer
	auto pLayer = new(std::nothrow) LayerMessageBox();
	if (pLayer && pLayer->initWithMessage(message, title, mode, bCloseByBg, callback, pRef))
	{
		pLayer->autorelease();
		return pLayer;
	}
	else
	{
		delete pLayer;
		pLayer = NULL;
		return NULL;
	}
	return pLayer;
}

bool LayerMessageBox::initWithMessage(const std::string& message, const std::string& title, MESSAGE_BOX_MODE mode, bool bCloseByBg, MessageBoxClickCallback callback, Ref* pRef)
{
	// 必须有信息
	CHECKF(message.empty() == false);
	// 相同信息的对话框仅能弹一个
	CHECKF(LogicDataMgr::getInstance()->isHaveMessageBox(message) == false);

	this->setLocalZOrder(ZORDER_TIPS);
	
	// 设置Layer层和监听
	m_pLayerTouchListener = EventListenerTouchOneByOne::create();
	m_pLayerTouchListener->setSwallowTouches(true);
	m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerMessageBox::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(m_pLayerTouchListener, this->getGlobalTouchPriority());
	// 加载csb
	this->setWidget(static_cast<ui::Widget*>(CSLoader::createNode("LayerMessageBox.csb")));
	auto pWidget = this->getWidget();
	CHECKF(pWidget);
	this->addChild(pWidget);
	ui::Helper::doLayout(pWidget);

	// 确定按钮
	auto okButton = static_cast<ui::Button*>(ui::Helper::seekWidgetByName(pWidget, "ButtonOK"));
	CHECKF(okButton);
	okButton->setLocalZOrder(ZORDER_TIPS);

	// 取消按钮
	auto cancelButton = static_cast<ui::Button*>(ui::Helper::seekWidgetByName(pWidget, "ButtonCancel"));
	CHECKF(cancelButton);
	cancelButton->setLocalZOrder(ZORDER_TIPS);

	// 根据不同模式设计界面布局
	if (mode == MESSAGE_BOX_MODE_OK)
	{
		// 仅有OK
		cancelButton->removeFromParent();
		auto okPosPercent = okButton->getPositionPercent();
		okButton->setPositionPercent(Vec2(0.5, okPosPercent.y));
		okButton->addClickEventListener(CC_CALLBACK_1(LayerMessageBox::clickMessageBoxBtnOK, this));
	}
	else if (mode == MESSAGE_BOX_MODE_CANCEL)
	{
		// 仅有Cancel
		okButton->removeFromParent();
		auto cancelPosPercent = cancelButton->getPositionPercent();
		cancelButton->setPositionPercent(Vec2(0.5, cancelPosPercent.y));
		cancelButton->addClickEventListener(CC_CALLBACK_1(LayerMessageBox::clickMessageBoxBtnCancel, this));
	}
	else if (mode == MESSAGE_BOX_MODE_OK_CANCEL)
	{
		// OK和Cancel
		okButton->addClickEventListener(CC_CALLBACK_1(LayerMessageBox::clickMessageBoxBtnOK, this));
		cancelButton->addClickEventListener(CC_CALLBACK_1(LayerMessageBox::clickMessageBoxBtnCancel, this));
	}
	else
	{
		// 未知模式
		return NULL;
	}

	// 标题区域
	auto TitleText = static_cast<ui::Text*>(ui::Helper::seekWidgetByName(pWidget, "TextTitle"));
	CHECKF(TitleText);
	TitleText->ignoreContentAdaptWithSize(true);
	TitleText->setString(title);

	// 通知文本区域
	auto messageText = static_cast<ui::Text*>(ui::Helper::seekWidgetByName(pWidget, "TextMessage"));
	CHECKF(messageText);
	messageText->ignoreContentAdaptWithSize(true);
	messageText->setString(message);

	this->setIsCloseByBg(bCloseByBg);
	// 注册回调
	this->setClickCallback(callback, pRef);

	LogicDataMgr::getInstance()->addMessageBox(message);
	this->setMessage(message);

	::AddBlurScreen(this, true);
	return (true);
}

void LayerMessageBox::setClickCallback(MessageBoxClickCallback callback, Ref* pRef)
{
	m_callbackMessageBoxClick = callback;
	m_pClickCallBackRef = pRef;
}

void LayerMessageBox::clickMessageBoxBtnOK(Ref* pSender)
{
	if (m_callbackMessageBoxClick)
	{
		m_callbackMessageBoxClick(m_pClickCallBackRef, MESSAGE_BOX_CLICK_OK);
	}
	this->removeFromParent();
}

void LayerMessageBox::clickMessageBoxBtnCancel(Ref* pSender)
{
	if (m_callbackMessageBoxClick)
	{
		m_callbackMessageBoxClick(m_pClickCallBackRef, MESSAGE_BOX_CLICK_CANCEL);
	}
	this->removeFromParent();
}

bool LayerMessageBox::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 通知文本区域
	auto layoutDialog = static_cast<ui::Layout*>(ui::Helper::seekWidgetByName(m_pWidget, "LayoutDialog"));
	CHECKF(layoutDialog);
	if (layoutDialog)
	{
		Vec2 touchPosition = touch->getLocation();
		if (layoutDialog->getBoundingBox().containsPoint(touchPosition))
		{
			return (false);
		}
		else if (m_bCloseByBg)
		{
			this->removeFromParent();
		}
	}
	return (true);
}
