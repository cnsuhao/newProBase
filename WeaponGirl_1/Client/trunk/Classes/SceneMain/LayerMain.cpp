////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMain.cpp
// Author: 李梦松(MengSong Lee)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#include "LayerMain.h"
#include "Root.h"
#include "SceneMain.h"
#include "Mgr\MoneyMgr.h"
#include "Mgr\LoginMgr.h"
#include "Mgr\GreenTipsMgr.h"

#pragma warning (disable: 4996)

//////////////////////////////////////////////////////////////////////////
bool LayerMain::init()
{
	this->setName("LayerMain");

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNodeWithVisibleSize("LayerMain.csb");
	CHECKF(m_pCsbWidget);
	this->addChild(m_pCsbWidget);

	// 主界面右侧按钮监听
	this->initMainButtonListen("LayoutHome", CC_CALLBACK_1(LayerMain::clickMain, this));
	this->initMainButtonListen("LayoutInstance", CC_CALLBACK_1(LayerMain::clickMain, this));
	this->initMainButtonListen("LayoutLottery", CC_CALLBACK_1(LayerMain::clickMain, this));
	this->initMainButtonListen("LayoutChallenge", CC_CALLBACK_1(LayerMain::clickMain, this));
	this->initMainButtonListen("LayoutSmelt", CC_CALLBACK_1(LayerMain::clickMain, this));
	this->initMainButtonListen("LayoutPoker", CC_CALLBACK_1(LayerMain::clickMain, this));
	this->initMainButtonListen("LayoutActivity", CC_CALLBACK_1(LayerMain::clickMain, this));

	// 更新主界面右侧按钮状态
	this->updateMainButton("LayoutHome", true);
	this->updateMainButton("LayoutInstance", false);
	this->updateMainButton("LayoutLottery", false);
	this->updateMainButton("LayoutChallenge", false);
	this->updateMainButton("LayoutSmelt", false);
	this->updateMainButton("LayoutPoker", false);
	this->updateMainButton("LayoutActivity", false);

	// 底栏按钮监听
	this->initBottomListen("ImageViewMail", CC_CALLBACK_1(LayerMain::clickBottom, this));
	this->initBottomListen("ImageViewAchievement", CC_CALLBACK_1(LayerMain::clickBottom, this));
	this->initBottomListen("ImageViewFriend", CC_CALLBACK_1(LayerMain::clickBottom, this));
	this->initBottomListen("ImageViewShop", CC_CALLBACK_1(LayerMain::clickBottom, this));
	this->initBottomListen("ImageViewNotify", CC_CALLBACK_1(LayerMain::clickBottom, this));
	this->initBottomListen("ImageViewSetup", CC_CALLBACK_1(LayerMain::clickBottom, this));

	// 充值按钮
	this->initBottomListen("ImageViewPayVas", CC_CALLBACK_1(LayerMain::clickBottom, this));

	// 默认开启主界面
	{
		auto pDefaultLayout = dynamic_cast<ui::Layout*>(ui::Helper::seekNodeByName(m_pCsbWidget, "LayoutHome"));
		CHECKF(pDefaultLayout);
		auto pDefaultImage = dynamic_cast<ui::ImageView*>(pDefaultLayout->getChildByName("ImageView"));
		CHECKF(pDefaultImage);
		this->scheduleOnce([=](float){this->clickMain(pDefaultImage); }, 0.f, "open LayoutHome");	// 下一帧处理
	}

	// 走马灯初始位置获取与第一次内容变化
	auto nodeTextHint = ui::Helper::seekNodeByName(m_pCsbWidget, "TextHint");
	CHECKF(nodeTextHint);
	m_initHintPos = nodeTextHint->getPosition();
	this->changeHintText();
	
	// 开启定时
	this->scheduleUpdate();

	// 更新顶部货币图标
	ui::Helper::setSprite(m_pCsbWidget, "SpriteExp", MoneyMgr::getInstance()->getMoneySpriteFrameName(USER_MONEY_TYPE_AUTO_EXP));
	ui::Helper::setSprite(m_pCsbWidget, "SpriteMoney", MoneyMgr::getInstance()->getMoneySpriteFrameName(USER_MONEY_TYPE_AUTO_MONEY));
	ui::Helper::setSprite(m_pCsbWidget, "SpriteVas", MoneyMgr::getInstance()->getMoneySpriteFrameName(USER_MONEY_TYPE_VAS));

	return true;
}

//////////////////////////////////////////////////////////////////////////
LayerMain::~LayerMain()
{
}

//////////////////////////////////////////////////////////////////////////
void LayerMain::update(float delta)
{
	Layer::update(delta);

	this->updateTopMoneyShow();		// 更新顶部money显示
	this->updateTimeShow();			// 更新时间显示
	this->updateGreenTips();		// 更新绿点显示
}

////////////////////////////////////////////////////////////////////////
// Description: 更新顶部money显示
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerMain::updateTopMoneyShow()
{
//	TextScore
	ui::Helper::setStringText(m_pCsbWidget, "TextExp", MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_AUTO_EXP));
	ui::Helper::setStringText(m_pCsbWidget, "TextMoney", MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_AUTO_MONEY));
	ui::Helper::setStringText(m_pCsbWidget, "TextVas", MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_VAS));

#ifdef COCOS2D_DEBUG
	static int64_t lastMS = 0;
	int64_t nowMS = ::GetUtcMillisecond();
	if (nowMS < lastMS + 1000)
	{
		return;
	}
	lastMS = nowMS;

	auto debugExp = MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_AUTO_EXP);
	auto debugExpStr = MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_AUTO_EXP);
	auto debugMoney = MoneyMgr::getInstance()->getMoney(USER_MONEY_TYPE_AUTO_MONEY);
	auto debugMoneyStr = MoneyMgr::getInstance()->getMoneyBigFormat(USER_MONEY_TYPE_AUTO_MONEY);
//	log("Debug Exp[%lld][%s] Money[%lld][%s]", debugExp, debugExpStr.c_str(), debugMoney, debugMoneyStr.c_str());
#endif // end of COCOS2D_DEBUG
}

////////////////////////////////////////////////////////////////////////
// Description: 更新时间显示
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerMain::updateTimeShow()
{
	auto nowSecond = LoginMgr::getInstance()->getHeartbeat();
	auto dayTime = UtcSecondConvert(nowSecond, TIME_DAYTIME);
	std::string strTime;
	if (::GetUtcMillisecond() % 1000 > 618)
	{
		strTime = StringUtils::format("%02d:%02d", dayTime / 10000, dayTime / 100 % 100);
	}
	else
	{
		strTime = StringUtils::format("%02d %02d", dayTime / 10000, dayTime / 100 % 100);
	}

	ui::Helper::setStringText(m_pCsbWidget, "TextTime", strTime);
}

////////////////////////////////////////////////////////////////////////
// Description: 绿点提示更新
// Arguments:	
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerMain::updateGreenTips()
{
	// 每5秒做一次检查
	static uint32_t unUpdateSecond = 0;
	uint32_t unNowSecond = ::TimeGet(TIME_SECOND);
	if (unNowSecond < unUpdateSecond + 5)
	{
		return;
	}
	unUpdateSecond = unNowSecond;

	ui::Helper::setVisable(m_pCsbWidget, "LayoutHome",		"ImageViewMark", GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_MainViewHome));
	ui::Helper::setVisable(m_pCsbWidget, "LayoutInstance",	"ImageViewMark", GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_MainViewInstance));
	ui::Helper::setVisable(m_pCsbWidget, "LayoutLottery",	"ImageViewMark", GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_MainViewLottery));
	ui::Helper::setVisable(m_pCsbWidget, "LayoutChallenge", "ImageViewMark", GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_MainViewChallenge));
	ui::Helper::setVisable(m_pCsbWidget, "LayoutSmelt",		"ImageViewMark", GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_MainViewSmelt));
	ui::Helper::setVisable(m_pCsbWidget, "LayoutPoker",		"ImageViewMark", GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_MainViewPoker));
	ui::Helper::setVisable(m_pCsbWidget, "LayoutActivity",	"ImageViewMark", GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_MainViewActivity));
	
	ui::Helper::setVisable(m_pCsbWidget, "ImageViewMailMark",			GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_BottomButtonMail));
	ui::Helper::setVisable(m_pCsbWidget, "ImageViewAchievementMark",	GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_BottomButtonAchievement));
	ui::Helper::setVisable(m_pCsbWidget, "ImageViewFriendMark",			GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_BottomButtonFriend));
	ui::Helper::setVisable(m_pCsbWidget, "ImageViewShopMark",			GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_BottomButtonShop));
	ui::Helper::setVisable(m_pCsbWidget, "ImageViewNotifyMark",			GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_BottomButtonNotify));
	ui::Helper::setVisable(m_pCsbWidget, "ImageViewSetupMark",			GreenTipsMgr::getInstance()->isHaveTips(GREEN_TIPS_TYPE_BottomButtonSetup));
}


////////////////////////////////////////////////////////////////////////
// Description: 初始化主界面按钮监听
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool LayerMain::initMainButtonListen(const std::string& strLayoutName, const ui::Widget::ccWidgetClickCallback& callback)
{
	CHECKF(m_pCsbWidget);
	auto pLayout = dynamic_cast<ui::Layout*>(ui::Helper::seekNodeByName(m_pCsbWidget, strLayoutName));
	CHECKF(pLayout);
	auto pImage = dynamic_cast<ui::ImageView*>(pLayout->getChildByName("ImageView"));
	CHECKF(pImage);
	pImage->addClickEventListener(callback);
	pImage->setAutoTouchChangeRenderer(true);
	pImage->setAutoTouchAction();
	pImage->setTouchEnabled(true);
	return true;
}


////////////////////////////////////////////////////////////////////////
// Description: 初始化右侧主要按钮
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool LayerMain::updateMainButton(const std::string& strLayoutName, bool bChoose)
{
	CHECKF(m_pCsbWidget);
	auto pLayout = dynamic_cast<ui::Layout*>(ui::Helper::seekNodeByName(m_pCsbWidget, strLayoutName));
	CHECKF(pLayout);

	auto pDisable = dynamic_cast<ui::ImageView*>(pLayout->getChildByName("ImageViewTabDisable"));
	auto pDisableMark = dynamic_cast<ui::ImageView*>(pLayout->getChildByName("ImageViewTabMark"));
	auto pEnable = dynamic_cast<ui::ImageView*>(pLayout->getChildByName("ImageViewTabEnable"));
	CHECKF(pDisable && pDisableMark && pEnable);

	pEnable->setVisible(bChoose);
	pDisable->setVisible(!bChoose);
	pDisableMark->setVisible(!bChoose);

	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 初始化主界面底栏按钮监听
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool LayerMain::initBottomListen(const std::string& strImageViewName, const ui::Widget::ccWidgetClickCallback& callback)
{
	CHECKF(m_pCsbWidget);
	auto pImage = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, strImageViewName));
	CHECKF(pImage);
	pImage->addClickEventListener(callback);
	pImage->setAutoTouchChangeRenderer(true);
	pImage->setAutoTouchAction();
	pImage->setTouchEnabled(true);
	return true;
}


////////////////////////////////////////////////////////////////////////
// Description: 点击主界面右侧按钮
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void LayerMain::clickMain(Ref* pSender)
{
	CHECK(pSender && m_pCsbWidget);

	auto pLayoutCtrl = dynamic_cast<ui::Layout*>(ui::Helper::seekNodeByName(m_pCsbWidget, "LayoutCtrl"));
	CHECK(pLayoutCtrl);
	auto pLayoutChoose = dynamic_cast<ui::Layout*>(((Node*)pSender)->getParent());
	CHECK(pLayoutChoose);

	for (auto child : pLayoutCtrl->getChildren())
	{
		if (child->getName() == pLayoutChoose->getName())
		{
			this->updateMainButton(child->getName(), true);
		}
		else
		{
			this->updateMainButton(child->getName(), false);
		}
	}

	// 按钮点击处理
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECK(sceneMain);
	sceneMain->loadMainView(pLayoutChoose->getName());
}

////////////////////////////////////////////////////////////////////////
// Description: 点击主界面底栏按钮
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerMain::clickBottom(Ref* pSender)
{
	CHECK(pSender);
	auto pImageView = dynamic_cast<ui::ImageView*>(pSender);
	CHECK(pImageView);

	// 按钮点击处理
	auto sceneMain = Root::getInstance()->getSceneMain();
	CHECK(sceneMain);
	sceneMain->popBottomDlg(pImageView->getName());
}

////////////////////////////////////////////////////////////////////////
// Description: 弹出充值界面
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerMain::clickPayVas(Ref* pSender)
{

}

////////////////////////////////////////////////////////////////////////
// Description: 更换走马灯文字
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void LayerMain::changeHintText()
{
	CHECK(m_pCsbWidget);
	auto textHint = dynamic_cast<ui::Text*>(ui::Helper::seekNodeByName(m_pCsbWidget, "TextHint"));
	CHECK(textHint);

	// 获取并设置新的文字
	VEC_DB_KEY vecAllKey;
	CHECK(ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_main_hint, vecAllKey));
	DB_KEY idKey = vecAllKey[::RandGet(vecAllKey.size())];
	auto strText = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_main_hint, idKey, MAIN_HINT_DATA_text);
	textHint->setString(strText);

	// 坐标归位
	textHint->setPosition(m_initHintPos);

	// 移动动作
	float moveLength = textHint->getContentSize().width + APP_DESIGN_WIDTH * 1.5f;
	float moveTime = moveLength / 150.f;
	auto move = MoveBy::create(moveTime, Vec2(-moveLength, 0));
	auto call = CallFunc::create([=](){this->changeHintText(); });
	textHint->runAction(Sequence::create(move, call, nullptr));
}
