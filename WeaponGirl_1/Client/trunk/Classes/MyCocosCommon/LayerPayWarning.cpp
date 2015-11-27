////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerPayWarning.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/07/07
////////////////////////////////////////////////////////////////////////
#include "LayerPayWarning.h"
#include "Root.h"

//////////////////////////////////////////////////////////////////////////
LayerPayWarning* LayerPayWarning::create(OBJID idItemType, int nNeedCount, const std::string& strDetail, PayWarningCallback callbackOK, PayWarningCallback callbackCancel)
{
	LayerPayWarning* pRet = new(std::nothrow) LayerPayWarning();
	if (pRet && pRet->init(idItemType, nNeedCount, strDetail, callbackOK, callbackCancel))
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
bool LayerPayWarning::init(OBJID idItemType, int nNeedCount, const std::string& strDetail, PayWarningCallback callbackOK, PayWarningCallback callbackCancel)
{
	CHECKF(idItemType && nNeedCount > 0 && strDetail.size() > 0 && callbackOK);

	this->setName("LayerPayWarning");

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerPayWarning.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerPayWarning", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerPayWarning::onTouchBegan, this);
		m_pLayerTouchListener->onTouchMoved = CC_CALLBACK_2(LayerPayWarning::onTouchMoved, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerPayWarning::onTouchEnded, this);
		m_pLayerTouchListener->onTouchCancelled = CC_CALLBACK_2(LayerPayWarning::onTouchCancelled, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

#pragma message(PRAGMAMSG(商店表加入后需要将此处价格进行计算))
	int nNeedVas = idItemType;

	// 控件数据设置
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextDetail", strDetail));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextItemCount", nNeedCount));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextVasCount", nNeedVas));
	auto imageItemType = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewItemType"));
	CHECKF(imageItemType);
//	imageItemType->loadTexture(::getItemIconFileName(idItemType), ui::TextureResType::PLIST);

// 	auto haveItemCount = ItemMgr::getInstance()->getItemAmountFromPackageByType(idItemType);
// 	if (haveItemCount >= nNeedCount)
// 	{
// 		CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutItem", true));
// 		CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutVas", false));
// 		CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutHint", false));
// 	}
// 	else
// 	{
// 		CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutItem", false));
// 		CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutVas", true));
// 		CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutHint", false));
// 	}

	// 监听
	ui::Button* ButtonOK = (ui::Button*)ui::Helper::seekWidgetByName(m_pCsbWidget, "ButtonOK");
	CHECKF(ButtonOK);
	ButtonOK->addClickEventListener(CC_CALLBACK_1(LayerPayWarning::clickBtnOK, this));

	ui::Button* ButtonCancel = (ui::Button*)ui::Helper::seekWidgetByName(m_pCsbWidget, "ButtonCancel");
	CHECKF(ButtonCancel);
	ButtonCancel->addClickEventListener(CC_CALLBACK_1(LayerPayWarning::clickBtnCancel, this));

	m_callbackOK = callbackOK;
	m_callbackCancel = callbackCancel;

	this->setPopLayoutMode();
	::AddBlurScreen(this, true);
	return true;
}

//////////////////////////////////////////////////////////////////////////
LayerPayWarning* LayerPayWarning::createWithHint(const std::string& strHint, const std::string& strDetail, PayWarningCallback callbackOK, PayWarningCallback callbackCancel)
{
	LayerPayWarning* pRet = new(std::nothrow) LayerPayWarning();
	if (pRet && pRet->initWithHint(strHint, strDetail, callbackOK, callbackCancel))
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
bool LayerPayWarning::initWithHint(const std::string& strHint, const std::string& strDetail, PayWarningCallback callbackOK, PayWarningCallback callbackCancel)
{
	CHECKF(strHint.size() > 0 && callbackOK);

	this->setName("LayerPayWarning");

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerPayWarning.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerPayWarning", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerPayWarning::onTouchBegan, this);
		m_pLayerTouchListener->onTouchMoved = CC_CALLBACK_2(LayerPayWarning::onTouchMoved, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerPayWarning::onTouchEnded, this);
		m_pLayerTouchListener->onTouchCancelled = CC_CALLBACK_2(LayerPayWarning::onTouchCancelled, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 控件数据设置
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextDetail", strDetail));
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextHint", strHint));
	CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutItem", false));
	CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutVas", false));
	CHECKF(ui::Helper::setVisable(m_pCsbWidget, "LayoutHint", true));

	// 监听
	ui::Button* ButtonOK = (ui::Button*)ui::Helper::seekWidgetByName(m_pCsbWidget, "ButtonOK");
	CHECKF(ButtonOK);
	ButtonOK->addClickEventListener(CC_CALLBACK_1(LayerPayWarning::clickBtnOK, this));

	ui::Button* ButtonCancel = (ui::Button*)ui::Helper::seekWidgetByName(m_pCsbWidget, "ButtonCancel");
	CHECKF(ButtonCancel);
	ButtonCancel->addClickEventListener(CC_CALLBACK_1(LayerPayWarning::clickBtnCancel, this));

	m_callbackOK = callbackOK;
	m_callbackCancel = callbackCancel;

	this->setPopLayoutMode();
	::AddBlurScreen(this, true);
	return true;
}

//////////////////////////////////////////////////////////////////////////
LayerPayWarning::LayerPayWarning()
{
	m_callbackOK = nullptr;
	m_callbackCancel = nullptr;
}

//////////////////////////////////////////////////////////////////////////
bool LayerPayWarning::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerPayWarning::onTouchMoved(Touch *touch, Event *unused_event)
{

}

//////////////////////////////////////////////////////////////////////////
void LayerPayWarning::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
// 	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
// 	{
// 		this->removeFromParent();
// 		return;
// 	}
}

//////////////////////////////////////////////////////////////////////////
void LayerPayWarning::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

//////////////////////////////////////////////////////////////////////////
void LayerPayWarning::clickBtnOK(Ref* pSender)
{
	if (m_callbackOK)
	{
		m_callbackOK();
	}
	this->removeFromParent();
}

//////////////////////////////////////////////////////////////////////////
void LayerPayWarning::clickBtnCancel(Ref* pSender)
{
	if (m_callbackCancel)
	{
		m_callbackCancel();
	}
	this->removeFromParent();
}
