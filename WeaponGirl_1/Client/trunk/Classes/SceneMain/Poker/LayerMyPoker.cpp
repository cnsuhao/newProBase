////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMyPoker.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/24
////////////////////////////////////////////////////////////////////////
#include "LayerMyPoker.h"
#include "../SceneMain.h"
#include "LayerPopPokerSort.h"
#include "Mgr/PokerMgr.h"
#include "WidgetPoker.h"
#include "Mgr/Poker.h"
#include "Mgr/LogicDataMgr.h"
#include "Mgr/MoneyMgr.h"
#include "ConstTable/ConstTableMgr.h"

//////////////////////////////////////////////////////////////////////////
bool LayerMyPoker::init()
{
	this->setName("LayerMyPoker");
	this->setCascadeOpacityEnabled(true);
	m_idShowMagicType = ID_NONE;

	// 加载csb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerMyPoker.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	m_pPokerCsbNode = CSLoader::createNode("NodePoker.csb");
	CHECKF(m_pPokerCsbNode);
	m_pPokerCsbNode->retain();

	// 加入触摸优先级
	if (this->initTouchPriority("LayerMyPoker", this))
	{
		m_pLayerTouchListener = EventListenerTouchOneByOne::create();
		m_pLayerTouchListener->setSwallowTouches(true);
		m_pLayerTouchListener->onTouchBegan = CC_CALLBACK_2(LayerMyPoker::onTouchBegan, this);
		m_pLayerTouchListener->onTouchEnded = CC_CALLBACK_2(LayerMyPoker::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pLayerTouchListener, this);
	}

	// 升星与强化按钮监听
	auto pImageViewUpStar = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewUpStarBg"));
	CHECKF(pImageViewUpStar);
	pImageViewUpStar->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::clickUpStar, this));
	pImageViewUpStar->setAutoTouchChangeRenderer();
	pImageViewUpStar->setAutoTouchAction();
	pImageViewUpStar->setTouchEnabled(true);

	auto pImageViewUpStrengthen = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewUpStrengthenBg"));
	CHECKF(pImageViewUpStrengthen);
	pImageViewUpStrengthen->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::clickUpStrengthen, this));
	pImageViewUpStrengthen->setAutoTouchChangeRenderer();
	pImageViewUpStrengthen->setAutoTouchAction();
	pImageViewUpStrengthen->setTouchEnabled(true);

	// 技能点击监听
	auto magicNode1 = ui::Helper::seekNodeByName(m_pCsbWidget, "NodeMagic1");
	CHECKF(magicNode1);
	auto pImageViewMagic1 = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(magicNode1, "ImageViewIcon"));
	CHECKF(pImageViewMagic1);
	pImageViewMagic1->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::clickMagic1, this));
	pImageViewMagic1->setAutoTouchChangeRenderer();

	auto magicNode2 = ui::Helper::seekNodeByName(m_pCsbWidget, "NodeMagic2");
	CHECKF(magicNode2);
	auto pImageViewMagic2 = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(magicNode2, "ImageViewIcon"));
	CHECKF(pImageViewMagic2);
	pImageViewMagic2->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::clickMagic2, this));
	pImageViewMagic2->setAutoTouchChangeRenderer();

	auto magicNode3 = ui::Helper::seekNodeByName(m_pCsbWidget, "NodeMagic3");
	CHECKF(magicNode3);
	auto pImageViewMagic3 = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(magicNode3, "ImageViewIcon"));
	CHECKF(pImageViewMagic3);
	pImageViewMagic3->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::clickMagic3, this));
	pImageViewMagic3->setAutoTouchChangeRenderer();

	auto equipNode = ui::Helper::seekNodeByName(m_pCsbWidget, "NodeEquip");
	CHECKF(equipNode);
	auto pImageViewEquip = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(equipNode, "ImageViewIcon"));
	CHECKF(pImageViewEquip);
	pImageViewEquip->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::clickEquip, this));
	pImageViewEquip->setAutoTouchChangeRenderer();

	auto bossMagicNode = ui::Helper::seekNodeByName(m_pCsbWidget, "NodeMagic");
	CHECKF(bossMagicNode);
	auto pImageViewBossMagic1 = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(bossMagicNode, "ImageViewIcon"));
	CHECKF(pImageViewBossMagic1);
	pImageViewBossMagic1->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::clickBossMagic, this));
	pImageViewBossMagic1->setAutoTouchChangeRenderer();

	auto pImageViewBossMagic2 = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewBossWeaponBg"));
	CHECKF(pImageViewBossMagic2);
	pImageViewBossMagic2->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::clickBossMagic, this));
	pImageViewBossMagic2->setAutoTouchChangeRenderer();

	#pragma message(PRAGMAMSG(合体技能触发动画加载))

	// 排序列表按钮
	auto pImageViewSortBtn = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, "ImageViewSortBtn"));
	CHECKF(pImageViewSortBtn);
	pImageViewSortBtn->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::popPokerSort, this));
	pImageViewSortBtn->setAutoTouchChangeRenderer();
	pImageViewSortBtn->setAutoTouchAction();
	pImageViewSortBtn->setTouchEnabled(true);
	m_eUiSortType = POKER_SORT_TYPE_none;

	// 底栏数量
	ui::Helper::setStringText(m_pCsbWidget, "TextPokerNumber", StringUtils::format("%d/%d", PokerMgr::getInstance()->getPokerCount(), PokerMgr::getInstance()->getPokerCountMax()));
	

	// 开启定时
	this->scheduleUpdate();
	
	this->setCloseImageView("ImageViewClose");	// 退出按钮
	this->setPopLayoutMode();					// 弹出模式
	::AddBlurScreen(this, true);				// 加半透背景
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool LayerMyPoker::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 吞掉不再触摸矩形中的事件
	if (!this->isInTouchRect(touch->getLocation()))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 其他区域点击退出
	if (!this->isInTouchRect(touch->getStartLocation()) && !this->isInTouchRect(touch->getLocation()))
	{
		this->removeFromParent();
		return;
	}
}

//////////////////////////////////////////////////////////////////////////
LayerMyPoker::~LayerMyPoker()
{
	CC_SAFE_RELEASE(m_pPokerCsbNode);
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::refreshPokerList()
{
	// 根据类型显示
	VEC_DB_KEY vecPokerID;
	PokerMgr::getInstance()->queryPokerVector(vecPokerID, m_eUiSortType);

	// 记录原来选中的卡牌
	DB_KEY idOldSelectPoker = this->getSelectPokerID();

	// 列表初始化
	auto scrollView = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewPoker"));
	CHECK(scrollView);
	scrollView->setScrollBarWidth(4);
	scrollView->setScrollBarPositionFromCorner(Vec2(2, 2));
	scrollView->setScrollBarColor(Color3B::WHITE);
	scrollView->setScrollBarEnabled(true);
	scrollView->removeAllChildren();
	auto autoInnerContainerSize = scrollView->getContentSize();
	int nLineCount = vecPokerID.size() / 5;
	if (0 != vecPokerID.size() % 5)
	{
		nLineCount++;
	}
	nLineCount = std::max(1, nLineCount);
	auto pPokerLayout = m_pPokerCsbNode->getChildByName("Layout");
	CHECK(pPokerLayout);
	autoInnerContainerSize.height = pPokerLayout->getContentSize().height * nLineCount + 10;
	scrollView->setInnerContainerSize(autoInnerContainerSize);

	// 加载卡牌
	for (auto idPoker : vecPokerID)
	{
		auto pokerWidget = WidgetPoker::create(m_pPokerCsbNode, idPoker);
		CHECKC(pokerWidget);

		auto nChildrenCount = scrollView->getChildrenCount();
		float innerWidth = scrollView->getInnerContainerSize().width;
		float innerHeight = scrollView->getInnerContainerSize().height;
		float nInfoWidth = (nChildrenCount % 5 + 0.5f) * pokerWidget->getContentSize().width + 10;
		float nInfoHeight = (nChildrenCount / 5 + 0.5f) * pokerWidget->getContentSize().height + 5;
		pokerWidget->setPosition(Vec2(nInfoWidth, innerHeight - nInfoHeight));
		pokerWidget->addClickEventListener(CC_CALLBACK_1(LayerMyPoker::selectPokerWidgetEvent, this));
		scrollView->addChild(pokerWidget);

		if (ID_NONE == idOldSelectPoker)
		{
			if (0 == nChildrenCount)
			{
				this->selectPokerWidgetEvent(pokerWidget);
			}
		}
		else
		{
			if (idOldSelectPoker == idPoker)
			{
				this->selectPokerWidgetEvent(pokerWidget);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::popPokerSort(Ref* pSender)
{
	auto popLayer = LayerPopPokerSort::create();
	CHECK(popLayer);
	this->getFather()->addChild(popLayer);
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::selectPokerWidgetEvent(Ref* pSender)
{
	auto pPokerWidget = dynamic_cast<WidgetPoker*>(pSender);
	CHECK(pPokerWidget);
	if (pPokerWidget->isSelected())
	{
		return;
	}

	// 设置是否选中
	auto scrollView = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewPoker"));
	CHECK(scrollView);
	for (auto child : scrollView->getChildren())
	{
		auto pThisPokerWidget = dynamic_cast<WidgetPoker*>(child);
		CHECKC_NOLOG(pThisPokerWidget);
		pThisPokerWidget->selectPoker(pSender == pThisPokerWidget);
	}
	
	auto pPokerData = pPokerWidget->getPoker();
	CHECK(pPokerData);

	// 设置技能框可见与否
	ui::Helper::setVisable(m_pCsbWidget, "NodeMagic1",		pPokerData->GetMemoryDataAttr(POKER_ATTR_type) != BOSS_POKER_TYPE);
	ui::Helper::setVisable(m_pCsbWidget, "NodeMagic2",		pPokerData->GetMemoryDataAttr(POKER_ATTR_type) != BOSS_POKER_TYPE);
	ui::Helper::setVisable(m_pCsbWidget, "NodeMagic3",		pPokerData->GetMemoryDataAttr(POKER_ATTR_type) != BOSS_POKER_TYPE);
	ui::Helper::setVisable(m_pCsbWidget, "NodeEquip",		pPokerData->GetMemoryDataAttr(POKER_ATTR_type) != BOSS_POKER_TYPE);
	ui::Helper::setVisable(m_pCsbWidget, "LayoutBossEquip", pPokerData->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE);

	// 标题栏基础卡牌信息	
	if (pPokerData->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE)
	{
		ui::Helper::setStringText(m_pCsbWidget, "TextName", LogicDataMgr::getInstance()->GetMemoryStringAttr(LOGIC_STRING_UserName));
	}
	else
	{
		ui::Helper::setStringText(m_pCsbWidget, "TextName", pPokerData->getTypeStr(POKER_TYPE_DATA_name));
	}
	ui::Helper::setStringText(m_pCsbWidget, "TextLevel", StringUtils::format("Lv%d", pPokerData->GetMemoryDataAttr(POKER_ATTR_lev)));
	ui::Helper::setStringText(m_pCsbWidget, "TextScore", MoneyMgr::getDivisionForamt(pPokerData->getScore()));
	ui::Helper::setStringTextBMFont(m_pCsbWidget, "TextBMFontUpStar", StringUtils::format("%lld/%lld", pPokerData->GetMemoryDataAttr(POKER_ATTR_star), pPokerData->getTypeData(POKER_TYPE_DATA_max_star)));
	ui::Helper::setStringTextBMFont(m_pCsbWidget, "TextBMFontUpStrengthen", StringUtils::format("%lld/30", pPokerData->GetMemoryDataAttr(POKER_ATTR_strengthen)));

	// 标题栏突破属性
	ui::Helper::setVisable(m_pCsbWidget, "ImageViewAttrIcon", pPokerData->GetMemoryDataAttr(POKER_ATTR_type) != BOSS_POKER_TYPE);
	ui::Helper::setVisable(m_pCsbWidget, "TextAttrValue", pPokerData->GetMemoryDataAttr(POKER_ATTR_type) != BOSS_POKER_TYPE);
	int nAttrType = pPokerData->GetMemoryDataAttr(POKER_ATTR_randomAttrType);
	if (nAttrType > 0 && nAttrType <= 4)
	{
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewAttrIcon", StringUtils::format("res/AttrIcon/%d.png", nAttrType));
		ui::Helper::setDataText(m_pCsbWidget, "TextAttrValue", pPokerData->GetMemoryDataAttr(POKER_ATTR_randomAttrData));

		if (pPokerData->GetMemoryDataAttr(POKER_ATTR_breakthrough) >= MAX_BREAKTHROUGH)
		{
			ui::Helper::setOpacity(m_pCsbWidget, "ImageViewAttrIcon", 255);
			ui::Helper::setOpacity(m_pCsbWidget, "TextAttrValue", 255);
		}
		else
		{
			ui::Helper::setOpacity(m_pCsbWidget, "ImageViewAttrIcon", 64);
			ui::Helper::setOpacity(m_pCsbWidget, "TextAttrValue", 64);
		}
	}

	// 技能图标
	for (int i = 1; i <= 3; i++)
	{
		OBJID idMagicType = pPokerData->getTypeData((POKER_TYPE_DATA)(POKER_TYPE_DATA_magic1 + i - 1));
		ui::Helper::setImageViewAttr(m_pCsbWidget, StringUtils::format("NodeMagic%d", i), "ImageViewIcon", idMagicType > 0, idMagicType > 0, idMagicType > 0, false);
		std::string strMagicIcon = idMagicType ? ::getMagicIconFileName(idMagicType) : "res/ColorFrame/ColorFrameBgEmpty.png";
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, StringUtils::format("NodeMagic%d", i), "ImageViewIcon", strMagicIcon);

		bool bTogether = false;
		if (idMagicType && ConstTableMgr::getInstance()->GetDataSingle( CONST_TABLE_TYPE_magic_type, idMagicType, MAGIC_TYPE_DATA_need_pokertype2) > ID_NONE)
		{
			bTogether = true;
		}
		ui::Helper::setVisable(m_pCsbWidget, StringUtils::format("NodeMagic%d", i), "ImageViewTogether", bTogether);
	}

	// 宝具
	OBJID idEquipMagicIcon = pPokerData->getTypeData(POKER_TYPE_DATA_equip_icon);
	std::string strEquipMagicIcon = idEquipMagicIcon ? ::getEquipMagicIconFileName(idEquipMagicIcon) : "res/ColorFrame/ColorFrameBgEmpty.png";
	ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "NodeEquip", "ImageViewIcon", strEquipMagicIcon);
	ui::Helper::setImageViewAttr(m_pCsbWidget, "NodeEquip", "ImageViewIcon", idEquipMagicIcon > 0, idEquipMagicIcon > 0, idEquipMagicIcon > 0, false);
	ui::Helper::setVisable(m_pCsbWidget, "NodeEquip", "ImageViewTogether", false);
	ui::Helper::setTouchEnable(m_pCsbWidget, "NodeMagic", "ImageViewIcon", pPokerData->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE);
	ui::Helper::setTouchEnable(m_pCsbWidget, "ImageViewBossWeaponBg", pPokerData->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE);

	// 默认选第一个
	if (pPokerData->GetMemoryDataAttr(POKER_ATTR_type) == BOSS_POKER_TYPE)
	{
		OBJID idWeapon = pPokerData->GetMemoryDataAttr(POKER_ATTR_weapon);
		this->showMagic(idWeapon);
		std::string strBossWeaponName = idWeapon ? ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_magic_type, idWeapon, MAGIC_TYPE_DATA_name) : "";
		std::string strBossWeaponIcon = idWeapon ? ::getMagicIconFileName(idWeapon) : "res/ColorFrame/ColorFrameBgEmpty.png";
		ui::Helper::setStringText(m_pCsbWidget, "TextBossWeaponName", strBossWeaponName);
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "NodeMagic", "ImageViewIcon", strBossWeaponIcon);
	}
	else
	{
		this->showMagic(pPokerData->getTypeData(POKER_TYPE_DATA_magic1));
	}
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::clickUpStar(Ref* pSender)
{

}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::clickUpStrengthen(Ref* pSender)
{

}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::clickMagic1(Ref* pSender)
{
	auto pPokerData = this->getSelectPoker();
	CHECK(pPokerData);
	this->showMagic(pPokerData->getTypeData(POKER_TYPE_DATA_magic1));
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::clickMagic2(Ref* pSender)
{
	auto pPokerData = this->getSelectPoker();
	CHECK(pPokerData);
	this->showMagic(pPokerData->getTypeData(POKER_TYPE_DATA_magic2));
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::clickMagic3(Ref* pSender)
{
	auto pPokerData = this->getSelectPoker();
	CHECK(pPokerData);
	this->showMagic(pPokerData->getTypeData(POKER_TYPE_DATA_magic3));
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::clickEquip(Ref* pSender)
{
	auto pPokerData = this->getSelectPoker();
	CHECK(pPokerData);
	OBJID idIcon = pPokerData->getTypeData(POKER_TYPE_DATA_equip_icon);
	std::string strName = pPokerData->getTypeStr(POKER_TYPE_DATA_equip_name);
	std::string strText = pPokerData->getTypeStr(POKER_TYPE_DATA_equip_text);
	if (idIcon)
	{
		this->showEquip(idIcon, strName, strText);
	}
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::clickBossMagic(Ref* pSender)
{
	// 弹出选择boss武器对话框
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::showMagic(OBJID idMagicType)
{
	CHECK(m_pCsbWidget);
	ui::Helper::setVisable(m_pCsbWidget, "LayoutTrigger", false);
	ui::Helper::setVisable(m_pCsbWidget, "TextTogetherDetail", false);
	m_idShowMagicType = idMagicType;

	ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_no_magic);
	if (ID_NONE == idMagicType)
	{
		ui::Helper::setStringText(m_pCsbWidget, "TextMagicName", ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_no_magic));
		ui::Helper::setStringText(m_pCsbWidget, "TextMagicDetail", ConstTableMgr::getInstance()->GetConfigText(CONFIG_TEXT_ID_no_magic_text));
		return;
	}

	CHECK(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_magic_type, idMagicType));

	ui::Helper::setStringText(m_pCsbWidget, "TextMagicName", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_magic_type, idMagicType, MAGIC_TYPE_DATA_name));
	ui::Helper::setStringText(m_pCsbWidget, "TextMagicDetail", ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_magic_type, idMagicType, MAGIC_TYPE_DATA_detail));

	// 组合技能才会显示后面的东西
	if (0 == ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_magic_type, idMagicType, MAGIC_TYPE_DATA_need_pokertype2))
	{
		return;
	}

	ui::Helper::setVisable(m_pCsbWidget, "LayoutTrigger", true);
	ui::Helper::setVisable(m_pCsbWidget, "TextTogetherDetail", true);

	#pragma message(PRAGMAMSG(是否激活技能动画切换))
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::showEquip(OBJID idIcon, const std::string& name, const std::string& text)
{
	CHECK(idIcon);
	ui::Helper::setStringText(m_pCsbWidget, "TextMagicName", name);
	ui::Helper::setStringText(m_pCsbWidget, "TextMagicDetail", text);
	ui::Helper::setVisable(m_pCsbWidget, "LayoutTrigger", false);
	ui::Helper::setVisable(m_pCsbWidget, "TextTogetherDetail", false);
	m_idShowMagicType = ID_NONE;
}


//////////////////////////////////////////////////////////////////////////
DB_KEY LayerMyPoker::getSelectPokerID() const
{
	CHECKF(m_pCsbWidget);
	auto scrollView = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewPoker"));
	CHECKF(scrollView);
	for (auto child : scrollView->getChildren())
	{
		auto pPokerWidget = dynamic_cast<WidgetPoker*>(child);
		if (pPokerWidget && pPokerWidget->isSelected())
		{
			return pPokerWidget->getPokerID();
		}
	}
	return ID_NONE;
}

//////////////////////////////////////////////////////////////////////////
Poker* LayerMyPoker::getSelectPoker() const
{
	CHECKF(m_pCsbWidget);
	auto scrollView = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewPoker"));
	CHECKF(scrollView);
	for (auto child : scrollView->getChildren())
	{
		auto pPokerWidget = dynamic_cast<WidgetPoker*>(child);
		if (pPokerWidget && pPokerWidget->isSelected())
		{
			return pPokerWidget->getPoker();
		}
	}
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::update(float delta)
{
	this->updatePokerSort();
	this->updatePokerAttrDetail();
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::updatePokerSort()
{
	if (m_eUiSortType == PokerMgr::getInstance()->getMyPokerSort())
	{
		return;
	}

	m_eUiSortType = PokerMgr::getInstance()->getMyPokerSort();
	switch (m_eUiSortType)
	{
	case POKER_SORT_TYPE_color:
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortText", "res/Text/PokerSortColor.png");
		break;
	case POKER_SORT_TYPE_level:
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortText", "res/Text/PokerSortLevel.png");
		break;
	case POKER_SORT_TYPE_upstar:
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortText", "res/Text/PokerSortStar.png");
		break;
	case POKER_SORT_TYPE_score:
		ui::Helper::setImageViewTexturePlist(m_pCsbWidget, "ImageViewSortText", "res/Text/PokerSortScore.png");
		break;
	default:
		break;
	}

	this->refreshPokerList();
}

//////////////////////////////////////////////////////////////////////////
void LayerMyPoker::updatePokerAttrDetail()
{
	// 逻辑每秒检查2次
	static int64_t lastMS = 0;
	int64_t nowMS = ::GetUtcMillisecond();
	if (nowMS < lastMS + 500)
	{
		return;
	}
	lastMS = nowMS;

	CHECK(m_pCsbWidget);
	auto scrollView = dynamic_cast<ui::ScrollView*>(ui::Helper::seekWidgetByName(m_pCsbWidget, "ScrollViewPoker"));
	CHECK(scrollView);
	if (POKER_SORT_TYPE_none == m_eUiSortType)
	{
		return;
	}

	for (auto child : scrollView->getChildren())
	{
		auto pThisPokerWidget = dynamic_cast<WidgetPoker*>(child);
		CHECKC_NOLOG(pThisPokerWidget);
		auto pPokerData = pThisPokerWidget->getPoker();
		CHECKC(pPokerData);
		
		std::string strDetail;
		switch (m_eUiSortType)
		{
		case POKER_SORT_TYPE_color:
		case POKER_SORT_TYPE_score:
			strDetail = StringUtils::format("%lld", pPokerData->getScore());
			break;
		case POKER_SORT_TYPE_level:
			strDetail = StringUtils::format("Lv%lld", pPokerData->GetMemoryDataAttr(POKER_ATTR_lev));
			break;
		case POKER_SORT_TYPE_upstar:
			strDetail = StringUtils::format("%lld/%lld", pPokerData->GetMemoryDataAttr(POKER_ATTR_star), pPokerData->getTypeData(POKER_TYPE_DATA_max_star));
			break;
		default:
			break;
		}
		pThisPokerWidget->setDetail(strDetail);
	}
}

