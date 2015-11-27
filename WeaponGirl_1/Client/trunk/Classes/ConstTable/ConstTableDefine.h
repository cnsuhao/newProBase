////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: ConstTableDefine.h
// Author: ������(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////

#ifndef _JYP_CONST_TABLE_TYPE_HEADER_
#define _JYP_CONST_TABLE_TYPE_HEADER_

#include "../Global/GlobalEnumDef.h"
#include "ConfigPassword.h"

class ConstTable;

// ��������������
enum CONST_TABLE_INDEX_TYPE
{
	CONST_TABLE_INDEX_TYPE_none,
	CONST_TABLE_INDEX_TYPE_single,	// ������
	CONST_TABLE_INDEX_TYPE_double,	// ˫����
};

// �������ֶνṹ��
struct ST_CONST_TABLE_FIELD
{
	FIELD_TYPE	eFieldType;			// �ֶ�����
	int32_t		nFieldEnum;			// �ֶ�ö��ֵ, ÿ����������
	char		pszFieldName[64];	// �ֶ���
};

//////////////////////////////////////////////////////////////////////////
// audio��
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

// ��������
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

// �������ñ�(������ͬ��)
enum CONFIG_DATA
{
	CONFIGDATA_TYPE = 0,			// typeid	uint
	CONFIGDATA_DATA,				// ����		uint
	CONFIGDATA_COMMENT,				// ע���ֶ�, �������ڴ�
};

static const ST_CONST_TABLE_FIELD configdataField[] = 
{
	{ FIELD_TYPE_int, CONFIGDATA_TYPE,		"type" },
	{ FIELD_TYPE_int, CONFIGDATA_DATA,		"data" },
	{ FIELD_TYPE_str, CONFIGDATA_COMMENT,	"comment" }
};

// ���������ֱ�(������ͬ��)
enum CONFIG_TEXT_DATA
{
	CONFIG_TEXT_DATA_ID = 0,	// id
	CONFIG_TEXT_DATA_TEXT = 1,	// ����������
};

static const ST_CONST_TABLE_FIELD configtextField[] =
{
	{ FIELD_TYPE_int, CONFIG_TEXT_DATA_ID, "id" },
	{ FIELD_TYPE_str, CONFIG_TEXT_DATA_TEXT, "text" }
};

// �ȼ������
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


// �䷽���ͱ�
enum PEIFANG_TYPE_DATA
{
	PEIFANG_TYPE_DATA_ID,					// �䷽ID				uint
	PEIFANG_TYPE_DATA_AWARD_ITEMTYPE,		// ��ȡ��ƷTYPE			uint
	PEIFANG_TYPE_DATA_AWARD_ITEMNUM,		// ��ȡ��ƷNUMBER		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE1,		// ������Ʒ1TYPE		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM1,		// ������Ʒ1NUMBER		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE2,		// ������Ʒ2TYPE		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM2,		// ������Ʒ2NUMBER		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE3,		// ������Ʒ3TYPE		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM3,		// ������Ʒ3NUMBER		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMTYPE4,		// ������Ʒ4TYPE		uint
	PEIFANG_TYPE_DATA_SPEND_ITEMNUM4,		// ������Ʒ4NUMBER		uint
	PEIFANG_TYPE_DATA_COST_MONEY_TYPE,		// ���Ļ�������			uint
	PEIFANG_TYPE_DATA_COST_PRICE,			// ���ļ۸�				uint
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


// ֡�������ͱ�
enum FRAME_ANIMATE_DATA
{
	FRAME_ANIMATE_DATA_id,				// id							uint
	FRAME_ANIMATE_DATA_frame_name,		// ֡�ļ�ǰ׺					varchar32
	FRAME_ANIMATE_DATA_frame_beg,		// ��ʼ֡						uint
	FRAME_ANIMATE_DATA_frame_end,		// ����֡						uint
	FRAME_ANIMATE_DATA_frame_time,		// ֡�ļ��ʱ��(ms)				uint
	FRAME_ANIMATE_DATA_loops,			// �������Ŵ���(0Ϊ����ѭ��)	uint
	FRAME_ANIMATE_DATA_end_restore,		// ���Ž������Ƿ�ص���ʼ֡		uint
	FRAME_ANIMATE_DATA_scale,			// ֡�����ű���(10000=1.0��)	uint
	FRAME_ANIMATE_DATA_delay_start,		// ��ʱ����(ms)					uint
	FRAME_ANIMATE_DATA_limit_execute,	// ����ʱ��(ms)-->[��������ʱ]	uint
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

// �������б��
enum SERVER_LIST_DATA
{
	SERVER_LIST_DATA_id,		// id							uint
	SERVER_LIST_DATA_short_name,// �̷�������					varchar
	SERVER_LIST_DATA_name,		// ��������						varchar
	SERVER_LIST_DATA_ip,		// ��ڷ�ip						varchar
	SERVER_LIST_DATA_port,		// ��ڷ��˿�					uint
	SERVER_LIST_DATA_open,		// �������Ƿ���				uint
	SERVER_LIST_DATA_see,		// �÷������Ƿ����б�ɼ�		uint
	SERVER_LIST_DATA_debug,		// �÷������Ƿ�ֻ�ڵ��Կɼ�		uint
	SERVER_LIST_DATA_explain,	// ��������������				varchar32
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

// �������ͱ�
enum POKER_TYPE_DATA
{
	POKER_TYPE_DATA_type = 0,			// ����				uint			1Ϊ����  1000�Ժ�Ϊ������
	POKER_TYPE_DATA_name,				// ����				varchar50
	POKER_TYPE_DATA_color,				// ��ɫ				uint
	POKER_TYPE_DATA_max_star,			// ����Ǽ�			uint
	POKER_TYPE_DATA_grow,				// �ɳ�				uint
	POKER_TYPE_DATA_base_score,			// �����ɳ�			uint
	POKER_TYPE_DATA_magic1,				// ħ��1			uint
	POKER_TYPE_DATA_magic2,				// ħ��2			uint
	POKER_TYPE_DATA_magic3,				// ħ��3			uint
	POKER_TYPE_DATA_equip_atk,			// �����ȹ�			int			�����ɸ�
	POKER_TYPE_DATA_equip_def,			// ���߷���			int			�����ɸ�
	POKER_TYPE_DATA_equip_dodge,		// ��������			int			�����ɸ�
	POKER_TYPE_DATA_equip_king,			// ��������			int			�����ɸ�
	POKER_TYPE_DATA_resolve_price,		// �ֽ�۸�			uint		0���ɷֽ�
	POKER_TYPE_DATA_lottery_weight,		// �齱��Ȩ��		uint		0�ó齱�ز���
	POKER_TYPE_DATA_holy_base_price,	// ������۸�		uint		0������
	POKER_TYPE_DATA_spine_type,			// ģ�ͱ�type		uint
	POKER_TYPE_DATA_equip_icon,			// ����icon			uint
	POKER_TYPE_DATA_equip_name,			// ��������			varchar50
	POKER_TYPE_DATA_equip_text,			// ����˵��			varchar511
	POKER_TYPE_DATA_explain,			// ˵��				varchar511
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
	POKER_STRENGTHEN_TYPE_DATA_lev = 0,		// ǿ���ȼ�
	POKER_STRENGTHEN_TYPE_DATA_effect,		// Ч��ֵ	��ֱ�
	POKER_STRENGTHEN_TYPE_DATA_percent,		// �ɹ�����	��ֱ�
	POKER_STRENGTHEN_TYPE_DATA_ore1,		// ������� ��ʼ
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
	POKER_STRENGTHEN_TYPE_DATA_adva2,		// ������� ����
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

// ǿ�����Ӹ��ʼ۸��
enum STRENGTHEN_SUCC_TYPE_DATA
{
	STRENGTHEN_SUCC_TYPE_DATA_add_percent = 0,		// ���Ӹ�����ֱ�	uint
	STRENGTHEN_SUCC_TYPE_DATA_price,				// ��ʯ�۸�			uint
};

static const ST_CONST_TABLE_FIELD strengthensuccField[] =
{
	{ FIELD_TYPE_int, STRENGTHEN_SUCC_TYPE_DATA_add_percent, "add_percent" },
	{ FIELD_TYPE_int, STRENGTHEN_SUCC_TYPE_DATA_price, "price" }
};

// ħ�����ñ�
enum MAGIC_TYPE_DATA
{
	MAGIC_TYPE_DATA_type = 0,			// ħ������			uint
	MAGIC_TYPE_DATA_name,				// ħ������			varchar50
	MAGIC_TYPE_DATA_need_pokertype1,	// ��Ҫ����1		uint		������弼�ܾ�ֻ��Ҫһ�ſ�, ��Ҫ���ſ��Ƶ�, ��λ�����ϱ�ʶ����, ��λ0��1��ʾֻ��Ҫһ��
	MAGIC_TYPE_DATA_need_pokertype2,	// ��Ҫ����2		uint		
	MAGIC_TYPE_DATA_need_pokertype3,	// ��Ҫ����3		uint		
	MAGIC_TYPE_DATA_need_pokertype4,	// ��Ҫ����4		uint		
	MAGIC_TYPE_DATA_need_pokertype5,	// ��Ҫ����5		uint		
	MAGIC_TYPE_DATA_need_pokertype6,	// ��Ҫ����6		uint		
	MAGIC_TYPE_DATA_passive_atk,		// ����Ч�� �ȹ�	uint
	MAGIC_TYPE_DATA_passive_def,		// ����Ч��	����	uint
	MAGIC_TYPE_DATA_passive_dodge,		// ����Ч��	����	uint
	MAGIC_TYPE_DATA_passive_king,		// ����Ч��	����	uint
	MAGIC_TYPE_DATA_condition1_type,	// ��������1 ����	uint
	MAGIC_TYPE_DATA_condition1_data,	// ��������1 ��ֵ	uint
	MAGIC_TYPE_DATA_condition2_type,	// ��������2 ����	uint
	MAGIC_TYPE_DATA_condition2_data,	// ��������2 ��ֵ	uint
	MAGIC_TYPE_DATA_rate,				// ��������			uint
	MAGIC_TYPE_DATA_count,				// ��������			uint
	MAGIC_TYPE_DATA_damage_type,		// �˺�����			uint
	MAGIC_TYPE_DATA_damage_data,		// �˺���ֵ			uint
	MAGIC_TYPE_DATA_addition_atk,		// ���ȹ��ӳ�		uint
	MAGIC_TYPE_DATA_addition_def,		// �ܷ����ӳ�		uint
	MAGIC_TYPE_DATA_addition_dodge,		// �����ܼӳ�		uint
	MAGIC_TYPE_DATA_addition_king,		// �����߼ӳ�		uint
	MAGIC_TYPE_DATA_seal_type,			// ��ӡ����			uint
	MAGIC_TYPE_DATA_seal_data,			// ��ӡ��ֵ			uint
	MAGIC_TYPE_DATA_seal_except_data,	// ��ӡ����ֵ		uint
	MAGIC_TYPE_DATA_seal_weak_flag,		// �������ܱ��		uint
	MAGIC_TYPE_DATA_recover_type,		// �ظ�����			uint
	MAGIC_TYPE_DATA_recover_data,		// �ָ���ֵ			uint
	MAGIC_TYPE_DATA_icon,				// ͼ����			uint
	MAGIC_TYPE_DATA_detail,				// ����˵��			varchar255
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

// ��Ʒ���ͱ�
enum ITEM_TYPE_DATA
{
	ITEM_TYPE_DATA_ID = 0,			// ����				uint
	ITEM_TYPE_DATA_NAME,			// ����				vchar
	ITEM_TYPE_DATA_COLOR,			// ��ɫ				uint
	ITEM_TYPE_DATA_ACTION,			// action			uint
	ITEM_TYPE_DATA_MONOPOLY,		// monopoly			uint
	ITEM_TYPE_DATA_DATA,			// ����				uint
	ITEM_TYPE_DATA_ICON,			// ͼ����			uint
	ITEM_TYPE_DATA_SPINE_NAME,		// spine�и�����	varchar50
	ITEM_TYPE_DATA_DETAIL,			// ��ϸ����			varchar512
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

// �̳����ñ�
enum SHOP_GOODS_DATA
{
	SHOP_GOODS_DATA_ID = 0,			// id				uint
	SHOP_GOODS_DATA_SHOP_TYPE,		// �̵�����			uint
	SHOP_GOODS_DATA_GOODS_TYPE,		// ��Ʒ����			uint
	SHOP_GOODS_DATA_GOODS_NUM,		// ��Ʒ����			uint
	SHOP_GOODS_DATA_SPEND_TYPE1,	// ���򻨷�����1	uint
	SHOP_GOODS_DATA_SPEND_NUM1,		// ���򻨷�����1	uint
	SHOP_GOODS_DATA_SPEND_TYPE2,	// ���򻨷�����2	uint
	SHOP_GOODS_DATA_SPEND_NUM2,		// ���򻨷�����2	uint
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

// ���ֿ�
enum NAME_LIBRARY_DATA
{
	NAME_LIBRARY_DATA_ID = 0,		// id		uint
	NAME_LIBRARY_DATA_NAME,			// ����		varchar32
};

static const ST_CONST_TABLE_FIELD namelibraryField[] =
{
	{ FIELD_TYPE_int, NAME_LIBRARY_DATA_ID, "id" },
	{ FIELD_TYPE_str, NAME_LIBRARY_DATA_NAME, "name" },
};

// ұ���¶ȱ�
enum SMELT_TEMP_TYPE_DATA
{
	SMELT_TEMP_TYPE_DATA_temp = 0,		// �¶�		uint
	SMELT_TEMP_TYPE_DATA_time_base,		// ��ʱ����	uint
	SMELT_TEMP_TYPE_DATA_monster_rate,	// ���ָ���	uint
	SMELT_TEMP_TYPE_DATA_empty,			// ����Ȩ��			uint
	SMELT_TEMP_TYPE_DATA_ore1,			// ԭ��1 ����Ȩ��	uint
	SMELT_TEMP_TYPE_DATA_ore2,
	SMELT_TEMP_TYPE_DATA_ore3,
	SMELT_TEMP_TYPE_DATA_ore4,
	SMELT_TEMP_TYPE_DATA_ore5,
	SMELT_TEMP_TYPE_DATA_gem1,			// ��ʯ1 ����Ȩ��	uint
	SMELT_TEMP_TYPE_DATA_gem2,
	SMELT_TEMP_TYPE_DATA_gem3,
	SMELT_TEMP_TYPE_DATA_gem4,
	SMELT_TEMP_TYPE_DATA_gem5,
	SMELT_TEMP_TYPE_DATA_soul1,			// ����1 ����Ȩ��	uint
	SMELT_TEMP_TYPE_DATA_soul2,
	SMELT_TEMP_TYPE_DATA_soul3,
	SMELT_TEMP_TYPE_DATA_soul4,
	SMELT_TEMP_TYPE_DATA_soul5,
	SMELT_TEMP_TYPE_DATA_statue,		// ���� ����Ȩ��	uint
	SMELT_TEMP_TYPE_DATA_adva1,			// ���� ����Ȩ��	uint
	SMELT_TEMP_TYPE_DATA_adva2,			// ʱ�� ����Ȩ��	uint
	SMELT_TEMP_TYPE_DATA_up0,			// ����0Ȩ��		uint
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

// ұ��ԭ���
enum SMELT_ORE_TYPE_DATA
{
	SMELT_ORE_TYPE_DATA_ore = 0,		// ԭ������	uint
	SMELT_ORE_TYPE_DATA_time_param,		// ʱ�����	uint
	SMELT_ORE_TYPE_DATA_monster_param,	// ���ֲ���	uint
};

static const ST_CONST_TABLE_FIELD smeltoreField[] =
{
	{ FIELD_TYPE_int, SMELT_ORE_TYPE_DATA_ore, "ore" },
	{ FIELD_TYPE_int, SMELT_ORE_TYPE_DATA_time_param, "time_param" },
	{ FIELD_TYPE_int, SMELT_ORE_TYPE_DATA_monster_param, "monster_param" },
};

// ұ�����ٱ�
enum SMELT_SPEEDUP_DATA
{
	SMELT_SPEEDUP_DATA_left_second = 0,		// ʣ��ʱ��	uint
	SMELT_SPEEDUP_DATA_need_bomb,			// ��Ҫը��	uint
};
static const ST_CONST_TABLE_FIELD smeltspeedupField[] =
{
	{ FIELD_TYPE_int, SMELT_SPEEDUP_DATA_left_second, "left_second" },
	{ FIELD_TYPE_int, SMELT_SPEEDUP_DATA_need_bomb, "need_bomb" },
};

// �������ñ�
enum INSTANCE_DATA
{
	INSTANCE_DATA_ID = 0,						// id(mode * 10000 + chapter * 1000 + pass)				uint
	INSTANCE_DATA_MODE,							// ģʽ				uint
	INSTANCE_DATA_CHAPTER,						// �½�				uint
	INSTANCE_DATA_PASS,							// �ؿ�				uint
	INSTANCE_DATA_OPEN_SCORE,					// ����ս��			uint
	INSTANCE_DATA_INIT_COST_MONEY,				// ��ʼ���Ľ��		uint
	INSTANCE_DATA_AUTO_ADD_MONEY,				// ÿ���Զ����ӽ��	uint
	INSTANCE_DATA_AUTO_ADD_EXP,					// ÿ���Զ����Ӿ���	uint
	INSTANCE_DATA_FIGHT_WAITING_TIME,			// ս���ȴ�ʱ��		uint
	INSTANCE_DATA_FIGHT_AWARD_ACTION,			// ս������action	uint
	INSTANCE_DATA_SEARCHING_INIT_TIME,			// ̽����ʼʱ��		uint
	INSTANCE_DATA_SEARCHING_TIME,				// ̽��ʱ��			uint
	INSTANCE_DATA_SEARCHING_AWARD_ACTION,		// ̽������action	uint
	INSTANCE_DATA_MONSTER_ID,					// ����id			uint
	INSTANCE_DATA_CHAPTER_NAME,					// �½�����			varchar32
	INSTANCE_DATA_CHAPTER_CSB_NAME,				// �½�csb���֣��ͻ��ˣ�varchar32
	INSTANCE_DATA_CHAPTER_DETAIL,				// �½�˵��			varchar256
	INSTANCE_DATA_DROP_POKER_TYPE1,				// ���俨������1	uint
	INSTANCE_DATA_DROP_POKER_TYPE2,				// ���俨������2	uint
	INSTANCE_DATA_DROP_POKER_TYPE3,				// ���俨������3	uint
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

// ұ�����ٱ�
enum MAIN_HINT_DATA
{
	MAIN_HINT_DATA_id = 0,		// id	uint
	MAIN_HINT_DATA_text,		// ���� varchar
};
static const ST_CONST_TABLE_FIELD mainhintField[] =
{
	{ FIELD_TYPE_int, MAIN_HINT_DATA_id, "id" },
	{ FIELD_TYPE_str, MAIN_HINT_DATA_text, "text" },
};

//////////////////////////////////////////////////////////////////////////
// ********************** �������ݷ��ڱ��ļ���� ***********************//
//////////////////////////////////////////////////////////////////////////

// ����������
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

// ��������Ϣ
struct ST_CONST_TABLE_INFO
{
	CONST_TABLE_TYPE			eTableType;		// ������
	CONST_TABLE_INDEX_TYPE		eIndexType;		// ��������
	int32_t						nKeyIndex1;		// ��һ�����������
	int32_t						nKeyIndex2;		// �ڶ������������(��������0)
	char						pszFileName[64];// json�ļ���
	const ST_CONST_TABLE_FIELD*	pFieldInfo;		// �ֶ���Ϣ
	int32_t						nFieldCount;	// �ֶ���Ϣ����
};

// ��������Ϣ
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
