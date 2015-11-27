////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerInstanceView.h
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-19
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_INSTANCE_VIEW_H_
#define _JPY_LAYER_INSTANCE_VIEW_H_

#include "Global/Global.h"

class SceneMain;
class WidgetInstanceViewInfo;
class LayerInstanceView : public Layer, public TouchPriorityBase
{
protected:
	virtual ~LayerInstanceView();
public:
	virtual bool init();
	CREATE_FUNC(LayerInstanceView);

	virtual void update(float delta) override;
	virtual void setVisible(bool bVisible) override;

public:
	void	updateFightTime(int nTime);
	void	updateSearchingTime(int nTime);
	void	openWarning();
	void	closeWarning();
	bool	setSearchingMaxCount(int nCount);
	bool	setSearchingCount(int nCount);
	bool	changePass(int nPass);
	bool	checkMap();
	bool	updateMap(int nChapter);

protected:
	bool	initButtonListen(const std::string& strName, const ui::Widget::ccWidgetClickCallback& callback);
	bool	changeMode(int nMode, bool bForce= false);
	bool	selectMode(int nMode);
	bool	cancelMode(int nMode);

protected:
	WidgetInstanceViewInfo* m_pInstanceViewInfo;
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event) { return false; }	// View类不吞事件
};

#endif // end of _JPY_LAYER_INSTANCE_VIEW_H_
