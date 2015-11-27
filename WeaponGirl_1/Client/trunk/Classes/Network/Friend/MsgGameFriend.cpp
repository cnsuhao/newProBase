////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameFriend.cpp
// Author: �½���(Chen Jianjun)
// Created: 2015-11-2
////////////////////////////////////////////////////////////////////////
#include "./MsgGameFriend.h"
#include "Mgr/FriendMgr.h"
#include "MyCocosCommon/LayerHint.h"

CMsgGameFriend::CMsgGameFriend()
{
	Init();
	m_pInfo = (MSG_Info*)m_bufMsg;
	m_head.usType = _MSG_GAME_FRIEND;
}

CMsgGameFriend::~CMsgGameFriend()
{

}

//////////////////////////////////////////////////////////////////////
bool CMsgGameFriend::CreateMsg(MSG_NUM_2BIT sAction, MSG_NUM_2BIT sResult, MSG_NUM_4BIT idFriend/* = ID_NONE*/)
{
	this->Init();
	m_head.usType = _MSG_GAME_FRIEND;
	m_head.usSize = sizeof(MSG_Info)-sizeof(ST_FRIEDN_INFO);

	m_pInfo->sAction = sAction;
	m_pInfo->sResult = sResult;
	m_pInfo->idFriend = 0;
	m_pInfo->nParamNum = 0;
	return true;
}

void CMsgGameFriend::Process()
{
	switch (m_pInfo->sAction)
	{
	case EMFA_SYN_FRIEND_LIST:	// ͬ�������б�			C <-- S
	case EMFA_UPDATE_FRIEND:	// ���º�����Ϣ			C <-- S
		{
			for (int i = 0; i < m_pInfo->nParamNum; i++)
			{
				FriendMgr::getInstance()->updateFriendInfo(m_pInfo->stInfo[i]);
			}
		}
		break;
	case EMFA_SYN_REQUST_LIST:	// ͬ�������б�			C <-- S
	case EMFA_UPDATE_REQUEST:	// ����������Ϣ			C <-- S
		{
			for (int i = 0; i < m_pInfo->nParamNum; i++)
			{
				FriendMgr::getInstance()->updateRequestInfo(m_pInfo->stInfo[i]);
			}
		}
		break;
	case EMFA_SEARCH:	// ��������			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_REQUEST:	// �������			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_AGREE:	// ͬ�����			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_REFUSE:	// �ܾ�����			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_DELETE:	// ɾ������			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_SENDGIFT:	// �������			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	case EMFA_FIGHT_FRIENDLY:	// �д����			C <-> S
		{
			if (EMFR_SUC == m_pInfo->sResult)
			{

			}
			else
			{
				this->ProcessFaildHint();
			}
		}
		break;
	default:
		break;
	}
}

void CMsgGameFriend::ProcessFaildHint()
{
	switch (m_pInfo->sResult)
	{
	case EMFR_SUC:					// ͨ�óɹ�
		{
			AddHint("123");
		}
		break;
	case EMFR_FAILD:				// ͨ��ʧ��
		{
				AddHint("123");
		}
		break;
	case EMFR_IS_FRIEND:			// �Ѿ��Ǻ�����
		{
			AddHint("123");
		}
		break;
	case EMFR_SELF_FRIEND_FULL:		// �Լ���������
		{
			AddHint("123");
		}
		break;
	case EMFR_TARGET_FRIEND_FULL:	// �Է���������
		{
			AddHint("123");
		}
		break;
	case EMFR_IS_REQUEST:			// �Ѿ��������
		{
			AddHint("123");
		}
		break;
	case EMFR_ID_ERRO:				// ID������
		{
			AddHint("123");
		}
		break;
	default:
		break;
	}
}
