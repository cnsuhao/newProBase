////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: CommonEnumdef.h
//			客户端服务端通用枚举声明处, 该文件保存客户端与服务端一致
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/05/21
////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_ENUM_DEF_H_
#define _COMMON_ENUM_DEF_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// 消息type号定义处, 定义协议号时强制将协议号显式填入
enum _MSG_TYPE_DEFINE_
{
	_MSG_NONE							= 0,

	_MSG_RL_SERVER_BEGIN				= 100,	// 入口服消息开始
	_MSG_RL_SERVER_REQ_LOGIN			= 101,	// 客户端请求登陆
	_MSG_RL_SERVER_QUERY_ONLINE			= 102,	// 关系服查询在线
	_MSG_RL_SERVER_END					= 200,	// 入口服消息结束

	// 客户端 登陆线程 消息区间
	_MSG_LOGIN_BEGIN					= 1000,
	_MSG_LOGIN_CONNECT					= 1001,	// 连接			C --> S
	_MSG_LOGIN_CONNECT_ACTION			= 1002,	// 连接操作		C <-> S
	_MSG_LOGIN_USER_LIST				= 1003,	// 玩家列表		C <-- S
	_MSG_LOGIN_CREATE_NEW_USER			= 1004,	// 建立新角色	C <-> S
	_MSG_LOGIN_KICK_REASON				= 1005,	// 踢出原因		C <-- S
	_MSG_LOGIN_END						= 2000,

	_MSG_GAME_BEGIN						= 5000,
	_MSG_GAME_LOGIN_QUERY,				// 登陆查询				C <-> S
	_MSG_GAME_KICK_REASON,				// 踢出原因				C <-- S
	_MSG_GAME_SMALLACTION,				// SmallAction消息		C <-> S
	_MSG_GAME_RELAY_DATABASE,			// 本服中转数据库		S <-> R
	_MSG_GAME_CROSS_RELAY_DATABASE,		// 跨服中转数据库		S <-> C
	_MSG_GAME_DEBUG,					// 调试指令				C <-> S
	_MSG_GAME_GIFT,						// 礼包					C <-> S
	_MSG_GAME_SMELT,					// 冶炼					C <-> S
	_MSG_GAME_SMELT_MONSTER,			// 冶炼怪物消息			C <-> S

	_MSG_GAME_TMP_DATA = 5010,			// UserTmpData			C <-> S
	_MSG_GAME_CROSS_INFO,				// 跨服基础信息			C <-> S
	_MSG_GAME_TASK,						// 任务					C <-> S
	_MSG_GAME_ACTIVITIES,				// 活动					C <-> S
	_MSG_GAME_SIGN,						// 签到					C <-> S
	_MSG_GAME_NEWCARD,					// 新手卡				C <-> S
	_MSG_GAME_NEWCARD_PRIZE,			// 新手卡奖励			C <-- S
	_MSG_GAME_ACTIVE_AWARD,				// 活动奖励				C <-> S

	_MSG_COMMENT_OPT = 5050,			// 评论操作				C <-> S
	_MSG_COMMENT_LIST,					// 评论列表				C <-> S

	_MSG_GAME_USER_INFO = 5100,			// UserInfo				C <-- S
	_MSG_GAME_USER_ATTR,				// UserAttr				C <-- S
	_MSG_GAME_USER_MONEY,				// 货币同步				C <-- S
	_MSG_GAME_USER_MONEY_HINT,			// 货币提示				C <-- S
	_MSG_GAME_USER_MAC,					// 玩家mac地址			C --> S
	_MSG_GAME_MASK,						// 掩码同步				C <-- S
	_MSG_GAME_VAS_INFO,					// 元宝详情				C <-- S
	_MSG_GAME_ONLINE_INFO,				// 在线玩家信息			S <-> R
	_MSG_GAME_ITEM,						// 物品信息				C <-> S
	_MSG_GAME_FRIEND,					// 好友信息				C <-> S
	_MSG_GAME_SHOP,						// 商城					C <-> S
	_MSG_GAME_BATTLE_INFO,				// 战斗信息				C <-- S
	_MSG_GAME_BATTLE_RESULT,			// 战斗结果				C <-- S
	_MSG_GAME_CHALLENGE,				// 挑战系统				C <-> S
	_MSG_GAME_INSTANCE_LIST,			// 副本列表				C <-- S
	_MSG_GAME_INSTANCE_INFO,			// 副本信息				C <-> S
	_MSG_GAME_AWARD_HINT,				// 各种奖励提示消息		C <-> S
	
	_MSG_GAME_POKER_LIST = 5200,		// 卡牌列表消息			C <-- S
	_MSG_GAME_POKER_OPT,				// 卡牌操作消息			C <-> S
	_MSG_GAME_POKER_BOOK_LIST,			// 卡牌图鉴列表消息		C <-- S
	_MSG_GAME_POKER_HOLY,				// 卡牌神殿消息			C <-> S
	_MSG_GAME_POKER_FIGHT_GROUP,		// 卡牌阵容信息			C <-> S

	_MSG_GAME_BBS		 = 5300,		// 论坛消息				C <-> S
	_MSG_GAME_BBS_REPLY,				// 论坛回帖				C <-> S

	_MSG_GAME_SYN_SERVER = 5400,		// 帮派服务器间消息		S <-> R
	_MSG_GAME_SYN_CLIENT,				// 帮派客户端消息		C <-> S
	_MSG_GAME_SYN_LIST,					// 帮派列表				C <-- S
	_MSG_GAME_SYN_MEMBER_LIST,			// 帮派成员列表			C <-- S
	_MSG_GAME_SYN_INFO,					// 帮派详情				C <-- S
	_MSG_GAME_SELF_SYN_INFO,			// 自己帮派详情			C <-- S
	_MSG_GAME_SYN_LOG,					// 帮派日志				C <-> S
	_MSG_GAME_SYN_MEMBER_APPLY_LIST,	// 帮派成员申请列表		C <-- S
	
	_MSG_GAME_END						= 7900,


	// php服务器 消息区间
	_MSG_PHP_BEGIN						= 7900,
	_MSG_PHP_PAY						= 8000,	// 充值消息
	_MSG_PHP_KICK						= 8001,	// php踢人
	_MSG_PHP_END						= 9000,

	// 关系服全部消息开始
	_MSG_RELATION_BEGIN						= 10000,

	// 关系服直接转发全服消息
	_MSG_RELATION_DIRCET_ALL_BEGIN			= 10000,
	_MSG_RELATION_DIRCET_ALL_END			= 12000,

	// 关系服直接转发其他服消息
	_MSG_RELATION_DIRCET_OTHER_BEGIN		= 12000,
	_MSG_RELATION_DIRCET_OTHER_END			= 15000,

	// 需要关系服处理消息
	_MSG_RELATION_PROCESS_BEGIN				= 15000,
	_MSG_RELATION_PROCESS_LOGIN				= 15001,	// 游戏服登陆到关系服
	_MSG_RELATION_PROCESS_ACTION			= 15002,	// 游戏服与关系服 通用操作action
	_MSG_RELATION_PROCESS_NEWCARD			= 15003,	// 新手卡消息
	_MSG_RELATION_PROCESS_ONLINE_INFO		= 15004,	// 更新角色在线信息
	_MSG_RELATION_PROCESS_SYN_SERVER		= 15005,	// 帮派处理消息
	_MSG_RELATION_PROCESS_REALY_DATABASE	= 15009,	// 中转数据库
	_MSG_RELATION_PROCESS_END				= 20000,
	
	// 关系服全部消息结束
	_MSG_RELATION_END						= 20000,

	// 跨服服务器处理消息
	_MSG_CROSS_BEGIN						= 20000,
	_MSG_CROSS_LOGIN						= 20001,	// 关系服登录跨服服务器消息
	_MSG_CROSS_ACTION						= 20002,	// action		
	_MSG_CROSS_REALY_DATABASE				= 20003,	// 跨服中转数据库
	_MSG_CROSS_END							= 30000,
};

// 踢出原因
enum KICK_REASON
{
	KICK_REASON_DEFAULT					= 0,	// 踢出默认值, 一般不要用这个值
	KICK_REASON_PASSWORD_ERROR			= 1,	// 密码错误
	KICK_REASON_BE_KICK_ANOTHER			= 2,	// 被别人踢
	KICK_REASON_RELATION_SERVER			= 3,	// 关系服务器指示你被踢了
	KICK_REASON_FULL					= 4,	// 人太多
	KICK_REASON_SYSTEM					= 5,	// 服务器控制面板踢人 或 GM踢人	
	KICK_REASON_NOT_ALLOW				= 6,	// 服务器未开启登陆允许
	KICK_REASON_GM_MAC_ERROR			= 7,	// GM工具Mac地址验证错误		
	KICK_REASON_CHECK_SPEED_TOO_FAST	= 8,	// 检测速度过快					**
	KICK_REASON_GMCMD					= 9,	// GM命令踢自己	
	KICK_REASON_LOGIN_TIMEOUT			= 10,	// 登陆过程超时
	KICK_REASON_ACCOUNT_STOP_BYTIME		= 11,	// 账号临时封停
	KICK_REASON_ACCOUNT_STOP_FOREVER	= 12,	// 账号永久封停

};


// 配置表类型字段, 有新增可配置的数据即可新增进来, 记得写好这里的注释和数据库comment字段
enum CONFIG_TYPE
{
	CONFIGTYPE_NONE																= 0,


	CONFIGTYPE_USER_TALK_TIME_LIMIT_PRIVATE										= 1,				// 聊天限时, 私聊限制
	CONFIGTYPE_USER_TALK_TIME_LIMIT_SYNDICATE									= 2,				// 聊天限时, 帮派限制
	CONFIGTYPE_USER_TALK_TIME_LIMIT_WORLD										= 3,				// 聊天限时, 世界限制
	CONFIGTYPE_USER_TALK_LEV_LIMIT_WORLD										= 4,				// 聊天等级限制, 世界限制

	CONFIGTYPE_TALK_RECORD_LIMIT_PRIVATE										= 6,				// 聊天配置, 私聊记录上限
	CONFIGTYPE_TALK_RECORD_LIMIT_SYNDICATE										= 7,				// 聊天配置, 帮派聊天记录上限
	CONFIGTYPE_TALK_RECORD_LIMIT_WORLD											= 8,				// 聊天配置, 世界聊天记录上限

	CONFIGTYPE_SYNDICATE_CREATE_LIMIT_LEVEL										= 10,				// 创建帮派 需要玩家等级
	CONFIGTYPE_SYNDICATE_CREATE_LIMIT_VAS										= 11,				// 创建帮派 需要元宝
	CONFIGTYPE_SYNDICATE_ACTIVITY_LIMIT_SYNDICATE								= 12,				// 帮派活跃 帮派每日活跃上限
	CONFIGTYPE_SYNDICATE_ACTIVITY_LIMIT_MEMBER									= 13,				// 帮派活跃 成员每日活跃上限

	CONFIGTYPE_SYSTEM_POWER_RECOVER_INTERVAL									= 16,				// 体力恢复时间间隔

	CONFIGTYPE_SIGN_FIRST_OPEN_TIME												= 17,				// 每日签到第一次开启时间
	CONFIGTYPE_SIGN_SECOND_OPEN_TIME											= 18,				// 每日签到第二次开启时间
	CONFIGTYPE_SIGN_THIRD_OPEN_TIME												= 19,				// 每日签到第三次开启时间
	CONFIGTYPE_END,
};

// 配置文字表id声明
// 注意: 1. 转义符%左侧不能有全角符号 2.如果文字中需要百分号, 需要填写全角的百分号
enum CONFIG_TEXT_ID
{
	CONFIG_TEXT_ID_NONE															= 0,

	// 玩家属性相关配置
	CONFIG_TEXT_ID_USER_NOT_FIND_USER											= 2,		// 玩家不存在或不在线
	CONFIG_TEXT_ID_USER_TO_FAST													= 3,		// 发送消息过快
	CONFIG_TEXT_ID_USER_INVALID_INFO											= 4,		// 不合法的消息
	CONFIG_TEXT_ID_USER_LESS_LEV												= 5,		// 等级不够
	CONFIG_TEXT_ID_USER_LESS_VAS												= 6,		// 元宝不足
	CONFIG_TEXT_ID_USER_NEWEST_SERVER											= 7,		// 最新服务器
	CONFIG_TEXT_ID_USER_LOGINED_SERVER											= 8,		// 登录过服务器
	CONFIG_TEXT_ID_USER_ALL_SERVER												= 9,		// 全部服务器

	// 踢出提示
	CONFIG_TEXT_ID_KICK_REASON_DEFAULT											= 10,	// 被系统踢出
	CONFIG_TEXT_ID_KICK_REASON_PASSWORD_ERROR									= 11,	// 密码错误
	CONFIG_TEXT_ID_KICK_REASON_BE_KICK_ANOTHER									= 12,	// 在其他处登入
	CONFIG_TEXT_ID_KICK_REASON_RELATION_SERVER									= 13,	// 在其他地方登入
	CONFIG_TEXT_ID_KICK_REASON_FULL												= 14,	// 登入人数过多，登入失败
	CONFIG_TEXT_ID_KICK_REASON_SYSTEM											= 15,	// 被GM踢出
	CONFIG_TEXT_ID_KICK_REASON_NOT_ALLOW										= 16,	// 服务器入口未开放
	CONFIG_TEXT_ID_KICK_REASON_GM_MAC_ERROR										= 17,	// GM工具Mac地址验证错误		
	CONFIG_TEXT_ID_KICK_REASON_CHECK_SPEED_TOO_FAST								= 18,	// 系统将您踢出
	CONFIG_TEXT_ID_KICK_REASON_GMCMD											= 19,	// GM命令踢自己	
	CONFIG_TEXT_ID_KICK_REASON_LOGIN_TIMEOUT									= 20,	// 登陆超时
	CONFIG_TEXT_ID_KICK_REASON_ACCOUNT_STOP_BYTIME								= 21,	// 您的账号被临时封停，预计%d小时后解封
	CONFIG_TEXT_ID_KICK_REASON_ACCOUNT_STOP_FOREVER								= 22,	// 您的账号被永久封停

	// 帮派
	CONFIG_TEXT_ID_CREATESYN_ss													= 31,		// %s创建公会%s
	CONFIG_TEXT_ID_SYN_RANK_LEADER												= 32,      // 会长
	CONFIG_TEXT_ID_SYN_RANK_ELDER												= 33,      // 长老
	CONFIG_TEXT_ID_SYN_RANK_NORMAL												= 34,      // 成员

	// 队伍团队帮派相关
	CONFIG_TEXT_ID_GROUP_SYN_NOT_EXIST											= 35,		// 公会不存在

	// 帮派日志
	CONFIG_TEXT_ID_SYN_LOG_CREATE_SYN			= 41,		// 【%s】创建公会
	CONFIG_TEXT_ID_SYN_LOG_DIRECT_JOIN_SYN		= 42,		// 【%s】加入公会
	CONFIG_TEXT_ID_SYN_LOG_EXIT_SYN				= 43,		// 【%s】退出公会
	CONFIG_TEXT_ID_SYN_LOG_KICK_SYN				= 44,		// 公会%s【%s】将【%s】踢出了公会
	CONFIG_TEXT_ID_SYN_LOG_AlTER_NOTICE			= 45,		// 公会%s【%s】修改了公会公告
	CONFIG_TEXT_ID_SYN_LOG_UP_ELDER				= 46,		// 会长【%s】将【%s】提升为长老
	CONFIG_TEXT_ID_SYN_LOG_DOWN_MEMBER			= 47,		// 会长【%s】取消了【%s】的长老职位
	CONFIG_TEXT_ID_SYN_LOG_RESET_INSTANCE 		= 48,		// 公会%s【%s】重置了团队副本：第%d章
	CONFIG_TEXT_ID_SYN_LOG_PASS_INSTANCE  		= 49,		// 团队副本:第%d章通关,最后一击由【%s】完成
	CONFIG_TEXT_ID_SYN_LOG_TRANSFER_LEADER		= 50,		// 【%s】将会长职位移交给了【%s】
	CONFIG_TEXT_ID_SYN_LOG_TROPHY_QUEUE			= 51,		// 【%s】在战利品%s的队列中插队
	CONFIG_TEXT_ID_SYN_LOG_AGREE_JOIN_SYN		= 52,		// 公会%s【%s】批准了【%s】加入公会
	CONFIG_TEXT_ID_SYN_LOG_ALTER_LEV_LIMIT		= 53,		// 公会%s【%s】修改了加入公会最小战队等级为：%d级
	CONFIG_TEXT_ID_SYN_LOG_SHARE_TROPHY			= 54,		// 公会%s【%s】将%s分配给了【%s】
	CONFIG_TEXT_ID_SYN_LOG_ALTER_NEED_CHECK		= 55,		// 公会%s【%s】修改了公会类型为：需验证
	CONFIG_TEXT_ID_SYN_LOG_ALTER_NO_CHECK		= 56,		// 公会%s【%s】修改了公会类型为：不需要验证
	CONFIG_TEXT_ID_SYN_LOG_AUTO_TRANSFER_LEADER = 57,		// 会长【%s】长时间未上线，会长职位自动禅让给【%s】

	CONFIG_TEXT_ID_NOT_CHOOSE_SERVER			= 71,		// 请先选择服务器
	CONFIG_TEXT_ID_NOT_GAME_SERVER				= 72,		// 没有游戏服可以连接
	CONFIG_TEXT_ID_CONNECT_GAME_SERVER_FAILED	= 73,		// 游戏服务器连接失败

	CONFIG_TEXT_ID_CREATE_FAILED				= 74,		// 角色创建失败！
	CONFIG_TEXT_ID_NAME_CHECK_ERROR				= 75,		// 名字中包含非法字符！
	CONFIG_TEXT_ID_STRING_CHECK_ERROR			= 76,		// 非法字符！(客户端词库拦截)
	CONFIG_TEXT_ID_NAME_REPEAT					= 77,		// 重复的角色名
	CONFIG_TEXT_ID_CAN_NOT_MORE_PLAYER			= 78,		// 无法创建更多的角色！
	CONFIG_TEXT_ID_OPERATOR_FAILED				= 79,		// 操作失败！
	CONFIG_TEXT_ID_UNKNOW_ACTION				= 80,		// 未知的操作类型！
	CONFIG_TEXT_ID_PACKAGE_NOT_ENOUGH			= 81,		// 背包空间不足！
	CONFIG_TEXT_ID_VAS_NOT_ENOUGH				= 82,		// 元宝不足！
	CONFIG_TEXT_ID_NEED_ITEMTYPE_ds				= 83,		// 需要%d个%s
	CONFIG_TEXT_ID_RECONNECT_START				= 84,		// 开始自动重连
	CONFIG_TEXT_ID_RECONNECT_SUCCESS			= 85,		// 重连成功
	CONFIG_TEXT_ID_RECONNECT_FAILED				= 86,		// 重连失败


	CONFIG_TEXT_ID_no_magic						= 90,		// 啥也不会
	CONFIG_TEXT_ID_no_magic_text				= 91,		// 奴家真的啥也不会啦啦
	
	CONFIG_TEXT_ID_END,
};

// 帮派成员等级
enum SYN_RANK_TYPE
{
	RANK_LEADER			= 3,	// 会长
	RANK_ELDER			= 2,	// 长老
	RANK_NORMAL			= 1,	// 成员
	RANK_NONE			= 0,	// 		
};


// 账号类型
enum ACCOUNT_TYPE
{
	ACCOUNT_TYPE_NORMAL		= 0,	// 正常账号
	ACCOUNT_TYPE_GM_LOW		= 1,	// GM低级别账号
	ACCOUNT_TYPE_GM_HI		= 2,	// GM高级别账号
};

// 账号状态
enum ACCOUNT_STATUS
{
	ACCOUNT_STATUS_NORMAL		= 0,	// 正常
	ACCOUNT_STATUS_STOP_BYTIME	= 1,	// 临时封停, 状态参数为解封utc时间
	ACCOUNT_STATUS_STOP_FOREVER = 2,	// 永久封停
};

enum USER_ATTR
{
	USER_ATTR_score,		// 当前战力
	USER_ATTR_score_max,	// 最大战力

	USER_ATTR_fight_index,	// 出战编号
	USER_ATTR_atk,			// 当前阵容 - 先攻
	USER_ATTR_def,			// 当前阵容 - 防御
	USER_ATTR_dodge,		// 当前阵容 - 闪避
	USER_ATTR_king,			// 当前阵容 - 王者

	USER_ATTR_end,
};

// 货币类型
enum USER_MONEY_TYPE
{
	USER_MONEY_TYPE_NONE			= 0,
	USER_MONEY_TYPE_BEGIN			= 100,
	USER_MONEY_TYPE_material_ore1,		// 资源 - 矿石	1-5		对应原版绿色
	USER_MONEY_TYPE_material_ore2,
	USER_MONEY_TYPE_material_ore3,
	USER_MONEY_TYPE_material_ore4,
	USER_MONEY_TYPE_material_ore5,
	USER_MONEY_TYPE_material_gem1,		// 资源 - 宝石 1-5		对应原版蓝色
	USER_MONEY_TYPE_material_gem2,
	USER_MONEY_TYPE_material_gem3,
	USER_MONEY_TYPE_material_gem4,
	USER_MONEY_TYPE_material_gem5,
	USER_MONEY_TYPE_material_soul1,		// 资源 - 魂石 1 - 5	对应原版紫色
	USER_MONEY_TYPE_material_soul2,
	USER_MONEY_TYPE_material_soul3,
	USER_MONEY_TYPE_material_soul4,
	USER_MONEY_TYPE_material_soul5,	
	USER_MONEY_TYPE_material_statue,	// 资源	- 雕像			对应原版金色
	USER_MONEY_TYPE_material_adva1,		// 资源 - 高级资源1
	USER_MONEY_TYPE_material_adva2,		// 资源 - 高级资源2

	USER_MONEY_TYPE_poker_chip,			// 碎片

	// 旷工道具也认为是特殊货币
	USER_MONEY_TYPE_materialitem_package,	// 矿工包
	USER_MONEY_TYPE_materialitem_ore,		// 低级矿石资源包
	USER_MONEY_TYPE_materialitem_gem,		// 中级矿石资源包
	USER_MONEY_TYPE_materialitem_soul,		// 高级矿石资源包
	USER_MONEY_TYPE_materialitem_bomb,		// 雷管

	USER_MONEY_TYPE_activity1,			// 活动货币1
	USER_MONEY_TYPE_activity2,			// 活动货币2
	USER_MONEY_TYPE_activity3,			// 活动货币3
	USER_MONEY_TYPE_activity4,			// 活动货币4
	USER_MONEY_TYPE_activity5,			// 活动货币5

	USER_MONEY_TYPE_ItemMaxBuy,		// 物品上限购买
	USER_MONEY_TYPE_PokerMaxBuy,	// 卡牌上限购买
	USER_MONEY_TYPE_ExploreMaxBuy,	// 探索上限购买
	USER_MONEY_TYPE_OreMaxBuy,		// 原矿上限购买
	USER_MONEY_TYPE_FriendPoint,	// 好友点数
	USER_MONEY_TYPE_KingBadge,		// 王者之章

	USER_MONEY_TYPE_END,

	USER_MONEY_TYPE_AUTO_BEGIN		= 500,
	USER_MONEY_TYPE_AUTO_MONEY,		// 钱
	USER_MONEY_TYPE_AUTO_EXP,		// 经验
	USER_MONEY_TYPE_AUTO_ORE,		// 原矿
	USER_MONEY_TYPE_AUTO_END,

	USER_MONEY_TYPE_VAS				= 998,	// 元宝,		实时读写账号库
};

// 经验等级类型
enum LEV_EXP_TYPE
{
	LEV_EXP_TYPE_STAR1 = 1,	// 星级1经验
	LEV_EXP_TYPE_STAR2 = 2,	// 星级2经验
	LEV_EXP_TYPE_STAR3 = 3,	// 星级3经验
	LEV_EXP_TYPE_STAR4 = 4,	// 星级4经验
	LEV_EXP_TYPE_STAR5 = 5,	// 星级5经验
};

// 主卡武器类型
enum BOSS_WEAPON_TYPE
{
	BOSS_WEAPON_TYPE_begin = 1,
	BOSS_WEAPON_TYPE_end = 11,
};


enum EUSERMASKTYPE					// 掩码类型
{
	EUMT_Begin = 0,
	EUMT_TaskMask = 1,	// 任务掩码
	EUMT_GiveMask = 2,	// 奖励掩码
	EUMT_DayMask = 3,	// 天掩码
	EUMT_WeekMask = 4,	// 周掩码
	EUMT_MonthMask = 5,	// 月掩码
	EUMT_End,
};


// 玩家掩码ID服务器占用声明, 策划使用掩码使用10W以上
enum E_USER_MASKID_PROGRAM
{
	//////////////////////////////////////////////////////////////////////////
	// 任务掩码
	EUMIP_MASK_begin = 10000,
	EUMIP_MASK_weapon,	// 武器获得掩码
	EUMIP_MASK_end,

	//////////////////////////////////////////////////////////////////////////
	// 奖励掩码
	EUMIP_DATA_begin = 20000,

	EUMIP_DATA_achievement_begin = 20002,
	EUMIP_DATA_achievement_arena_win1 = 20002,	// 竞技场1胜
	EUMIP_DATA_achievement_arena_win3,			// 竞技场3胜
	EUMIP_DATA_achievement_wa_kuang,			// 挖矿点数, 待处理
	EUMIP_DATA_achievement_friend_send_gift,	// 送礼次数
	EUMIP_DATA_achievement_friend_get_gift,		// 获礼次数
	EUMIP_DATA_achievement_strengthen,			// 强化点数
	EUMIP_DATA_achievement_upstar,				// 升星次数
	EUMIP_DATA_achievement_kill_boss,			// 弄死boss次数
	EUMIP_DATA_achievement_chip_total,			// 碎片总数
	EUMIP_DATA_achievement_arena_all_win,		// 竞技场总胜
	EUMIP_DATA_achievement_lottery_poker,		// 招募次数
	EUMIP_DATA_achievement_weapon_strengthen,	// 主角武器强化次数
	EUMIP_DATA_achievement_pass_progress,		// 关卡进度
	EUMIP_DATA_achievement_max_score,			// 最大战力
	EUMIP_DATA_achievement_end,

	EUMIP_DATA_end,

	//////////////////////////////////////////////////////////////////////////
	// 天掩码 按位
	EUMIP_DAY_BIT_begin = 30000,	
	EUMIP_DAY_BIT_SIGN,							// 每日签到
	EUMIP_DAY_BIT_Challenge_first_award,		// 每日挑战榜首次胜利额外奖励
	EUMIP_DAY_BIT_end,	

	//////////////////////////////////////////////////////////////////////////
	// 天掩码 记次
	EUMIP_DAY_COUNT_begin = 40000,
	EUMIP_DAY_COUNT_LotteryMoneyCount,			// 每日金币抽奖次数
	EUMIP_DAY_COUNT_world_rank_Count,			// 每日世界榜挑战次数
	EUMIP_DAY_COUNT_End,		

	//////////////////////////////////////////////////////////////////////////
	// 周掩码 按位
	EUMIP_WEEK_BIT_begin = 50000,
	EUMIP_WEEK_BIT_end,	

	//////////////////////////////////////////////////////////////////////////
	// 周掩码 记次
	EUMIP_WEEK_COUNT_begin = 60000,
	EUMIP_WEEK_COUNT_End,

	//////////////////////////////////////////////////////////////////////////
	// 月掩码 按位
	EUMIP_MONTH_BIT_begin = 70000,
	EUMIP_MONTH_BIT_end,

	//////////////////////////////////////////////////////////////////////////
	// 月掩码 记次
	EUMIP_MONTH_COUNT_begin = 80000,
	EUMIP_MONTH_COUNT_End,

	// 策划自定义掩码范围
	EUMIP_custom_MASK_begin			= 100000,		// 任务掩码
	EUMIP_custom_MASK_end			= 199999,
	EUMIP_custom_DATA_begin			= 200000,		// 奖励掩码
	EUMIP_custom_DATA_end			= 299999,
	EUMIP_custom_DAY_BIT_begin		= 300000,		// 天掩码 按位
	EUMIP_custom_DAY_BIT_end		= 399999,
	EUMIP_custom_DAY_COUNT_begin	= 400000,		// 天掩码 记次
	EUMIP_custom_DAY_COUNT_End		= 499999,
	EUMIP_custom_WEEK_BIT_begin		= 500000,		// 周掩码 按位
	EUMIP_custom_WEEK_BIT_end		= 599999,		
	EUMIP_custom_WEEK_COUNT_begin	= 600000,		// 周掩码 记次
	EUMIP_custom_WEEK_COUNT_End		= 699999,
	EUMIP_custom_MONTH_BIT_begin	= 700000,		// 月掩码 按位
	EUMIP_custom_MONTH_BIT_end		= 799999,
	EUMIP_custom_MONTH_COUNT_begin	= 800000,		// 月掩码 记次
	EUMIP_custom_MONTH_COUNT_End	= 899999,
};


// 卡牌属性
enum POKER_IMPORTANT_ATTR
{
	POKER_IMPORTANT_ATTR_atk = 1,
	POKER_IMPORTANT_ATTR_def,
	POKER_IMPORTANT_ATTR_dodge,
	POKER_IMPORTANT_ATTR_king,
};

// 魔法释放条件类型
enum MAGIC_CONDITION_TYPE
{
	MAGIC_CONDITION_TYPE_None = 0,
	MAGIC_CONDITION_TYPE_BigOwnerScoreRate,		// 大于己方战力万分比
	MAGIC_CONDITION_TYPE_SmallOwnerScoreRate,	// 小于己方战力万分比
	MAGIC_CONDITION_TYPE_BigEnemyScoreRate,		// 大于敌方战力万分比
	MAGIC_CONDITION_TYPE_SmallEnemyScoreRate,	// 小于敌方战力万分比
	MAGIC_CONDITION_TYPE_BigRound,				// 大于回合数
	MAGIC_CONDITION_TYPE_SmallRound,			// 小于回合数
};

// 魔法封印类型
enum MAGIC_SEAL_TYPE
{
	MAGIC_SEAL_TYPE_None = 0,
	MAGIC_SEAL_TYPE_BigRate,		// 封印技能触发概率 大于 多少的
	MAGIC_SEAL_TYPE_SmallRate,		// 封印技能触发概率 小于 多少的
};

// 魔法伤害类型
enum MAGIC_DAMAGE_TYPE
{
	MAGIC_DAMAGE_TYPE_None,					// 基础伤害
	MAGIC_DAMAGE_TYPE_OwnerNowScoreRate,	// 己方当前战力比率
	MAGIC_DAMAGE_TYPE_OwnerMaxScoreRate,	// 己方最大战力比率
	MAGIC_DAMAGE_TYPE_EnemyNowScoreRate,	// 敌方当前战力比率
	MAGIC_DAMAGE_TYPE_EnemyMaxScoreRate,	// 敌方最大战力比率
	MAGIC_DAMAGE_TYPE_OwnerLostScoreRate,	// 己方已损失战力比率
	MAGIC_DAMAGE_TYPE_EnemyLostScoreRate,	// 敌方已损失战力比率
};

// 魔法恢复类型
enum MAGIC_RECOVER_TYPE
{
	// 恢复当前战力
	MAGIC_RECOVER_TYPE_None,					// 按照本次攻击伤害
	MAGIC_RECOVER_TYPE_OwnerNowScoreRate,		// 己方当前战力比率
	MAGIC_RECOVER_TYPE_OwnerMaxScoreRate,		// 己方最大战力比率
	MAGIC_RECOVER_TYPE_EnemyNowScoreRate,		// 敌方当前战力比率
	MAGIC_RECOVER_TYPE_EnemyMaxScoreRate,		// 敌方最大战力比率
};

// 物品颜色
enum ITEMCOLOR
{
	ITEMCOLOR_NONE   = 0,
	ITEMCOLOR_WHITE  = 1,	// 白
	ITEMCOLOR_GREEN  = 2,	// 绿
	ITEMCOLOR_BLUE	 = 3,	// 蓝
	ITEMCOLOR_VIOLET = 4,	// 紫
	ITEMCOLOR_ORANGE = 5,	// 橙
};

// 物品monopoly 掩码
enum ITEMTYPE_MONOPOLY
{
	ITEMTYPE_MONOPOLY_NONE		  = 0x0000,
	ITEMTYPE_MONOPOLY_NEED_RECORD = 0x0001,		// 需要写库记录流向
	ITEMTYPE_MONOPOLY_MONEY		  = 0x0002,		// 其实就是货币 
};

enum E_USER_THING_TYPE
{
	E_USER_THING_TYPE_NONE,
	E_USER_THING_TYPE_MONEY,		// 货币
	E_USER_THING_TYPE_POKER,		// 卡牌
	E_USER_THING_TYPE_ITEM,			// 物品
};

// 商店类型
enum E_SHOP_TYPE
{
	E_SHOP_TYPE_NORMAL		= 0,	// 普通商城
	E_SHOP_TYPE_PVP			= 1,	// pvp兑换商店
};

// 活动类型
enum ACTIVITY_CONFIG_TYPE
{
	ACTIVITY_CONFIG_TYPE_none = 0,
	ACTIVITY_CONFIG_TYPE_lottery = 1,	// 限时抽卡活动	
};

// 战斗类型
enum E_BATTLE_TYPE
{
	E_BATTLE_TYPE_NONE = 0,
	E_BATTLE_TYPE_MONSTER,			// 怪物战斗
	E_BATTLE_TYPE_FRIENDLY,			// 玩家切磋
	E_BATTLE_TYPE_PVP_CHALLENGE,	// pvp挑战榜
	E_BATTLE_TYPE_PVP_WORLD,		// pvp世界榜
	E_BATTLE_TYPE_INSTANCE,			// 副本
	E_BATTLE_TYPE_SMELT,			// 矿区杂兵
};

// 怪物类型
enum MONSTER_TYPE
{
	MONSTER_TYPE_soldier_begin	= 200000,
	MONSTER_TYPE_soldier_end	= 210000,

	MONSTER_TYPE_boss_begin		= 210000,
	MONSTER_TYPE_boss_end		= 220000,
};

enum E_INSTANCE_MODE_TYPE				// 副本难度模式
{
	E_INSTANCE_MODE_TYPE_NONE,
	E_INSTANCE_MODE_TYPE_EASY,			// 简单
	E_INSTANCE_MODE_TYPE_NORMAL,		// 普通
	E_INSTANCE_MODE_TYPE_DIFFICULTY,	// 困难
};

#endif // end of _COMMON_ENUM_DEF_H_

