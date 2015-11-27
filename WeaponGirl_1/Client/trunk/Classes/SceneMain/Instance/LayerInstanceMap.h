////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceMap.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-20
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_INSTANCE_MAP_H_
#define _JPY_LAYER_INSTANCE_MAP_H_

#include "Global/Global.h"

class SceneMain;
class LayerInstanceMap : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerInstanceMap();
public:
	virtual bool init();
	CREATE_FUNC(LayerInstanceMap);
	
	virtual void setVisible(bool bVisible) override;

	bool	updateMap(OBJID idInstance);

protected:
	bool	checkMap();
	Node*	m_pMapThroughCsbNode;
	Node*	m_pMapLockCsbNode;
	cocos2d::Map<int, Node*>	m_mapChapterInfo;
	SceneMain* getFather() const { return (SceneMain*)_parent; }
};

#endif // end of _JPY_LAYER_INSTANCE_MAP_H_
