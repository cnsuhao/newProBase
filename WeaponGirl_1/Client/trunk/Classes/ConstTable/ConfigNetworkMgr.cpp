////////////////////////////////////////////////////////////////////////
// Copyright(c) 2015-9999, WuHan GoodGame, All Rights Reserved
// Moudle: ConfigNetworkMgr.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015/10/09
////////////////////////////////////////////////////////////////////////
#include "ConfigNetworkMgr.h"
#include "ConfigPassword.h"
#include "ConstTableMgr.h"
#include "Audio\Audio.h"
#include "Global\md5.h"
#include "SceneLogin\SceneLogin.h"
#include "Root.h"
#include "SceneLogin\LayerLogin.h"
#include "SceneLogin\LayerAskToUpdate.h"

static const char* TAG_HTTP_REQ_MD5 = "md5";	// 请求版本号标记

ConfigNetworkMgr* ConfigNetworkMgr::_instance = nullptr;

//////////////////////////////////////////////////////////////////////////
ConfigNetworkMgr* ConfigNetworkMgr::getInstance()
{
	if (nullptr == _instance)
	{
		_instance = new ConfigNetworkMgr();
	}

	return _instance;
}

//////////////////////////////////////////////////////////////////////////
void ConfigNetworkMgr::destroyInstance()
{
	CC_SAFE_DELETE(_instance);
}

//////////////////////////////////////////////////////////////////////////
bool ConfigNetworkMgr::Init()
{
	m_nNeedDownloadCount = 0;

	// 请求MD5码
	std::string url = getBaseUrl() + RES_MD5_FILE_NAME;
	network::HttpRequest* request = new network::HttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(ConfigNetworkMgr::recvHttp, this));
	request->setTag(TAG_HTTP_REQ_MD5);
	network::HttpClient::getInstance()->send(request);
	request->release();

	return true;
}


//////////////////////////////////////////////////////////////////////////
std::string ConfigNetworkMgr::getBaseUrl() const
{
	std::string strTextPath = FileUtils::getInstance()->fullPathForFilename("baseurl.txt");
	std::string strData = FileUtils::getInstance()->getStringFromFile(strTextPath);
	return FileUtils::getInstance()->getRemoveBomStringData(strData.c_str(), strData.size());
}

////////////////////////////////////////////////////////////////////////
// Description: 将文件拷贝到可读写目录
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: bool
////////////////////////////////////////////////////////////////////////
bool ConfigNetworkMgr::copyFile(const std::string& filename)
{
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		return false;
	}

	// 资源路径  
	Data data = FileUtils::getInstance()->getDataFromFile(filename);

	// 可写路径  
	std::string destPath = FileUtils::getInstance()->getWritablePath() + filename;
	FILE *fp = fopen(destPath.c_str(), "wb+");
	if (fp)
	{
		size_t size = fwrite(data.getBytes(), sizeof(unsigned char), data.getSize(), fp);
		fclose(fp);

		if (size > 0)
		{
			LogSave("copy file %s success!", filename.c_str());
			return true;
		}
	}
	LogSave("copy file %s failed.", filename.c_str());
	return false;
}

////////////////////////////////////////////////////////////////////////
// Description: 接收http文件
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: 
////////////////////////////////////////////////////////////////////////
void ConfigNetworkMgr::recvHttp(network::HttpClient* client, network::HttpResponse* response)
{
	CHECK(response);

	if (!response->isSucceed())
	{
		LogSave("response failed");
		LogSave("error buffer: %s", response->getErrorBuffer());
		return;
	}

	LogSave("ConfigNetworkMgr::recvHttp [%s] completed", response->getHttpRequest()->getTag());
	if		(0 == strcmp(response->getHttpRequest()->getTag(), TAG_HTTP_REQ_MD5))	// MD5返回
	{
		std::vector<char> *buffer = response->getResponseData();
		std::string strData(buffer->begin(), buffer->end());
		std::string load_str = FileUtils::getInstance()->getRemoveBomStringData(strData.c_str(), strData.size());

		std::vector<std::string> vecSplitString;
		::SpiltString(load_str, "\n", vecSplitString, 10000);
		int nNeedDownloadTotalSize = 0;
		std::vector<std::string> vecNeedDownloadFileName;
		for (auto iter = vecSplitString.begin(); iter != vecSplitString.end(); iter++)
		{
			auto strData = *iter;
			if (strData.empty())
			{
				continue;
			}
			::ReplaceStdString(strData, "\r", "", true);

			std::vector<std::string> vecFieldString;
			::SpiltString(strData, " ", vecFieldString, 3);

			CHECKC(vecFieldString.size() == 3);
			const std::string& remoteMD5 = vecFieldString[0];
			const std::string& fileName = vecFieldString[1];
			int fileSize = atoi(vecFieldString[2].c_str());

			// 强制使用调试资源时, 直接拷贝覆盖
			if (FileUtils::getInstance()->isFileExist("debug.txt"))
			{
				this->copyFile(fileName);
				continue;
			}

			// 可写目录不存在的, 先尝试拷贝
			if (!FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->getWritablePath() + fileName))
			{
				this->copyFile(fileName);
			}

			// 可写目录存在md5相同时不予理睬
			bool bNeedDownload = true;
			if (FileUtils::getInstance()->isFileExist(FileUtils::getInstance()->getWritablePath() + fileName))
			{
				auto dataFile = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->getWritablePath() + fileName);
				MD5 md5(dataFile.getBytes(), dataFile.getSize());
				std::string localMD5 = md5.toString();
				if (localMD5 == remoteMD5)
				{
					bNeedDownload = false;
				}
			}

			if (bNeedDownload)
			{
				nNeedDownloadTotalSize += fileSize;
				m_nNeedDownloadCount++;
				vecNeedDownloadFileName.push_back(fileName);
			}
		}

		if (m_nNeedDownloadCount > 0)
		{
			// 2M以内不询问
			if (nNeedDownloadTotalSize < 1 * 1024 * 1024)
			{
				for (auto fileName : vecNeedDownloadFileName)
				{
					LogSave("Auto Req Download Remote Res[%s]", fileName.c_str());
					std::string url = getBaseUrl() + fileName;
					network::HttpRequest* request = new network::HttpRequest();
					request->setUrl(url.c_str());
					request->setRequestType(network::HttpRequest::Type::GET);
					request->setResponseCallback(CC_CALLBACK_2(ConfigNetworkMgr::recvHttp, this));
					request->setTag(fileName.c_str());
					network::HttpClient::getInstance()->send(request);
					request->release();
				}
			}
			else
			{
				auto ask = LayerAskToUpdate::create(nNeedDownloadTotalSize, [=](){
					for (auto fileName : vecNeedDownloadFileName)
					{
						LogSave("Auto Req Download Remote Res[%s]", fileName.c_str());
						std::string url = getBaseUrl() + fileName;
						network::HttpRequest* request = new network::HttpRequest();
						request->setUrl(url.c_str());
						request->setRequestType(network::HttpRequest::Type::GET);
						request->setResponseCallback(CC_CALLBACK_2(ConfigNetworkMgr::recvHttp, this));
						request->setTag(fileName.c_str());
						network::HttpClient::getInstance()->send(request);
						request->release();
					}
				});
				CHECK(ask);
				Director::getInstance()->getRunningScene()->addChild(ask);
			}

		}
	}
	else
	{
		// 其他资源文件, 直接拷贝
		std::vector<char> *buffer = response->getResponseData();
		log("file[%s] buffer size[%d]", response->getHttpRequest()->getTag(), buffer->size());
		std::string strData(buffer->begin(), buffer->end());
		std::string fileName = FileUtils::getInstance()->getWritablePath() + response->getHttpRequest()->getTag();  //获取写入
		FILE *fp = fopen(fileName.c_str(), "wb+");
		CHECK(fp);
		fwrite(strData.c_str(), 1, buffer->size(), fp);
		fclose(fp);
		log("Write succeed");

		m_nNeedDownloadCount--;
	}

	this->finishInit();
}

////////////////////////////////////////////////////////////////////////
// Description: 完成初始化
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: void
////////////////////////////////////////////////////////////////////////
void ConfigNetworkMgr::finishInit()
{
	if (m_nNeedDownloadCount > 0)
	{
		return;
	}

	CHECK(ConstTableMgr::getInstance()->ReloadAll());	// 常量表
	Audio::getInstance()->preload();				// 声音系统预读
	SpineCache::getInstance()->proloadCache();		// 骨骼缓存

	auto sceneLogin = Root::getInstance()->getSceneLogin();
	CHECK(sceneLogin);
	auto layerLogin = dynamic_cast<LayerLogin*>(sceneLogin->getChildByName("LayerLogin"));
	if (layerLogin)
	{
		layerLogin->finishConfigNetworkData();
	}
}
