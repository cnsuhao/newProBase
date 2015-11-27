////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: SaveData.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015-1-13
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SAVE_DATA_
#define _JYP_SAVE_DATA_

#include "SaveDataDefine.h"

bool		SetSaveData(SAVE_DATA eData, int32_t nData);
bool		SetSaveStr(SAVE_DATA eData, const std::string& strData);

int64_t		GetSaveData(SAVE_DATA eData);
std::string GetSaveStr(SAVE_DATA eData);

#endif // end of _JYP_SAVE_DATA_