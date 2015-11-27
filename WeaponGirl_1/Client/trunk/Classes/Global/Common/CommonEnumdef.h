////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommonEnumdef.h
//			�ͻ��˷����ͨ��ö��������, ���ļ�����ͻ���������һ��
// Author: ������(Peng Wenqi)
// Created: 2015/05/21
////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_ENUM_DEF_H_
#define _COMMON_ENUM_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ��Ϣtype�Ŷ��崦, ����Э���ʱǿ�ƽ�Э�����ʽ����
enum _MSG_TYPE_DEFINE_
{
	_MSG_NONE							= 0,

	_MSG_RL_SERVER_BEGIN				= 100,	// ��ڷ���Ϣ��ʼ
	_MSG_RL_SERVER_REQ_LOGIN			= 101,	// �ͻ��������½
	_MSG_RL_SERVER_QUERY_ONLINE			= 102,	// ��ϵ����ѯ����
	_MSG_RL_SERVER_END					= 200,	// ��ڷ���Ϣ����

	// �ͻ��� ��½�߳� ��Ϣ����
	_MSG_LOGIN_BEGIN					= 1000,
	_MSG_LOGIN_CONNECT					= 1001,	// ����			C --> S
	_MSG_LOGIN_CONNECT_ACTION			= 1002,	// ���Ӳ���		C <-> S
	_MSG_LOGIN_USER_LIST				= 1003,	// ����б�		C <-- S
	_MSG_LOGIN_CREATE_NEW_USER			= 1004,	// �����½�ɫ	C <-> S
	_MSG_LOGIN_KICK_REASON				= 1005,	// �߳�ԭ��		C <-- S
	_MSG_LOGIN_END						= 2000,

	_MSG_GAME_BEGIN						= 5000,
	_MSG_GAME_LOGIN_QUERY,				// ��½��ѯ				C <-> S
	_MSG_GAME_KICK_REASON,				// �߳�ԭ��				C <-- S
	_MSG_GAME_SMALLACTION,				// SmallAction��Ϣ		C <-> S
	_MSG_GAME_RELAY_DATABASE,			// ������ת���ݿ�		S <-> R
	_MSG_GAME_CROSS_RELAY_DATABASE,		// �����ת���ݿ�		S <-> C
	_MSG_GAME_DEBUG,					// ����ָ��				C <-> S
	_MSG_GAME_GIFT,						// ���					C <-> S
	_MSG_GAME_SMELT,					// ұ��					C <-> S
	_MSG_GAME_SMELT_MONSTER,			// ұ��������Ϣ			C <-> S

	_MSG_GAME_TMP_DATA = 5010,			// UserTmpData			C <-> S
	_MSG_GAME_CROSS_INFO,				// ���������Ϣ			C <-> S
	_MSG_GAME_TASK,						// ����					C <-> S
	_MSG_GAME_ACTIVITIES,				// �					C <-> S
	_MSG_GAME_SIGN,						// ǩ��					C <-> S
	_MSG_GAME_NEWCARD,					// ���ֿ�				C <-> S
	_MSG_GAME_NEWCARD_PRIZE,			// ���ֿ�����			C <-- S
	_MSG_GAME_ACTIVE_AWARD,				// �����				C <-> S

	_MSG_COMMENT_OPT = 5050,			// ���۲���				C <-> S
	_MSG_COMMENT_LIST,					// �����б�				C <-> S

	_MSG_GAME_USER_INFO = 5100,			// UserInfo				C <-- S
	_MSG_GAME_USER_ATTR,				// UserAttr				C <-- S
	_MSG_GAME_USER_MONEY,				// ����ͬ��				C <-- S
	_MSG_GAME_USER_MONEY_HINT,			// ������ʾ				C <-- S
	_MSG_GAME_USER_MAC,					// ���mac��ַ			C --> S
	_MSG_GAME_MASK,						// ����ͬ��				C <-- S
	_MSG_GAME_VAS_INFO,					// Ԫ������				C <-- S
	_MSG_GAME_ONLINE_INFO,				// ���������Ϣ			S <-> R
	_MSG_GAME_ITEM,						// ��Ʒ��Ϣ				C <-> S
	_MSG_GAME_FRIEND,					// ������Ϣ				C <-> S
	_MSG_GAME_SHOP,						// �̳�					C <-> S
	_MSG_GAME_BATTLE_INFO,				// ս����Ϣ				C <-- S
	_MSG_GAME_BATTLE_RESULT,			// ս�����				C <-- S
	_MSG_GAME_CHALLENGE,				// ��սϵͳ				C <-> S
	_MSG_GAME_INSTANCE_LIST,			// �����б�				C <-- S
	_MSG_GAME_INSTANCE_INFO,			// ������Ϣ				C <-> S
	_MSG_GAME_AWARD_HINT,				// ���ֽ�����ʾ��Ϣ		C <-> S
	
	_MSG_GAME_POKER_LIST = 5200,		// �����б���Ϣ			C <-- S
	_MSG_GAME_POKER_OPT,				// ���Ʋ�����Ϣ			C <-> S
	_MSG_GAME_POKER_BOOK_LIST,			// ����ͼ���б���Ϣ		C <-- S
	_MSG_GAME_POKER_HOLY,				// ���������Ϣ			C <-> S
	_MSG_GAME_POKER_FIGHT_GROUP,		// ����������Ϣ			C <-> S

	_MSG_GAME_BBS		 = 5300,		// ��̳��Ϣ				C <-> S
	_MSG_GAME_BBS_REPLY,				// ��̳����				C <-> S

	_MSG_GAME_SYN_SERVER = 5400,		// ���ɷ���������Ϣ		S <-> R
	_MSG_GAME_SYN_CLIENT,				// ���ɿͻ�����Ϣ		C <-> S
	_MSG_GAME_SYN_LIST,					// �����б�				C <-- S
	_MSG_GAME_SYN_MEMBER_LIST,			// ���ɳ�Ա�б�			C <-- S
	_MSG_GAME_SYN_INFO,					// ��������				C <-- S
	_MSG_GAME_SELF_SYN_INFO,			// �Լ���������			C <-- S
	_MSG_GAME_SYN_LOG,					// ������־				C <-> S
	_MSG_GAME_SYN_MEMBER_APPLY_LIST,	// ���ɳ�Ա�����б�		C <-- S
	
	_MSG_GAME_END						= 7900,


	// php������ ��Ϣ����
	_MSG_PHP_BEGIN						= 7900,
	_MSG_PHP_PAY						= 8000,	// ��ֵ��Ϣ
	_MSG_PHP_KICK						= 8001,	// php����
	_MSG_PHP_END						= 9000,

	// ��ϵ��ȫ����Ϣ��ʼ
	_MSG_RELATION_BEGIN						= 10000,

	// ��ϵ��ֱ��ת��ȫ����Ϣ
	_MSG_RELATION_DIRCET_ALL_BEGIN			= 10000,
	_MSG_RELATION_DIRCET_ALL_END			= 12000,

	// ��ϵ��ֱ��ת����������Ϣ
	_MSG_RELATION_DIRCET_OTHER_BEGIN		= 12000,
	_MSG_RELATION_DIRCET_OTHER_END			= 15000,

	// ��Ҫ��ϵ��������Ϣ
	_MSG_RELATION_PROCESS_BEGIN				= 15000,
	_MSG_RELATION_PROCESS_LOGIN				= 15001,	// ��Ϸ����½����ϵ��
	_MSG_RELATION_PROCESS_ACTION			= 15002,	// ��Ϸ�����ϵ�� ͨ�ò���action
	_MSG_RELATION_PROCESS_NEWCARD			= 15003,	// ���ֿ���Ϣ
	_MSG_RELATION_PROCESS_ONLINE_INFO		= 15004,	// ���½�ɫ������Ϣ
	_MSG_RELATION_PROCESS_SYN_SERVER		= 15005,	// ���ɴ�����Ϣ
	_MSG_RELATION_PROCESS_REALY_DATABASE	= 15009,	// ��ת���ݿ�
	_MSG_RELATION_PROCESS_END				= 20000,
	
	// ��ϵ��ȫ����Ϣ����
	_MSG_RELATION_END						= 20000,

	// ���������������Ϣ
	_MSG_CROSS_BEGIN						= 20000,
	_MSG_CROSS_LOGIN						= 20001,	// ��ϵ����¼�����������Ϣ
	_MSG_CROSS_ACTION						= 20002,	// action		
	_MSG_CROSS_REALY_DATABASE				= 20003,	// �����ת���ݿ�
	_MSG_CROSS_END							= 30000,
};

// �߳�ԭ��
enum KICK_REASON
{
	KICK_REASON_DEFAULT					= 0,	// �߳�Ĭ��ֵ, һ�㲻Ҫ�����ֵ
	KICK_REASON_PASSWORD_ERROR			= 1,	// �������
	KICK_REASON_BE_KICK_ANOTHER			= 2,	// ��������
	KICK_REASON_RELATION_SERVER			= 3,	// ��ϵ������ָʾ�㱻����
	KICK_REASON_FULL					= 4,	// ��̫��
	KICK_REASON_SYSTEM					= 5,	// ����������������� �� GM����	
	KICK_REASON_NOT_ALLOW				= 6,	// ������δ������½����
	KICK_REASON_GM_MAC_ERROR			= 7,	// GM����Mac��ַ��֤����		
	KICK_REASON_CHECK_SPEED_TOO_FAST	= 8,	// ����ٶȹ���					**
	KICK_REASON_GMCMD					= 9,	// GM�������Լ�	
	KICK_REASON_LOGIN_TIMEOUT			= 10,	// ��½���̳�ʱ
	KICK_REASON_ACCOUNT_STOP_BYTIME		= 11,	// �˺���ʱ��ͣ
	KICK_REASON_ACCOUNT_STOP_FOREVER	= 12,	// �˺����÷�ͣ

};


// ���ñ������ֶ�, �����������õ����ݼ�����������, �ǵ�д�������ע�ͺ����ݿ�comment�ֶ�
enum CONFIG_TYPE
{
	CONFIGTYPE_NONE																= 0,


	CONFIGTYPE_USER_TALK_TIME_LIMIT_PRIVATE										= 1,				// ������ʱ, ˽������
	CONFIGTYPE_USER_TALK_TIME_LIMIT_SYNDICATE									= 2,				// ������ʱ, ��������
	CONFIGTYPE_USER_TALK_TIME_LIMIT_WORLD										= 3,				// ������ʱ, ��������
	CONFIGTYPE_USER_TALK_LEV_LIMIT_WORLD										= 4,				// ����ȼ�����, ��������

	CONFIGTYPE_TALK_RECORD_LIMIT_PRIVATE										= 6,				// ��������, ˽�ļ�¼����
	CONFIGTYPE_TALK_RECORD_LIMIT_SYNDICATE										= 7,				// ��������, ���������¼����
	CONFIGTYPE_TALK_RECORD_LIMIT_WORLD											= 8,				// ��������, ���������¼����

	CONFIGTYPE_SYNDICATE_CREATE_LIMIT_LEVEL										= 10,				// �������� ��Ҫ��ҵȼ�
	CONFIGTYPE_SYNDICATE_CREATE_LIMIT_VAS										= 11,				// �������� ��ҪԪ��
	CONFIGTYPE_SYNDICATE_ACTIVITY_LIMIT_SYNDICATE								= 12,				// ���ɻ�Ծ ����ÿ�ջ�Ծ����
	CONFIGTYPE_SYNDICATE_ACTIVITY_LIMIT_MEMBER									= 13,				// ���ɻ�Ծ ��Աÿ�ջ�Ծ����

	CONFIGTYPE_SYSTEM_POWER_RECOVER_INTERVAL									= 16,				// �����ָ�ʱ����

	CONFIGTYPE_SIGN_FIRST_OPEN_TIME												= 17,				// ÿ��ǩ����һ�ο���ʱ��
	CONFIGTYPE_SIGN_SECOND_OPEN_TIME											= 18,				// ÿ��ǩ���ڶ��ο���ʱ��
	CONFIGTYPE_SIGN_THIRD_OPEN_TIME												= 19,				// ÿ��ǩ�������ο���ʱ��
	CONFIGTYPE_END,
};

// �������ֱ�id����
// ע��: 1. ת���%��಻����ȫ�Ƿ��� 2.�����������Ҫ�ٷֺ�, ��Ҫ��дȫ�ǵİٷֺ�
enum CONFIG_TEXT_ID
{
	CONFIG_TEXT_ID_NONE															= 0,

	// ��������������
	CONFIG_TEXT_ID_USER_NOT_FIND_USER											= 2,		// ��Ҳ����ڻ�����
	CONFIG_TEXT_ID_USER_TO_FAST													= 3,		// ������Ϣ����
	CONFIG_TEXT_ID_USER_INVALID_INFO											= 4,		// ���Ϸ�����Ϣ
	CONFIG_TEXT_ID_USER_LESS_LEV												= 5,		// �ȼ�����
	CONFIG_TEXT_ID_USER_LESS_VAS												= 6,		// Ԫ������
	CONFIG_TEXT_ID_USER_NEWEST_SERVER											= 7,		// ���·�����
	CONFIG_TEXT_ID_USER_LOGINED_SERVER											= 8,		// ��¼��������
	CONFIG_TEXT_ID_USER_ALL_SERVER												= 9,		// ȫ��������

	// �߳���ʾ
	CONFIG_TEXT_ID_KICK_REASON_DEFAULT											= 10,	// ��ϵͳ�߳�
	CONFIG_TEXT_ID_KICK_REASON_PASSWORD_ERROR									= 11,	// �������
	CONFIG_TEXT_ID_KICK_REASON_BE_KICK_ANOTHER									= 12,	// ������������
	CONFIG_TEXT_ID_KICK_REASON_RELATION_SERVER									= 13,	// �������ط�����
	CONFIG_TEXT_ID_KICK_REASON_FULL												= 14,	// �����������࣬����ʧ��
	CONFIG_TEXT_ID_KICK_REASON_SYSTEM											= 15,	// ��GM�߳�
	CONFIG_TEXT_ID_KICK_REASON_NOT_ALLOW										= 16,	// ���������δ����
	CONFIG_TEXT_ID_KICK_REASON_GM_MAC_ERROR										= 17,	// GM����Mac��ַ��֤����		
	CONFIG_TEXT_ID_KICK_REASON_CHECK_SPEED_TOO_FAST								= 18,	// ϵͳ�����߳�
	CONFIG_TEXT_ID_KICK_REASON_GMCMD											= 19,	// GM�������Լ�	
	CONFIG_TEXT_ID_KICK_REASON_LOGIN_TIMEOUT									= 20,	// ��½��ʱ
	CONFIG_TEXT_ID_KICK_REASON_ACCOUNT_STOP_BYTIME								= 21,	// �����˺ű���ʱ��ͣ��Ԥ��%dСʱ����
	CONFIG_TEXT_ID_KICK_REASON_ACCOUNT_STOP_FOREVER								= 22,	// �����˺ű����÷�ͣ

	// ����
	CONFIG_TEXT_ID_CREATESYN_ss													= 31,		// %s��������%s
	CONFIG_TEXT_ID_SYN_RANK_LEADER												= 32,      // �᳤
	CONFIG_TEXT_ID_SYN_RANK_ELDER												= 33,      // ����
	CONFIG_TEXT_ID_SYN_RANK_NORMAL												= 34,      // ��Ա

	// �����ŶӰ������
	CONFIG_TEXT_ID_GROUP_SYN_NOT_EXIST											= 35,		// ���᲻����

	// ������־
	CONFIG_TEXT_ID_SYN_LOG_CREATE_SYN			= 41,		// ��%s����������
	CONFIG_TEXT_ID_SYN_LOG_DIRECT_JOIN_SYN		= 42,		// ��%s�����빫��
	CONFIG_TEXT_ID_SYN_LOG_EXIT_SYN				= 43,		// ��%s���˳�����
	CONFIG_TEXT_ID_SYN_LOG_KICK_SYN				= 44,		// ����%s��%s������%s���߳��˹���
	CONFIG_TEXT_ID_SYN_LOG_AlTER_NOTICE			= 45,		// ����%s��%s���޸��˹��ṫ��
	CONFIG_TEXT_ID_SYN_LOG_UP_ELDER				= 46,		// �᳤��%s������%s������Ϊ����
	CONFIG_TEXT_ID_SYN_LOG_DOWN_MEMBER			= 47,		// �᳤��%s��ȡ���ˡ�%s���ĳ���ְλ
	CONFIG_TEXT_ID_SYN_LOG_RESET_INSTANCE 		= 48,		// ����%s��%s���������ŶӸ�������%d��
	CONFIG_TEXT_ID_SYN_LOG_PASS_INSTANCE  		= 49,		// �ŶӸ���:��%d��ͨ��,���һ���ɡ�%s�����
	CONFIG_TEXT_ID_SYN_LOG_TRANSFER_LEADER		= 50,		// ��%s�����᳤ְλ�ƽ����ˡ�%s��
	CONFIG_TEXT_ID_SYN_LOG_TROPHY_QUEUE			= 51,		// ��%s����ս��Ʒ%s�Ķ����в��
	CONFIG_TEXT_ID_SYN_LOG_AGREE_JOIN_SYN		= 52,		// ����%s��%s����׼�ˡ�%s�����빫��
	CONFIG_TEXT_ID_SYN_LOG_ALTER_LEV_LIMIT		= 53,		// ����%s��%s���޸��˼��빫����Сս�ӵȼ�Ϊ��%d��
	CONFIG_TEXT_ID_SYN_LOG_SHARE_TROPHY			= 54,		// ����%s��%s����%s������ˡ�%s��
	CONFIG_TEXT_ID_SYN_LOG_ALTER_NEED_CHECK		= 55,		// ����%s��%s���޸��˹�������Ϊ������֤
	CONFIG_TEXT_ID_SYN_LOG_ALTER_NO_CHECK		= 56,		// ����%s��%s���޸��˹�������Ϊ������Ҫ��֤
	CONFIG_TEXT_ID_SYN_LOG_AUTO_TRANSFER_LEADER = 57,		// �᳤��%s����ʱ��δ���ߣ��᳤ְλ�Զ����ø���%s��

	CONFIG_TEXT_ID_NOT_CHOOSE_SERVER			= 71,		// ����ѡ�������
	CONFIG_TEXT_ID_NOT_GAME_SERVER				= 72,		// û����Ϸ����������
	CONFIG_TEXT_ID_CONNECT_GAME_SERVER_FAILED	= 73,		// ��Ϸ����������ʧ��

	CONFIG_TEXT_ID_CREATE_FAILED				= 74,		// ��ɫ����ʧ�ܣ�
	CONFIG_TEXT_ID_NAME_CHECK_ERROR				= 75,		// �����а����Ƿ��ַ���
	CONFIG_TEXT_ID_STRING_CHECK_ERROR			= 76,		// �Ƿ��ַ���(�ͻ��˴ʿ�����)
	CONFIG_TEXT_ID_NAME_REPEAT					= 77,		// �ظ��Ľ�ɫ��
	CONFIG_TEXT_ID_CAN_NOT_MORE_PLAYER			= 78,		// �޷���������Ľ�ɫ��
	CONFIG_TEXT_ID_OPERATOR_FAILED				= 79,		// ����ʧ�ܣ�
	CONFIG_TEXT_ID_UNKNOW_ACTION				= 80,		// δ֪�Ĳ������ͣ�
	CONFIG_TEXT_ID_PACKAGE_NOT_ENOUGH			= 81,		// �����ռ䲻�㣡
	CONFIG_TEXT_ID_VAS_NOT_ENOUGH				= 82,		// Ԫ�����㣡
	CONFIG_TEXT_ID_NEED_ITEMTYPE_ds				= 83,		// ��Ҫ%d��%s
	CONFIG_TEXT_ID_RECONNECT_START				= 84,		// ��ʼ�Զ�����
	CONFIG_TEXT_ID_RECONNECT_SUCCESS			= 85,		// �����ɹ�
	CONFIG_TEXT_ID_RECONNECT_FAILED				= 86,		// ����ʧ��


	CONFIG_TEXT_ID_no_magic						= 90,		// ɶҲ����
	CONFIG_TEXT_ID_no_magic_text				= 91,		// ū�����ɶҲ��������
	
	CONFIG_TEXT_ID_END,
};

// ���ɳ�Ա�ȼ�
enum SYN_RANK_TYPE
{
	RANK_LEADER			= 3,	// �᳤
	RANK_ELDER			= 2,	// ����
	RANK_NORMAL			= 1,	// ��Ա
	RANK_NONE			= 0,	// 		
};


// �˺�����
enum ACCOUNT_TYPE
{
	ACCOUNT_TYPE_NORMAL		= 0,	// �����˺�
	ACCOUNT_TYPE_GM_LOW		= 1,	// GM�ͼ����˺�
	ACCOUNT_TYPE_GM_HI		= 2,	// GM�߼����˺�
};

// �˺�״̬
enum ACCOUNT_STATUS
{
	ACCOUNT_STATUS_NORMAL		= 0,	// ����
	ACCOUNT_STATUS_STOP_BYTIME	= 1,	// ��ʱ��ͣ, ״̬����Ϊ���utcʱ��
	ACCOUNT_STATUS_STOP_FOREVER = 2,	// ���÷�ͣ
};

enum USER_ATTR
{
	USER_ATTR_score,		// ��ǰս��
	USER_ATTR_score_max,	// ���ս��

	USER_ATTR_fight_index,	// ��ս���
	USER_ATTR_atk,			// ��ǰ���� - �ȹ�
	USER_ATTR_def,			// ��ǰ���� - ����
	USER_ATTR_dodge,		// ��ǰ���� - ����
	USER_ATTR_king,			// ��ǰ���� - ����

	USER_ATTR_end,
};

// ��������
enum USER_MONEY_TYPE
{
	USER_MONEY_TYPE_NONE			= 0,
	USER_MONEY_TYPE_BEGIN			= 100,
	USER_MONEY_TYPE_material_ore1,		// ��Դ - ��ʯ	1-5		��Ӧԭ����ɫ
	USER_MONEY_TYPE_material_ore2,
	USER_MONEY_TYPE_material_ore3,
	USER_MONEY_TYPE_material_ore4,
	USER_MONEY_TYPE_material_ore5,
	USER_MONEY_TYPE_material_gem1,		// ��Դ - ��ʯ 1-5		��Ӧԭ����ɫ
	USER_MONEY_TYPE_material_gem2,
	USER_MONEY_TYPE_material_gem3,
	USER_MONEY_TYPE_material_gem4,
	USER_MONEY_TYPE_material_gem5,
	USER_MONEY_TYPE_material_soul1,		// ��Դ - ��ʯ 1 - 5	��Ӧԭ����ɫ
	USER_MONEY_TYPE_material_soul2,
	USER_MONEY_TYPE_material_soul3,
	USER_MONEY_TYPE_material_soul4,
	USER_MONEY_TYPE_material_soul5,	
	USER_MONEY_TYPE_material_statue,	// ��Դ	- ����			��Ӧԭ���ɫ
	USER_MONEY_TYPE_material_adva1,		// ��Դ - �߼���Դ1
	USER_MONEY_TYPE_material_adva2,		// ��Դ - �߼���Դ2

	USER_MONEY_TYPE_poker_chip,			// ��Ƭ

	// ��������Ҳ��Ϊ���������
	USER_MONEY_TYPE_materialitem_package,	// �󹤰�
	USER_MONEY_TYPE_materialitem_ore,		// �ͼ���ʯ��Դ��
	USER_MONEY_TYPE_materialitem_gem,		// �м���ʯ��Դ��
	USER_MONEY_TYPE_materialitem_soul,		// �߼���ʯ��Դ��
	USER_MONEY_TYPE_materialitem_bomb,		// �׹�

	USER_MONEY_TYPE_activity1,			// �����1
	USER_MONEY_TYPE_activity2,			// �����2
	USER_MONEY_TYPE_activity3,			// �����3
	USER_MONEY_TYPE_activity4,			// �����4
	USER_MONEY_TYPE_activity5,			// �����5

	USER_MONEY_TYPE_ItemMaxBuy,		// ��Ʒ���޹���
	USER_MONEY_TYPE_PokerMaxBuy,	// �������޹���
	USER_MONEY_TYPE_ExploreMaxBuy,	// ̽�����޹���
	USER_MONEY_TYPE_OreMaxBuy,		// ԭ�����޹���
	USER_MONEY_TYPE_FriendPoint,	// ���ѵ���
	USER_MONEY_TYPE_KingBadge,		// ����֮��

	USER_MONEY_TYPE_END,

	USER_MONEY_TYPE_AUTO_BEGIN		= 500,
	USER_MONEY_TYPE_AUTO_MONEY,		// Ǯ
	USER_MONEY_TYPE_AUTO_EXP,		// ����
	USER_MONEY_TYPE_AUTO_ORE,		// ԭ��
	USER_MONEY_TYPE_AUTO_END,

	USER_MONEY_TYPE_VAS				= 998,	// Ԫ��,		ʵʱ��д�˺ſ�
};

// ����ȼ�����
enum LEV_EXP_TYPE
{
	LEV_EXP_TYPE_STAR1 = 1,	// �Ǽ�1����
	LEV_EXP_TYPE_STAR2 = 2,	// �Ǽ�2����
	LEV_EXP_TYPE_STAR3 = 3,	// �Ǽ�3����
	LEV_EXP_TYPE_STAR4 = 4,	// �Ǽ�4����
	LEV_EXP_TYPE_STAR5 = 5,	// �Ǽ�5����
};

// ������������
enum BOSS_WEAPON_TYPE
{
	BOSS_WEAPON_TYPE_begin = 1,
	BOSS_WEAPON_TYPE_end = 11,
};


enum EUSERMASKTYPE					// ��������
{
	EUMT_Begin = 0,
	EUMT_TaskMask = 1,	// ��������
	EUMT_GiveMask = 2,	// ��������
	EUMT_DayMask = 3,	// ������
	EUMT_WeekMask = 4,	// ������
	EUMT_MonthMask = 5,	// ������
	EUMT_End,
};


// �������ID������ռ������, �߻�ʹ������ʹ��10W����
enum E_USER_MASKID_PROGRAM
{
	//////////////////////////////////////////////////////////////////////////
	// ��������
	EUMIP_MASK_begin = 10000,
	EUMIP_MASK_weapon,	// �����������
	EUMIP_MASK_end,

	//////////////////////////////////////////////////////////////////////////
	// ��������
	EUMIP_DATA_begin = 20000,

	EUMIP_DATA_achievement_begin = 20002,
	EUMIP_DATA_achievement_arena_win1 = 20002,	// ������1ʤ
	EUMIP_DATA_achievement_arena_win3,			// ������3ʤ
	EUMIP_DATA_achievement_wa_kuang,			// �ڿ����, ������
	EUMIP_DATA_achievement_friend_send_gift,	// �������
	EUMIP_DATA_achievement_friend_get_gift,		// �������
	EUMIP_DATA_achievement_strengthen,			// ǿ������
	EUMIP_DATA_achievement_upstar,				// ���Ǵ���
	EUMIP_DATA_achievement_kill_boss,			// Ū��boss����
	EUMIP_DATA_achievement_chip_total,			// ��Ƭ����
	EUMIP_DATA_achievement_arena_all_win,		// ��������ʤ
	EUMIP_DATA_achievement_lottery_poker,		// ��ļ����
	EUMIP_DATA_achievement_weapon_strengthen,	// ��������ǿ������
	EUMIP_DATA_achievement_pass_progress,		// �ؿ�����
	EUMIP_DATA_achievement_max_score,			// ���ս��
	EUMIP_DATA_achievement_end,

	EUMIP_DATA_end,

	//////////////////////////////////////////////////////////////////////////
	// ������ ��λ
	EUMIP_DAY_BIT_begin = 30000,	
	EUMIP_DAY_BIT_SIGN,							// ÿ��ǩ��
	EUMIP_DAY_BIT_Challenge_first_award,		// ÿ����ս���״�ʤ�����⽱��
	EUMIP_DAY_BIT_end,	

	//////////////////////////////////////////////////////////////////////////
	// ������ �Ǵ�
	EUMIP_DAY_COUNT_begin = 40000,
	EUMIP_DAY_COUNT_LotteryMoneyCount,			// ÿ�ս�ҳ齱����
	EUMIP_DAY_COUNT_world_rank_Count,			// ÿ���������ս����
	EUMIP_DAY_COUNT_End,		

	//////////////////////////////////////////////////////////////////////////
	// ������ ��λ
	EUMIP_WEEK_BIT_begin = 50000,
	EUMIP_WEEK_BIT_end,	

	//////////////////////////////////////////////////////////////////////////
	// ������ �Ǵ�
	EUMIP_WEEK_COUNT_begin = 60000,
	EUMIP_WEEK_COUNT_End,

	//////////////////////////////////////////////////////////////////////////
	// ������ ��λ
	EUMIP_MONTH_BIT_begin = 70000,
	EUMIP_MONTH_BIT_end,

	//////////////////////////////////////////////////////////////////////////
	// ������ �Ǵ�
	EUMIP_MONTH_COUNT_begin = 80000,
	EUMIP_MONTH_COUNT_End,

	// �߻��Զ������뷶Χ
	EUMIP_custom_MASK_begin			= 100000,		// ��������
	EUMIP_custom_MASK_end			= 199999,
	EUMIP_custom_DATA_begin			= 200000,		// ��������
	EUMIP_custom_DATA_end			= 299999,
	EUMIP_custom_DAY_BIT_begin		= 300000,		// ������ ��λ
	EUMIP_custom_DAY_BIT_end		= 399999,
	EUMIP_custom_DAY_COUNT_begin	= 400000,		// ������ �Ǵ�
	EUMIP_custom_DAY_COUNT_End		= 499999,
	EUMIP_custom_WEEK_BIT_begin		= 500000,		// ������ ��λ
	EUMIP_custom_WEEK_BIT_end		= 599999,		
	EUMIP_custom_WEEK_COUNT_begin	= 600000,		// ������ �Ǵ�
	EUMIP_custom_WEEK_COUNT_End		= 699999,
	EUMIP_custom_MONTH_BIT_begin	= 700000,		// ������ ��λ
	EUMIP_custom_MONTH_BIT_end		= 799999,
	EUMIP_custom_MONTH_COUNT_begin	= 800000,		// ������ �Ǵ�
	EUMIP_custom_MONTH_COUNT_End	= 899999,
};


// ��������
enum POKER_IMPORTANT_ATTR
{
	POKER_IMPORTANT_ATTR_atk = 1,
	POKER_IMPORTANT_ATTR_def,
	POKER_IMPORTANT_ATTR_dodge,
	POKER_IMPORTANT_ATTR_king,
};

// ħ���ͷ���������
enum MAGIC_CONDITION_TYPE
{
	MAGIC_CONDITION_TYPE_None = 0,
	MAGIC_CONDITION_TYPE_BigOwnerScoreRate,		// ���ڼ���ս����ֱ�
	MAGIC_CONDITION_TYPE_SmallOwnerScoreRate,	// С�ڼ���ս����ֱ�
	MAGIC_CONDITION_TYPE_BigEnemyScoreRate,		// ���ڵз�ս����ֱ�
	MAGIC_CONDITION_TYPE_SmallEnemyScoreRate,	// С�ڵз�ս����ֱ�
	MAGIC_CONDITION_TYPE_BigRound,				// ���ڻغ���
	MAGIC_CONDITION_TYPE_SmallRound,			// С�ڻغ���
};

// ħ����ӡ����
enum MAGIC_SEAL_TYPE
{
	MAGIC_SEAL_TYPE_None = 0,
	MAGIC_SEAL_TYPE_BigRate,		// ��ӡ���ܴ������� ���� ���ٵ�
	MAGIC_SEAL_TYPE_SmallRate,		// ��ӡ���ܴ������� С�� ���ٵ�
};

// ħ���˺�����
enum MAGIC_DAMAGE_TYPE
{
	MAGIC_DAMAGE_TYPE_None,					// �����˺�
	MAGIC_DAMAGE_TYPE_OwnerNowScoreRate,	// ������ǰս������
	MAGIC_DAMAGE_TYPE_OwnerMaxScoreRate,	// �������ս������
	MAGIC_DAMAGE_TYPE_EnemyNowScoreRate,	// �з���ǰս������
	MAGIC_DAMAGE_TYPE_EnemyMaxScoreRate,	// �з����ս������
	MAGIC_DAMAGE_TYPE_OwnerLostScoreRate,	// ��������ʧս������
	MAGIC_DAMAGE_TYPE_EnemyLostScoreRate,	// �з�����ʧս������
};

// ħ���ָ�����
enum MAGIC_RECOVER_TYPE
{
	// �ָ���ǰս��
	MAGIC_RECOVER_TYPE_None,					// ���ձ��ι����˺�
	MAGIC_RECOVER_TYPE_OwnerNowScoreRate,		// ������ǰս������
	MAGIC_RECOVER_TYPE_OwnerMaxScoreRate,		// �������ս������
	MAGIC_RECOVER_TYPE_EnemyNowScoreRate,		// �з���ǰս������
	MAGIC_RECOVER_TYPE_EnemyMaxScoreRate,		// �з����ս������
};

// ��Ʒ��ɫ
enum ITEMCOLOR
{
	ITEMCOLOR_NONE   = 0,
	ITEMCOLOR_WHITE  = 1,	// ��
	ITEMCOLOR_GREEN  = 2,	// ��
	ITEMCOLOR_BLUE	 = 3,	// ��
	ITEMCOLOR_VIOLET = 4,	// ��
	ITEMCOLOR_ORANGE = 5,	// ��
};

// ��Ʒmonopoly ����
enum ITEMTYPE_MONOPOLY
{
	ITEMTYPE_MONOPOLY_NONE		  = 0x0000,
	ITEMTYPE_MONOPOLY_NEED_RECORD = 0x0001,		// ��Ҫд���¼����
	ITEMTYPE_MONOPOLY_MONEY		  = 0x0002,		// ��ʵ���ǻ��� 
};

enum E_USER_THING_TYPE
{
	E_USER_THING_TYPE_NONE,
	E_USER_THING_TYPE_MONEY,		// ����
	E_USER_THING_TYPE_POKER,		// ����
	E_USER_THING_TYPE_ITEM,			// ��Ʒ
};

// �̵�����
enum E_SHOP_TYPE
{
	E_SHOP_TYPE_NORMAL		= 0,	// ��ͨ�̳�
	E_SHOP_TYPE_PVP			= 1,	// pvp�һ��̵�
};

// �����
enum ACTIVITY_CONFIG_TYPE
{
	ACTIVITY_CONFIG_TYPE_none = 0,
	ACTIVITY_CONFIG_TYPE_lottery = 1,	// ��ʱ�鿨�	
};

// ս������
enum E_BATTLE_TYPE
{
	E_BATTLE_TYPE_NONE = 0,
	E_BATTLE_TYPE_MONSTER,			// ����ս��
	E_BATTLE_TYPE_FRIENDLY,			// ����д�
	E_BATTLE_TYPE_PVP_CHALLENGE,	// pvp��ս��
	E_BATTLE_TYPE_PVP_WORLD,		// pvp�����
	E_BATTLE_TYPE_INSTANCE,			// ����
	E_BATTLE_TYPE_SMELT,			// �����ӱ�
};

// ��������
enum MONSTER_TYPE
{
	MONSTER_TYPE_soldier_begin	= 200000,
	MONSTER_TYPE_soldier_end	= 210000,

	MONSTER_TYPE_boss_begin		= 210000,
	MONSTER_TYPE_boss_end		= 220000,
};

enum E_INSTANCE_MODE_TYPE				// �����Ѷ�ģʽ
{
	E_INSTANCE_MODE_TYPE_NONE,
	E_INSTANCE_MODE_TYPE_EASY,			// ��
	E_INSTANCE_MODE_TYPE_NORMAL,		// ��ͨ
	E_INSTANCE_MODE_TYPE_DIFFICULTY,	// ����
};

#endif // end of _COMMON_ENUM_DEF_H_

