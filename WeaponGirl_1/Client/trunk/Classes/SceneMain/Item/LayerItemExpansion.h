////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerItemExpansion.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-10-28
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_ITEM_EXPASION_H_
#define _JPY_LAYER_ITEM_EXPASION_H_

#include "Global/Global.h"

class SceneMain;
class LayerItemExpansion : public Layer, public TouchPriorityBase
{
public:
	static LayerItemExpansion* create();
	bool init();

protected:
	Node*		m_csbNode;
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // end of _JPY_LAYER_ITEM_EXPASION_H_