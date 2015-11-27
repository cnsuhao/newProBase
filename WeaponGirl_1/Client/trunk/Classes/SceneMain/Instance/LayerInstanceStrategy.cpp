////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceStrategy.cpp
// Author: �½���(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#include "LayerInstanceStrategy.h"
#include "Root.h"
#include "mgr/InstanceMgr.h"
#include "Mgr/CommentMgr.h"
#include "../SceneMain.h"
#include "LayerInstanceStrategySend.h"
#include "Network\Comment\MsgCommentOpt.h"

//////////////////////////////////////////////////////////////////////////
LayerInstanceStrategy::~LayerInstanceStrategy()
{
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceStrategy::init()
{
	this->setName("LayerInstanceStrategy");
	this->setCascadeOpacityEnabled(true);

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceStrategy.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// ���봥�����ȼ�
	if (this->initTouchPriority("LayerInstanceStrategy", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceStrategy::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceStrategy::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// ��ʼ���ؼ�
	// �رհ�ť
	CHECKF(this->initButtonListen("ImageViewClose", [=](Ref*){
		this->removeFromParent();
	}));

	// �������۰�ť
	CHECKF(this->initButtonListen("ImageViewSend", [=](Ref*){
		auto scene = Root::getInstance()->getSceneMain();
		CHECK_NOLOG(scene);
		auto layer = LayerInstanceStrategySend::create();
		CHECK_NOLOG(layer);
		scene->addChild(layer);
	}, true));

	// ����Ч��
	this->setPopLayoutMode();

	// ������͸����
	::AddBlurScreen(this, true);
	return true;
}

// ��ʼ��������ť
bool LayerInstanceStrategy::initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback, bool bLight/* = false*/)
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

// ���¹�����Ϣ
bool LayerInstanceStrategy::updateStrategy(OBJID idCommentType)
{
	CHECKF(idCommentType);
	auto listViewStrategy = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewStrategy"));
	CHECKF(listViewStrategy);
	auto layoutStrategy = dynamic_cast<ui::Layout*>(ui::Helper::seekWidgetByName(listViewStrategy, "LayoutStrategy"));
	CHECKF(layoutStrategy);
	listViewStrategy->setItemModel(layoutStrategy);
	listViewStrategy->removeItem(0);
	m_mapCommentInfo.clear();
	auto nCommentCount = CommentMgr::getInstance()->getSize();
	if (nCommentCount > 0)
	{
		for (int i = 0; i < nCommentCount; i++)
		{
			auto commentInfo = CommentMgr::getInstance()->queryInfo(i);
			auto commentItem = layoutStrategy->clone();
			CHECKC(commentItem);
			CHECKC(this->LoadItemInfo(commentItem, commentInfo));
			listViewStrategy->pushBackCustomItem(commentItem);
			m_mapCommentInfo.insert(commentInfo.idComment, commentItem);
		}
	}
	m_idCommentType = idCommentType;
	return true;
}

// �����µĹ�����Ϣ
bool LayerInstanceStrategy::updateStrategyNew(OBJID idCommentType, const COMMENT_INFO& info)
{
	CHECKF(idCommentType);
	CHECKF(m_idCommentType == idCommentType);
	auto listViewStrategy = dynamic_cast<ui::ListView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ListViewStrategy"));
	CHECKF(listViewStrategy);
	listViewStrategy->insertDefaultItem(0);
	auto commentItem = listViewStrategy->getItem(0);
	CHECKF(commentItem);
	CHECKF(this->LoadItemInfo(commentItem, info));
	m_mapCommentInfo.insert(info.idComment, commentItem);
	return true;
}

// ���ع�����Ϣ
bool LayerInstanceStrategy::LoadItemInfo(ui::Widget* pWidgetItem, const COMMENT_INFO& info)
{
	CHECKF(pWidgetItem);
	CHECKF(ui::Helper::setStringText(pWidgetItem, "TextUserName", info.szName));
	CHECKF(ui::Helper::setDataText(pWidgetItem, "TextGoodNum", info.nGoodCount));
	
	// ���ޱ��
	auto imageViewGood = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(pWidgetItem, "ImageViewGood"));
	CHECKF(imageViewGood);
	imageViewGood->addClickEventListener([=](Ref*){
		CMsgCommentOpt msg;
		CHECK_NOLOG(msg.CreateCommentOpt(MSG_COMMENT_OPT_ACTION_click_good, m_idCommentType, info.idComment));
		NetworkServe::getInstance()->sendMsg(msg);
	});
	if (info.nSelfGoodFlag > 0)
	{
		imageViewGood->loadTexture("res/Common/Good.png", ui::Widget::TextureResType::PLIST);
	}
	else
	{
		imageViewGood->loadTexture("res/Common/GoodCancel.png", ui::Widget::TextureResType::PLIST);
	}
	imageViewGood->setAutoTouchChangeRenderer(true);
	imageViewGood->setAutoTouchAction(AUTO_TOUCH_ACTION_scale_copy_big);
	imageViewGood->setTouchEnabled(true);

	// ��������,�����ı�Size
	auto textDetail = dynamic_cast<ui::Text*>(ui::Helper::seekWidgetByName(pWidgetItem, "TextDetail"));
	CHECKF(textDetail);
	auto orderWidth = textDetail->getContentSize().width;
	textDetail->ignoreContentAdaptWithSize(true);
	textDetail->setString(info.szText);
	auto textDetailSize = textDetail->getContentSize();
	auto orderHeight = (textDetailSize.width / orderWidth + 1) * (textDetailSize.height);
	textDetail->setContentSize(Size(orderWidth, orderHeight));
	textDetail->ignoreContentAdaptWithSize(false);
	textDetail->setTextVerticalAlignment(TextVAlignment::BOTTOM);

	// ����item����
	auto layoutHead = dynamic_cast<ui::Layout*>(ui::Helper::seekWidgetByName(pWidgetItem, "LayoutHead"));
	CHECKF(layoutHead);
	layoutHead->setPositionY(layoutHead->getPositionY() + orderHeight);
	pWidgetItem->setContentSize(Size(pWidgetItem->getContentSize().width, pWidgetItem->getContentSize().height + orderHeight));
	return true;
}

// ���¹��Ե���
bool LayerInstanceStrategy::updateStrategyGood(OBJID idCommentType, const COMMENT_INFO& info)
{
	CHECKF(m_idCommentType == idCommentType);
	auto iter = m_mapCommentInfo.find(info.idComment);
	CHECKF(iter != m_mapCommentInfo.end());
	CHECKF(iter->second);
	auto imageViewGood = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(iter->second, "ImageViewGood"));
	CHECKF(imageViewGood);
	if (info.nSelfGoodFlag > 0)
	{
		imageViewGood->loadTexture("res/Common/Good.png", ui::Widget::TextureResType::PLIST);
	}
	else
	{
		imageViewGood->loadTexture("res/Common/GoodCancel.png", ui::Widget::TextureResType::PLIST);
	}
	imageViewGood->setAutoTouchChangeRenderer(true);
	CHECKF(ui::Helper::setDataText(iter->second, "TextGoodNum", info.nGoodCount));
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerInstanceStrategy::onTouchBegan(Touch *touch, Event *unused_event)
{
	// �̵����ٴ��������е��¼�
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceStrategy::onTouchEnded(Touch *touch, Event *unused_event)
{
	// �����������˳�
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}