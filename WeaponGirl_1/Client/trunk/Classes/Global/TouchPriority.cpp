////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: TouchPriority.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/05/27
////////////////////////////////////////////////////////////////////////
#include "TouchPriority.h"
#include "GlobalMacro.h"
#include "ui\UIHelper.h"
#include "ui\UIWidget.h"
#include "ui\UILayout.h"
#include "ui\UIImageView.h"
#include "base\CCDirector.h"


TouchPriority* TouchPriority::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
TouchPriority* TouchPriority::getInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new TouchPriority();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void TouchPriority::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}

////////////////////////////////////////////////////////////////////////
// Description: 获得一个新的触摸优先级
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
int TouchPriority::genTouchPriority(const std::string& nodeName /*= ""*/, Node* node /*= nullptr*/)
{
	TouchPriorityData st;
	st.nPriority = 0;
	st.strNodeName = nodeName;
	st.node = node;

	// 如果注册了节点, 则不准重复
	if (node != nullptr)
	{
		for (auto i : m_deqTouchPriority)
		{
			if (i.node == node)
			{
				return i.nPriority;
			}
		}
	}

	// 新的触摸优先级会减一, 处于更高的触摸优先级
	if (m_deqTouchPriority.empty())
	{
		st.nPriority = -1;
	}
	else
	{
		auto index = m_deqTouchPriority.size() - 1;
		st.nPriority = m_deqTouchPriority[index].nPriority - 1;
	}

	m_deqTouchPriority.push_back(st);
	return st.nPriority;
}

////////////////////////////////////////////////////////////////////////
// Description: 弹出触摸优先级
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void TouchPriority::popTouchPriority(int nPriority)
{
	CHECK(nPriority < 0);
	for (auto iter = m_deqTouchPriority.begin(); iter != m_deqTouchPriority.end(); iter++)
	{
		if (iter->nPriority == nPriority)
		{
			m_deqTouchPriority.erase(iter);
			return;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
TouchPriorityBase::~TouchPriorityBase()
{
	if (m_nFixedTouchPriority < 0)
	{
		TouchPriority::getInstance()->popTouchPriority(m_nFixedTouchPriority);
	}

	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	if (m_pLayerTouchListener && eventDispatcher)
	{
		eventDispatcher->removeEventListener(m_pLayerTouchListener);
	}
}

//////////////////////////////////////////////////////////////////////////
bool TouchPriorityBase::initTouchPriority(const std::string& name /*= ""*/, Node* node /*= nullptr*/)
{
	m_nFixedTouchPriority = TouchPriority::getInstance()->genTouchPriority(name, node);
	return m_nFixedTouchPriority < 0;
}

////////////////////////////////////////////////////////////////////////
// Description: 判断是否在触摸矩形内
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool TouchPriorityBase::isInTouchRect(Vec2 point) const
{
	CHECKF(m_pCsbWidget);
	
	// 未配置触摸范围精灵
	auto layout = (ui::Layout*)ui::Helper::seekWidgetByName(m_pCsbWidget, "LayoutTouch");
	if (!layout)
	{
		return false;
	}

	// 在配置矩形中
	if (!layout->getBoundingBox().containsPoint(point))
	{
		return false; 
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 以缩放方式弹出触摸层
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void TouchPriorityBase::setPopLayoutMode(TOUCH_LAYER_POP_MODE eMode)
{
	CHECK(m_pCsbWidget);
	auto touchNode = ui::Helper::seekNodeByName(m_pCsbWidget, "LayoutTouch");
	CHECK(touchNode);

	switch (eMode)
	{
	case TOUCH_LAYER_POP_MODE_none:
		break;
	case TOUCH_LAYER_POP_MODE_scale:
		{
			auto scaleAction = EaseSineIn::create(ScaleTo::create(0.2f, 1.f));	// EaseBounceOut弹
			touchNode->setScale(0.01f);
			touchNode->runAction(scaleAction);
		}
		break;
	case TOUCH_LAYER_POP_MODE_fadein:
		{
			auto fadeinAction = FadeIn::create(0.2f);
			touchNode->setCascadeOpacityEnabled(true);
			touchNode->setOpacity(0);
			touchNode->runAction(fadeinAction);
		}
		break;
	default:
		break;
	}
	
}

//////////////////////////////////////////////////////////////////////////
void TouchPriorityBase::setCloseImageView(const std::string& closeImageviewName)
{
	CHECK(m_pCsbWidget);
	auto pImageViewExit = dynamic_cast<ui::ImageView*>(ui::Helper::seekNodeByName(m_pCsbWidget, closeImageviewName));
	CHECK(pImageViewExit);

	pImageViewExit->addClickEventListener([=](Ref*){
		m_pCsbWidget->getParent()->removeFromParent();
	});
//	pImageViewExit->setAutoTouchChangeRenderer(true);
	pImageViewExit->setAutoTouchAction();
	pImageViewExit->setTouchEnabled(true);
}
