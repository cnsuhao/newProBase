////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceSearchingBuy.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceSearchingBuy.h"
#include "Root.h"
#include "mgr/InstanceMgr.h"
#include "mgr/MoneyMgr.h"
#include "../SceneMain.h"
#include "MyCocosCommon/LayerHint.h"
#include "Network/Instance/MsgGameInstanceInfo.h"
#include "Network/NetworkServe.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceSearchingBuy::~LayerInstanceSearchingBuy()
{
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceSearchingBuy::init()
{
	this->setName("LayerInstanceSearchingBuy");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceSearchingBuy.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerInstanceSearchingBuy", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceSearchingBuy::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceSearchingBuy::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 初始化控件
	// 关闭按钮
	CHECKF(this->initButtonListen("ImageViewClose", [=](Ref*){
		this->removeFromParent();
	}));

	// 探索减少按钮
	CHECKF(this->initButtonListen("ImageViewDec", [=](Ref*){
		this->decBuyNum();
	}, false, true));

	// 探索增加按钮
	CHECKF(this->initButtonListen("ImageViewAdd", [=](Ref*){
		this->addBuyNum();
	}, false, true));

	// 购买按钮
	CHECKF(this->initButtonListen("ImageViewBuy", [=](Ref*){
		// 发送购买消息
		CMsgGameInstanceInfo msg;
		msg.CreateMsg(EMSGINSTANCEA_SEARCHING_COUNT, EMSGINSTANCER_SUC, m_nBuyNum);
		NetworkServe::getInstance()->sendMsg(msg);
	}, true));

	// 取消按钮
	CHECKF(this->initButtonListen("ImageViewCancel", [=](Ref*){
		this->removeFromParent();
	}, true));

	// 设置数据
	m_nBuyNum = 0;
	CHECKF(this->addBuyNum());
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", InstanceMgr::getInstance()->getSearchingMaxCount()));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingCount", InstanceMgr::getInstance()->getSearchingCount()));
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextSpendMaxNum", MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_VAS)));
	CHECKF(ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewVas", MoneyMgr::getInstance()->getMoneySpriteFrameName(USER_MONEY_TYPE_VAS)));

	// 背景半透处理
	::AddBlurScreen(this, true);
	return true;
}

// 初始化监听按钮
bool LayerInstanceSearchingBuy::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback, bool bLight/* = false*/, bool bLongPress/* = false*/)
{
	CHECKF(m_pCsbWidget);
	auto pImage = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, strName));
	CHECKF(pImage);
	// 设置长按效果
	if (bLongPress)
	{
		pImage->setLongPressed(callback, nullptr, 150);
	}
	pImage->setAutoTouchChangeRenderer(bLight);
	pImage->addClickEventListener(callback);
	pImage->setAutoTouchAction();
	pImage->setTouchEnabled(true);
	return true;
}

// 设置SearchingMaxCount
bool LayerInstanceSearchingBuy::setSearchingMaxCount(int nCount)
{
	m_nBuyNum = 0;
	CHECKF(this->addBuyNum());
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextSpendMaxNum", MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_VAS)));

	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", nCount));
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 增加购买数量
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool LayerInstanceSearchingBuy::addBuyNum()
{
	auto bUpdate = false;
	if (MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_VAS) >= (INSTANCE_SEARCHING_COUNT_VAS * (m_nBuyNum + 1)))
	{
		m_nBuyNum++;
		bUpdate = true;
	}

	if (bUpdate || 0 == m_nBuyNum)
	{
		CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextAddNum",   m_nBuyNum));
		CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSpendNum", INSTANCE_SEARCHING_COUNT_VAS * m_nBuyNum));
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 减少购买数量
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool LayerInstanceSearchingBuy::decBuyNum()
{
	CHECKF1_NOLOG(m_nBuyNum > 0);
	m_nBuyNum--;
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextAddNum", m_nBuyNum));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSpendNum", INSTANCE_SEARCHING_COUNT_VAS * m_nBuyNum));
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceSearchingBuy::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceSearchingBuy::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}