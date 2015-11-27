////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: ConstTableDefine.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////

#ifndef _JYP_CONST_TABLE_TYPE_HEADER_
#define _JYP_CONST_TABLE_TYPE_HEADER_

#include "../Global/GlobalEnumDef.h"
#include "ConfigPassword.h"

class ConstTable;

// 常量表索引类型
enum CONST_TABLE_INDEX_TYPE
{
	CONST_TABLE_INDEX_TYPE_none,
	CONST_TABLE_INDEX_TYPE_single,	// 单键表
	CONST_TABLE_INDEX_TYPE_double,	// 双键表
};

// 常量表字段结构体
struct ST_CONST_TABLE_FIELD
{
	FIELD_TYPE	eFieldType;			// 字段类型
	int32_t		nFieldEnum;			// 字段枚举值, 每个表单独声明
	char		pszFieldName[64];	// 字段名
};

//////////////////////////////////////////////////////////////////////////
// audio表
enum AUDIO
{
	AUDIO_id,
	AUDIO_preload,
	AUDIO_filename,
};

static const ST_CONST_TABLE_FIELD audioField[] =
{
	{FIELD_TYPE_int, AUDIO_id,			"id"},
	{FIELD_TYPE_int, AUDIO_preload,		"preload"},
	{FIELD_TYPE_str, AUDIO_filename,	"filename"}
};

// 骨骼配置
enum SPINE_TYPE
{
	SPINE_TYPE_type = 0,
	SPINE_TYPE_name,
	SPINE_TYPE_json,
	SPINE_TYPE_atlas,
	SPINE_TYPE_scale,
	SPINE_TYPE_preload,
	SPINE_TYPE_forever,
	SPINE_TYPE_action_idle,
	SPINE_TYPE_action_atk1,
	SPINE_TYPE_action_atk2,
	SPINE_TYPE_effect1,
	SPINE_TYPE_effect1_order,
	SPINE_TYPE_effect1_scale,
	SPINE_TYPE_effect2,
	SPINE_TYPE_effect2_order,
	SPINE_TYPE_effect2_scale,
};

static const ST_CONST_TABLE_FIELD spinetypeField[] = 
{
	{FIELD_TYPE_int, SPINE_TYPE_type,					"type"},
	{FIELD_TYPE_str, SPINE_TYPE_name,					"name"},
	{FIELD_TYPE_str, SPINE_TYPE_json,					"json"},
	{FIELD_TYPE_str, SPINE_TYPE_atlas,					"atlas"},
	{FIELD_TYPE_int, SPINE_TYPE_scale,					"scale"},
	{FIELD_TYPE_int, SPINE_TYPE_preload,				"preload"},
	{FIELD_TYPE_int, SPINE_TYPE_forever,				"forever"},
	{FIELD_TYPE_str, SPINE_TYPE_action_idle,			"action_idle"},
	{FIELD_TYPE_str, SPINE_TYPE_action_atk1,			"action_atk1"},
	{FIELD_TYPE_str, SPINE_TYPE_action_atk2,			"action_atk2"},
	{FIELD_TYPE_str, SPINE_TYPE_effect1,				"effect1" },
	{FIELD_TYPE_int, SPINE_TYPE_effect1_order,			"effect1_order" },
	{FIELD_TYPE_int, SPINE_TYPE_effect1_scale,			"effect1_scale" },
	{FIELD_TYPE_str, SPINE_TYPE_effect2,				"effect2" },
	{FIELD_TYPE_int, SPINE_TYPE_effect2_order,			"effect2_order" },
	{FIELD_TYPE_int, SPINE_TYPE_effect2_scale,			"effect2_scale" }
};								

// 常量配置表(与服务端同步)
enum CONFIG_DATA
{
	CONFIGDATA_TYPE = 0,			// typeid	uint
	CONFIGDATA_DATA,				// 数据		uint
	CONFIGDATA_COMMENT,				// 注释字段, 不加载内存
};

static const ST_CONST_TABLE_FIELD configdataField[] = 
{
	{ FIELD_TYPE_int, CONFIGDATA_TYPE,		"type" },
	{ FIELD_TYPE_int, CONFIGDATA_DATA,		"data" },
	{ FIELD_TYPE_str, CONFIGDATA_COMMENT,	"comment" }
};

// 可配置文字表(与服务端同步)
enum CONFIG_TEXT_DATA
{
	CONFIG_TEXT_DATA_ID = 0,	// id
	CONFIG_TEXT_DATA_TEXT = 1,	// 可配置文字
};

static const ST_CONST_TABLE_FIELD configtextField[] =
{
	{ FIELD_TYPE_int, CONFIG_TEXT_DATA_ID, "id" },
	{ FIELD_TYPE_str, CONFIG_TEXT_DATA_TEXT, "text" }
};

// 等级经验表
enum LEV_EXP
{
	LEV_EXP_type,
	LEV_EXP_lev,
	LEV_EXP_exp,
};

static const ST_CONST_TABLE_FIELD levexpField[] =
{
	{ FIELD_TYPE_int, LEV_EXP_type, "type" },
	{ FIELD_TYPE_int, LEV_EXP_lev, "lev" },
	{ FIELD_TYPE_int, LEV_EXP_exp, "exp" },
};


// 配方类型表
enum PEIFANG_TYPE_DATA
{
	PEIFANG_TYPE_DATA_ID,					// 配方ID				uint
	PEIFANG_TYPE_DATA_AWARD_ITEMTYPE,		// 获取物品TYPE			uint
	PEIFANG_TYPE_DATA_AWARD_ITEMNUM,		// 获取物品NUMBER		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE1,		// 消耗物品1TYPE		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM1,		// 消耗物品1NUMBER		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE2,		// 消耗物品2TYPE		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM2,		// 消耗物品2NUMBER		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE3,		// 消耗物品3TYPE		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM3,		// 消耗物品3NUMBER		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE4,		// 消耗物品4TYPE		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM4,		// 消耗物品4NUMBER		uint
	PEIFANG_TYPE_DATA_COST_MONEY_TYPE,		// 消耗货币类型			uint
	PEIFANG_TYPE_DATA_COST_PRICE,			// 消耗价格				uint
};

static const ST_CONST_TABLE_FIELD peifangtypeField[] =
{
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_ID,				"id"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_AWARD_ITEMTYPE,	"award_itemtype"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_AWARD_ITEMNUM,	"award_itemnum"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_SPEND_ITEMTYPE1, "spend_itemtype1"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_SPEND_ITEMNUM1,	"spend_itemnum1"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_SPEND_ITEMTYPE2, "spend_itemtype2"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_SPEND_ITEMNUM2,	"spend_itemnum2"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_SPEND_ITEMTYPE3, "spend_itemtype3"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_SPEND_ITEMNUM3,	"spend_itemnum3"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_SPEND_ITEMTYPE4, "spend_itemtype4"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_SPEND_ITEMNUM4,	"spend_itemnum4"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_COST_MONEY_TYPE, "cost_money_type"},
	{FIELD_TYPE_int, PEIFANG_TYPE_DATA_COST_PRICE,		"cost_price"}
};


// 帧动画类型表
enum FRAME_ANIMATE_DATA
{
	FRAME_ANIMATE_DATA_id,				// id							uint
	FRAME_ANIMATE_DATA_frame_name,		// 帧文件前缀					varchar32
	FRAME_ANIMATE_DATA_frame_beg,		// 开始帧						uint
	FRAME_ANIMATE_DATA_frame_end,		// 结束帧						uint
	FRAME_ANIMATE_DATA_frame_time,		// 帧的间隔时间(ms)				uint
	FRAME_ANIMATE_DATA_loops,			// 动画播放次数(0为无限循环)	uint
	FRAME_ANIMATE_DATA_end_restore,		// 播放结束后是否回到初始帧		uint
	FRAME_ANIMATE_DATA_scale,			// 帧的缩放倍数(10000=1.0倍)	uint
	FRAME_ANIMATE_DATA_delay_start,		// 延时播放(ms)					uint
	FRAME_ANIMATE_DATA_limit_execute,	// 播放时限(ms)-->[不包含延时]	uint
};

static const ST_CONST_TABLE_FIELD frameanimateField[] =
{
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_id, "id"},
	{FIELD_TYPE_str, FRAME_ANIMATE_DATA_frame_name, "frame_name"},
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_frame_beg, "frame_beg"},
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_frame_end, "frame_end"},
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_frame_time, "frame_time"},
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_loops, "loops"},
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_end_restore, "end_restore"},
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_scale, "scale"},
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_delay_start, "delay_start"},
	{FIELD_TYPE_int, FRAME_ANIMATE_DATA_limit_execute, "limit_execute"},
};

// 服务器列表表
enum SERVER_LIST_DATA
{
	SERVER_LIST_DATA_id,		// id							uint
	SERVER_LIST_DATA_short_name,// 短服务器名					varchar
	SERVER_LIST_DATA_name,		// 服务器名						varchar
	SERVER_LIST_DATA_ip,		// 入口服ip						varchar
	SERVER_LIST_DATA_port,		// 入口服端口					uint
	SERVER_LIST_DATA_open,		// 服务器是否开启				uint
	SERVER_LIST_DATA_see,		// 该服务器是否在列表可见		uint
	SERVER_LIST_DATA_debug,		// 该服务器是否只在调试可见		uint
	SERVER_LIST_DATA_explain,	// 服务器解释文字				varchar32
};

static const ST_CONST_TABLE_FIELD serverlistField[] =
{
	{ FIELD_TYPE_int, SERVER_LIST_DATA_id, "id" },
	{ FIELD_TYPE_str, SERVER_LIST_DATA_short_name, "short_name" },
	{ FIELD_TYPE_str, SERVER_LIST_DATA_name, "name" },
	{ FIELD_TYPE_str, SERVER_LIST_DATA_ip, "ip" },
	{ FIELD_TYPE_int, SERVER_LIST_DATA_port, "port" },
	{ FIELD_TYPE_int, SERVER_LIST_DATA_open, "open" },
	{ FIELD_TYPE_int, SERVER_LIST_DATA_see, "see" },
	{ FIELD_TYPE_int, SERVER_LIST_DATA_debug, "debug" },
	{ FIELD_TYPE_str, SERVER_LIST_DATA_explain, "explain" }
};

// 卡牌类型表
enum POKER_TYPE_DATA
{
	POKER_TYPE_DATA_type = 0,			// 类型				uint			1为主卡  1000以后为正常卡
	POKER_TYPE_DATA_name,				// 名字				varchar50
	POKER_TYPE_DATA_color,				// 颜色				uint
	POKER_TYPE_DATA_max_star,			// 最大星级			uint
	POKER_TYPE_DATA_grow,				// 成长				uint
	POKER_TYPE_DATA_base_score,			// 基础成长			uint
	POKER_TYPE_DATA_magic1,				// 魔法1			uint
	POKER_TYPE_DATA_magic2,				// 魔法2			uint
	POKER_TYPE_DATA_magic3,				// 魔法3			uint
	POKER_TYPE_DATA_equip_atk,			// 宝具先攻			int			可正可负
	POKER_TYPE_DATA_equip_def,			// 宝具防御			int			可正可负
	POKER_TYPE_DATA_equip_dodge,		// 宝具闪避			int			可正可负
	POKER_TYPE_DATA_equip_king,			// 宝具王者			int			可正可负
	POKER_TYPE_DATA_resolve_price,		// 分解价格			uint		0不可分解
	POKER_TYPE_DATA_lottery_weight,		// 抽奖池权重		uint		0该抽奖池不抽
	POKER_TYPE_DATA_holy_base_price,	// 神殿起点价格		uint		0神殿不出现
	POKER_TYPE_DATA_spine_type,			// 模型表type		uint
	POKER_TYPE_DATA_equip_icon,			// 宝具icon			uint
	POKER_TYPE_DATA_equip_name,			// 宝具名字			varchar50
	POKER_TYPE_DATA_equip_text,			// 宝具说明			varchar511
	POKER_TYPE_DATA_explain,			// 说明				varchar511
};

static const ST_CONST_TABLE_FIELD pokertypeField[] =
{
	{ FIELD_TYPE_int, POKER_TYPE_DATA_type, "type" },
	{ FIELD_TYPE_str, POKER_TYPE_DATA_name, "name" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_color, "color" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_max_star, "max_star" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_grow, "grow" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_base_score, "base_score" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_magic1, "magic1" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_magic2, "magic2" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_magic3, "magic3" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_equip_atk, "equip_atk" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_equip_def, "equip_def" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_equip_dodge, "equip_dodge" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_equip_king, "equip_king" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_resolve_price, "resolve_price" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_lottery_weight, "lottery_weight" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_holy_base_price, "holy_base_price" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_spine_type, "spine_type" },
	{ FIELD_TYPE_int, POKER_TYPE_DATA_equip_icon, "equip_icon" },
	{ FIELD_TYPE_str, POKER_TYPE_DATA_equip_name, "equip_name" },
	{ FIELD_TYPE_str, POKER_TYPE_DATA_equip_text, "equip_text" },
	{ FIELD_TYPE_str, POKER_TYPE_DATA_explain, "explain" }
};

enum POKER_STRENGTHEN_TYPE_DATA
{
	POKER_STRENGTHEN_TYPE_DATA_lev = 0,		// 强化等级
	POKER_STRENGTHEN_TYPE_DATA_effect,		// 效果值	万分比
	POKER_STRENGTHEN_TYPE_DATA_percent,		// 成功概率	万分比
	POKER_STRENGTHEN_TYPE_DATA_ore1,		// 需求材料 开始
	POKER_STRENGTHEN_TYPE_DATA_ore2,
	POKER_STRENGTHEN_TYPE_DATA_ore3,
	POKER_STRENGTHEN_TYPE_DATA_ore4,
	POKER_STRENGTHEN_TYPE_DATA_ore5,
	POKER_STRENGTHEN_TYPE_DATA_gem1,
	POKER_STRENGTHEN_TYPE_DATA_gem2,
	POKER_STRENGTHEN_TYPE_DATA_gem3,
	POKER_STRENGTHEN_TYPE_DATA_gem4,
	POKER_STRENGTHEN_TYPE_DATA_gem5,
	POKER_STRENGTHEN_TYPE_DATA_soul1,
	POKER_STRENGTHEN_TYPE_DATA_soul2,
	POKER_STRENGTHEN_TYPE_DATA_soul3,
	POKER_STRENGTHEN_TYPE_DATA_soul4,
	POKER_STRENGTHEN_TYPE_DATA_soul5,
	POKER_STRENGTHEN_TYPE_DATA_statue,
	POKER_STRENGTHEN_TYPE_DATA_adva1,
	POKER_STRENGTHEN_TYPE_DATA_adva2,		// 需求材料 结束
};

static const ST_CONST_TABLE_FIELD pokerstrengthentypeField[] = 
{
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_lev, "lev" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_effect, "effect" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_percent, "percent" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_ore1, "ore1" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_ore2, "ore2" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_ore3, "ore3" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_ore4, "ore4" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_ore5, "ore5" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_gem1, "gem1" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_gem2, "gem2" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_gem3, "gem3" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_gem4, "gem4" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_gem5, "gem5" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_soul1, "soul1" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_soul2, "soul2" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_soul3, "soul3" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_soul4, "soul4" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_soul5, "soul5" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_statue, "statue" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_adva1, "adva1" },
	{ FIELD_TYPE_int, POKER_STRENGTHEN_TYPE_DATA_adva2, "adva2" }
};

// 强化增加概率价格表
enum STRENGTHEN_SUCC_TYPE_DATA
{
	STRENGTHEN_SUCC_TYPE_DATA_add_percent = 0,		// 增加概率万分比	uint
	STRENGTHEN_SUCC_TYPE_DATA_price,				// 钻石价格			uint
};

static const ST_CONST_TABLE_FIELD strengthensuccField[] =
{
	{ FIELD_TYPE_int, STRENGTHEN_SUCC_TYPE_DATA_add_percent, "add_percent" },
	{ FIELD_TYPE_int, STRENGTHEN_SUCC_TYPE_DATA_price, "price" }
};

// 魔法配置表
enum MAGIC_TYPE_DATA
{
	MAGIC_TYPE_DATA_type = 0,			// 魔法类型			uint
	MAGIC_TYPE_DATA_name,				// 魔法名称			varchar50
	MAGIC_TYPE_DATA_need_pokertype1,	// 需要卡牌1		uint		如果单体技能就只需要一张卡, 需要多张卡牌的, 万位及以上标识数量, 万位0或1表示只需要一张
	MAGIC_TYPE_DATA_need_pokertype2,	// 需要卡牌2		uint		
	MAGIC_TYPE_DATA_need_pokertype3,	// 需要卡牌3		uint		
	MAGIC_TYPE_DATA_need_pokertype4,	// 需要卡牌4		uint		
	MAGIC_TYPE_DATA_need_pokertype5,	// 需要卡牌5		uint		
	MAGIC_TYPE_DATA_need_pokertype6,	// 需要卡牌6		uint		
	MAGIC_TYPE_DATA_passive_atk,		// 被动效果 先攻	uint
	MAGIC_TYPE_DATA_passive_def,		// 被动效果	防御	uint
	MAGIC_TYPE_DATA_passive_dodge,		// 被动效果	闪避	uint
	MAGIC_TYPE_DATA_passive_king,		// 被动效果	王者	uint
	MAGIC_TYPE_DATA_condition1_type,	// 触发条件1 类型	uint
	MAGIC_TYPE_DATA_condition1_data,	// 触发条件1 数值	uint
	MAGIC_TYPE_DATA_condition2_type,	// 触发条件2 类型	uint
	MAGIC_TYPE_DATA_condition2_data,	// 触发条件2 数值	uint
	MAGIC_TYPE_DATA_rate,				// 触发概率			uint
	MAGIC_TYPE_DATA_count,				// 触发次数			uint
	MAGIC_TYPE_DATA_damage_type,		// 伤害类型			uint
	MAGIC_TYPE_DATA_damage_data,		// 伤害数值			uint
	MAGIC_TYPE_DATA_addition_atk,		// 受先攻加成		uint
	MAGIC_TYPE_DATA_addition_def,		// 受防御加成		uint
	MAGIC_TYPE_DATA_addition_dodge,		// 受闪避加成		uint
	MAGIC_TYPE_DATA_addition_king,		// 受王者加成		uint
	MAGIC_TYPE_DATA_seal_type,			// 封印类型			uint
	MAGIC_TYPE_DATA_seal_data,			// 封印数值			uint
	MAGIC_TYPE_DATA_seal_except_data,	// 封印豁免值		uint
	MAGIC_TYPE_DATA_seal_weak_flag,		// 虚弱技能标记		uint
	MAGIC_TYPE_DATA_recover_type,		// 回复类型			uint
	MAGIC_TYPE_DATA_recover_data,		// 恢复数值			uint
	MAGIC_TYPE_DATA_icon,				// 图标编号			uint
	MAGIC_TYPE_DATA_detail,				// 技能说明			varchar255
};


static const ST_CONST_TABLE_FIELD magictypeField[] =
{
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_type, "type" },
	{ FIELD_TYPE_str, MAGIC_TYPE_DATA_name, "name" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_need_pokertype1, "need_pokertype1" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_need_pokertype2, "need_pokertype2" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_need_pokertype3, "need_pokertype3" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_need_pokertype4, "need_pokertype4" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_need_pokertype5, "need_pokertype5" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_need_pokertype6, "need_pokertype6" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_passive_atk, "passive_atk" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_passive_def, "passive_def" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_passive_dodge, "passive_dodge" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_passive_king, "passive_king" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_condition1_type, "condition1_type" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_condition1_data, "condition1_data" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_condition2_type, "condition2_type" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_condition2_data, "condition2_data" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_rate, "rate" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_count, "count" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_damage_type, "damage_type" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_damage_data, "damage_data" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_addition_atk, "addition_atk" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_addition_def, "addition_def" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_addition_dodge, "addition_dodge" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_addition_king, "addition_king" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_seal_type, "seal_type" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_seal_data, "seal_data" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_seal_except_data, "seal_except_data" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_seal_weak_flag, "weak_flag" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_recover_type, "recover_type" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_recover_data, "recover_data" },
	{ FIELD_TYPE_int, MAGIC_TYPE_DATA_icon, "icon" },
	{ FIELD_TYPE_str, MAGIC_TYPE_DATA_detail, "detail" }
};

// 物品类型表
enum ITEM_TYPE_DATA
{
	ITEM_TYPE_DATA_ID = 0,			// 类型				uint
	ITEM_TYPE_DATA_NAME,			// 名字				vchar
	ITEM_TYPE_DATA_COLOR,			// 颜色				uint
	ITEM_TYPE_DATA_ACTION,			// action			uint
	ITEM_TYPE_DATA_MONOPOLY,		// monopoly			uint
	ITEM_TYPE_DATA_DATA,			// 数据				uint
	ITEM_TYPE_DATA_ICON,			// 图标编号			uint
	ITEM_TYPE_DATA_SPINE_NAME,		// spine中附件名	varchar50
	ITEM_TYPE_DATA_DETAIL,			// 详细描述			varchar512
	ITEM_TYPE_DATA_END,
};

static const ST_CONST_TABLE_FIELD itemtypeField[] =
{
	{ FIELD_TYPE_int, ITEM_TYPE_DATA_ID, "type_id" },
	{ FIELD_TYPE_str, ITEM_TYPE_DATA_NAME, "name" },
	{ FIELD_TYPE_int, ITEM_TYPE_DATA_COLOR, "color" },
	{ FIELD_TYPE_int, ITEM_TYPE_DATA_ACTION, "action" },
	{ FIELD_TYPE_int, ITEM_TYPE_DATA_MONOPOLY, "monopoly" },
	{ FIELD_TYPE_int, ITEM_TYPE_DATA_DATA, "data" },
	{ FIELD_TYPE_int, ITEM_TYPE_DATA_ICON, "icon" },
	{ FIELD_TYPE_str, ITEM_TYPE_DATA_SPINE_NAME, "spine_name" },
	{ FIELD_TYPE_str, ITEM_TYPE_DATA_DETAIL, "detail" },
};

// 商城配置表
enum SHOP_GOODS_DATA
{
	SHOP_GOODS_DATA_ID = 0,			// id				uint
	SHOP_GOODS_DATA_SHOP_TYPE,		// 商店类型			uint
	SHOP_GOODS_DATA_GOODS_TYPE,		// 商品类型			uint
	SHOP_GOODS_DATA_GOODS_NUM,		// 商品数量			uint
	SHOP_GOODS_DATA_SPEND_TYPE1,	// 购买花费类型1	uint
	SHOP_GOODS_DATA_SPEND_NUM1,		// 购买花费数量1	uint
	SHOP_GOODS_DATA_SPEND_TYPE2,	// 购买花费类型2	uint
	SHOP_GOODS_DATA_SPEND_NUM2,		// 购买花费数量2	uint
};

static const ST_CONST_TABLE_FIELD shopGoodsField[] =
{
	{ FIELD_TYPE_int, SHOP_GOODS_DATA_ID, "id" },
	{ FIELD_TYPE_int, SHOP_GOODS_DATA_SHOP_TYPE, "shop_type" },
	{ FIELD_TYPE_int, SHOP_GOODS_DATA_GOODS_TYPE, "goods_type" },
	{ FIELD_TYPE_int, SHOP_GOODS_DATA_GOODS_NUM, "goods_num" },
	{ FIELD_TYPE_int, SHOP_GOODS_DATA_SPEND_TYPE1, "spend_type1" },
	{ FIELD_TYPE_int, SHOP_GOODS_DATA_SPEND_NUM1, "spend_num1" },
	{ FIELD_TYPE_int, SHOP_GOODS_DATA_SPEND_TYPE2, "spend_type2" },
	{ FIELD_TYPE_int, SHOP_GOODS_DATA_SPEND_NUM2, "spend_num2" },
};

// 名字库
enum NAME_LIBRARY_DATA
{
	NAME_LIBRARY_DATA_ID = 0,		// id		uint
	NAME_LIBRARY_DATA_NAME,			// 名字		varchar32
};

static const ST_CONST_TABLE_FIELD namelibraryField[] =
{
	{ FIELD_TYPE_int, NAME_LIBRARY_DATA_ID, "id" },
	{ FIELD_TYPE_str, NAME_LIBRARY_DATA_NAME, "name" },
};

// 冶炼温度表
enum SMELT_TEMP_TYPE_DATA
{
	SMELT_TEMP_TYPE_DATA_temp = 0,		// 温度		uint
	SMELT_TEMP_TYPE_DATA_time_base,		// 耗时基数	uint
	SMELT_TEMP_TYPE_DATA_monster_rate,	// 遇怪概率	uint
	SMELT_TEMP_TYPE_DATA_empty,			// 产出权重			uint
	SMELT_TEMP_TYPE_DATA_ore1,			// 原矿1 产出权重	uint
	SMELT_TEMP_TYPE_DATA_ore2,
	SMELT_TEMP_TYPE_DATA_ore3,
	SMELT_TEMP_TYPE_DATA_ore4,
	SMELT_TEMP_TYPE_DATA_ore5,
	SMELT_TEMP_TYPE_DATA_gem1,			// 宝石1 产出权重	uint
	SMELT_TEMP_TYPE_DATA_gem2,
	SMELT_TEMP_TYPE_DATA_gem3,
	SMELT_TEMP_TYPE_DATA_gem4,
	SMELT_TEMP_TYPE_DATA_gem5,
	SMELT_TEMP_TYPE_DATA_soul1,			// 精魂1 产出权重	uint
	SMELT_TEMP_TYPE_DATA_soul2,
	SMELT_TEMP_TYPE_DATA_soul3,
	SMELT_TEMP_TYPE_DATA_soul4,
	SMELT_TEMP_TYPE_DATA_soul5,
	SMELT_TEMP_TYPE_DATA_statue,		// 雕像 产出权重	uint
	SMELT_TEMP_TYPE_DATA_adva1,			// 地狱 产出权重	uint
	SMELT_TEMP_TYPE_DATA_adva2,			// 时间 产出权重	uint
	SMELT_TEMP_TYPE_DATA_up0,			// 升温0权重		uint
	SMELT_TEMP_TYPE_DATA_up10,
	SMELT_TEMP_TYPE_DATA_up20,
	SMELT_TEMP_TYPE_DATA_up40,
	SMELT_TEMP_TYPE_DATA_up60,
	SMELT_TEMP_TYPE_DATA_up80,
};

static const ST_CONST_TABLE_FIELD smelttempField[] =
{
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_temp, "temp" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_time_base, "time_base" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_monster_rate, "monster_rate" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_empty, "empty" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_ore1, "monster_ore1" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_ore2, "monster_ore2" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_ore3, "monster_ore3" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_ore4, "monster_ore4" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_ore5, "monster_ore5" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_gem1, "monster_gem1" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_gem2, "monster_gem2" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_gem3, "monster_gem3" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_gem4, "monster_gem4" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_gem5, "monster_gem5" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_soul1, "monster_soul1" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_soul2, "monster_soul2" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_soul3, "monster_soul3" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_soul4, "monster_soul4" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_soul5, "monster_soul5" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_statue, "monster_statue" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_adva1, "monster_adva1" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_adva2, "monster_adva2" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_up0, "up0" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_up10, "up10" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_up20, "up20" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_up40, "up40" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_up60, "up60" },
	{ FIELD_TYPE_int, SMELT_TEMP_TYPE_DATA_up80, "up80" },
};

// 冶炼原矿表
enum SMELT_ORE_TYPE_DATA
{
	SMELT_ORE_TYPE_DATA_ore = 0,		// 原矿数量	uint
	SMELT_ORE_TYPE_DATA_time_param,		// 时间参数	uint
	SMELT_ORE_TYPE_DATA_monster_param,	// 遇怪参数	uint
};

static const ST_CONST_TABLE_FIELD smeltoreField[] =
{
	{ FIELD_TYPE_int, SMELT_ORE_TYPE_DATA_ore, "ore" },
	{ FIELD_TYPE_int, SMELT_ORE_TYPE_DATA_time_param, "time_param" },
	{ FIELD_TYPE_int, SMELT_ORE_TYPE_DATA_monster_param, "monster_param" },
};

// 冶炼加速表
enum SMELT_SPEEDUP_DATA
{
	SMELT_SPEEDUP_DATA_left_second = 0,		// 剩余时间	uint
	SMELT_SPEEDUP_DATA_need_bomb,			// 需要炸弹	uint
};
static const ST_CONST_TABLE_FIELD smeltspeedupField[] =
{
	{ FIELD_TYPE_int, SMELT_SPEEDUP_DATA_left_second, "left_second" },
	{ FIELD_TYPE_int, SMELT_SPEEDUP_DATA_need_bomb, "need_bomb" },
};

// 副本配置表
enum INSTANCE_DATA
{
	INSTANCE_DATA_ID = 0,						// id(mode * 10000 + chapter * 1000 + pass)				uint
	INSTANCE_DATA_MODE,							// 模式				uint
	INSTANCE_DATA_CHAPTER,						// 章节				uint
	INSTANCE_DATA_PASS,							// 关卡				uint
	INSTANCE_DATA_OPEN_SCORE,					// 开放战力			uint
	INSTANCE_DATA_INIT_COST_MONEY,				// 初始消耗金币		uint
	INSTANCE_DATA_AUTO_ADD_MONEY,				// 每秒自动增加金币	uint
	INSTANCE_DATA_AUTO_ADD_EXP,					// 每秒自动增加经验	uint
	INSTANCE_DATA_FIGHT_WAITING_TIME,			// 战斗等待时间		uint
	INSTANCE_DATA_FIGHT_AWARD_ACTION,			// 战斗奖励action	uint
	INSTANCE_DATA_SEARCHING_INIT_TIME,			// 探索初始时间		uint
	INSTANCE_DATA_SEARCHING_TIME,				// 探索时间			uint
	INSTANCE_DATA_SEARCHING_AWARD_ACTION,		// 探索奖励action	uint
	INSTANCE_DATA_MONSTER_ID,					// 怪物id			uint
	INSTANCE_DATA_CHAPTER_NAME,					// 章节名字			varchar32
	INSTANCE_DATA_CHAPTER_CSB_NAME,				// 章节csb名字（客户端）varchar32
	INSTANCE_DATA_CHAPTER_DETAIL,				// 章节说明			varchar256
	INSTANCE_DATA_DROP_POKER_TYPE1,				// 掉落卡牌类型1	uint
	INSTANCE_DATA_DROP_POKER_TYPE2,				// 掉落卡牌类型2	uint
	INSTANCE_DATA_DROP_POKER_TYPE3,				// 掉落卡牌类型3	uint
};

static const ST_CONST_TABLE_FIELD instanceField[] =
{
	{ FIELD_TYPE_int, INSTANCE_DATA_ID, "id" },
	{ FIELD_TYPE_int, INSTANCE_DATA_MODE, "mode" },
	{ FIELD_TYPE_int, INSTANCE_DATA_CHAPTER, "chapter" },
	{ FIELD_TYPE_int, INSTANCE_DATA_PASS, "pass" },
	{ FIELD_TYPE_int, INSTANCE_DATA_OPEN_SCORE, "open_score" },
	{ FIELD_TYPE_int, INSTANCE_DATA_INIT_COST_MONEY, "init_cost_money" },
	{ FIELD_TYPE_int, INSTANCE_DATA_AUTO_ADD_MONEY, "auto_add_money" },
	{ FIELD_TYPE_int, INSTANCE_DATA_AUTO_ADD_EXP, "auto_add_exp" },
	{ FIELD_TYPE_int, INSTANCE_DATA_FIGHT_WAITING_TIME, "fight_waiting_time" },
	{ FIELD_TYPE_int, INSTANCE_DATA_FIGHT_AWARD_ACTION, "fight_award_action" },
	{ FIELD_TYPE_int, INSTANCE_DATA_SEARCHING_INIT_TIME, "searching_init_time" },
	{ FIELD_TYPE_int, INSTANCE_DATA_SEARCHING_TIME, "searching_time" },
	{ FIELD_TYPE_int, INSTANCE_DATA_SEARCHING_AWARD_ACTION, "searching_award_action" },
	{ FIELD_TYPE_int, INSTANCE_DATA_MONSTER_ID, "monster_id" },
	{ FIELD_TYPE_str, INSTANCE_DATA_CHAPTER_NAME, "chapter_name" },
	{ FIELD_TYPE_str, INSTANCE_DATA_CHAPTER_CSB_NAME, "chapter_csb_name" },
	{ FIELD_TYPE_str, INSTANCE_DATA_CHAPTER_DETAIL, "chapter_detail" },
	{ FIELD_TYPE_int, INSTANCE_DATA_DROP_POKER_TYPE1, "drop_poker_type1" },
	{ FIELD_TYPE_int, INSTANCE_DATA_DROP_POKER_TYPE2, "drop_poker_type2" },
	{ FIELD_TYPE_int, INSTANCE_DATA_DROP_POKER_TYPE3, "drop_poker_type3" },
};

// 冶炼加速表
enum MAIN_HINT_DATA
{
	MAIN_HINT_DATA_id = 0,		// id	uint
	MAIN_HINT_DATA_text,		// 文字 varchar
};
static const ST_CONST_TABLE_FIELD mainhintField[] =
{
	{ FIELD_TYPE_int, MAIN_HINT_DATA_id, "id" },
	{ FIELD_TYPE_str, MAIN_HINT_DATA_text, "text" },
};

//////////////////////////////////////////////////////////////////////////
// ********************** 以下内容放在本文件最后 ***********************//
//////////////////////////////////////////////////////////////////////////

// 常量表类型
enum CONST_TABLE_TYPE
{
	CONST_TABLE_TYPE_BEGIN = 0,
	CONST_TABLE_TYPE_audio = 0 ,
	CONST_TABLE_TYPE_spine_type,
	CONST_TABLE_TYPE_config,
	CONST_TABLE_TYPE_config_text,
	CONST_TABLE_TYPE_lev_exp,
	CONST_TABLE_TYPE_peifang_type,
	CONST_TABLE_TYPE_frame_animate,
	CONST_TABLE_TYPE_server_list,
	CONST_TABLE_TYPE_poker_type,
	CONST_TABLE_TYPE_poker_strengthen_type,
	CONST_TABLE_TYPE_strengthen_succ_type,
	CONST_TABLE_TYPE_magic_type,
	CONST_TABLE_TYPE_item_type,
	CONST_TABLE_TYPE_shop_goods,
	CONST_TABLE_TYPE_name_library,
	CONST_TABLE_TYPE_smelt_temp,
	CONST_TABLE_TYPE_smelt_ore,
	CONST_TABLE_TYPE_smelt_speedup,
	CONST_TABLE_TYPE_instance,
	CONST_TABLE_TYPE_main_hint,
	CONST_TABLE_TYPE_END
};

// 常量表信息
struct ST_CONST_TABLE_INFO
{
	CONST_TABLE_TYPE			eTableType;		// 表类型
	CONST_TABLE_INDEX_TYPE		eIndexType;		// 索引类型
	int32_t						nKeyIndex1;		// 第一个索引键序号
	int32_t						nKeyIndex2;		// 第二个索引键序号(单键表填0)
	char						pszFileName[64];// json文件名
	const ST_CONST_TABLE_FIELD*	pFieldInfo;		// 字段信息
	int32_t						nFieldCount;	// 字段信息个数
};

// 常量表信息
static const ST_CONST_TABLE_INFO CONST_TABLE_INFOS[] = 
{
	{ CONST_TABLE_TYPE_audio,					CONST_TABLE_INDEX_TYPE_single, 0, 0, "audio.csv",					audioField,					sizeof(audioField) / sizeof(ST_CONST_TABLE_FIELD)},
	{ CONST_TABLE_TYPE_spine_type,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "spine_type.csv",				spinetypeField,				sizeof(spinetypeField) / sizeof(ST_CONST_TABLE_FIELD)},
	{ CONST_TABLE_TYPE_config,					CONST_TABLE_INDEX_TYPE_single, 0, 0, "config.csv",					configdataField,			sizeof(configdataField) / sizeof(ST_CONST_TABLE_FIELD)},
	{ CONST_TABLE_TYPE_config_text,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "config_text.csv",				configtextField,			sizeof(configtextField) / sizeof(ST_CONST_TABLE_FIELD)},
	{ CONST_TABLE_TYPE_lev_exp,					CONST_TABLE_INDEX_TYPE_double, 0, 1, "lev_exp.csv",					levexpField,				sizeof(levexpField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_peifang_type,			CONST_TABLE_INDEX_TYPE_single, 0, 0, "peifang_type.csv",			peifangtypeField,			sizeof(peifangtypeField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_frame_animate,			CONST_TABLE_INDEX_TYPE_single, 0, 0, "frame_animate.csv",			frameanimateField,			sizeof(frameanimateField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_server_list,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "server_list.csv",				serverlistField,			sizeof(serverlistField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_poker_type,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "poker_type.csv",				pokertypeField,				sizeof(pokertypeField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_poker_strengthen_type,	CONST_TABLE_INDEX_TYPE_single, 0, 0, "poker_strengthen_type.csv",	pokerstrengthentypeField,	sizeof(pokerstrengthentypeField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_strengthen_succ_type,	CONST_TABLE_INDEX_TYPE_single, 0, 0, "strengthen_succ_type.csv",	strengthensuccField,		sizeof(strengthensuccField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_magic_type,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "magic_type.csv",				magictypeField,				sizeof(magictypeField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_item_type,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "item_type.csv",				itemtypeField,				sizeof(itemtypeField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_shop_goods,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "shop_goods.csv",				shopGoodsField,				sizeof(shopGoodsField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_name_library,			CONST_TABLE_INDEX_TYPE_single, 0, 0, "name_library.csv",			namelibraryField,			sizeof(namelibraryField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_smelt_temp,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "smelt_temp_type.csv",			smelttempField,				sizeof(smelttempField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_smelt_ore,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "smelt_ore_type.csv",			smeltoreField,				sizeof(smeltoreField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_smelt_speedup,			CONST_TABLE_INDEX_TYPE_single, 0, 0, "smelt_speedup.csv",			smeltspeedupField,			sizeof(smeltspeedupField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_instance,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "instance.csv",				instanceField,				sizeof(instanceField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_main_hint,				CONST_TABLE_INDEX_TYPE_single, 0, 0, "main_hint.csv",				mainhintField,				sizeof(mainhintField) / sizeof(ST_CONST_TABLE_FIELD) },
	{ CONST_TABLE_TYPE_END,	CONST_TABLE_INDEX_TYPE_none, 0, 0, ""}
};

#endif
