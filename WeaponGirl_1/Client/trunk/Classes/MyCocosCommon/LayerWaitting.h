////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerWaitting.h
// Author: ¿Ó√ŒÀ…(MengSong Lee)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_WAITTING_H_
#define _JPY_LAYER_WAITTING_H_

#include "Global/Global.h"

class LayerWaitting : public Layer, public TouchPriorityBase
{
protected:
	LayerWaitting();
	~LayerWaitting();

protected:
	virtual bool init();
	static LayerWaitting* create();

public:
	static void startWaitting(Scene* fatherScene = nullptr, bool bMaskLayer = false);
	static void stopWaitting(Scene* fatherScene = nullptr); 
	static void clearWaitting(Scene* fatherScene);

protected:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // end of _JPY_LAYER_WAITTING_H_