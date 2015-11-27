////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: MsgGameSmelt.h
// Author: 彭文奇(Peng Wenqi)
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
	MSG_SMELT_ACTION_query = 1,			// 查询				C <-> S
	MSG_SMELT_ACTION_smelt_begin,		// 开始熔炼			C <-> S
	MSG_SMELT_ACTION_smelt_end,			// 结束熔炼			C <-> S
	MSG_SMELT_ACTION_uptemp,			// 升温				C <-- S
	MSG_SMELT_ACTION_find_monster,		// 找怪				C --> S
	MSG_SMELT_ACTION_battle,			// 战斗				C --> S
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
				uint32_t	unResetTime;		// 重置时间

				uint32_t	unSmeltBeginTime;	// 熔炼开始时间
				uint32_t	unSmeltEndTime;		// 熔炼结束时间
				uint32_t	unSmeltTemp;		// 熔炼温度
				uint32_t	unSmeltOre;			// 熔炼原矿

				uint32_t	unSmeltTempMax;		// 最高温度

				uint32_t	unFailedCount;		// 失败次数
				uint32_t	unFailedResetTime;	// 失败重置时间

				uint32_t	unMonsterType[MAX_MEET_MONSTER_COUNT];
				uint32_t	unMonsterTime[MAX_MEET_MONSTER_COUNT];
			}Query;

			struct  
			{
				uint32_t	unSmeltBeginTime;	// 熔炼开始时间
				uint32_t	unSmeltEndTime;		// 熔炼结束时间
				uint32_t	unTemp;				// 熔炼温度
				uint32_t	unOre;				// 熔炼原矿
			}SmeltBegin;

			struct
			{
				uint32_t unOldTemp;	// 旧温度
				uint32_t unNewTemp;	// 新温度
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