////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: GlobalConstDef.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_GLOBAL_CONST_DEF_H_
#define _JYP_GLOBAL_CONST_DEF_H_

#include "Common/Commonconstdef.h"
#include "Common/CommonEnumdef.h"

#include "cocos2d.h"
using namespace cocos2d;

const int ID_NONE = 0;

const float APP_DESIGN_WIDTH = 1080.f;		// 程序设计尺寸
const float APP_DESIGN_HEIGHT = 1920.f;		// 程序设计尺寸

const float		ZORDER_WAITTING		= 99999.f;		// WAITTING
const float		ZORDER_TIPS			= 99998.f;		// 弹窗
const float		ZORDER_EFFECT		= 25.f;			// 特效

const float		MOVE_OUT_LEFT_EFFECT_TIME = 0.6f;	
const float		MOVE_IN_LEFT_EFFECT_TIME = 0.6f;

const int MAX_USER_AMOUNT = 3;		// 最多3个角色
const int NAME_SIZE = 32;		// 最多32个字符



#endif // end of _JYP_GLOBAL_CONST_DEF_H_