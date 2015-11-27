////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginCreateNewUser.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_LOGIN_CREATE_NEW_USER_H_
#define _GAMESERVER_MSG_LOGIN_CREATE_NEW_USER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_LOGIN_CREATE_NEW_USER_RESULT
{
	MSG_LOGIN_CREATE_NEW_USER_RESULT_SUCCESS		= 0,
	MSG_LOGIN_CREATE_NEW_USER_RESULT_FAIL			= 1,	// 通用失败
	MSG_LOGIN_CREATE_NEW_USER_RESULT_NAME_CHECK		= 2,	// 名字过不了服务端敏感字检查
	MSG_LOGIN_CREATE_NEW_USER_RESULT_CODE_REPEAT	= 3,	// code重复,稍后重试
	MSG_LOGIN_CREATE_NEW_USER_RESULT_COUNT_FULL		= 4,	// 已经有3个角色
};

class CMsgLoginCreateNewUser : public CNetMsg  
{
public:
	CMsgLoginCreateNewUser();
	virtual ~CMsgLoginCreateNewUser();
	virtual void Process();

	bool createCreateNewPlayer(const char* pszName, int nLookface, int nJob);

private:
	typedef struct
	{
		MSG_STR_32BIT	szName;
		MSG_NUM_4BIT	nSex;
		MSG_NUM_4BIT	nLookface;
		MSG_NUM_4BIT	nJob;

		MSG_NUM_4BIT	nResult;
		MSG_NUM_4BIT	nUserID;
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMESERVER_MSG_LOGIN_CREATE_NEW_USER_H_