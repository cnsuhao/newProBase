////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetPoker.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/24
////////////////////////////////////////////////////////////////////////
#include "WidgetPoker.h"
#include "Mgr\PokerMgr.h"
#include "Mgr\Poker.h"
#include "Mgr\UserAttrMgr.h"

//////////////////////////////////////////////////////////////////////////
WidgetPoker::WidgetPoker()
	: m_idPoker(ID_NONE)
{

}

//////////////////////////////////////////////////////////////////////////
WidgetPoker::~WidgetPoker()
{

}

//////////////////////////////////////////////////////////////////////////
WidgetPoker* WidgetPoker::create(Node* pCsbNode, DB_KEY idPoker)
{
	WidgetPoker* pRet = new(std::nothrow) WidgetPoker();
	if (pRet && pRet->init(pCsbNode, idPoker))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
bool WidgetPoker::init(Node* pCsbNode, DB_KEY idPoker)
{
	CHECKF(pCsbNode);
	m_idPoker = idPoker;

	// 根据csb加载基础
	auto csbLayout = (ui::Widget*)pCsbNode->getChildByName("Layout");
	CHECKF(csbLayout);
	this->copyProperties(csbLayout);
	this->copyClonedWidgetChildren(csbLayout);

	auto pPoker = PokerMgr::getInstance()->getPoker(idPoker);
	CHECKF(pPoker);
	int nColor = pPoker->getTypeData(POKER_TYPE_DATA_color);
	IF_OK(nColor > 0 && nColor <= POKER_COLOR_COUNT)
	{
		ui::Helper::setImageViewTexturePlist(this, "ImageViewFrame", StringUtils::format("res/ColorFrame/ColorFrame%d.png", nColor));
		ui::Helper::setImageViewTexturePlist(this, "ImageViewBg", StringUtils::format("res/ColorFrame/ColorFrameBg%d.png", nColor));
	}
	
	// 卡牌类型即lookface
	OBJID idLookface = pPoker->GetMemoryDataAttr(POKER_ATTR_type);	
	ui::Helper::setImageViewTexturePlist(this, "ImageViewIcon", ::getLookfaceFileName(idLookface));

	int nFightIndex = UserAttrMgr::getInstance()->getAttr(USER_ATTR_fight_index);
	IF_OK(nFightIndex > 0 && nFightIndex <= MAX_POKER_FIGHT_GROUP)
	{
		ui::Helper::setVisable(this, "ImageViewFight", pPoker->GetMemoryDataAttr((POKER_ATTR)(POKER_ATTR_pos1 + nFightIndex - 1)) > 0);
	}
	
	// 文字显示默认都false
	ui::Helper::setVisable(this, "ImageViewDetailBg", false);
	ui::Helper::setVisable(this, "TextDetail", false);
	ui::Helper::setVisable(this, "ImageViewCountBg", false);
	ui::Helper::setVisable(this, "TextCount", false);

	// 默认不选中
	this->selectPoker(false);

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool WidgetPoker::isSelected()
{
	auto pImageView = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(this, "ImageViewSelectBg"));
	CHECKF(pImageView);
	return pImageView->isVisible();
}

//////////////////////////////////////////////////////////////////////////
void WidgetPoker::selectPoker(bool bSelect)
{
	auto pImageView = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(this, "ImageViewSelectBg"));
	IF_OK(pImageView)
	{
		pImageView->setVisible(bSelect);
	}

	if (bSelect)
	{
		this->runAction(EaseElasticOut::create(ScaleTo::create(0.2f, 1.2f)));
	}
	else
	{
		this->runAction(ScaleTo::create(0.1f, 1.f));
	}
}

//////////////////////////////////////////////////////////////////////////
void WidgetPoker::setDetail(const std::string& text)
{
	auto pImageView = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(this, "ImageViewDetailBg"));
	auto pText = dynamic_cast<ui::Text*>(ui::Helper::seekNodeByName(this, "TextDetail"));
	CHECK(pImageView && pText);

	if (text.empty())
	{
		pImageView->setVisible(false);
		pText->setVisible(false);
		return;
	}

	pImageView->setVisible(true);
	pText->setVisible(true);
	pText->setString(text);
}

//////////////////////////////////////////////////////////////////////////
void WidgetPoker::setCount(int nCount)
{
	auto pImageView = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(this, "ImageViewCountBg"));
	auto pText = dynamic_cast<ui::Text*>(ui::Helper::seekNodeByName(this, "TextCount"));
	CHECK(pImageView && pText);

	if (nCount < 0)
	{
		pImageView->setVisible(false);
		pText->setVisible(false);
		return;
	}

	pImageView->setVisible(true);
	pText->setVisible(true);
	pText->setString(StringUtils::format("%d", nCount));
}

//////////////////////////////////////////////////////////////////////////
Poker* WidgetPoker::getPoker() const
{
	CHECKF(m_idPoker);
	return PokerMgr::getInstance()->getPoker(m_idPoker);
}
