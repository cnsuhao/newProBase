////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: GlobalEnumDef.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_GLOBAL_ENUM_DEF_H_
#define _JYP_GLOBAL_ENUM_DEF_H_

#include "Common/CommonEnumdef.h"

// 字段类型
enum FIELD_TYPE
{
	FIELD_TYPE_int,		// 整型
	FIELD_TYPE_str,		// 字符串
};

// 逻辑数据 i64
enum LOGIC_DATA
{
	LOGIC_DATA_LoginServerId					= 0,
	LOGIC_DATA_GameServerPort					= 1,

	LOGIC_DATA_NeedProcessNetBreak				= 2,		// 需要处理网络断开

	LOGIC_DATA_heartbeat_server_start			= 3,		// 服务端心跳起点
	LOGIC_DATA_heartbeat_client_start			= 4,		// 客户端心跳起点

	LOGIC_DATA_server_group						= 5,		// 当前服务器组
	LOGIC_DATA_server_line						= 6,		// 当前服务器线

	LOGIC_DATA_BreakReasonCode,								// 断开原因
	LOGIC_DATA_ReconnectingFlag,							// 重连中标记
	LOGIC_DATA_ReconnectCount,								// 重连次数
	LOGIC_DATA_ReconnectStartTime,							// 重连开始utc秒数

	LOGIC_DATA_userinfo_user_id					= 101,		// 玩家ID
	LOGIC_DATA_userinfo_account_id				= 102,		// 账号ID
	LOGIC_DATA_userinfo_account_type			= 103,		// 账号类型	0普通, 1普通GM, 2高级GM
	LOGIC_DATA_userinfo_exit_time				= 104,		// 上次退出时间(utc时间)
	LOGIC_DATA_userinfo_sex						= 106,		// 性别
	LOGIC_DATA_userinfo_lookface				= 107,		// LOOKFACE


	LOGIC_DATA_END,
};

// 逻辑数据 字符串
enum LOGIC_STRING
{
	LOGIC_STRING_AccountName,
	LOGIC_STRING_AccountPwd,
	LOGIC_STRING_UserName,
	LOGIC_STRING_UserCode,

	LOGIC_STRING_GameServerIp,

	LOGIC_STRING_BreakReason,			// 断开原因
};

enum USER_DATA
{
	USER_DATA_user_id,
	USER_DATA_account_id,
	USER_DATA_account_type,			// 账号类型	0普通, 1普通GM, 2高级GM
	USER_DATA_exit_time,			// 上次退出时间(utc时间)
	USER_DATA_stop_talk_end_time,	// 禁言结束时间(utc时间)
	USER_DATA_sex,
	USER_DATA_lookface,
	USER_DATA_job,					// 职业
	USER_DATA_job_stage,			// 转职阶段1-5
	USER_DATA_lev,
	USER_DATA_exp,
	USER_DATA_str_point,			// 力量配点
	USER_DATA_dex_point,			// 敏捷配点
	USER_DATA_int_point,			// 智力配点
	USER_DATA_sta_point,			// 耐力配点
	USER_DATA_life_point,			// 体质配点
	USER_DATA_left_point,			// 剩余配点
};

enum CONNECT_STATUS
{
	CONNECT_STATUS_none,		// 初始状态
	CONNECT_STATUS_reqLogin,	// 请求入口服	请求游服线路
	CONNECT_STATUS_reqPwd,		// 请求游服		发送密码
	CONNECT_STATUS_choose,		// 角色选择
	CONNECT_STATUS_login,		// 登录状态		请求数据
	CONNECT_STATUS_run,			// 运行中
};

enum MESSAGE_BOX_MODE
{
	MESSAGE_BOX_MODE_OK			= 1,	// 仅一个OK按钮
	MESSAGE_BOX_MODE_CANCEL		= 2,	// 仅一个Cancel按钮
	MESSAGE_BOX_MODE_OK_CANCEL	= MESSAGE_BOX_MODE_OK | MESSAGE_BOX_MODE_CANCEL,	// OK和Cancel按钮
};

enum MESSAGE_BOX_CLICK
{
	MESSAGE_BOX_CLICK_OK		= 1,	// 选择了OK
	MESSAGE_BOX_CLICK_CANCEL	= 2,	// 选择了Cancel
};

// 出生方向
enum BORN_FROM
{
	BORN_FROM_NONE = 0,
	BORN_FROM_LEFT = 1,
	BORN_FROM_RIGHT = 2,
};

// 战斗者属性
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

// 物品列表类型
enum ITEM_LIST_TYPE
{
	ITEM_LIST_TYPE_UNKNOWN	= 0,
	ITEM_LIST_TYPE_PACKAGE,							// 所有背包
	ITEM_LIST_TYPE_PACKAGE_EQUIP,					// 装备背包
	ITEM_LIST_TYPE_PACKAGE_MEDICINE,				// 药品背包
	ITEM_LIST_TYPE_PACKAGE_PROP,					// 道具背包
	
	ITEM_LIST_TYPE_PACKAGE_SCROLL_WEAPON,											// 武器卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_ARMOR,											// 衣服卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_HELMET,											// 头盔卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_NECKLACE,											// 项链卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_GLOVE,											// 护手卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_BELT,												// 腰带卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_SHOES,											// 鞋子卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_RING,												// 戒指卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_BADGE = ITEM_LIST_TYPE_PACKAGE_SCROLL_RING + 1,	// 徽章卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_DRESS_WEAPON,										// 武器时装卷轴
	ITEM_LIST_TYPE_PACKAGE_SCROLL_DRESS_ARMOR,										// 衣服时装卷轴
	ITEM_LIST_TYPE_PACKAGE_APPEND_MATERIAL,											// 装备追加材料
	ITEM_LIST_TYPE_PACKAGE_EMBED_GEM,												// 装备镶嵌宝石

	ITEM_LIST_TYPE_BODY,				// 道具背包
	ITEM_LIST_TYPE_BODY_WEAPON,			// 武器
	ITEM_LIST_TYPE_BODY_ARMOR,			// 衣服
	ITEM_LIST_TYPE_BODY_HELMET,			// 头盔
	ITEM_LIST_TYPE_BODY_NECKLACE,		// 项链
	ITEM_LIST_TYPE_BODY_GLOVE,			// 护手
	ITEM_LIST_TYPE_BODY_BELT,			// 腰带
	ITEM_LIST_TYPE_BODY_SHOES,			// 鞋子
	ITEM_LIST_TYPE_BODY_RING_LEFT,		// 左戒指
	ITEM_LIST_TYPE_BODY_RING_RIGHT,		// 右戒指
	ITEM_LIST_TYPE_BODY_BADGE,			// 徽章
	ITEM_LIST_TYPE_BODY_DRESS_WEAPON,	// 武器时装
	ITEM_LIST_TYPE_BODY_DRESS_ARMOR,	// 衣服时装

	ITEM_LIST_TYPE_CLASSFIY_EQUIP,					// 所有装备
	ITEM_LIST_TYPE_CLASSFIY_EQUIP_BEAPPEND,			// 所有可追加装备
	ITEM_LIST_TYPE_CLASSFIY_EQUIP_BEADDLEV,			// 所有可强化的装备
	ITEM_LIST_TYPE_CLASSFIY_EQUIP_BEWASH,			// 所有可洗练的装备
	ITEM_LIST_TYPE_CLASSFIY_EQUIP_BERESET_NATURE,	// 所有可重置自然属性的装备
	ITEM_LIST_TYPE_WASH_EUDEMON,				// 洗礼宠物物品
};

enum ITEM_LIST_MODE
{
	ITEM_LIST_MODE_LIST,		// 列表模式
	ITEM_LIST_MODE_PACKAGE,		// 背包模式
	ITEM_LIST_MODE_TYPE,		// 背包模式
};

enum ITEM_CLICK_MODE
{
	ITEM_CLICK_MODE_NONE,		// 不处理
	ITEM_CLICK_MODE_TIPS,		// 点击弹出详细TIPS
	ITEM_CLICK_MODE_OPT_TIPS,	// 点击弹出详细TIPS 带操作按钮
	ITEM_CLICK_MODE_CHOOSE,		// 点击选中
};

enum SHOW_HPMP_TYPE
{
	SHOW_HPMP_TYPE_normal,		// 白字
	SHOW_HPMP_TYPE_hp,			// 掉血
	SHOW_HPMP_TYPE_mp,			// 掉蓝
	SHOW_HPMP_TYPE_crit,		// 暴击
	SHOW_HPMP_TYPE_recover_hp,	// 回血
	SHOW_HPMP_TYPE_recover_mp,	// 回蓝
	SHOW_HPMP_TYPE_miss,		// 闪避
	SHOW_HPMP_TYPE_parry,		// 格挡
	SHOW_HPMP_TYPE_spend_hp,	// 消耗生命
};

enum MAGIC_ANIMATE_POS_TYPE
{
	MAGIC_ANIMATE_POS_TYPE_beatk			= 0,	// 0 施法者受击骨骼坐标
	MAGIC_ANIMATE_POS_TYPE_target_mid_each	= 2,	// 2 每个目标受击骨骼坐标
	MAGIC_ANIMATE_POS_TYPE_owner_mid		= 3,	// 3 我方正中
	MAGIC_ANIMATE_POS_TYPE_enemy_mid		= 4,	// 4 敌方正中
	MAGIC_ANIMATE_POS_TYPE_screen_mid		= 5,	// 5 屏幕正中
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

// 卡牌属性数据
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

// 绿点提示类型
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

// 卡牌排序方式
enum POKER_SORT_TYPE
{
	POKER_SORT_TYPE_none = 0,
	POKER_SORT_TYPE_color,
	POKER_SORT_TYPE_level,
	POKER_SORT_TYPE_upstar,
	POKER_SORT_TYPE_score,
};


#endif // end of _JYP_GLOBAL_ENUM_DEF_H_
