////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2012, WuHan GoodGame, All Rights Reserved
// Moudle: MsgSmallAction.h
// Author: ������(Lee MengSong)
// Created: 2012-10-23
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_GAME_SMALL_ACTION_H_
#define _GAMESERVER_MSG_GAME_SMALL_ACTION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

// SmallActionö��, ��ӦsAction
enum MSG_SMALL_ACTION
{
	MSG_SMALL_ACTION_NONE = 0,
	MSG_SMALL_ACTION_QUERY_NEWCARDPRIZE_INFO		= 1,	// ��ѯ���ֿ�������Ϣ   	C --> S
	MSG_SMALL_ACTION_RUN_LUA_SCRIPT					= 2,	// ִ��LUA�ű�				C --> S
	MSG_SMALL_ACTION_GET_MONTH_CARD					= 3,	// ��ȡ�¿�					C <-> S
};

// ������ö��, ��ӦsResult
enum MSG_SMALL_RESULT
{
	MSG_SMALL_RESULT_SUCC = 0,
	MSG_SMALL_RESULT_ERROR = 1,
};

//////////////////////////////////////////////////////////////////////////
//	�ر�ע��:
//	�������Э���Ǹ��㷺Ӧ�õı䳤Э��
//	����Э��Create��Processʱ, �����ÿ��������дһ������, ��Ҫ����, �ɶ��Ի�ܺ� 
class CMsgGameSmallAction : public CNetMsg
{
public:
	CMsgGameSmallAction();
	virtual ~CMsgGameSmallAction();

	virtual void Process();
	// Create Func Here...
public:

	// Process Func Here...
private:
	

private:
	bool createSmallAction(MSG_SMALL_ACTION eAction, MSG_SMALL_RESULT eResult);
	bool appendParam(int nAddParam);
	int  getParamVector(OUT VEC_INT& rVec);

public:

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	nParamNumber;
		MSG_NUM_4BIT	nParam[1];
	}MSG_Info;

	MSG_Info* m_pInfo;

};

#endif // end of _GAMESERVER_MSG_GAME_SMALL_ACTION_H_