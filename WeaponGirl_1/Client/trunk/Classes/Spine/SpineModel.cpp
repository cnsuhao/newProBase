////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: SpineModel.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/19
////////////////////////////////////////////////////////////////////////
#include "SpineModel.h"

SpineModel* SpineModel::createWithPokerType(OBJID idPokerType)
{
	SpineModel *pRet = new(std::nothrow) SpineModel();
	if (pRet && pRet->initWithPokerType(idPokerType))
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
bool SpineModel::initWithPokerType(OBJID idPokerType)
{
	CHECKF(idPokerType);
	this->setName("SpineModel");

#pragma message(PRAGMAMSG(initWithPokerType临时用卡牌类型当做模型类型进行初始化))
	OBJID idSpineType = idPokerType;	
	CHECKF(this->initSpine(idSpineType));

	return true;
}

//////////////////////////////////////////////////////////////////////////
SpineModel::SpineModel()
{
	m_idPokerType = ID_NONE;
}

//////////////////////////////////////////////////////////////////////////
SpineModel::~SpineModel()
{

}
