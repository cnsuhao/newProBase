////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: GlobalTypeDef.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_GLOBAL_TYPE_DEF_H_
#define _JYP_GLOBAL_TYPE_DEF_H_

#include "cocos2d.h"
#include "GlobalEnumDef.h"
#include "Common/CommonStruct.h"

typedef int64_t DB_KEY;
typedef std::vector<int64_t>	VEC_DB_KEY;
typedef std::vector<int>		VEC_INT;
typedef std::set<OBJID>			SET_OBJID;

// 场景网络接口
class SceneNetworkProtocol
{
public:
	virtual void OnConnectOK() = 0;
	virtual void OnConnectBreak() = 0;
};

typedef std::function<void(cocos2d::Ref*, MESSAGE_BOX_CLICK)> MessageBoxClickCallback;
typedef std::function<void()> PayWarningCallback;

#endif // end of _JYP_GLOBAL_TYPE_DEF_H_