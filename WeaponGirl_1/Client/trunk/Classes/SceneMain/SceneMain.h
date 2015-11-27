////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: SceneMain.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-14
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_MAIN_SCENE_H_
#define _JYP_MAIN_SCENE_H_

#include "Global/Global.h"

class LayerMain;
class SceneMain : public Scene, public SceneNetworkProtocol
{
public:
	virtual bool init();
	CREATE_FUNC(SceneMain);

protected:
	virtual ~SceneMain();

public:
	virtual void OnConnectOK();
	virtual void OnConnectBreak();

public:
	LayerMain* getLayerMain() const;
	bool loadMainView(const std::string& rLayoutName);
	bool popBottomDlg(const std::string& rImageViewName);
	
protected:
	void reconnect(float dt);

};

#endif // end of _JYP_MAIN_SCENE_H_
