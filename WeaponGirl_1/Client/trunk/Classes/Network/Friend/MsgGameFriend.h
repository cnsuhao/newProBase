////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameFriend.h
// Author: �½���(Chen Jianjun)
// Created: 2015-11-2
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_FRIEND_H_
#define _GAMEKERNEL_MSG_GAME_FRIEND_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

enum EMSGFRIENDACTION			// ��Ϣ����
{
	EMFA_NONE				= 0,
	EMFA_SYN_FRIEND_LIST	= 1,	// ͬ�������б�		C <-- S
	EMFA_SYN_REQUST_LIST	= 2,	// ͬ�������б�		C <-- S
	EMFA_UPDATE_FRIEND		= 3,	// ���º�����Ϣ		C <-- S
	EMFA_UPDATE_REQUEST		= 4,	// ����������Ϣ		C <-- S
	EMFA_SEARCH				= 5,	// ��������			C <-> S
	EMFA_REQUEST			= 6,	// �������			C <-> S
	EMFA_AGREE				= 7,	// ͬ�����			C <-> S
	EMFA_REFUSE				= 8,	// �ܾ�����			C <-> S
	EMFA_DELETE				= 9,	// ɾ������			C <-> S
	EMFA_SENDGIFT			= 10,	// �������			C <-> S
	EMFA_FIGHT_FRIENDLY		= 11,	// �д�ս��			C <-> S
};

enum EMSGFRIENDRESULT				// ��Ϣ�������
{
	EMFR_SUC				= 0,	// ͨ�óɹ�
	EMFR_FAILD				= 1,	// ͨ��ʧ��
	EMFR_IS_FRIEND			= 2,	// �Ѿ��Ǻ�����
	EMFR_SELF_FRIEND_FULL	= 3,	// �Լ���������
	EMFR_TARGET_FRIEND_FULL = 4,	// �Է���������
	EMFR_IS_REQUEST			= 5,	// �Ѿ��������
	EMFR_ID_ERRO			= 6,	// ID������
};

class CMsgGameFriend : public CNetMsg
{
public:
	CMsgGameFriend();
	virtual ~CMsgGameFriend();

protected:
	virtual void Process();
	void	ProcessFaildHint();

public:
	bool	CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idFriend = ID_NONE);

private:
	typedef struct{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	idFriend;
		MSG_STR_32BIT	strSearch;

		MSG_NUM_4BIT	nParamNum;
		ST_FRIEDN_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_FRIEND_H_
