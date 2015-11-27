// proj.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include "../../trunk/Classes/ConstTable/ConfigPassword.h"
#include "ConstTableMgr.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	if (!ConstTableMgr::getInstance()->Init())
	{
		printf("��������ڴ���, ����!\n");
		system("pause");
		return 0;
	}
	
	bool bSuccess = true;

	// ���տ��Ƽ�鼼���Ƿ�����
	VEC_DB_KEY vecPoker;
	ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_poker_type, vecPoker);
	for (auto idPoker : vecPoker)
	{
		for (int i = POKER_TYPE_DATA_magic1; i <= POKER_TYPE_DATA_magic3; i++)
		{
			auto magicType = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, idPoker, i);
			if (magicType > 0 && !ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_magic_type, magicType))
			{
				printf("MagicType��©��! ��������[%I64d] ����[%I64d]�ڼ��ܱ����޷��ҵ�����\n", idPoker, magicType);
				bSuccess = false;
			}
		}
	}


	// �������ü��ܼ�鿨������
	VEC_DB_KEY vecMagic;
	ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_magic_type, vecMagic);
	for (auto idMagicType : vecMagic)
	{
		for (int i = MAGIC_TYPE_DATA_need_pokertype1; i <= MAGIC_TYPE_DATA_need_pokertype6; i++)
		{
			auto needPokerType = ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_magic_type, idMagicType, i);
			if (0 == needPokerType || 1 == needPokerType)	// ���������
			{
				continue;
			}
			needPokerType %= 10000;	// ǧλ���²��ǿ�������

			if (!ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_poker_type, needPokerType))
			{
				printf("PokerType��©��! ��������[%I64d] ��Ҫ����[%I64d] ���Ʊ���û�����ſ�\n", idMagicType, needPokerType);
				bSuccess = false;
				continue;
			} 

			if (ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, needPokerType, POKER_TYPE_DATA_magic1) != idMagicType &&
				ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, needPokerType, POKER_TYPE_DATA_magic2) != idMagicType &&
				ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_poker_type, needPokerType, POKER_TYPE_DATA_magic3) != idMagicType )
			{
				printf("PokerType��©��! ��������[%I64d] ��Ҫ����[%I64d] ���Ʊ�����������λδ�Ҹ�����\n", idMagicType, needPokerType);
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

