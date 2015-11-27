////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-2016, WuHan GoodGame, All Rights Reserved
// Moudle: LayerMain.h
// Author: 李梦松(MengSong Lee)
// Created: 2015-3-30
////////////////////////////////////////////////////////////////////////
#ifndef _JPY_LAYER_MAIN_H_
#define _JPY_LAYER_MAIN_H_

#include "Global/Global.h"

class SceneMain;
class LayerMain : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(LayerMain);

	// 初始化
protected:
	bool initMainButtonListen(const std::string& strLayoutName, const ui::Widget::ccWidgetClickCallback& callback);
	bool updateMainButton(const std::string& strLayoutName, bool bChoose);
	bool initBottomListen(const std::string& strImageViewName, const ui::Widget::ccWidgetClickCallback& callback);

	// 监听按钮回调
protected:
	void clickMain(Ref* pSender);
	void clickBottom(Ref* pSender);
	void clickPayVas(Ref* pSender); 

	// 界面定时更新
public:
	virtual void update(float delta) override;
	void updateTopMoneyShow();
	void updateTimeShow();
	void updateGreenTips();

public:
	void changeHintText();
protected:
	Vec2 m_initHintPos;

protected:
	virtual ~LayerMain();
	SceneMain* getFather() const { return (SceneMain*)_parent; }
	CC_SYNTHESIZE_READONLY(ui::Widget*, m_pCsbWidget, CsbWidget);
};

#endif // end of _JPY_LAYER_MAIN_H_
