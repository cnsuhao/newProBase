////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerCreateNew.cpp
// Author: ������(Peng Wenqi)
// Created: 2015/05/24
////////////////////////////////////////////////////////////////////////
#include "LayerCreateNew.h"
#include "Root.h"
#include "SceneLogin.h"
#include "Network\Login\MsgLoginCreateNewUser.h"

//////////////////////////////////////////////////////////////////////////
bool LayerCreateNew::init()
 {
	 this->setName("LayerCreateNew");

	// ����csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerCreateNew.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// ���봥�����ȼ�
	if (this->initTouchPriority("LayerCreateNew", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerCreateNew::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}
	
	ui::Button* btnRandom = (ui::Button*)ui::Helper::seekWidgetByName(m_pCsbWidget, "ButtonRandom");
	CHECKF(btnRandom);
	btnRandom->addClickEventListener(CC_CALLBACK_1(LayerCreateNew::clickRandomName, this));

	ui::Button* btnCreate = (ui::Button*)ui::Helper::seekWidgetByName(m_pCsbWidget, "ButtonCreate");
	CHECKF(btnCreate);
	btnCreate->addClickEventListener(CC_CALLBACK_1(LayerCreateNew::clickCreateUser, this));

	// ���һ������
	this->clickRandomName(btnRandom);
	this->setPopLayoutMode();
	::AddBlurScreen(this, true);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool LayerCreateNew::onTouchBegan(Touch *touch, Event *unused_event)
{
	// �̵����ٴ��������е��¼�
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: �����������
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerCreateNew::clickRandomName(Ref* pSender)
{
	ui::TextField* textName = (ui::TextField*)ui::Helper::seekWidgetByName(m_pCsbWidget, "TextFieldName");
	CHECK(textName);

	std::string name = "";
	for (int i = 0; i <= RandGet(6) + 6; i++)
	{
		name += 'a' + RandGet(26);
	}
	textName->setString(name);
}

////////////////////////////////////////////////////////////////////////
// Description: �������
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerCreateNew::clickCreateUser(Ref* pSender)
{
	ui::TextField* textField = (ui::TextField*)ui::Helper::seekWidgetByName(m_pCsbWidget, "TextFieldName");
	CHECK(textField);
	auto inputName = textField->getString();
	IF_NOT(::CheckName(inputName))
	{
		return;
	}

	// 3��CD
	static uint32_t clickCD = 0;
	uint32_t nowSecond = ::TimeGet(TIME_SECOND);
	if (clickCD + 3 >= nowSecond)
	{
		return;
	}
	clickCD = nowSecond;

	// ��ʱû��ѡ��lookface�Ĺ���
	int nJob = 0;
	int nLookface = 1;

	CMsgLoginCreateNewUser msg;
	CHECK(msg.createCreateNewPlayer(inputName.c_str(), nLookface, nJob));
	NetworkServe::getInstance()->sendMsg(msg);
}
