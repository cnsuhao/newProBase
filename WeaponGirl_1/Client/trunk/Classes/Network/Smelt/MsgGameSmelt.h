////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameSmelt.h
// Author: ������(Peng Wenqi)
// Created: 2015/11/18
////////////////////////////////////////////////////////////////////////
#ifndef _GAMESERVER_MSG_MsgGameSmelt_H_
#define _GAMESERVER_MSG_MsgGameSmelt_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_SMELT_ACTION
{
	MSG_SMELT_ACTION_query = 1,			// ��ѯ				C <-> S
	MSG_SMELT_ACTION_smelt_begin,		// ��ʼ����			C <-> S
	MSG_SMELT_ACTION_smelt_end,			// ��������			C <-> S
	MSG_SMELT_ACTION_uptemp,			// ����				C <-- S
	MSG_SMELT_ACTION_find_monster,		// �ҹ�				C --> S
	MSG_SMELT_ACTION_battle,			// ս��				C --> S
};

enum MSG_SMELT_RESULT
{
	MSG_SMELT_RESULT_success = 0,	
	MSG_SMELT_RESULT_failed,
};


class CMsgGameSmelt : public CNetMsg
{
public:
	CMsgGameSmelt();
	virtual ~CMsgGameSmelt();
	virtual void Process();

public:
	bool CreateQuery();
	bool CreateSmeltBegin(uint32_t unTemp, uint32_t unOre);
	bool CreateSmeltEnd();
	bool CreateFindMonster(uint32_t unTemp);
	bool CreateBattle(int nIndex);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sResult;
		
		union 
		{
			struct 
			{
				uint32_t	unResetTime;		// ����ʱ��

				uint32_t	unSmeltBeginTime;	// ������ʼʱ��
				uint32_t	unSmeltEndTime;		// ��������ʱ��
				uint32_t	unSmeltTemp;		// �����¶�
				uint32_t	unSmeltOre;			// ����ԭ��

				uint32_t	unSmeltTempMax;		// ����¶�

				uint32_t	unFailedCount;		// ʧ�ܴ���
				uint32_t	unFailedResetTime;	// ʧ������ʱ��

				uint32_t	unMonsterType[MAX_MEET_MONSTER_COUNT];
				uint32_t	unMonsterTime[MAX_MEET_MONSTER_COUNT];
			}Query;

			struct  
			{
				uint32_t	unSmeltBeginTime;	// ������ʼʱ��
				uint32_t	unSmeltEndTime;		// ��������ʱ��
				uint32_t	unTemp;				// �����¶�
				uint32_t	unOre;				// ����ԭ��
			}SmeltBegin;

			struct
			{
				uint32_t unOldTemp;	// ���¶�
				uint32_t unNewTemp;	// ���¶�
			}UpTemp;

			struct  
			{
				uint32_t unTemp;
			}FindMonster;

			struct
			{
				int nIndex;
				uint32_t unMonsterType;
				uint32_t unTime;
			}MeetMonster;

			struct
			{
				int nIndex;
			}Battle;

			struct
			{
				int nIndex;
			}RemoveMonster;
		} data;
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif	// end of _GAMESERVER_MSG_MsgGameSmelt_H_