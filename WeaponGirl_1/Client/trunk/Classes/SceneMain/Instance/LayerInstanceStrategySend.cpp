////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceStrategySend.cpp
// Author: �½���(Chen Jianjun)
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

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInstanceStrategySend.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// ���봥�����ȼ�
	if (this->initTouchPriority("LayerInstanceStrategySend", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInstanceStrategySend::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerInstanceStrategySend::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// ��ʼ�������
	auto textFieldStrategy = dynamic_cast<ui::TextField*>(ui::Helper::seekNodeByName(m_pCsbWidget, "TextFieldStrategy"));
	CHECKF(textFieldStrategy);
	textFieldStrategy->setString(InstanceMgr::getInstance()->getStrategyText());
	textFieldStrategy->addEventListener([=](Ref* pSender, cocos2d::ui::TextField::EventType type) {
		auto textField = (ui::TextField*)pSender;
		CHECK(textField);
		switch (type)
		{
		case cocos2d::ui::TextField::EventType::INSERT_TEXT:		 // д���¼�
		case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:	 // �����¼�
			{
				ui::Helper::setDataText(m_pCsbWidget, "TextNum", textFieldStrategy->getMaxLength() - textField->getStringLength());
			}
			break;
		default: break;
		}
	});
	CHECKF(ui::Helper::setDataText(m_pCsbWidget, "TextNum", textFieldStrategy->getMaxLength() - textFieldStrategy->getStringLength()));

	// ��ʼ���ؼ�
	// ȡ����ť
	CHECKF(this->initButtonListen("ImageViewCancel", [=](Ref*){
		auto textFieldStrategy = dynamic_cast<ui::TextField*>(ui::Helper::seekNodeByName(m_pCsbWidget, "TextFieldStrategy"));
		if (textFieldStrategy)
		{
			InstanceMgr::getInstance()->setStrategyText(textFieldStrategy->getString());
		}
		this->removeFromParent();
	}, true));

	// �������۰�ť
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

	// ����Ч��
	this->setPopLayoutMode();

	// ������͸����
	::AddBlurScreen(this, true);
	return true;
}

// ��ʼ��������ť
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
	// �̵����ٴ��������е��¼�
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerInstanceStrategySend::onTouchEnded(Touch *touch, Event *unused_event)
{
	// �����������˳�
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