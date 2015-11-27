// proj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include "../../trunk/Classes/ConstTable/ConfigPassword.h"

int _tmain(int argc, _TCHAR* argv[])
{
	

	system("del spine.zip /s /q");

	char szBuf[1024] = "";
	sprintf_s(szBuf, sizeof(szBuf), "7za a -tzip \"%s\" \"*.json\" \"*.png\" \"*.atlas\" -r -p\"%s\" -mx=1", SPINE_FILE_NAME, SPINE_LIST_FILE_PASSWORD);
	system(szBuf);
	return 0;
}

