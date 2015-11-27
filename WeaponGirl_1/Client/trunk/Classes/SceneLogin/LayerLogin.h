////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerLogin.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_LOGIN_H_
#define _JPY_LAYER_LOGIN_H_

#include "Global/Global.h"
#include "network/HttpClient.h"

class SceneLogin;
class LayerLogin : public Layer, public TouchPriorityBase
{
public:
	virtual bool init();
	CREATE_FUNC(LayerLogin);

public:
	virtual void update(float delta) override;
	void sendReqLogin();
	void updateLoginServerName();
	void finishConfigNetworkData();

protected:
	void clickChooseServer(Ref* pSender);
	void clickLogin(Ref* pSender);
	SceneLogin* getFather() const {return (SceneLogin*)_parent;}
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	void recvHttp(network::HttpClient* client, network::HttpResponse* response);

protected:
	bool m_bActiveButton;
	
};

#endif // end of _JPY_LAYER_LOGIN_H_
