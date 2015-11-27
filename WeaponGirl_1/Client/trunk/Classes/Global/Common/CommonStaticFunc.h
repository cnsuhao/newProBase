////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommonStaticFunc.hpp
// Author: ������(Peng Wenqi)
// Created: 2015/10/23
////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_CommonStaticFunc_H_
#define _COMMON_CommonStaticFunc_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommonConstdef.h"
#include "CommonEnumdef.h"
#include "CommonStruct.h"
#include <algorithm>

////////////////////////////////////////////////////////////////////////
// Description: ��û�׼ս��
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
static int64_t GetStdScore(int lev, int star)
{
	if (star <= 0 || star > 5 || lev <= 0)
	{
		return 0;
	}

	// ���ȼ��ָ�Ϊ4���ּ���
	const int partCount = 4;
	int levPart[partCount] = { 0 };
	if (lev > 80)
	{
		levPart[0] = 20;
		levPart[1] = 15;
		levPart[2] = 45;
		levPart[3] = lev - 80;
	}
	else if (lev > 35)
	{
		levPart[0] = 20;
		levPart[1] = 15;
		levPart[2] = lev - 35;
		levPart[3] = 0;
	}
	else if (lev > 20)
	{
		levPart[0] = 20;
		levPart[1] = lev - 20;
		levPart[2] = 0;
		levPart[3] = 0;
	}
	else
	{
		levPart[0] = lev;
		levPart[1] = 0;
		levPart[2] = 0;
		levPart[3] = 0;
	}

	const int* scoreBase = nullptr;
	switch (star)
	{
	case 1:
		{
			const int SCORE_BASE[partCount] = { 15, 8, 5, 4 };
			scoreBase = SCORE_BASE;
		}
		break;
	case 2:
		{
			const int SCORE_BASE[partCount] = { 80, 45, 32, 24 };
			scoreBase = SCORE_BASE;
		}
		break;
	case 3:
		{
			const int SCORE_BASE[partCount] = { 280, 150, 50, 40};
			scoreBase = SCORE_BASE;
		}
		break;
	case 4:
		{
			const int SCORE_BASE[partCount] = { 700, 270, 150, 120 };
			scoreBase = SCORE_BASE;
		}
		break;
	case 5:
		{
			const int SCORE_BASE[partCount] = { 2222, 1555, 1111, 929 };
			scoreBase = SCORE_BASE;
		}
		break;
	default:
		return 0;
		break;
	}

	int64_t result = 0;
	for (int i = 0; i < partCount; i++)
	{
		result += scoreBase[i] * levPart[i];
	}

	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: �������ս����
// Arguments:	ս���� = ����ս�� + ��׼ս�� * �ɳ��� * (1.0 + ǿ��Ч�� + ͻ��Ч��)	
// Author: ������(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
static int64_t GetFinalScore(int64_t stdScore, int64_t baseScore, int64_t grow, int64_t strengthen, int64_t breakthough)
{
	if (stdScore < 0 || baseScore < 0 || grow < 500 || strengthen < 0 || breakthough < 0)
	{
		return 0;
	}

	int64_t result = stdScore * grow / 10000i64;
	result = result * (10000i64 + strengthen + breakthough * 100) / 10000i64;
	result += baseScore;
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: ������ͬ����Ч��
// Arguments:	2��������ͬ��������ս��
// Author: ������(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
static int64_t GetSamePokerEffect(int nSameCount)
{
	if (nSameCount > 6)
	{
		return 70;
	}
	else if (nSameCount > 5)
	{
		return 80;
	}
	else if (nSameCount > 4)
	{
		return 90;
	}
	else
	{
		return 100;
	}
}

////////////////////////////////////////////////////////////////////////
// Description: ��ȡ���Ͷ���
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: E_USER_THING_TYPE
////////////////////////////////////////////////////////////////////////
static E_USER_THING_TYPE getUserThingType(OBJID idThing)
{
	if (idThing >= 100 && idThing < 1000)
	{
		return E_USER_THING_TYPE_MONEY;		// ����
	}
	else if (idThing >= 1000 && idThing < 10000)
	{
		return E_USER_THING_TYPE_POKER;		// ����
	}
	else if (idThing >= 10000 && idThing < 100000)
	{
		return E_USER_THING_TYPE_ITEM;		// ��Ʒ
	}
	return E_USER_THING_TYPE_NONE;
}

////////////////////////////////////////////////////////////////////////
// Description: ��ý�ҳ鿨����
// Arguments:
// Author: ������(Peng Wenqi)
// Return Value: int64_t
////////////////////////////////////////////////////////////////////////
static int64_t calcLotteryMoney(int nCount)
{
	int64_t result = 1000;	// �׼�1000
	nCount = (std::min)(nCount, 30);
	nCount = (std::max)(nCount, 0);

	for (int i = 0; i < nCount; i++)
	{
		result *= 2;
	}
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: �ж��Ƿ�Ϊ���Ƽ���
// Arguments:
// Author: �½���(Chen Jianjun)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
static bool isCopyMagicType(OBJID idMagicType)
{
	if (idMagicType >= 9000 && idMagicType < 10000)
	{
		return true;
	}
	return false;
}
#endif // end of _COMMON_CommonStaticFunc_H_