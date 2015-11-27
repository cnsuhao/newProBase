////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommonStruct.h
// Author: 彭文奇(Peng Wenqi)
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

// 兼容旧消息
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
	MSG_NUM_4BIT	nUserID;		// 角色id
	MSG_STR_32BIT	szName;			// 角色名
	MSG_NUM_4BIT	nLastLoginDate;	// 上次登陆日期	YYYYMMDD
	MSG_NUM_4BIT	nLev;			// 等级
	MSG_NUM_4BIT	nLookface;		// 头像
	MSG_NUM_4BIT	nJob;			// 职业
	MSG_NUM_4BIT	nJobStage;		// 职业阶段

	MSG_NUM_4BIT	nDressWeapon;	// 武器外套
	MSG_NUM_4BIT	nDressArmor;	// 衣服外套
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
	MSG_NUM_4BIT	type;	// 卡牌类型
	MSG_NUM_4BIT	count;	// 碎片数量, 0是没有碎片, 但是拥有图鉴
};

// 战斗组属性
struct	FIGHT_GROUP_ATTR
{
	int64_t totalScore;	// 总战力
	int32_t	atk;		// 先攻
	int32_t	def;		// 防御
	int32_t	dodge;		// 闪避
	int32_t	king;		// 王者
};

// 物品信息
struct ITEM_INFO
{
	MSG_NUM_8BIT	i64ID;
	MSG_NUM_4BIT	idItemType;
	MSG_NUM_4BIT	idUser;
	MSG_NUM_4BIT	nParam;
};

struct ST_SIGN_AWARD_INFO			// 签到奖励信息
{
	MSG_NUM_4BIT	nDayIndex;		// 天索引(0为今天)
	MSG_NUM_4BIT	nAwardType1;	// 第一次签到奖励类型
	MSG_NUM_4BIT	nAwardNum1;		// 第一次签到奖励数量
	MSG_NUM_4BIT	nAwardType2;	// 第二次签到奖励类型
	MSG_NUM_4BIT	nAwardNum2;		// 第二次签到奖励数量
	MSG_NUM_4BIT	nAwardType3;	// 第三次签到奖励类型
	MSG_NUM_4BIT	nAwardNum3;		// 第三次签到奖励数量
};

// 评论信息
struct COMMENT_INFO
{
	int64_t			idComment;		// id
	int64_t			i64UserID;		// 角色id
	int32_t			nGoodCount;		// 好评次数
	int32_t			nSelfGoodFlag;	// 自己给好评标记
	uint32_t		unDeleteTime;	// 移除时间
	MSG_STR_32BIT	szName;			// 名字
	MSG_STR_192BIT	szText;			// 正文
};

// 论坛信息
struct BBS_INFO
{
	int64_t			idBbs;			// id
	int64_t			i64UserID;		// 角色id
	int32_t			nRelayCount;	// 回帖数量
	uint32_t		unSendTime;		// 发帖时间
	uint32_t		unLookface;		// 头像
	MSG_STR_32BIT	szName;			// 名字
	MSG_STR_192BIT	szText;			// 正文
};

// 论坛回帖
struct BBS_REPLY_INFO
{
	int32_t			nIndex;		// 序号
	MSG_STR_160BIT	szText;		// 正文
};


struct ST_FRIEDN_INFO
{
	MSG_NUM_4BIT	idTarget;			// id
	MSG_NUM_4BIT	nLookFace;			// 头像
	MSG_NUM_2BIT	sGiftSendState;		// 送礼状态
	MSG_NUM_2BIT	sGiftRecvState;		// 收礼状态
	MSG_NUM_4BIT	nGiftSendTime;		// 送礼时间
	MSG_NUM_4BIT	nGiftRecvTime;		// 收礼时间
	MSG_NUM_4BIT	nLastLoginTime;		// 上次登录时间
	MSG_STR_32BIT	szFriendName;		// 好友名字
};

// 礼包箱
struct GIFT_INFO
{
	int64_t			idGift;			// id
	MSG_STR_96BIT	szTitle;		// 标题
	int32_t			nGiftType;		// 礼物类型
	int64_t			i64GiftCount;	// 礼物数量
	uint32_t		unDeleteTime;	// 删除时间
	int32_t			nGetFlag;		// 获取标志
};

// 活动信息
struct Activity_Info
{
	int nType;			// 活动类型
	int nStartSecond;	// 活动开始时间(utc)
	int nEndSecond;		// 活动结束时间(utc)
	int nParam1;
	int nParam2;
	int nParam3;
	int nParam4;
	int nParam5;
};

struct  BATTLE_FIGHTER_INFO			// 战斗者信息
{
	MSG_NUM_4BIT	id;				// id
	MSG_STR_32BIT	szName;			// 名字
	MSG_NUM_8BIT	i64Score;		// 战力
	MSG_NUM_4BIT	nAttrAtk;		// 先攻(四维属性)
	MSG_NUM_4BIT	nAttrDef;		// 防御(四维属性)
	MSG_NUM_4BIT	nAttrDodge;		// 闪避(四维属性)
	MSG_NUM_4BIT	nAttrKing;		// 王者(四维属性)
	MSG_NUM_4BIT	nWeapon;		// 主角武器类型
	MSG_NUM_4BIT	nFightArray[BATTLE_MAX_FIGHTER_COUNT];	// 阵容信息
};

struct  BATTLE_ROUND_INFO			// 战斗回合信息
{
	MSG_NUM_4BIT	idAttacker;		// 攻击者id
	MSG_NUM_4BIT	idMagicType;	// 技能类型（0为普攻）
	MSG_NUM_2BIT	nRound;			// 回合
	MSG_NUM_2BIT	nHitFlag;		// 命中标记
	MSG_NUM_8BIT	i64Damage;		// 伤害量
	MSG_NUM_8BIT	i64Recover;		// 恢复量
};

struct CHALLENGER_INFO				// 挑战者信息
{
	MSG_NUM_4BIT	id;				// id
	MSG_NUM_4BIT	nLookFace;		// 头像
	MSG_STR_32BIT	szName;			// 名字
	MSG_NUM_8BIT	i64Score;		// 战力
	MSG_NUM_4BIT	nData;			// 数据
};

struct ST_INSTANCE_LIST_INFO			// 副本列表信息
{
	MSG_NUM_4BIT	idInstance;			// 副本id
	MSG_NUM_2BIT	sSearchingFlag;		// 探索标记
	MSG_NUM_2BIT	sPassFlag;			// 通关标记
};

// 熔炼怪物信息
struct SMELT_MONSTER_INFO
{
	int64_t		id;
	uint32_t	idMonsterType;
	uint32_t	unStartTime;
	uint32_t	unResetTime;
	uint32_t	unFailedCount;
	uint32_t	unBasePrice;
};

// 奖励提示信息
struct ST_AWARD_INFO
{
	MSG_NUM_4BIT	nAwardType;				// 奖励类型
	MSG_NUM_4BIT	nAwardNum;				// 奖励数量
};
#endif // end of _COMMON_STRUCT_DEF_H_