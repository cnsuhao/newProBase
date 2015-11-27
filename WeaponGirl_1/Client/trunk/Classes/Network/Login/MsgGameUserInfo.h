////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameUserInfo.h
// Author: ������(Peng Wenqi)
// Created: 2014-11-10
////////////////////////////////////////////////////////////////////////
#ifndef _GAMEKERNER_MSG_GAME_USER_INFO_H_
#define _GAMEKERNER_MSG_GAME_USER_INFO_H_

#include "../NetMsg.h"

class CMsgGameUserInfo : public CNetMsg
{
public:
	CMsgGameUserInfo();
	virtual ~CMsgGameUserInfo();

	virtual void Process();

private:
	typedef struct  
	{
		MSG_NUM_4BIT	nUserID;			// ��ɫid
		MSG_NUM_4BIT	nAccountID;			// �˺�id
		MSG_NUM_4BIT	nAccountType;		// �˺�����
		MSG_NUM_4BIT	nExitTime;			// �ϴ��˳�ʱ��(utcʱ��)

		MSG_NUM_4BIT	nSex;				// �Ա�
		MSG_NUM_4BIT	nLookface;			// ͷ��
		MSG_NUM_4BIT	nLev;				// �ȼ�
		MSG_NUM_8BIT	i64Exp;				// ����

		MSG_NUM_2BIT	nServerGroup;		// ���������
		MSG_NUM_2BIT	nServerLine;		// ��������·��

		MSG_STR_32BIT	szUserName;			// ��ɫ��
		MSG_STR_8BIT	szCode;				// ����id���������Ψһcode
	}MSG_Info;

	MSG_Info* m_pInfo;
};


#endif // end of _GAMEKERNER_MSG_GAME_USER_INFO_H_