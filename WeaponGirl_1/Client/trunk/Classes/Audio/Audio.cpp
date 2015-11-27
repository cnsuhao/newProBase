////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: Audio.cpp
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-15
////////////////////////////////////////////////////////////////////////
#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "ConstTable/ConstTableMgr.h"
#include "SaveData/SaveData.h"

Audio* Audio::m_pInstance = nullptr;

//////////////////////////////////////////////////////////////////////////
Audio* Audio::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new Audio();
	}
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
void Audio::destroyInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}

////////////////////////////////////////////////////////////////////////
// Description: ²¥·ÅÉùÒô½Ó¿Ú
// Arguments:
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Audio::play( AUDIO_ID eID )
{
	CHECK(ConstTableMgr::getInstance()->IsExistSingle(CONST_TABLE_TYPE_audio, eID));
	auto filename = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_audio, eID, AUDIO_filename);
	if (eID < AUDIO_ID_EFFECT_BEGIN)
	{
		if (m_bOpenMusic)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filename.c_str(), true);
		}
	}
	else
	{
		if (m_bOpen)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filename.c_str(), false);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void Audio::pause()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//////////////////////////////////////////////////////////////////////////
void Audio::resume()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

////////////////////////////////////////////////////////////////////////
// Description: Ô¤¼ÓÔØ
// Arguments:
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Audio::preload()
{
	VEC_DB_KEY vec;
	CHECK(ConstTableMgr::getInstance()->EnumKey(CONST_TABLE_TYPE_audio, vec));
	for (auto &id : vec)
	{
		if (0 == ConstTableMgr::getInstance()->GetDataSingle(CONST_TABLE_TYPE_audio, id, AUDIO_preload))
		{
			continue;
		}
		
		auto filename = ConstTableMgr::getInstance()->GetStrSingle(CONST_TABLE_TYPE_audio, id, AUDIO_filename);
		if (id < AUDIO_ID_EFFECT_BEGIN)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filename.c_str());
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(filename.c_str());
		}
	}

	m_bOpen = !::GetSaveData(SAVE_DATA_close_sound);
	m_bOpenMusic = !::GetSaveData(SAVE_DATA_close_music);
}

////////////////////////////////////////////////////////////////////////
// Description: ÉèÖÃÉùÒôÒýÇæ×´Ì¬
// Arguments:
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void Audio::setStatus( bool bOpen, bool bInGame /*= false*/ )
{
	if (m_bOpen == bOpen)
	{
		return;
	}

	m_bOpen = bOpen;
	if (!m_bOpen)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	}

	int nCloseFlag = !m_bOpen;
	::SetSaveData(SAVE_DATA_close_sound, nCloseFlag);
}

////////////////////////////////////////////////////////////////////////
// Description: ÉèÖÃÒôÀÖ×´Ì¬
// Arguments:
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void Audio::setStatusMusic( bool bOpenMusic, bool bInGame /*= false*/ )
{
	if (m_bOpenMusic == bOpenMusic)
	{
		return;
	}

	m_bOpenMusic = bOpenMusic;
	if (!m_bOpenMusic)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		if (bInGame)
		{
			this->play(AUDIO_ID_MUSIC);
		}
	}

	int nCloseFlag = !bOpenMusic;
	::SetSaveData(SAVE_DATA_close_music, nCloseFlag);
}

//////////////////////////////////////////////////////////////////////////
void Audio::stopBackgroundMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
