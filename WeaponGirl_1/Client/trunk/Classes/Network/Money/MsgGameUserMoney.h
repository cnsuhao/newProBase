#ifndef _GAMEKERNER_MSG_GAME_USER_MONEY_H_
#define _GAMEKERNER_MSG_GAME_USER_MONEY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

enum MSG_USER_MONEY_ACTION
{
	MSG_USER_MONEY_ACTION_UPDATE	= 1,	// 货币更新		C <-- S
	MSG_USER_MONEY_ACTION_QUERY_ALL = 2,	// 查询所有货币	C <-> S
};

struct MSG_USER_MONEY
{
	MSG_NUM_4BIT	nType;
	MSG_NUM_8BIT	i64Data;
	MSG_NUM_4BIT	unTimeStart;
	MSG_NUM_4BIT	unAddSpeed;
};

class CMsgGameUserMoney : public CNetMsg
{
public:
	CMsgGameUserMoney();
	virtual ~CMsgGameUserMoney();

protected:
	virtual void Process();

public:
	bool CreateUserMoneyBase(short sAction = MSG_USER_MONEY_ACTION_UPDATE);
	bool AppendMoneyInfo(int nType, int64_t i64Data);

private:
	typedef struct
	{
		MSG_NUM_2BIT	sAction;
		MSG_NUM_2BIT	sCount;

		MSG_USER_MONEY	stInfo[1];
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif	// end of _GAMEKERNER_MSG_GAME_USER_MONEY_H_