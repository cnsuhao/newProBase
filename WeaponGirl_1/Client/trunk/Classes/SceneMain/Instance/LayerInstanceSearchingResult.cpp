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
#include "../SceneMain.h"

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
	auto nSearchingMaxCount = InstanceMgr::getInstance()->getSearchingMaxCount();
	for (int i = 1; i < nSearchingMaxCount; i++)
	{
		listViewResult->pushBackDefaultItem();
	}
	// ��������
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", nSearchingMaxCount));
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingCount", InstanceMgr::getInstance()->getSearchingCount()));

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
		this->removeFromParent();
	}, true));
	
	// ����Ч��
	this->setPopLayoutMode();

	// ������͸����
	::AddBlurScreen(this, true);
	return true;
}

// ��ʼ��������ť
bool LayerInstanceSearchingResult::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback, bool bLight/* = false*/)
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

// ����SearchingMaxCount
bool LayerInstanceSearchingResult::setSearchingMaxCount(int nCount)
{
	auto listViewResult = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewResult"));
	CHECKF(listViewResult);
	auto nItemCount = listViewResult->getItems().size();
	if (nCount > nItemCount)
	{
		for (int i = 0; i < nCount - nItemCount; i++)
		{
			listViewResult->pushBackDefaultItem();
		}
		CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingMaxCount", nCount));
	}
	return true;
}

// ���½�����Ϣ
bool LayerInstanceSearchingResult::updateAwardInfo(const std::vector<ST_AWARD_INFO>& vecInfo)
{
	CHECKF(vecInfo.size() > 0);
	auto listViewResult = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewResult"));
	CHECKF(listViewResult);
	for (int nIndex = 0; nIndex < vecInfo.size(); nIndex++)
	{
		const ST_AWARD_INFO& stAwardInfo = vecInfo[nIndex];
		CHECKC(E_USER_THING_TYPE_ITEM == ::getUserThingType(stAwardInfo.nAwardType));			// �޶�Ϊ��Ʒ����
		auto pItem = listViewResult->getItem(nIndex);
		CHECKC(pItem);
		auto nColor = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_item_type, stAwardInfo.nAwardType, ITEM_TYPE_DATA_COLOR);
		CHECKC(ui::Helper::setImageViewTexturePlist(pItem, "ImageViewBg", StringUtils::format("res/ColorFrame/ColorFrameBg%d.png", nColor)));		// bg
		CHECKC(ui::Helper::setImageViewTexturePlist(pItem, "ImageViewFrame", StringUtils::format("res/ColorFrame/ColorFrame%d.png", nColor)));		// frame
		CHECKC(ui::Helper::setImageViewTexturePlist(pItem, "ImageViewIcon", ::getItemIconFileName(stAwardInfo.nAwardType)));	// icon
		CHECKC(ui::Helper::setStringText(pItem, "TextName", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_item_type, stAwardInfo.nAwardType, ITEM_TYPE_DATA_NAME)));		// name
		CHECKC(ui::Helper::setStringText(pItem, "TextDetail", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_item_type, stAwardInfo.nAwardType, ITEM_TYPE_DATA_DETAIL)));	// detail
	}
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextSearchingCount", InstanceMgr::getInstance()->getSearchingCount()));
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