////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameDebug.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/13
////////////////////////////////////////////////////////////////////////

#ifndef _GAMEKERNEL_MsgGameDebug_H_
#define _GAMEKERNEL_MsgGameDebug_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

class CMsgGameDebug : public CNetMsg
{
public:
	CMsgGameDebug();
	virtual ~CMsgGameDebug();

	virtual void Process();

public:
	bool CreateString(const char* pszString);

private:
	typedef struct
	{
		char szString[512];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif // end of _GAMEKERNEL_MsgGameDebug_H_