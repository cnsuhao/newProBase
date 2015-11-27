////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2015, WuHan GoodGame, All Rights Reserved
// Moudle: SceneBattle.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-28
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_BATTLE_SCENE_H_
#define _JPY_BATTLE_SCENE_H_

#include "./../Global/Global.h"

class SceneBattle : public Scene, public SceneNetworkProtocol
{
public:
	virtual bool init();
	CREATE_FUNC(SceneBattle);
protected:
	virtual ~SceneBattle();

public:
	virtual void OnConnectOK();
	virtual void OnConnectBreak();

public:
	virtual void update(float delta) override;
	virtual void onEnterTransitionDidFinish();

public:
	void shake();

};

#endif // end of _JPY_BATTLE_SCENE_H_
