// proj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "../../trunk/Classes/ConstTable/ConfigPassword.h"

int _tmain(int argc, _TCHAR* argv[])
{
	

	system("del config.zip /s /q");

	char szBuf[1024] = "";
	sprintf_s(szBuf, sizeof(szBuf), "7za a -tzip \"%s\" \".\\config_files\\*.*\" -p\"%s\" -mx=1", RES_CONFIG_FILE_NAME, RES_CONFIG_FILE_PASSWORD);
	system(szBuf);
	return 0;
}

