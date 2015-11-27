////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameLoginQuery.h
// Author: ������(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_LOGIN_QUERY_H_
#define _GAMEKERNER_MSG_GAME_LOGIN_QUERY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

// ��¼actionö��, ��ӦsAction
enum MSG_LOGIN_QUERY_ACTION
{
	MSG_LOGIN_QUERY_ACTION_HEARTBEAT					= 1,	// ����				C <-> S
	MSG_LOGIN_QUERY_ACTION_CLIENT_LOGIN_OVER			= 2,	// �ͻ��˵�½���	C --> S


	MSG_LOGIN_QUERY_ACTION_AUTOBACK_BEGIN				= 100,	// �Զ��ذ���ʼ	����ȫ�� C <-> S
	MSG_LOGIN_QUERY_ACTION_ALL_MONEY					= 101,	// ��ѯȫ����Ǯ		
	MSG_LOGIN_QUERY_ACTION_MASKINFO						= 102,	// ��ѯ����		
	MSG_LOGIN_QUERY_ACTION_PACKAGE						= 103,	// ��ѯ����
	MSG_LOGIN_QUERY_ACTION_ALL_FRIEND					= 104,	// ��ѯ����
	MSG_LOGIN_QUERY_ACTION_CLIENT_TMPDATA				= 105,	// ��ѯ�ͻ����Զ���TmpData
	MSG_LOGIN_QUERY_ACTION_ALL_TASK						= 106,	// ��ѯ�����б�
	MSG_LOGIN_QUERY_ACTION_UNREADMAILCOUNT				= 107,	// ��ѯδ���ʼ�����
	MSG_LOGIN_QUERY_ACTION_SIGN							= 108,	// ��ѯǩ��
	MSG_LOGIN_QUERY_ACTION_SELF_SYNDICATE				= 109,	// ��ѯ�Լ�������Ϣ
	MSG_LOGIN_QUERY_ACTION_ACTIVITES					= 110,	// ��ѯ���л
	MSG_LOGIN_QUERY_ACTION_INSTANCE_LIST				= 111,	// ��ѯ�����б�

	MSG_LOGIN_QUERY_ACTION_SERVER_GROUP					= 113,	// ��ѯ����������Ϣ
};

// ������ö��, ��ӦsResult
enum MSG_LOGIN_QUERY_RESULT
{
	MSG_LOGIN_QUERY_RESULT_SUCC		= 0,
	MSG_LOGIN_QUERY_RESULT_ERROR	= 1,
};

class CMsgGameLoginQuery : public CNetMsg
{
public:
	CMsgGameLoginQuery();
	virtual ~CMsgGameLoginQuery();

	virtual void Process();

public:
	bool CreateLoginQuery(MSG_LOGIN_QUERY_ACTION eAction, MSG_LOGIN_QUERY_RESULT eResult = MSG_LOGIN_QUERY_RESULT_SUCC, int nParam1 = 0, int nParam2 = 0);

private:
	void ProcessHeartbeat(void);

private:
	typedef struct  
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	nParam1;
		MSG_NUM_4BIT	nParam2;
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMEKERNER_MSG_GAME_LOGIN_QUERY_H_