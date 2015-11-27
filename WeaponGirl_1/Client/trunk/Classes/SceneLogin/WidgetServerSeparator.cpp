////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetServerSeparator.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/10
////////////////////////////////////////////////////////////////////////
#include "WidgetServerSeparator.h"

//////////////////////////////////////////////////////////////////////////
WidgetServerSeparator::WidgetServerSeparator()
{

}

//////////////////////////////////////////////////////////////////////////
WidgetServerSeparator::~WidgetServerSeparator()
{

}

//////////////////////////////////////////////////////////////////////////
WidgetServerSeparator* WidgetServerSeparator::create(Node* pCsbNode, const std::string& text /*= ""*/)
{
	WidgetServerSeparator* pRet = new(std::nothrow) WidgetServerSeparator();
	if (pRet && pRet->init(pCsbNode, text))
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
bool WidgetServerSeparator::init(Node* pCsbNode, const std::string& text)
{
	CHECKF(pCsbNode);
	auto csbLayout = (ui::Widget*)pCsbNode->getChildByName("Layout");
	CHECKF(csbLayout);

	this->copyProperties(csbLayout);
	this->copyClonedWidgetChildren(csbLayout);
	ui::Helper::setStringText(this, "Text", text);

	return true;
}
