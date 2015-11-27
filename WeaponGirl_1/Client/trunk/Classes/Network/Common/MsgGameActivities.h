////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: CMsgGameActivities.h
// Author: 
// Created: 2014-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_GAME_ACTIVITIES_H_
#define _GAMESERVER_MSG_GAME_ACTIVITIES_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_ACTIVITY_ACTION
{
	MSG_ACTIVITY_ACTION_BEGIN,

	MSG_ACTIVITY_ACTION_BROADCAST_START,			// ֪ͨ���ʼ		S --> C
	MSG_ACTIVITY_ACTION_BROADCAST_OVER,				// ֪ͨ�����		S --> C
	MSG_ACTIVITY_ACTION_QUERY_ALL_ACTIVITIES,		// ��ѯ���л		C <-> S
	MSG_ACTIVITY_ACTION_QUERY_RUN_ACTIVITIES,		// ��ѯ���л		C <-> S
	MSG_ACTIVITY_ACTION_END,
};

enum MSG_ACTIVITY_RESULT_TYPE
{
	MSG_ACTIVITY_RESULT_TYPE_BEGIN,

	MSG_ACTIVITY_RESULT_TYPE_SUCC = MSG_ACTIVITY_RESULT_TYPE_BEGIN,					// �����ɹ�
	MSG_ACTIVITY_RESULT_TYPE_FAIL,													// ʧ��

	MSG_ACTIVITY_RESULT_TYPE_END,
};

class CMsgGameActivities : public CNetMsg
{
public:
	CMsgGameActivities(void);
	virtual ~CMsgGameActivities(void);
public:
	virtual void	Process();
	bool createQueryAll();

private:
	typedef struct 
	{
		MSG_NUM_2BIT	sAction;		// ��������
		MSG_NUM_2BIT	sResult;		// ���
		MSG_NUM_4BIT	nCount;			// �䳤����
		Activity_Info	stActivity[1];	// �����
	}MSG_Info;
	
	MSG_Info* m_pInfo;

};
#endif // _GAMESERVER_MSG_GAME_ACTIVITIES_H_
