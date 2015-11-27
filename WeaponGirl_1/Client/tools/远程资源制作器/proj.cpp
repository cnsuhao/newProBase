// proj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include "md5.h"


std::string getFileMD5(const char* fileName, size_t& filesize)
{
	unsigned char* buffer = nullptr;
	size_t size = 0;

	FILE *fp = fopen(fileName, "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		buffer = (unsigned char*)malloc(sizeof(unsigned char) * size);
		filesize = fread(buffer, sizeof(unsigned char), size, fp);
		fclose(fp);
		MD5 md5(buffer, filesize);
		free(buffer);
		return md5.toString();
	}
	return "";
}

void writeFileMD5(const char* pszFileName, const char* md5, size_t size)
{
	if (pszFileName && md5)
	{
		FILE* fp = fopen("RemoteRes\\md5.txt", "a+");
		if (fp)
		{
			char szOutputBuffer[8192] = "";
			sprintf(szOutputBuffer, "%s %s %d\n", md5, pszFileName, size);
			fwrite(szOutputBuffer, strlen(szOutputBuffer), 1, fp);
			fclose(fp);
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	system("del RemoteRes\\*.* /s /q");
	system("del list.txt /s /q");
	system("copy Resources\\*.zip RemoteRes\\*.*");
	system("dir RemoteRes\\*.zip /b /n >> list.txt");

	std::ifstream infile("list.txt", std::ios::in);
	std::string textline;

	while (std::getline(infile, textline, '\n'))
	{
		size_t filesize = 0;
		std::string fullpath = "RemoteRes\\" + textline;
		auto md5 = getFileMD5(fullpath.c_str(), filesize);
		writeFileMD5(textline.c_str(), md5.c_str(), filesize);
	}
	infile.close();
	system("del list.txt /s /q");

	return 0;
}

