////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceSearchingResult.cpp
// Author: �½���(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceSearchingResult.h"
#include "Root.h"
#include "mgr/InstanceMgr.h"
#include "LayerInstanceSearchingBuy.h"
#include "SceneMain.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceSearchingResult::~LayerInstanceSearchingResult()
{
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceSearchingResult::init()
{
	this->setName("LayerInstanceSearchingResult");
	this->setCascadeOpacityEnabled(true);

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceSearchingResult.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// ���봥�����ȼ�
	if (this->initTouchPriority("LayerInstanceSearchingResult", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceSearchingResult::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceSearchingResult::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// ��ʼ���б�
	auto listViewResult = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewResult"));
	CHECKF(listViewResult);
	auto layoutResult = dynamic_cast<ui::Layout*>(ui::Helper::seekWidgetByName(listViewResult, "LayoutResult"));
	CHECKF(layoutResult);
	listViewResult->setItemModel(layoutResult);
	listViewResult->removeItem(0);
	auto nSearchingMaxCount = InstanceMgr::getInstance()->getSearchingMaxCount();
	auto nSerchingCount = InstanceMgr::getInstance()->getSearchingCount();
	for (int i = 0; i < nSearchingMaxCount - nSerchingCount; i++)
	{
		listViewResult->pushBackDefaultItem();
	}

	// ��ʼ���ؼ�
	// �رհ�ť
	CHECKF(this->initButtonListen("ImageViewClose", [=](Ref*){
		this->removeFromParent();
	}));

	// ̽�����Ӱ�ť
	CHECKF(this->initButtonListen("ImageViewAdd", [=](Ref*){
		auto sence = Root::getInstance()->getSceneMain();
		CHECK_NOLOG(sence);
		auto layer = LayerInstanceSearchingBuy::create();
		CHECK_NOLOG(layer);
		sence->addChild(layer);
	}));

	// һ����ȡ��ť
	CHECKF(this->initButtonListen("ImageViewAward", [=](Ref*){

	}));

	// ��������
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", nSearchingMaxCount));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingCount", nSerchingCount));

	// ������͸����
	::AddBlurScreen(this, true);
	return true;
}

// ��ʼ��������ť
bool LayerInstanceSearchingResult::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback)
{
	CHECKF(m_pCsbWidget);
	auto pImage = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, strName));
	CHECKF(pImage);
	pImage->addClickEventListener(callback);
	pImage->setAutoTouchAction(true);
	pImage->setTouchEnabled(true);
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceSearchingResult::onTouchBegan(Touch *touch, Event *unused_event)
{
	// �̵����ٴ��������е��¼�
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceSearchingResult::onTouchEnded(Touch *touch, Event *unused_event)
{
	// �����������˳�
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}