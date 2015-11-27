////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: TouchPriority.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/05/27
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_MGR_TOUCH_PRIORITY_MGR_H_
#define _JYP_MGR_TOUCH_PRIORITY_MGR_H_

#include "cocos2d.h"
using namespace cocos2d;

// 触摸优先级
struct TouchPriorityData
{
	int				nPriority;
	std::string		strNodeName;
	cocos2d::Node*	node;
};

enum TOUCH_LAYER_POP_MODE
{
	TOUCH_LAYER_POP_MODE_none,
	TOUCH_LAYER_POP_MODE_scale,
	TOUCH_LAYER_POP_MODE_fadein,
};

class TouchPriorityBase 
{
protected:
	TouchPriorityBase(){ m_nFixedTouchPriority = 0; m_pLayerTouchListener = nullptr; m_pCsbWidget = nullptr; }
	virtual ~TouchPriorityBase();
	bool initTouchPriority(const std::string& name = "", Node* node = nullptr);
	int m_nFixedTouchPriority;
	EventListenerTouchOneByOne* m_pLayerTouchListener;

public:
	bool isInTouchRect(Vec2 point) const;
	void setPopLayoutMode(TOUCH_LAYER_POP_MODE eMode = TOUCH_LAYER_POP_MODE_scale);
	void setCloseImageView(const std::string& closeImageviewName);

protected:
	CC_SYNTHESIZE_READONLY(ui::Widget*, m_pCsbWidget, CsbWidget);
	
};

class TouchPriority : public Ref
{
public:
	static TouchPriority*	getInstance();
	static void				destroyInstance();
private:
	static TouchPriority*	m_pInstance;

public:
	int		genTouchPriority(const std::string& nodeName = "", Node* node = nullptr);
	void	popTouchPriority(int nPriority);
protected:
	std::deque<TouchPriorityData>	m_deqTouchPriority;
};

#endif // end of _JYP_MGR_TOUCH_PRIORITY_MGR_H_