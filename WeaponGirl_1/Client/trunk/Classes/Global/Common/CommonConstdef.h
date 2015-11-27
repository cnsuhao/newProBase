////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommonConstdef.h
//			�ͻ��˷����ͨ�ó���������, ���ļ�����ͻ���������һ��
// Author: ������(Peng Wenqi)
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

const OBJID USER_ID_FIRST		= 10000000;		// Player�ĵ�һ��ID, 1000W��
const OBJID MAX_ID_DEFINE = (OBJID)-1;

const int	MAX_PACKETSIZE = 1024;							// ������Ϣ���ߴ�
const int	MAX_MESSAGESIZE = MAX_PACKETSIZE + 40;			// �ڲ���Ϣ���ߴ�


const OBJID BOSS_POKER_TYPE = 1;																// ���ǿ�(�ϰ忨)����
const int	MAX_BREAKTHROUGH = 35;																// ͻ��ֵ����
const int	MAX_POKER_STAR = 5;																	// ����Ǽ�
const int	MAX_POKER_LEVEL[MAX_POKER_STAR + 1] = { 0, 25, 25, 25, 25, 99 };					// �ȼ�����
const int	UPSTAR_NEED_MONEY[MAX_POKER_STAR + 1] = { 0, 6000, 650000, 550000, 7200000, 0 };	// ������Ҫ����
const int	UPSTAR_NEED_STATUE[MAX_POKER_STAR + 1] = { 0, 0, 1, 3, 5, 0 };						// ������Ҫ����
const int	BASE_POKER_MAX_COUNT = 50;															// ������������
const int	MAKE_WEAPON_NEED_STRENGTHEN = 20;													// ����������Ҫ��ǿ���ȼ�
const int	POKER_COLOR_COUNT = 6;																// ������ɫ����
const int	DISTRACT_ABILITY_PRICE[POKER_COLOR_COUNT + 1] = { 0, 8, 32, 64, 128, 256, 256 };	// ��������ת�Ƽ۸�
const int	MAX_AWARD_POKER_COUNT = 10;															// �����������
const int	MAX_RESOLVE_POKER_COUNT = 25;														// ���������
const int	PACKAGE_INIT_SIZE = 10;																// ������ʼ��С
const int	PACKAGE_EXPANSION_SIZE  = 2;														// ����������С
const int	PACKAGE_EXPANSION_MAX_COUNT = 30;													// ��������������
const int	PACKAGE_EXPANSION_SPEND = 10;														// �����������Ľ��
const int	FRIEND_MAX_NUMBER = 20;																// �����������
const int	FRIEND_GIFT_POINT = 10;																// �����������
const int	LOTTERY_POKER_FRIEND_COST = 150;													// ����һ����Ҫ����
const int	BATTLE_MAX_FIGHTER_COUNT = 25;														// ս�����������
const int	BATTLE_MAX_FIGHT_ROUND	 = 200;														// ս�����غ���
const int	LOTTERY_POKER_VAS_1 = 60;															// Ԫ������۸�
const int	LOTTERY_POKER_VAS_10 = 580;															// Ԫ��10����۸�
const int	POKER_HOLY_COUNT = 9;																// ����������
const int	MAX_POKER_FIGHT_GROUP = 4;															// �����������

const int	MIN_KING_DIFF = -20;	// ��С���߲�

const int	PVP_CHALLENGE_REFRESH_TIME    = 2 * 60 * 60;										// pvp��ս���Զ�ˢ��ʱ��(s)
const int	PVP_CHALLENGE_FIGHT_MAX_COUNT = 8;													// pvp��ս�������ս����
const int	PVP_CHALLENGE_FIGHT_MAX_COUNT_MONTH = 10;											// pvp��ս���¿������ս����
const int	PVP_CHALLENGE_ROBOT_RATE	  = 2000;												// pvp��ս�����˴�������
const int	PVP_CHALLENGE_MAX_COUNT		  = 7;													// pvp��ս���������
const float PVP_CHALLENGE_SCORE_PARAM1	  = 0.8f;												// pvp��սս��ϵ��1
const float PVP_CHALLENGE_SCORE_PARAM2	  = 0.9f;												// pvp��սս��ϵ��2
const float PVP_CHALLENGE_SCORE_PARAM3    = 0.99f;												// pvp��սս��ϵ��3
const float PVP_CHALLENGE_SCORE_PARAM4    = 1.05f;												// pvp��սս��ϵ��4
const float PVP_CHALLENGE_SCORE_PARAM5    = 1.10f;												// pvp��սս��ϵ��5
const float PVP_CHALLENGE_SCORE_PARAM6    = 1.15f;												// pvp��սս��ϵ��6
const float PVP_CHALLENGE_SCORE_PARAM7    = 1.20f;												// pvp��սս��ϵ��7

const int   PVP_WORLD_RANK_MAX_RANK       = 2000;												// pvp�������󱣴�����
const int   PVP_WORLD_RANK_FIGHT_TIME     = 5 * 60;												// pvp�������ս���ʱ��(s)
const int   PVP_WORLD_RANK_FIGHT_COUNT    = 10;													// pvp����������ս����
const int	PVP_WORLD_RANK_MAX_COUNT      = 10;													// pvp������������
const int   PVP_WORLD_RANK_AWARD_TIME     = 220000;												// pvp����񷢽�ʱ��

const int	PRE_ORE_COUNT = 120;							// ÿ120�����һ��ԭ��
const int	RESET_BLANK_SECOND = 2 * 24 * 60 * 60;			// ÿ��������������һ��
const int	MONSTER_RESET_TIME = 2 * 60 * 60;				// ������������ʱ��
const int	BOSS_LEFT_TIME = 2 * 60 * 60;					// boss����ʱ��
const int	MAX_MEET_MONSTER_COUNT = 10;					// �����������
const int	RESET_SMELT_MONSTER_FAILED_TIME = 2 * 60 * 60;	// ÿ2Сʱ����ʧ�ܴ���

const int   INSTANCE_SERACHING_INIT_COUNT	  = 3;												// ������ʼ��̽������
const int   INSTANCE_SEARCHING_COUNT_VAS	  = 30;												// ��������̽�������۸�
const int   INSTANCE_COST_RESET_INTEVAL_TIME  = 3 * 60 * 60;									// �����������ü��ʱ��(s)
const int   INSTANCE_COST_MONEY_PARAM		  = 2;												// ��������ϵ��

const int	MAX_AWARD_HINT_COUNT			  = 10;			// ������ʾ��Ϣ�������

#endif // end of _COMMON_CONST_DEF_H_