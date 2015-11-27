////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameChallenge.h
// Author: �½���(Chen Jianjun)
// Created: 2015-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_CHALLENGE_H_
#define _GAMEKERNEL_MSG_GAME_CHALLENGE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

enum EMSGCHALLENGEACTION					// ��Ϣ����
{
	EMCHALLENGEA_NONE = 0,
	EMCHALLENGEA_QUERY_LIST,				// ��ѯ�б�				C <-> S
	EMCHALLENGEA_FIGHT,						// ��ʼ��ս				C <-> S

	EMCHALLENGEA_QUERY_WORLDRANK_LIST,		// ��ѯ������б�		C <-> S
	EMCHALLENGEA_FIGHT_WORLDRANK,			// ��ʼ������ս			C <-> S
};

enum EMSGCHALLENGERESULT					// ��Ϣ�������
{
	EMCHALLENGER_SUC = 0,					// ǩ���ɹ�
	EMCHALLENGER_FAILD = 1,					// ͨ��ʧ��
};

class CMsgGameChallenge : public CNetMsg
{
public:
	CMsgGameChallenge();
	virtual ~CMsgGameChallenge();

protected:
	virtual void Process();

public:
	bool	CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idTarget);

private:
	typedef struct{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	idTarget;
		MSG_NUM_4BIT	nData1;
		MSG_NUM_4BIT	nData2;

		MSG_NUM_2BIT	sMsgEnd;
		MSG_NUM_2BIT	sParamNum;
		CHALLENGER_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_CHALLENGE_H_
