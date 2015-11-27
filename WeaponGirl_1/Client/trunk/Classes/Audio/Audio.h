////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: Audio.h
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-15
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_AUDIO_
#define _JYP_AUDIO_

#include "Global/Global.h"

enum AUDIO_ID
{
	AUDIO_ID_MUSIC = 1,				// 背景音乐

	AUDIO_ID_EFFECT_BEGIN		= 1000,	// 音效开始
	AUDIO_ID_EFFECT_NUM_BEGIN	= 1000,	// 数字1-9点击
	AUDIO_ID_EFFECT_NUM1		= 1001,	
	AUDIO_ID_EFFECT_NUM2		= 1002,	
	AUDIO_ID_EFFECT_NUM3		= 1003,	
	AUDIO_ID_EFFECT_NUM4		= 1004,	
	AUDIO_ID_EFFECT_NUM5		= 1005,	
	AUDIO_ID_EFFECT_NUM6		= 1006,	
	AUDIO_ID_EFFECT_NUM7		= 1007,	
	AUDIO_ID_EFFECT_NUM8		= 1008,	
	AUDIO_ID_EFFECT_NUM9		= 1009,	
	AUDIO_ID_EFFECT_CLICK		= 1010,	// 其他按钮点击
	AUDIO_ID_EFFECT_RESET		= 1011,	// 重置
	AUDIO_ID_EFFECT_WIN_ACTION	= 1012,	// 胜利action
	AUDIO_ID_EFFECT_WIN_MENU	= 1013,	// 胜利菜单
	AUDIO_ID_EFFECT_GAME_OVER	= 1014,	// 游戏结束
	AUDIO_ID_EFFECT_ELIMINATE	= 1015,	// 数字消除
	
};

class Audio : public Ref
{
public:
	static Audio*	getInstance();
	static void		destroyInstance();
protected:
	static Audio*	m_pInstance;

public:
	void play(AUDIO_ID eID);										// 播放声音接口
	void pause();													// 暂停
	void resume();													// 恢复
	void preload();													// 预加载接口
	void stopBackgroundMusic();										// 停止背景音乐
	void setStatus(bool bOpen, bool bInGame = false);				// 设置音效状态
	void setStatusMusic(bool bOpenMusic, bool bInGame = false);	// 设置音乐状态

protected:
	CC_SYNTHESIZE_READONLY(bool, m_bOpen, Open);
	CC_SYNTHESIZE_READONLY(bool, m_bOpenMusic, OpenMusic);
};



#endif // end of _JYP_AUDIO_