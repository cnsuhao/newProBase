// proj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "../../trunk/Classes/ConstTable/ConfigPassword.h"
#include "ConstTableMgr.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	if (!ConstTableMgr::getInstance()->Init())
	{
		printf("常量表存在错误, 请检查!\n");
		system("pause");
		return 0;
	}
	
	bool bSuccess = true;

	// 按照卡牌检查技能是否配置
	VEC_DB_KEY vecPoker;
	ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_poker_type, vecPoker);
	for (auto idPoker : vecPoker)
	{
		for (int i = POKER_TYPE_DATA_magic1; i <= POKER_TYPE_DATA_magic3; i++)
		{
			auto magicType = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, idPoker, i);
			if (magicType > 0 && !ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_magic_type, magicType))
			{
				printf("MagicType表漏配! 卡牌类型[%I64d] 技能[%I64d]在技能表中无法找到配置\n", idPoker, magicType);
				bSuccess = false;
			}
		}
	}


	// 按照配置技能检查卡牌配置
	VEC_DB_KEY vecMagic;
	ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_magic_type, vecMagic);
	for (auto idMagicType : vecMagic)
	{
		for (int i = MAGIC_TYPE_DATA_need_pokertype1; i <= MAGIC_TYPE_DATA_need_pokertype6; i++)
		{
			auto needPokerType = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_magic_type, idMagicType, i);
			if (0 == needPokerType || 1 == needPokerType)	// 主卡不检查
			{
				continue;
			}
			needPokerType %= 10000;	// 千位以下才是卡牌类型

			if (!ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_poker_type, needPokerType))
			{
				printf("PokerType表漏配! 技能类型[%I64d] 需要卡牌[%I64d] 卡牌表中没有这张卡\n", idMagicType, needPokerType);
				bSuccess = false;
				continue;
			} 

			if (ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, needPokerType, POKER_TYPE_DATA_magic1) != idMagicType &&
				ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, needPokerType, POKER_TYPE_DATA_magic2) != idMagicType &&
				ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, needPokerType, POKER_TYPE_DATA_magic3) != idMagicType )
			{
				printf("PokerType表漏配! 技能类型[%I64d] 需要卡牌[%I64d] 卡牌表中三个技能位未找个配置\n", idMagicType, needPokerType);
				bSuccess = false;
				continue;
			}
		}
	}



	if (!bSuccess)
	{
		system("pause");
	}

	
	
	return 0;
}

