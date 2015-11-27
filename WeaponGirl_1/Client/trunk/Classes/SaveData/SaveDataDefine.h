////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: SaveDataDefine.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-13
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SAVE_DATA_DEFINE_HEADER_
#define _JYP_SAVE_DATA_DEFINE_HEADER_

#include "cocos2d.h"
#include "Global/GlobalEnumDef.h"

// 持久化数据枚举值, 哨兵值不可修改, 枚举值必须自然增长
enum SAVE_DATA
{
	SAVE_DATA_BEGIN = 0,
	SAVE_DATA_close_sound = 0,	// 关闭声音标记
	SAVE_DATA_close_music,		// 关闭音乐标记

	SAVE_DATA_choose_server_id1,		// 选择服务器id - 1
	SAVE_DATA_choose_server_id2,		// 选择服务器id - 2
	SAVE_DATA_choose_server_id3,		// 选择服务器id - 3

	SAVE_DATA_input_account_name,		// 账号名
	SAVE_DATA_input_account_pwd,		// 账号密码
	SAVE_DATA_input_account_pwd_flag,	// 密码保存标记

	SAVE_DATA_notify_short,				// 短公告
	SAVE_DATA_notify_long,				// 长公告
	SAVE_DATA_END,
};

// 持久化数据结构
struct ST_SAVE_DATA
{
	FIELD_TYPE	eFieldType;			// 字段类型
	SAVE_DATA	eFieldEnum;			// 字段枚举值
	char		pszFieldName[64];	// 字段名
	bool		bEncrypt;			// 是否加密
	int32_t		nDefault;			// 默认值(整型)
	char		szDefault[32];		// 默认值(字符串)
};

static const ST_SAVE_DATA ARR_SAVE_DATA[] = 
{
	{ FIELD_TYPE_int, SAVE_DATA_close_sound,			"close_sound",				false,	0, "" },
	{ FIELD_TYPE_int, SAVE_DATA_close_music,			"close_music",				false,	0, "" },
	{ FIELD_TYPE_int, SAVE_DATA_choose_server_id1,		"choose_server_id1",		false,	0, "" },
	{ FIELD_TYPE_int, SAVE_DATA_choose_server_id2,		"choose_server_id2",		false,	0, "" },
	{ FIELD_TYPE_int, SAVE_DATA_choose_server_id3,		"choose_server_id3",		false,	0, "" },
	{ FIELD_TYPE_str, SAVE_DATA_input_account_name,		"input_account_name",		true,	0, "" },
	{ FIELD_TYPE_str, SAVE_DATA_input_account_pwd,		"input_account_pwd",		true,	0, "" },
	{ FIELD_TYPE_int, SAVE_DATA_input_account_pwd_flag, "input_account_pwd_flag",	false,	0, "" },
	{ FIELD_TYPE_str, SAVE_DATA_notify_short,			"notify_short",				false,	0, "" },
	{ FIELD_TYPE_int, SAVE_DATA_notify_long,			"notify_long",				false,	0, "" }
};

#endif // end of _JYP_SAVE_DATA_DEFINE_HEADER_