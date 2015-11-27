////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommonConstdef.h
//			客户端服务端通用常量声明处, 该文件保存客户端与服务端一致
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/06/02
////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_CONST_DEF_H_
#define _COMMON_CONST_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned int OBJID;

const int MAX_NAME_LENGTH = 32;
const int MAX_TEXT_LENGTH = 256;

const OBJID USER_ID_FIRST		= 10000000;		// Player的第一个ID, 1000W起
const OBJID MAX_ID_DEFINE = (OBJID)-1;

const int	MAX_PACKETSIZE = 1024;							// 网络消息包尺寸
const int	MAX_MESSAGESIZE = MAX_PACKETSIZE + 40;			// 内部消息包尺寸


const OBJID BOSS_POKER_TYPE = 1;																// 主角卡(老板卡)类型
const int	MAX_BREAKTHROUGH = 35;																// 突破值上限
const int	MAX_POKER_STAR = 5;																	// 最高星级
const int	MAX_POKER_LEVEL[MAX_POKER_STAR + 1] = { 0, 25, 25, 25, 25, 99 };					// 等级上限
const int	UPSTAR_NEED_MONEY[MAX_POKER_STAR + 1] = { 0, 6000, 650000, 550000, 7200000, 0 };	// 升星需要货币
const int	UPSTAR_NEED_STATUE[MAX_POKER_STAR + 1] = { 0, 0, 1, 3, 5, 0 };						// 升星需要雕像
const int	BASE_POKER_MAX_COUNT = 50;															// 基础卡牌容量
const int	MAKE_WEAPON_NEED_STRENGTHEN = 20;													// 打造武器需要的强化等级
const int	POKER_COLOR_COUNT = 6;																// 卡牌颜色种类
const int	DISTRACT_ABILITY_PRICE[POKER_COLOR_COUNT + 1] = { 0, 8, 32, 64, 128, 256, 256 };	// 卡牌能力转移价格
const int	MAX_AWARD_POKER_COUNT = 10;															// 最大新增数量
const int	MAX_RESOLVE_POKER_COUNT = 25;														// 最大解雇数量
const int	PACKAGE_INIT_SIZE = 10;																// 背包初始大小
const int	PACKAGE_EXPANSION_SIZE  = 2;														// 背包解锁大小
const int	PACKAGE_EXPANSION_MAX_COUNT = 30;													// 背包解锁最大次数
const int	PACKAGE_EXPANSION_SPEND = 10;														// 背包解锁消耗金币
const int	FRIEND_MAX_NUMBER = 20;																// 好友最大数量
const int	FRIEND_GIFT_POINT = 10;																// 好友送礼点数
const int	LOTTERY_POKER_FRIEND_COST = 150;													// 友情一次需要点数
const int	BATTLE_MAX_FIGHTER_COUNT = 25;														// 战斗最大上阵数
const int	BATTLE_MAX_FIGHT_ROUND	 = 200;														// 战斗最大回合数
const int	LOTTERY_POKER_VAS_1 = 60;															// 元宝单抽价格
const int	LOTTERY_POKER_VAS_10 = 580;															// 元宝10连抽价格
const int	POKER_HOLY_COUNT = 9;																// 神殿出卡张数
const int	MAX_POKER_FIGHT_GROUP = 4;															// 最大阵容数量

const int	MIN_KING_DIFF = -20;	// 最小王者差

const int	PVP_CHALLENGE_REFRESH_TIME    = 2 * 60 * 60;										// pvp挑战榜自动刷新时间(s)
const int	PVP_CHALLENGE_FIGHT_MAX_COUNT = 8;													// pvp挑战榜最大挑战次数
const int	PVP_CHALLENGE_FIGHT_MAX_COUNT_MONTH = 10;											// pvp挑战榜月卡最大挑战次数
const int	PVP_CHALLENGE_ROBOT_RATE	  = 2000;												// pvp挑战机器人触发概率
const int	PVP_CHALLENGE_MAX_COUNT		  = 7;													// pvp挑战榜最大人数
const float PVP_CHALLENGE_SCORE_PARAM1	  = 0.8f;												// pvp挑战战力系数1
const float PVP_CHALLENGE_SCORE_PARAM2	  = 0.9f;												// pvp挑战战力系数2
const float PVP_CHALLENGE_SCORE_PARAM3    = 0.99f;												// pvp挑战战力系数3
const float PVP_CHALLENGE_SCORE_PARAM4    = 1.05f;												// pvp挑战战力系数4
const float PVP_CHALLENGE_SCORE_PARAM5    = 1.10f;												// pvp挑战战力系数5
const float PVP_CHALLENGE_SCORE_PARAM6    = 1.15f;												// pvp挑战战力系数6
const float PVP_CHALLENGE_SCORE_PARAM7    = 1.20f;												// pvp挑战战力系数7

const int   PVP_WORLD_RANK_MAX_RANK       = 2000;												// pvp世界榜最大保存名次
const int   PVP_WORLD_RANK_FIGHT_TIME     = 5 * 60;												// pvp世界榜挑战间隔时间(s)
const int   PVP_WORLD_RANK_FIGHT_COUNT    = 10;													// pvp世界榜最大挑战次数
const int	PVP_WORLD_RANK_MAX_COUNT      = 10;													// pvp世界榜最大人数
const int   PVP_WORLD_RANK_AWARD_TIME     = 220000;												// pvp世界榜发奖时间

const int	PRE_ORE_COUNT = 120;							// 每120秒产生一个原矿
const int	RESET_BLANK_SECOND = 2 * 24 * 60 * 60;			// 每两天可以免费重置一次
const int	MONSTER_RESET_TIME = 2 * 60 * 60;				// 怪物消耗重置时间
const int	BOSS_LEFT_TIME = 2 * 60 * 60;					// boss逃走时间
const int	MAX_MEET_MONSTER_COUNT = 10;					// 最大遇怪数量
const int	RESET_SMELT_MONSTER_FAILED_TIME = 2 * 60 * 60;	// 每2小时重置失败次数

const int   INSTANCE_SERACHING_INIT_COUNT	  = 3;												// 副本初始可探索次数
const int   INSTANCE_SEARCHING_COUNT_VAS	  = 30;												// 副本新增探索次数价格
const int   INSTANCE_COST_RESET_INTEVAL_TIME  = 3 * 60 * 60;									// 副本消耗重置间隔时间(s)
const int   INSTANCE_COST_MONEY_PARAM		  = 2;												// 副本消耗系数

const int	MAX_AWARD_HINT_COUNT			  = 10;			// 奖励提示信息最大数量

#endif // end of _COMMON_CONST_DEF_H_