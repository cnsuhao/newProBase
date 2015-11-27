////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgLoginAction.h
// Author: ������(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_LOGIN_ACTION_H_
#define _GAMESERVER_MSG_LOGIN_ACTION_H_

#include "../NetMsg.h"

enum MSG_LOGIN_ACTION_TYPE
{
	MSG_LOGIN_ACTION_TYPE_CHOOSE_USER	= 1,	// ѡ�����		C --> S
	MSG_LOGIN_ACTION_TYPE_DELETE_USER	= 2,	// ɾ�����		C <-> S
};

enum MSG_LOGIN_ACTION_RESULT
{
	MSG_LOGIN_ACTION_RESULT_SUCCESS		= 0,	// �ɹ�
	MSG_LOGIN_ACTION_RESULT_FAIL		= 1,	// ʧ��
};

class CMsgLoginAction : public CNetMsg  
{
public:
	CMsgLoginAction();
	virtual ~CMsgLoginAction();
	virtual void	Process		();

public:
	bool CreateChooseUser(OBJID idUser);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;

		MSG_NUM_4BIT	nUserID;
		MSG_NUM_4BIT	nParam;
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMESERVER_MSG_LOGIN_ACTION_H_