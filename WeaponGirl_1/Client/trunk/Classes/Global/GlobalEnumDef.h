////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: GlobalEnumDef.h
// Author: ������(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_GLOBAL_ENUM_DEF_H_
#define _JYP_GLOBAL_ENUM_DEF_H_

#include "Common/CommonEnumdef.h"

// �ֶ�����
enum FIELD_TYPE
{
	FIELD_TYPE_int,		// ����
	FIELD_TYPE_str,		// �ַ���
};

// �߼����� i64
enum LOGIC_DATA
{
	LOGIC_DATA_LoginServerId					= 0,
	LOGIC_DATA_GameServerPort					= 1,

	LOGIC_DATA_NeedProcessNetBreak				= 2,		// ��Ҫ��������Ͽ�

	LOGIC_DATA_heartbeat_server_start			= 3,		// ������������
	LOGIC_DATA_heartbeat_client_start			= 4,		// �ͻ����������

	LOGIC_DATA_server_group						= 5,		// ��ǰ��������
	LOGIC_DATA_server_line						= 6,		// ��ǰ��������

	LOGIC_DATA_BreakReasonCode,								// �Ͽ�ԭ��
	LOGIC_DATA_ReconnectingFlag,							// �����б��
	LOGIC_DATA_ReconnectCount,								// ��������
	LOGIC_DATA_ReconnectStartTime,							// ������ʼutc����

	LOGIC_DATA_userinfo_user_id					= 101,		// ���ID
	LOGIC_DATA_userinfo_account_id				= 102,		// �˺�ID
	LOGIC_DATA_userinfo_account_type			= 103,		// �˺�����	0��ͨ, 1��ͨGM, 2�߼�GM
	LOGIC_DATA_userinfo_exit_time				= 104,		// �ϴ��˳�ʱ��(utcʱ��)
	LOGIC_DATA_userinfo_sex						= 106,		// �Ա�
	LOGIC_DATA_userinfo_lookface				= 107,		// LOOKFACE


	LOGIC_DATA_END,
};

// �߼����� �ַ���
enum LOGIC_STRING
{
	LOGIC_STRING_AccountName,
	LOGIC_STRING_AccountPwd,
	LOGIC_STRING_UserName,
	LOGIC_STRING_UserCode,

	LOGIC_STRING_GameServerIp,

	LOGIC_STRING_BreakReason,			// �Ͽ�ԭ��
};

enum USER_DATA
{
	USER_DATA_user_id,
	USER_DATA_account_id,
	USER_DATA_account_type,			// �˺�����	0��ͨ, 1��ͨGM, 2�߼�GM
	USER_DATA_exit_time,			// �ϴ��˳�ʱ��(utcʱ��)
	USER_DATA_stop_talk_end_time,	// ���Խ���ʱ��(utcʱ��)
	USER_DATA_sex,
	USER_DATA_lookface,
	USER_DATA_job,					// ְҵ
	USER_DATA_job_stage,			// תְ�׶�1-5
	USER_DATA_lev,
	USER_DATA_exp,
	USER_DATA_str_point,			// �������
	USER_DATA_dex_point,			// �������
	USER_DATA_int_point,			// �������
	USER_DATA_sta_point,			// �������
	USER_DATA_life_point,			// �������
	USER_DATA_left_point,			// ʣ�����
};

enum CONNECT_STATUS
{
	CONNECT_STATUS_none,		// ��ʼ״̬
	CONNECT_STATUS_reqLogin,	// ������ڷ�	�����η���·
	CONNECT_STATUS_reqPwd,		// �����η�		��������
	CONNECT_STATUS_choose,		// ��ɫѡ��
	CONNECT_STATUS_login,		// ��¼״̬		��������
	CONNECT_STATUS_run,			// ������
};

enum MESSAGE_BOX_MODE
{
	MESSAGE_BOX_MODE_OK			= 1,	// ��һ��OK��ť
	MESSAGE_BOX_MODE_CANCEL		= 2,	// ��һ��Cancel��ť
	MESSAGE_BOX_MODE_OK_CANCEL	= MESSAGE_BOX_MODE_OK | MESSAGE_BOX_MODE_CANCEL,	// OK��Cancel��ť
};

enum MESSAGE_BOX_CLICK
{
	MESSAGE_BOX_CLICK_OK		= 1,	// ѡ����OK
	MESSAGE_BOX_CLICK_CANCEL	= 2,	// ѡ����Cancel
};

// ��������
enum BORN_FROM
{
	BORN_FROM_NONE = 0,
	BORN_FROM_LEFT = 1,
	BORN_FROM_RIGHT = 2,
};

// ս��������
enum FIGHTER_ATTR
{
	FIGHTER_ATTR_USER_ID,
	FIGHTER_ATTR_EUDEMON_ID,
	FIGHTER_ATTR_MONSTER_TYPE,

	FIGHTER_ATTR_CAMP,
	FIGHTER_ATTR_POSITION,

	FIGHTER_ATTR_USERJOB,
	FIGHTER_ATTR_USERJOBSTAGE,
	FIGHTER_ATTR_EUDEMONTYPE,
	FIGHTER_ATTR_EUDEMONSORT,

	FIGHTER_ATTR_SPINETYPE,
	FIGHTER_ATTR_WEAPON_TYPE,
	FIGHTER_ATTR_CLOTH_TYPE,
	FIGHTER_ATTR_LOOKFACE,
	FIGHTER_ATTR_FAR_ATTACK_FLAG,

	FIGHTER_ATTR_BORN_FROM,

	FIGHTER_ATTR_HP,
	FIGHTER_ATTR_HP_MAX,
	FIGHTER_ATTR_MP,
	FIGHTER_ATTR_MP_MAX,

	FIGHTER_ATTR_NEXT_ACTION_ROUND,
	FIGHTER_ATTR_SPEED,
};

// ��Ʒ�б�����
enum ITEM_LIST_TYPE
{
	ITEM_LIST_TYPE_UNKNOWN	= 0,
	ITEM_LIST_TYPE_PACKAGE,							// ���б���
	ITEM_LIST_TYPE_PACKAGE_EQUIP,					// װ������
	ITEM_LIST_TYPE_PACKAGE_MEDICINE,				// ҩƷ����
	ITEM_LIST_TYPE_PACKAGE_PROP,					// ���߱���
	
	ITEM_LIST_TYPE_PACKAGE_SCROLL_WEAPON,											// ��������
	ITEM_LIST_TYPE_PACKAGE_SCROLL_ARMOR,											// �·�����
	ITEM_LIST_TYPE_PACKAGE_SCROLL_HELMET,											// ͷ������
	ITEM_LIST_TYPE_PACKAGE_SCROLL_NECKLACE,											// ��������
	ITEM_LIST_TYPE_PACKAGE_SCROLL_GLOVE,											// ���־���
	ITEM_LIST_TYPE_PACKAGE_SCROLL_BELT,												// ��������
	ITEM_LIST_TYPE_PACKAGE_SCROLL_SHOES,											// Ь�Ӿ���
	ITEM_LIST_TYPE_PACKAGE_SCROLL_RING,												// ��ָ����
	ITEM_LIST_TYPE_PACKAGE_SCROLL_BADGE = ITEM_LIST_TYPE_PACKAGE_SCROLL_RING + 1,	// ���¾���
	ITEM_LIST_TYPE_PACKAGE_SCROLL_DRESS_WEAPON,										// ����ʱװ����
	ITEM_LIST_TYPE_PACKAGE_SCROLL_DRESS_ARMOR,										// �·�ʱװ����
	ITEM_LIST_TYPE_PACKAGE_APPEND_MATERIAL,											// װ��׷�Ӳ���
	ITEM_LIST_TYPE_PACKAGE_EMBED_GEM,												// װ����Ƕ��ʯ

	ITEM_LIST_TYPE_BODY,				// ���߱���
	ITEM_LIST_TYPE_BODY_WEAPON,			// ����
	ITEM_LIST_TYPE_BODY_ARMOR,			// �·�
	ITEM_LIST_TYPE_BODY_HELMET,			// ͷ��
	ITEM_LIST_TYPE_BODY_NECKLACE,		// ����
	ITEM_LIST_TYPE_BODY_GLOVE,			// ����
	ITEM_LIST_TYPE_BODY_BELT,			// ����
	ITEM_LIST_TYPE_BODY_SHOES,			// Ь��
	ITEM_LIST_TYPE_BODY_RING_LEFT,		// ���ָ
	ITEM_LIST_TYPE_BODY_RING_RIGHT,		// �ҽ�ָ
	ITEM_LIST_TYPE_BODY_BADGE,			// ����
	ITEM_LIST_TYPE_BODY_DRESS_WEAPON,	// ����ʱװ
	ITEM_LIST_TYPE_BODY_DRESS_ARMOR,	// �·�ʱװ

	ITEM_LIST_TYPE_CLASSFIY_EQUIP,					// ����װ��
	ITEM_LIST_TYPE_CLASSFIY_EQUIP_BEAPPEND,			// ���п�׷��װ��
	ITEM_LIST_TYPE_CLASSFIY_EQUIP_BEADDLEV,			// ���п�ǿ����װ��
	ITEM_LIST_TYPE_CLASSFIY_EQUIP_BEWASH,			// ���п�ϴ����װ��
	ITEM_LIST_TYPE_CLASSFIY_EQUIP_BERESET_NATURE,	// ���п�������Ȼ���Ե�װ��
	ITEM_LIST_TYPE_WASH_EUDEMON,				// ϴ�������Ʒ
};

enum ITEM_LIST_MODE
{
	ITEM_LIST_MODE_LIST,		// �б�ģʽ
	ITEM_LIST_MODE_PACKAGE,		// ����ģʽ
	ITEM_LIST_MODE_TYPE,		// ����ģʽ
};

enum ITEM_CLICK_MODE
{
	ITEM_CLICK_MODE_NONE,		// ������
	ITEM_CLICK_MODE_TIPS,		// ���������ϸTIPS
	ITEM_CLICK_MODE_OPT_TIPS,	// ���������ϸTIPS ��������ť
	ITEM_CLICK_MODE_CHOOSE,		// ���ѡ��
};

enum SHOW_HPMP_TYPE
{
	SHOW_HPMP_TYPE_normal,		// ����
	SHOW_HPMP_TYPE_hp,			// ��Ѫ
	SHOW_HPMP_TYPE_mp,			// ����
	SHOW_HPMP_TYPE_crit,		// ����
	SHOW_HPMP_TYPE_recover_hp,	// ��Ѫ
	SHOW_HPMP_TYPE_recover_mp,	// ����
	SHOW_HPMP_TYPE_miss,		// ����
	SHOW_HPMP_TYPE_parry,		// ��
	SHOW_HPMP_TYPE_spend_hp,	// ��������
};

enum MAGIC_ANIMATE_POS_TYPE
{
	MAGIC_ANIMATE_POS_TYPE_beatk			= 0,	// 0 ʩ�����ܻ���������
	MAGIC_ANIMATE_POS_TYPE_target_mid_each	= 2,	// 2 ÿ��Ŀ���ܻ���������
	MAGIC_ANIMATE_POS_TYPE_owner_mid		= 3,	// 3 �ҷ�����
	MAGIC_ANIMATE_POS_TYPE_enemy_mid		= 4,	// 4 �з�����
	MAGIC_ANIMATE_POS_TYPE_screen_mid		= 5,	// 5 ��Ļ����
};

enum BATTLE_CTRL_TYPE
{
	BATTLE_CTRL_TYPE_atk,
	BATTLE_CTRL_TYPE_def,
	BATTLE_CTRL_TYPE_magic1,
	BATTLE_CTRL_TYPE_magic2,
	BATTLE_CTRL_TYPE_magic3,
	BATTLE_CTRL_TYPE_magic4,
	BATTLE_CTRL_TYPE_magic5,
	BATTLE_CTRL_TYPE_end,
};

// ������������
enum POKER_ATTR
{
	POKER_ATTR_id,
	POKER_ATTR_type,
	POKER_ATTR_lev,
	POKER_ATTR_star,
	POKER_ATTR_strengthen,
	POKER_ATTR_breakthrough,
	POKER_ATTR_randomAttrType,
	POKER_ATTR_randomAttrData,
	POKER_ATTR_pos1,
	POKER_ATTR_pos2,
	POKER_ATTR_pos3,
	POKER_ATTR_pos4,
	POKER_ATTR_weapon,
	POKER_ATTR_exScore,
	POKER_ATTR_totalScore,
};

// �̵���ʾ����
enum GREEN_TIPS_TYPE
{
	GREEN_TIPS_TYPE_MainViewHome = 1,
	GREEN_TIPS_TYPE_MainViewInstance,
	GREEN_TIPS_TYPE_MainViewLottery,
	GREEN_TIPS_TYPE_MainViewChallenge,
	GREEN_TIPS_TYPE_MainViewSmelt,
	GREEN_TIPS_TYPE_MainViewPoker,
	GREEN_TIPS_TYPE_MainViewActivity,

	GREEN_TIPS_TYPE_BottomButtonMail,
	GREEN_TIPS_TYPE_BottomButtonAchievement,
	GREEN_TIPS_TYPE_BottomButtonFriend,
	GREEN_TIPS_TYPE_BottomButtonShop,
	GREEN_TIPS_TYPE_BottomButtonNotify,
	GREEN_TIPS_TYPE_BottomButtonSetup,
};

// ��������ʽ
enum POKER_SORT_TYPE
{
	POKER_SORT_TYPE_none = 0,
	POKER_SORT_TYPE_color,
	POKER_SORT_TYPE_level,
	POKER_SORT_TYPE_upstar,
	POKER_SORT_TYPE_score,
};


#endif // end of _JYP_GLOBAL_ENUM_DEF_H_
