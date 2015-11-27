////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLoginLoad.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/05/26
////////////////////////////////////////////////////////////////////////
#include "LayerLoginLoad.h"
#include "Root.h"
#include "SceneLogin.h"

//////////////////////////////////////////////////////////////////////////
bool LayerLoginLoad::init()
{
	this->setName("LayerLoginLoad");

	// ¼ÓÔØcsb
	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerLoginLoad.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);

	m_loadbar = (ui::LoadingBar*)ui::Helper::seekWidgetByName(m_pCsbWidget, "LoginLoadingBar");
	CHECKF(m_loadbar);
	m_loadbar->setCapInsets(Rect(18, 18, 8, 8));
	m_loadbar->setScale9Enabled(true);


	// ¼ÓÔØ¹Ç÷À»º´æ
	SpineCache::getInstance()->proloadCache();		// ¹Ç÷À»º´æ
	this->setPercent(20);

	return true;
}

//////////////////////////////////////////////////////////////////////////
void LayerLoginLoad::setPercent(float fPercent)
{
	CHECK(fPercent >= 0 && fPercent <= 100);
	CHECK(m_loadbar);
	m_loadbar->setPercent(fPercent);
}
