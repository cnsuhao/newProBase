////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerPopPokerSort.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/11/24
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LayerPopPokerSort_H_
#define _JPY_LayerPopPokerSort_H_

#include "Global/Global.h"

class SceneMain;
class LayerPopPokerSort : public Layer, public TouchPriorityBase
{
public:
	virtual bool init();
	CREATE_FUNC(LayerPopPokerSort);

protected:
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

};

#endif // end of _JPY_LayerPopPokerSort_H_