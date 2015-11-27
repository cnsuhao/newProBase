////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: LayerHomeView.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/11/20
////////////////////////////////////////////////////////////////////////

#ifndef _JPY_LayerHomeView_H_
#define _JPY_LayerHomeView_H_

#include "Global/Global.h"

class SceneMain;
class LayerHomeView : public Layer, public TouchPriorityBase, public ui::EditBoxDelegate
{
protected:
	virtual ~LayerHomeView();
public:
	virtual bool init();
	CREATE_FUNC(LayerHomeView);

protected:
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	virtual bool onTouchBegan(Touch *touch, Event *unused_event) { return false; }	// View类不吞事件

	// 调试相关
public:
	virtual void editBoxEditingDidBegin(ui::EditBox* editBox) { CCLOG("begin"); };
	virtual void editBoxEditingDidEnd(ui::EditBox* editBox) { CCLOG("end"); };
	virtual void editBoxTextChanged(ui::EditBox* editBox, const std::string& text){ CCLOG("changed"); }
	virtual void editBoxReturn(ui::EditBox* editBox);
	void processClientGmCmd(const std::string& cmd);
};

#endif // end of _JPY_LayerHomeView_H_
