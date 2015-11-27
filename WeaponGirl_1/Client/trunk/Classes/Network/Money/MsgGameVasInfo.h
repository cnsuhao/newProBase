#ifndef _GAMEKERNER_MSG_GAME_VAS_INFO_H_
#define _GAMEKERNER_MSG_GAME_VAS_INFO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../NetMsg.h"

class CMsgGameVasInfo : public CNetMsg
{
public:
	CMsgGameVasInfo();
	virtual ~CMsgGameVasInfo();

protected:
	virtual void Process();

private:
	typedef struct
	{
		MSG_NUM_8BIT	i64Vas;

		MSG_NUM_4BIT	nFirstMask;

		MSG_NUM_4BIT	nMonthCardID;
		MSG_NUM_2BIT	sMonthCardTodayCanGet;
		MSG_NUM_2BIT	sMonthCardLeftCount;

		MSG_NUM_4BIT	nSynMonthCardID;
		MSG_NUM_4BIT	nSynMonthCardTodayCanGet;
		MSG_NUM_4BIT	nSynMonthCardEndTime;
	}MSG_Info;

	MSG_Info* m_pInfo;
};

#endif	// end of _GAMEKERNER_MSG_GAME_VAS_INFO_H_