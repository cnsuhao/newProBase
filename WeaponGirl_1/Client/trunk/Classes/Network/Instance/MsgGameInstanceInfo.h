////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameInstanceInfo.h
// Author: �½���(Chen Jianjun)
// Created: 2015-11-13
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_INSTANCE_INFO_H_
#define _GAMEKERNEL_MSG_GAME_INSTANCE_INFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./Network/NetMsg.h"

enum EMSGINSTANCEACTION				// ��Ϣ����
{
	EMSGINSTANCEA_NONE = 0,
	EMSGINSTANCEA_QUERY_INFO,		// ��ѯ������Ϣ			C <-> S
	EMSGINSTANCEA_FIGHT,			// ��ʼս��				C <-> S

	EMSGINSTANCEA_SEARCHING,		// ��ʼ̽��				C <-> S
	EMSGINSTANCEA_SEARCHING_AWARD,	// ���̽�����			C <-> S
	EMSGINSTANCEA_SEARCHING_COUNT,	// ����̽������			C <-> S
};

enum EMSGINSTANCERESULT				// ��Ϣ�������
{
	EMSGINSTANCER_SUC	= 0,		// ͨ�óɹ�
	EMSGINSTANCER_FAILD = 1,		// ͨ��ʧ��
};

class CMsgGameInstanceInfo : public CNetMsg
{
public:
	CMsgGameInstanceInfo();
	virtual ~CMsgGameInstanceInfo();

protected:
	virtual void Process();

public:
	bool CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idInstance);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;
		MSG_NUM_4BIT	idInstance;			// ����id
		MSG_NUM_4BIT	nFightLeftTime;		// ս��ʣ��ʱ��
		MSG_NUM_4BIT	nFightCount;		// ս������
		MSG_NUM_4BIT	nResetTime;			// ��������ʱ��
		MSG_NUM_4BIT	nSearchingLeftTime;	// ̽��ʣ��ʱ��
		MSG_NUM_4BIT	nSearchingCount;	// ̽������
		MSG_NUM_4BIT	nCommentCount;		// ������
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif