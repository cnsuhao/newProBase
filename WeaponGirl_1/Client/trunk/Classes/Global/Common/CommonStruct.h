////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommonStruct.h
// Author: ������(Peng Wenqi)
// Created: 2015/06/17
////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_STRUCT_DEF_H_
#define _COMMON_STRUCT_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack (4)

#include <stdint.h>
#include "CommonEnumdef.h"
#include "CommonConstdef.h"

// ���ݾ���Ϣ
typedef char	MSG_NUM_1BIT;
typedef short	MSG_NUM_2BIT;
typedef int		MSG_NUM_4BIT;
typedef int64_t MSG_NUM_8BIT;

typedef char	MSG_STR_8BIT[8];
typedef char	MSG_STR_16BIT[16];
typedef char	MSG_STR_32BIT[32];
typedef char	MSG_STR_64BIT[64];
typedef char	MSG_STR_96BIT[96];
typedef char	MSG_STR_128BIT[128];
typedef char	MSG_STR_160BIT[160];
typedef char	MSG_STR_192BIT[192];
typedef char	MSG_STR_256BIT[256];

struct USER_LOGIN_SNAP
{
	MSG_NUM_4BIT	nUserID;		// ��ɫid
	MSG_STR_32BIT	szName;			// ��ɫ��
	MSG_NUM_4BIT	nLastLoginDate;	// �ϴε�½����	YYYYMMDD
	MSG_NUM_4BIT	nLev;			// �ȼ�
	MSG_NUM_4BIT	nLookface;		// ͷ��
	MSG_NUM_4BIT	nJob;			// ְҵ
	MSG_NUM_4BIT	nJobStage;		// ְҵ�׶�

	MSG_NUM_4BIT	nDressWeapon;	// ��������
	MSG_NUM_4BIT	nDressArmor;	// �·�����
};

struct MSG_POKER_INFO
{
	MSG_NUM_8BIT	idPoker;

	MSG_NUM_2BIT	type;
	MSG_NUM_2BIT	lev;
	MSG_NUM_2BIT	star;
	MSG_NUM_2BIT	strengthen;
	MSG_NUM_2BIT	breakthrough;
	MSG_NUM_2BIT	randomAttr;

	MSG_NUM_1BIT	pos1;
	MSG_NUM_1BIT	pos2;
	MSG_NUM_1BIT	pos3;
	MSG_NUM_1BIT	pos4;

	MSG_NUM_4BIT	weapon;
	MSG_NUM_4BIT	exScore;
	MSG_NUM_4BIT	totalScore;
};

struct MSG_POKER_BOOK_INFO
{
	MSG_NUM_4BIT	type;	// ��������
	MSG_NUM_4BIT	count;	// ��Ƭ����, 0��û����Ƭ, ����ӵ��ͼ��
};

// ս��������
struct	FIGHT_GROUP_ATTR
{
	int64_t totalScore;	// ��ս��
	int32_t	atk;		// �ȹ�
	int32_t	def;		// ����
	int32_t	dodge;		// ����
	int32_t	king;		// ����
};

// ��Ʒ��Ϣ
struct ITEM_INFO
{
	MSG_NUM_8BIT	i64ID;
	MSG_NUM_4BIT	idItemType;
	MSG_NUM_4BIT	idUser;
	MSG_NUM_4BIT	nParam;
};

struct ST_SIGN_AWARD_INFO			// ǩ��������Ϣ
{
	MSG_NUM_4BIT	nDayIndex;		// ������(0Ϊ����)
	MSG_NUM_4BIT	nAwardType1;	// ��һ��ǩ����������
	MSG_NUM_4BIT	nAwardNum1;		// ��һ��ǩ����������
	MSG_NUM_4BIT	nAwardType2;	// �ڶ���ǩ����������
	MSG_NUM_4BIT	nAwardNum2;		// �ڶ���ǩ����������
	MSG_NUM_4BIT	nAwardType3;	// ������ǩ����������
	MSG_NUM_4BIT	nAwardNum3;		// ������ǩ����������
};

// ������Ϣ
struct COMMENT_INFO
{
	int64_t			idComment;		// id
	int64_t			i64UserID;		// ��ɫid
	int32_t			nGoodCount;		// ��������
	int32_t			nSelfGoodFlag;	// �Լ����������
	uint32_t		unDeleteTime;	// �Ƴ�ʱ��
	MSG_STR_32BIT	szName;			// ����
	MSG_STR_192BIT	szText;			// ����
};

// ��̳��Ϣ
struct BBS_INFO
{
	int64_t			idBbs;			// id
	int64_t			i64UserID;		// ��ɫid
	int32_t			nRelayCount;	// ��������
	uint32_t		unSendTime;		// ����ʱ��
	uint32_t		unLookface;		// ͷ��
	MSG_STR_32BIT	szName;			// ����
	MSG_STR_192BIT	szText;			// ����
};

// ��̳����
struct BBS_REPLY_INFO
{
	int32_t			nIndex;		// ���
	MSG_STR_160BIT	szText;		// ����
};


struct ST_FRIEDN_INFO
{
	MSG_NUM_4BIT	idTarget;			// id
	MSG_NUM_4BIT	nLookFace;			// ͷ��
	MSG_NUM_2BIT	sGiftSendState;		// ����״̬
	MSG_NUM_2BIT	sGiftRecvState;		// ����״̬
	MSG_NUM_4BIT	nGiftSendTime;		// ����ʱ��
	MSG_NUM_4BIT	nGiftRecvTime;		// ����ʱ��
	MSG_NUM_4BIT	nLastLoginTime;		// �ϴε�¼ʱ��
	MSG_STR_32BIT	szFriendName;		// ��������
};

// �����
struct GIFT_INFO
{
	int64_t			idGift;			// id
	MSG_STR_96BIT	szTitle;		// ����
	int32_t			nGiftType;		// ��������
	int64_t			i64GiftCount;	// ��������
	uint32_t		unDeleteTime;	// ɾ��ʱ��
	int32_t			nGetFlag;		// ��ȡ��־
};

// ���Ϣ
struct Activity_Info
{
	int nType;			// �����
	int nStartSecond;	// ���ʼʱ��(utc)
	int nEndSecond;		// �����ʱ��(utc)
	int nParam1;
	int nParam2;
	int nParam3;
	int nParam4;
	int nParam5;
};

struct  BATTLE_FIGHTER_INFO			// ս������Ϣ
{
	MSG_NUM_4BIT	id;				// id
	MSG_STR_32BIT	szName;			// ����
	MSG_NUM_8BIT	i64Score;		// ս��
	MSG_NUM_4BIT	nAttrAtk;		// �ȹ�(��ά����)
	MSG_NUM_4BIT	nAttrDef;		// ����(��ά����)
	MSG_NUM_4BIT	nAttrDodge;		// ����(��ά����)
	MSG_NUM_4BIT	nAttrKing;		// ����(��ά����)
	MSG_NUM_4BIT	nWeapon;		// ������������
	MSG_NUM_4BIT	nFightArray[BATTLE_MAX_FIGHTER_COUNT];	// ������Ϣ
};

struct  BATTLE_ROUND_INFO			// ս���غ���Ϣ
{
	MSG_NUM_4BIT	idAttacker;		// ������id
	MSG_NUM_4BIT	idMagicType;	// �������ͣ�0Ϊ�չ���
	MSG_NUM_2BIT	nRound;			// �غ�
	MSG_NUM_2BIT	nHitFlag;		// ���б��
	MSG_NUM_8BIT	i64Damage;		// �˺���
	MSG_NUM_8BIT	i64Recover;		// �ָ���
};

struct CHALLENGER_INFO				// ��ս����Ϣ
{
	MSG_NUM_4BIT	id;				// id
	MSG_NUM_4BIT	nLookFace;		// ͷ��
	MSG_STR_32BIT	szName;			// ����
	MSG_NUM_8BIT	i64Score;		// ս��
	MSG_NUM_4BIT	nData;			// ����
};

struct ST_INSTANCE_LIST_INFO			// �����б���Ϣ
{
	MSG_NUM_4BIT	idInstance;			// ����id
	MSG_NUM_2BIT	sSearchingFlag;		// ̽�����
	MSG_NUM_2BIT	sPassFlag;			// ͨ�ر��
};

// ����������Ϣ
struct SMELT_MONSTER_INFO
{
	int64_t		id;
	uint32_t	idMonsterType;
	uint32_t	unStartTime;
	uint32_t	unResetTime;
	uint32_t	unFailedCount;
	uint32_t	unBasePrice;
};

// ������ʾ��Ϣ
struct ST_AWARD_INFO
{
	MSG_NUM_4BIT	nAwardType;				// ��������
	MSG_NUM_4BIT	nAwardNum;				// ��������
};
#endif // end of _COMMON_STRUCT_DEF_H_