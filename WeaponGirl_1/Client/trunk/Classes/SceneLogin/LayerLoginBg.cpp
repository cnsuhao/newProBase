////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLoginBg.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/05/22
////////////////////////////////////////////////////////////////////////
#include "LayerLoginBg.h"
#include "Root.h"

//////////////////////////////////////////////////////////////////////////
bool LayerLoginBg::init()
{
	this->setName("LayerLoginBg");

	m_pCsbWidget = (ui::Widget*)CSLoader::createNode("LayerLoginBg.csb");
	this->addChild(m_pCsbWidget);
	ui::Helper::doLayout(m_pCsbWidget);
	return true;
}
