////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: SaveDataDefine.h
// Author: ������(Peng Wenqi)
// Created: 2015-1-13
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SAVE_DATA_DEFINE_HEADER_
#define _JYP_SAVE_DATA_DEFINE_HEADER_

#include "cocos2d.h"
#include "Global/GlobalEnumDef.h"

// �־û�����ö��ֵ, �ڱ�ֵ�����޸�, ö��ֵ������Ȼ����
enum SAVE_DATA
{
	SAVE_DATA_BEGIN = 0,
	SAVE_DATA_close_sound = 0,	// �ر��������
	SAVE_DATA_close_music,		// �ر����ֱ��

	SAVE_DATA_choose_server_id1,		// ѡ�������id - 1
	SAVE_DATA_choose_server_id2,		// ѡ�������id - 2
	SAVE_DATA_choose_server_id3,		// ѡ�������id - 3

	SAVE_DATA_input_account_name,		// �˺���
	SAVE_DATA_input_account_pwd,		// �˺�����
	SAVE_DATA_input_account_pwd_flag,	// ���뱣����

	SAVE_DATA_notify_short,				// �̹���
	SAVE_DATA_notify_long,				// ������
	SAVE_DATA_END,
};

// �־û����ݽṹ
struct ST_SAVE_DATA
{
	FIELD_TYPE	eFieldType;			// �ֶ�����
	SAVE_DATA	eFieldEnum;			// �ֶ�ö��ֵ
	char		pszFieldName[64];	// �ֶ���
	bool		bEncrypt;			// �Ƿ����
	int32_t		nDefault;			// Ĭ��ֵ(����)
	char		szDefault[32];		// Ĭ��ֵ(�ַ���)
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