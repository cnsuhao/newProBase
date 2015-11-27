////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInputName.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/05/22
////////////////////////////////////////////////////////////////////////
#include "LayerInputName.h"
#include "Root.h"
#include "SceneLogin.h"

////////////////////////////////////////////////////////////////////////
// Description:	初始化
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool 
////////////////////////////////////////////////////////////////////////
bool LayerInputName::init()
{
	this->setName("LayerInputName");

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerInputName.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	// 加入触摸优先级
	if (this->initTouchPriority("LayerInputName", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerInputName::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 控件监听
	auto enterButton = dynamic_cast<ui::ImageView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ImageViewEnter"));
	CHECKF(enterButton);
	enterButton->setTouchEnabled(true);
	enterButton->setAutoTouchChangeRenderer(true);
	enterButton->setAutoTouchAction();
	enterButton->addClickEventListener(CC_CALLBACK_1(LayerInputName::clickOK, this));

	// 控件获取
	ui::TextField* accountNameField = (ui::TextField*)ui::Helper::seekWidgetByName(m_pCsbWidget, "TextFieldName");
	CHECKF(accountNameField);
	ui::TextField* accountPwdField = (ui::TextField*)ui::Helper::seekWidgetByName(m_pCsbWidget, "TextFieldPassword");
	CHECKF(accountPwdField);
	ui::CheckBox* accountPwdFlagCheckBox = (ui::CheckBox*)ui::Helper::seekWidgetByName(m_pCsbWidget, "CheckBoxSavePwdFlag");
	CHECKF(accountPwdFlagCheckBox);
	accountPwdFlagCheckBox->setSelected(true);
	accountPwdFlagCheckBox->setSelected(false);

	// 读取保存记录
	std::string saveAccountName = ::GetSaveStr(SAVE_DATA_input_account_name);
	std::string saveAccountPwd = ::GetSaveStr(SAVE_DATA_input_account_pwd);
	int saveAccountPwdFlag = ::GetSaveData(SAVE_DATA_input_account_pwd_flag);

	// 保存密码标记
	if (0 != saveAccountPwdFlag)
	{
		LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_AccountName, saveAccountName.c_str());
		LogicDataMgr::getInstance()->SetMemoryStringAttr(LOGIC_STRING_AccountPwd, saveAccountPwd.c_str());
		accountPwdFlagCheckBox->setSelected(true);
	}
	else
	{
		accountPwdFlagCheckBox->setSelected(false);
	}

	accountNameField->setString(saveAccountName);
	accountPwdField->setString(saveAccountPwd);
	this->setPopLayoutMode(TOUCH_LAYER_POP_MODE_none);
	::AddBlurScreen(this, true);
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 点击登陆
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerInputName::clickOK(Ref* pSender)
{
	// 控件获取
	ui::TextField* accountNameField = (ui::TextField*)ui::Helper::seekWidgetByName(m_pCsbWidget, "TextFieldName");
	CHECK(accountNameField);
	ui::TextField* accountPwdField = (ui::TextField*)ui::Helper::seekWidgetByName(m_pCsbWidget, "TextFieldPassword");
	CHECK(accountPwdField);
	ui::CheckBox* accountPwdFlagCheckBox = (ui::CheckBox*)ui::Helper::seekWidgetByName(m_pCsbWidget, "CheckBoxSavePwdFlag");
	CHECK(accountPwdFlagCheckBox);

	auto accountName = accountNameField->getString();
	auto accountPwd = accountPwdField->getString();

	// 保存本地快捷存储
	if (accountPwdFlagCheckBox->isSelected())
	{
		::SetSaveStr(SAVE_DATA_input_account_pwd, accountPwd);
		::SetSaveData(SAVE_DATA_input_account_pwd_flag, 1);
	}
	else
	{
		::SetSaveStr(SAVE_DATA_input_account_pwd, "");
		::SetSaveData(SAVE_DATA_input_account_pwd_flag, 0);
	}
	::SetSaveStr(SAVE_DATA_input_account_name, accountName);

	// 回调登陆
	getFather()->callbackStartLogin(accountName, accountPwd);
}

//////////////////////////////////////////////////////////////////////////
bool LayerInputName::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}
