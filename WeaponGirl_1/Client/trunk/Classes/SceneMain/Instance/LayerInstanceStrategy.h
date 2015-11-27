////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceStrategy.h
// Author: ³Â½¨¾ü(Chen Jianjun)
// Created: 2015-11-21
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_INSTANCE_STRATEGY_H_
#define _JPY_LAYER_INSTANCE_STRATEGY_H_

#include "Global/Global.h"

class SceneMain;
class LayerInstanceStrategy : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerInstanceStrategy();
public:
	virtual bool init();
	CREATE_FUNC(LayerInstanceStrategy);

	bool	updateStrategy(OBJID idCommentType);
	bool	updateStrategyNew(OBJID idCommentType, const COMMENT_INFO& info);
	bool	updateStrategyGood(OBJID idCommentType, const COMMENT_INFO& info);

protected:
	bool	LoadItemInfo(ui::Widget* pWidgetItem, const COMMENT_INFO& info);
	bool	initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback, bool bLight = false);
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	CC_SYNTHESIZE_READONLY(OBJID, m_idCommentType, idCommentType);
	cocos2d::Map<DB_KEY, ui::Widget*>	m_mapCommentInfo;
};

#endif // end of _JPY_LAYER_INSTANCE_STRATEGY_H_
