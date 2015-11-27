////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameSign.h
// Author: �½���(Chen Jianjun)
// Created: 2015-10-30
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNEL_MSG_GAME_SIGN_H_
#define _GAMEKERNEL_MSG_GAME_SIGN_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "./Network/NetMsg.h"

enum EMSGSIGNACTION			// ��Ϣ����
{
	EMSA_NONE = 0,
	EMSA_QUERY_SIGN_INFO = 1,	// ��ѯǩ����Ϣ
	EMSA_SIGN = 2,	// ǩ��
};

enum EMSGSIGNRESULT			// ��Ϣ�������
{
	EMSR_SUC = 0,	// ǩ���ɹ�
	EMSR_FAILD = 1,	// ͨ��ʧ��
	EMSR_ALREADY_SIGN = 2,	// �Ѿ�ǩ����
	EMSR_NOT_ENOUGH = 3,	// ��������
	EMSR_PACKFULL = 4,	// ��������
};

class CMsgGameSign : public CNetMsg
{
public:
	CMsgGameSign();
	virtual ~CMsgGameSign();

protected:
	virtual void Process();

public:
	bool	CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult);

private:
	typedef struct{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;
		MSG_NUM_4BIT	nParamNum;
		ST_SIGN_AWARD_INFO	stInfo[1];
	}MSG_Info;

	MSG_Info*			m_pInfo;
};

#endif // !defined _GAMEKERNEL_MSG_GAME_SIGN_H_
