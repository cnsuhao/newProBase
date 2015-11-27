////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: SceneBattle.cpp
// Author: ������(Peng Wenqi)
// Created: 2015-1-28
////////////////////////////////////////////////////////////////////////
#include "SceneBattle.h"

#include "Network/NetworkServe.h"
#include "Root.h"

#include "Mgr/LogicDataMgr.h"


bool SceneBattle::init()
{
	if(!Scene::init())
	{
		return false;
	}

	this->setName("SceneBattle");
	Root::getInstance()->setSceneBattle(this);
		

	// ������ʱ
	this->scheduleUpdate();

	return false;
}

//////////////////////////////////////////////////////////////////////////
SceneBattle::~SceneBattle()
{
	Root::getInstance()->setSceneBattle(nullptr);
	Root::getInstance()->autoClearCache();
}

//////////////////////////////////////////////////////////////////////////
void SceneBattle::OnConnectOK()
{

}

//////////////////////////////////////////////////////////////////////////
void SceneBattle::OnConnectBreak()
{
	Director::getInstance()->popScene();
}

////////////////////////////////////////////////////////////////////////
// Description: ����ά��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void SceneBattle::update( float delta )
{
	Scene::update(delta);

	// �߼�ÿ����4��
	static int64_t lastMS = 0;
	int64_t nowMS = ::GetUtcMillisecond();
	if (nowMS < lastMS + 250)
	{
		return;
	}
	lastMS = nowMS;

}

//////////////////////////////////////////////////////////////////////////
void SceneBattle::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
}

//////////////////////////////////////////////////////////////////////////
void SceneBattle::shake()
{
	const float fShakeTime = 0.5f;
	const float fShakestrength = 16.f;
	const int nShakeTag = 998;

// 	auto actionShakeMap = FallOffShake::create(fShakeTime, fShakestrength);
// 	actionShakeMap->setTag(nShakeTag);
// 	auto layerMap = this->getChildByName("LayerBattleMap");
// 	CHECK(layerMap);
// 	if (layerMap->getActionByTag(nShakeTag))
// 	{
// 		return;
// 	}
// 	layerMap->runAction(actionShakeMap);
// 
// 
// 	auto actionShakeFighter = FallOffShake::create(fShakeTime, fShakestrength);
// 	actionShakeMap->setTag(nShakeTag);
// 	auto layerFighter = this->getChildByName("LayerBattleFighter");
// 	CHECK(layerFighter);
// 	if (layerFighter->getActionByTag(nShakeTag))
// 	{
// 		return;
// 	}
// 	layerFighter->runAction(actionShakeFighter);
}
