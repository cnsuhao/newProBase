////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceDrop.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-24
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_INSTANCE_DROP_H_
#define _JPY_LAYER_INSTANCE_DROP_H_

#include "Global/Global.h"

class SceneMain;
class LayerInstanceDrop : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerInstanceDrop();
public:
	virtual bool init();
	CREATE_FUNC(LayerInstanceDrop);

	bool	updateDropInfo(OBJID idInstance);

protected:
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
};

#endif // end of _JPY_LAYER_INSTANCE_DROP_H_
