////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ConfigNetworkMgr.h
// Author: ÅíÎÄÆæ(Peng Wenqi)
// Created: 2015/10/09
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_CONST_ConfigNetworkMgr_
#define _JYP_CONST_ConfigNetworkMgr_

#include "Global/Global.h"
#include "network/HttpClient.h"

class ConfigNetworkMgr
{
public:
	static ConfigNetworkMgr*	getInstance();
	static void					destroyInstance();
	bool						Init();

private:
	static ConfigNetworkMgr* _instance;

public:
	bool isInitFinish() const { return m_nNeedDownloadCount <= 0; }
	std::string getBaseUrl() const;
private:
	bool copyFile(const std::string& filename);
	void recvHttp(network::HttpClient* client, network::HttpResponse* response);
	void finishInit();

private:
	int m_nNeedDownloadCount;
};


#endif // end of _JYP_CONST_ConfigNetworkMgr_