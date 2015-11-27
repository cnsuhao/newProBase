////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: SceneLogin.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-14
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LOGIN_SCENE_H_
#define _JPY_LOGIN_SCENE_H_

#include "Global/Global.h"

class LayerLoginBg;
class LayerLogin;
class LayerInputName;
class LayerCreateNew;
class LayerLoginLoad;

class SceneLogin : public Scene, public SceneNetworkProtocol
{
public:
	virtual bool init();
	CREATE_FUNC(SceneLogin);
protected:
	virtual ~SceneLogin();

public:
	virtual void OnConnectOK();
	virtual void OnConnectBreak();

public:
	void reInit();
	void callbackStartLogin(const std::string& accountName, const std::string& accountPassword);
	void popLayerInputName();
	void popLayerCreateNew();
	void popLayerLoad();
	void popLayerServerList();
};

#endif // end of _JPY_LOGIN_SCENE_H_
