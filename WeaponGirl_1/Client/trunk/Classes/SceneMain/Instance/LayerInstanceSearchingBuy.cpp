////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceSearchingBuy.cpp
// Author: �½���(Chen Jianjun)
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

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceSearchingBuy.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// ���봥�����ȼ�
	if (this->initTouchPriority("LayerInstanceSearchingBuy", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceSearchingBuy::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceSearchingBuy::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// ��ʼ���ؼ�
	// �رհ�ť
	CHECKF(this->initButtonListen("ImageViewClose", [=](Ref*){
		this->removeFromParent();
	}));

	// ̽�����ٰ�ť
	CHECKF(this->initButtonListen("ImageViewDec", [=](Ref*){
		this->decBuyNum();
	}, false, true));

	// ̽�����Ӱ�ť
	CHECKF(this->initButtonListen("ImageViewAdd", [=](Ref*){
		this->addBuyNum();
	}, false, true));

	// ����ť
	CHECKF(this->initButtonListen("ImageViewBuy", [=](Ref*){
		// ���͹�����Ϣ
		CMsgGameInstanceInfo msg;
		msg.CreateMsg(EMSGINSTANCEA_SEARCHING_COUNT, EMSGINSTANCER_SUC, m_nBuyNum);
		NetworkServe::getInstance()->sendMsg(msg);
	}, true));

	// ȡ����ť
	CHECKF(this->initButtonListen("ImageViewCancel", [=](Ref*){
		this->removeFromParent();
	}, true));

	// ��������
	m_nBuyNum = 0;
	CHECKF(this->addBuyNum());
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", InstanceMgr::getInstance()->getSearchingMaxCount()));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingCount", InstanceMgr::getInstance()->getSearchingCount()));
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextSpendMaxNum", MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_VAS)));
	CHECKF(ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewVas", MoneyMgr::getInstance()->getMoneySpriteFrameName(USER_MONEY_TYPE_VAS)));

	// ������͸����
	::AddBlurScreen(this, true);
	return true;
}

// ��ʼ��������ť
bool LayerInstanceSearchingBuy::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback, bool bLight/* = false*/, bool bLongPress/* = false*/)
{
	CHECKF(m_pCsbWidget);
	auto pImage = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, strName));
	CHECKF(pImage);
	// ���ó���Ч��
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

// ����SearchingMaxCount
bool LayerInstanceSearchingBuy::setSearchingMaxCount(int nCount)
{
	m_nBuyNum = 0;
	CHECKF(this->addBuyNum());
	CHECKF(ui::Helper::setStringText(m_pCsbWidget, "TextSpendMaxNum", MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_VAS)));

	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", nCount));
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: ���ӹ�������
// Arguments:
// Author: �½���(Chen Jianjun)
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
// Description: ���ٹ�������
// Arguments:
// Author: �½���(Chen Jianjun)
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
	// �̵����ٴ��������е��¼�
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceSearchingBuy::onTouchEnded(Touch *touch, Event *unused_event)
{
	// �����������˳�
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}