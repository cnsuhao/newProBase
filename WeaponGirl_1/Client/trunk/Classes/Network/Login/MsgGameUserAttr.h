////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameUserAttr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_USER_ATTR_H_
#define _GAMEKERNER_MSG_GAME_USER_ATTR_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"


struct MSG_USER_ATTR_INFO
{
	int nType;
	int64_t	i64Data;
};

class CMsgGameUserAttr : public CNetMsg
{
public:
	CMsgGameUserAttr();
	virtual ~CMsgGameUserAttr();

	virtual void Process();

private:
	typedef struct  
	{
		MSG_NUM_4BIT		nCount;
		MSG_USER_ATTR_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMEKERNER_MSG_GAME_USER_ATTR_H_