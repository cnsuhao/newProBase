////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerHomeView.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/20
////////////////////////////////////////////////////////////////////////
#include "LayerHomeView.h"
#include "Root.h"
#include "../SceneMain.h"

//////////////////////////////////////////////////////////////////////////
LayerHomeView::~LayerHomeView()
{

}

//////////////////////////////////////////////////////////////////////////
bool LayerHomeView::init()
{
	this->setName("LayerHomeView");
	this->setCascadeOpacityEnabled(true);

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerHomeView.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerHomeView", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerHomeView::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// gm号调试特权
	if (LogicDataMgr::getInstance()->GetMemoryDataAttr(LOGIC_DATA_userinfo_account_type) > ACCOUNT_TYPE_NORMAL)
	{
		auto editSprite = ui::Scale9Sprite::createWithSpriteFrameName("res/UiFrame/frame7.png", Rect(30, 30, 200, 200));
		CHECKF(editSprite);
		editSprite->setScale9Enabled(true);
		auto inputEditBox = ui::EditBox::create(Size(800, 60), editSprite);
		inputEditBox->setName("DebugEditBox");
		inputEditBox->setText("DebugCommand");
		inputEditBox->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		inputEditBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		inputEditBox->setFontName("Helvetica");
		inputEditBox->setFontSize(48);
		inputEditBox->setPlaceholderFontSize(48);
		inputEditBox->setDelegate(this);
		inputEditBox->setPositionX(APP_DESIGN_WIDTH * 0.4f);
		inputEditBox->setPositionY(APP_DESIGN_HEIGHT * 0.2f);
		inputEditBox->setLocalZOrder(100);
		this->addChild(inputEditBox);
	}

	return true;
}
