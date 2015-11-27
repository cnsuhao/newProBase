////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: Audio.h
// Author: ������(Peng Wenqi)
// Created: 2015-1-15
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_AUDIO_
#define _JYP_AUDIO_

#include "Global/Global.h"

enum AUDIO_ID
{
	AUDIO_ID_MUSIC = 1,				// ��������

	AUDIO_ID_EFFECT_BEGIN		= 1000,	// ��Ч��ʼ
	AUDIO_ID_EFFECT_NUM_BEGIN	= 1000,	// ����1-9���
	AUDIO_ID_EFFECT_NUM1		= 1001,	
	AUDIO_ID_EFFECT_NUM2		= 1002,	
	AUDIO_ID_EFFECT_NUM3		= 1003,	
	AUDIO_ID_EFFECT_NUM4		= 1004,	
	AUDIO_ID_EFFECT_NUM5		= 1005,	
	AUDIO_ID_EFFECT_NUM6		= 1006,	
	AUDIO_ID_EFFECT_NUM7		= 1007,	
	AUDIO_ID_EFFECT_NUM8		= 1008,	
	AUDIO_ID_EFFECT_NUM9		= 1009,	
	AUDIO_ID_EFFECT_CLICK		= 1010,	// ������ť���
	AUDIO_ID_EFFECT_RESET		= 1011,	// ����
	AUDIO_ID_EFFECT_WIN_ACTION	= 1012,	// ʤ��action
	AUDIO_ID_EFFECT_WIN_MENU	= 1013,	// ʤ���˵�
	AUDIO_ID_EFFECT_GAME_OVER	= 1014,	// ��Ϸ����
	AUDIO_ID_EFFECT_ELIMINATE	= 1015,	// ��������
	
};

class Audio : public Ref
{
public:
	static Audio*	getInstance();
	static void		destroyInstance();
protected:
	static Audio*	m_pInstance;

public:
	void play(AUDIO_ID eID);										// ���������ӿ�
	void pause();													// ��ͣ
	void resume();													// �ָ�
	void preload();													// Ԥ���ؽӿ�
	void stopBackgroundMusic();										// ֹͣ��������
	void setStatus(bool bOpen, bool bInGame = false);				// ������Ч״̬
	void setStatusMusic(bool bOpenMusic, bool bInGame = false);	// ��������״̬

protected:
	CC_SYNTHESIZE_READONLY(bool, m_bOpen, Open);
	CC_SYNTHESIZE_READONLY(bool, m_bOpenMusic, OpenMusic);
};



#endif // end of _JYP_AUDIO_