////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: WidgetInstanceViewInfo.cpp
// Author: 陈建军(Chen Jianjun)
// Created: 2015-11-19
////////////////////////////////////////////////////////////////////////
#include "WidgetInstanceViewInfo.h"
#include "Mgr\InstanceMgr.h"
#include "LayerInstanceView.h"
#include "ConstTable\ConstTableMgr.h"
#include "Network\NetworkServe.h"
#include "Network\Instance\MsgGameInstanceInfo.h"

const int	CONST_INT_MAX_PASS	= 4;	// 每章最大关卡
//////////////////////////////////////////////////////////////////////////
WidgetInstanceViewInfo::WidgetInstanceViewInfo()
{
	m_nSelectMode = 0;
	m_nSelectPass = 0;
}

//////////////////////////////////////////////////////////////////////////
WidgetInstanceViewInfo::~WidgetInstanceViewInfo()
{

}

//////////////////////////////////////////////////////////////////////////
WidgetInstanceViewInfo* WidgetInstanceViewInfo::create(int nChapter, const std::string& strCsbName)
{
	WidgetInstanceViewInfo* pRet = new(std::nothrow) WidgetInstanceViewInfo();
	if (pRet && pRet->init(nChapter, strCsbName))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////
bool WidgetInstanceViewInfo::init(int nChapter, const std::string& strCsbName)
{
	// 根据csb加载基础
	auto pCsbNode = CSLoader::createNode(strCsbName);
	CHECKF(pCsbNode);
	auto csbLayout = (ui::Widget*)pCsbNode->getChildByName("Layout");
	this->copyProperties(csbLayout);
	this->copyClonedWidgetChildren(csbLayout);
	
	// 初始化位置
	auto nnfoSize = csbLayout->getContentSize();
	this->setPosition(Vec2(nnfoSize.width / 2, nnfoSize.height / 2));

	// 初始化关卡模型和数据
	for (auto nPassIndex = 1; nPassIndex <= CONST_INT_MAX_PASS; nPassIndex++)
	{
		auto pPassView = this->getPassView(nPassIndex);
		CHECKC(pPassView);
		CHECKF(ui::Helper::setImageViewShaderEffect(pPassView, "ImageViewStar", MY_SHADER_EFFECT_DARK));
		CHECKC(ui::Helper::setImageViewShaderEffect(pPassView,	"ImageViewPassView", MY_SHADER_EFFECT_DARK));
		CHECKC(ui::Helper::setWidgetClickEventListener(pPassView, "ImageViewPassView", [=](Ref*){
			// 开启关卡探索
			auto idInstance = InstanceMgr::getInstance()->getInstanceKey(m_nSelectMode, nChapter, nPassIndex);
			CHECK_NOLOG(idInstance && idInstance != InstanceMgr::getInstance()->getidCurInstance());
			CMsgGameInstanceInfo msg;
			CHECK_NOLOG(msg.CreateMsg(EMSGINSTANCEA_SEARCHING, EMSGINSTANCER_SUC, idInstance));
			NetworkServe::getInstance()->sendMsg(msg);
		}));
		CHECKC(ui::Helper::setDataText(pPassView, "TextChapter", nChapter));
	}
	m_nSelectChapter = nChapter;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 更新地图
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool WidgetInstanceViewInfo::updateMap(int nChapter, const std::string& strCsbName)
{
	this->removeAllChildren();
	CHECKF(this->init(nChapter, strCsbName));
	return true;
}

ui::Widget*	WidgetInstanceViewInfo::getPassView(int nPassIndex)
{
	return dynamic_cast<ui::Widget*>(this->getChildByName(StringUtils::format("LayoutPass_%d", nPassIndex)));
}

////////////////////////////////////////////////////////////////////////
// Description: 模式切换
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool WidgetInstanceViewInfo::changeMode(int nMode)
{
	auto idInstance = InstanceMgr::getInstance()->getidCurInstance();
	CHECKF(idInstance);
	auto nChapter = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_instance, idInstance, INSTANCE_DATA_CHAPTER);
	for (auto nPassIndex = 1; nPassIndex <= CONST_INT_MAX_PASS; nPassIndex++)
	{
		auto idInstance = InstanceMgr::getInstance()->getInstanceKey(nMode, nChapter, nPassIndex);
		CHECKC(idInstance);
		if (InstanceMgr::getInstance()->isPass(idInstance))
		{
			CHECKC(this->winPass(nPassIndex));
		}
	}
	m_nSelectMode = nMode;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 关卡通关
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool WidgetInstanceViewInfo::winPass(int nPass)
{
	auto layoutPass = (ui::Layout*)this->getChildByName(StringUtils::format("LayoutPass_%d", nPass));
	CHECKF(layoutPass);
	CHECKF(ui::Helper::setImageViewTexturePlist(layoutPass, "ImageViewStar", "res/Instance/InstanceStarLight.png"));
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 切换关卡
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool WidgetInstanceViewInfo::changePass(int nPass)
{
	CHECKF(this->cancelPass(m_nSelectPass));
	CHECKF(this->selectPass(nPass)); 
	m_nSelectPass = nPass;
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 取消关卡
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool WidgetInstanceViewInfo::cancelPass(int nPass)
{
	auto pPassView = this->getPassView(nPass);
	if (pPassView)
	{
		CHECKF(ui::Helper::setImageViewShaderEffect(pPassView, "ImageViewStar", MY_SHADER_EFFECT_DARK));
		CHECKF(ui::Helper::setImageViewShaderEffect(pPassView, "ImageViewPassView", MY_SHADER_EFFECT_DARK));
		CHECKF(ui::Helper::setImageViewScale(pPassView, "ImageViewPassView", 1.f, 1.f));
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Description: 选择关卡
// Arguments:
// Author: 陈建军(Chen Jianjun)
// Return Value: void
////////////////////////////////////////////////////////////////////////
bool WidgetInstanceViewInfo::selectPass(int nPass)
{
	auto pPassView = this->getPassView(nPass);
	if (pPassView)
	{
		CHECKF(ui::Helper::setImageViewShaderEffect(pPassView, "ImageViewStar", MY_SHADER_EFFECT_NONE));
		CHECKF(ui::Helper::setImageViewShaderEffect(pPassView, "ImageViewPassView", MY_SHADER_EFFECT_NONE));
		CHECKF(ui::Helper::setImageViewScale(pPassView, "ImageViewPassView", 1.2f, 1.1f));
	}
	return true;
}
////////////////////////////////////////////////////////////////////////
