////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: RC4.cpp
// Author: 彭文奇(Peng Wenqi)
// Created: 2015-1-13
////////////////////////////////////////////////////////////////////////
#include "RC4.h"

namespace rc4{
const uint32_t BOX_LEN = 256;
const uint32_t BUFFER_SIZE = 4096;

int GetKey(const unsigned char* pass, uint32_t pass_len, unsigned char* out);

inline void swap_byte(unsigned char* a, unsigned char* b)
{
	unsigned char swapByte; 
	swapByte = *a;
	*a = *b;
	*b = swapByte;
}


void ByteToHex(const unsigned char* vByte, const uint32_t vLen, char* bufHex); // 把字节码pbBuffer转为十六进制字符串，方便传输
void HexToByte(const char* szHex, unsigned char* bufByte); // 把十六进制字符串转为字节码pbBuffer，解码


////////////////////////////////////////////////////////////////////////
// Description: 加密，返回加密结果
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string Encrypt( const char* szSource, const char* szPassWord )
{
	if (szSource == nullptr || szPassWord == nullptr) return "";
	if (strlen(szSource) > BUFFER_SIZE / 2) return "";
	unsigned char szBuffer[BUFFER_SIZE] = {0};
	char szHexBuffer[BUFFER_SIZE] = { 0 };
	unsigned char* ret = szBuffer;
	uint32_t ret_len = 0;
	if (RC4((unsigned char*)szSource, strlen(szSource), (unsigned char*)szPassWord, strlen(szPassWord), ret, &ret_len) == 0) return "";
	ByteToHex(ret, ret_len, szHexBuffer);
	std::string result = szHexBuffer;
	return result;
}

////////////////////////////////////////////////////////////////////////
// Description: 解密，返回解密结果
// Arguments:
// Author: 彭文奇(Peng Wenqi)
// Return Value: std::string
////////////////////////////////////////////////////////////////////////
std::string Decrypt( const char* szSource, const char* szPassWord )
{
	if (szSource == nullptr || (strlen(szSource)%2 != 0) || szPassWord == nullptr) return "";
	if (strlen(szSource) > BUFFER_SIZE / 2) return "";
	unsigned char szBuffer[BUFFER_SIZE] = {0};
	unsigned char szByteBuffer[BUFFER_SIZE] = { 0 };
	HexToByte(szSource, szByteBuffer);
	unsigned char* ret = szBuffer;
	uint32_t ret_len = 0;
	memset(ret, 0, strlen(szSource) / 2 + 1);
	if (0 == RC4(szByteBuffer, strlen(szSource) / 2, (unsigned char*)szPassWord, strlen(szPassWord), ret, &ret_len)) return "";
	ret[ret_len] = '\0';
	std::string result((char*)ret);
	return result;
}

//////////////////////////////////////////////////////////////////////////
int RC4(const unsigned char* data, uint32_t data_len, const unsigned char* key, uint32_t key_len, unsigned char* out, uint32_t* out_len)
{
	if (data == nullptr || key == nullptr || out == nullptr) return 0;

	unsigned char szBuffer[BUFFER_SIZE] = {0};
	unsigned char* mBox = szBuffer;
	if(GetKey(key, key_len, mBox) == 0) return 0;

	uint32_t i=0;
	int x=0;
	int y=0;

	for(uint32_t k = 0; k < data_len; k++)
	{
		x = (x + 1) % BOX_LEN;
		y = (mBox[x] + y) % BOX_LEN;
		swap_byte(&mBox[x], &mBox[y]);
		out[k] = data[k] ^ mBox[(mBox[x] + mBox[y]) % BOX_LEN];
	}
	*out_len = data_len;
	return -1;
}

//////////////////////////////////////////////////////////////////////////
int GetKey(const unsigned char* pass, uint32_t pass_len, unsigned char* out)
{
	if(pass == nullptr || out == nullptr) return 0;

	int i;

	for(i = 0; i < BOX_LEN; i++)
		out[i] = i;

	int j = 0;
	for(i = 0; i < BOX_LEN; i++)
	{
		j = (pass[i % pass_len] + out[i] + j) % BOX_LEN;
		swap_byte(&out[i], &out[j]); 
	} 
	return -1;
}


// 把字节码转为十六进制码，一个字节两个十六进制，内部为字符串分配空间
void ByteToHex(const unsigned char* vByte, const uint32_t vLen, char* bufHex)
{
	if (!vByte) 
		return;
	char* tmp = bufHex; // 一个字节两个十六进制码，最后要多一个'/0'
	int tmp2;
	for (uint32_t i = 0; i < vLen; i++)
	{
		tmp2 = (int)(vByte[i]) / 16;
		tmp[i * 2] = (char)(tmp2 + ((tmp2 > 9) ? 'A' - 10 : '0'));
		tmp2 = (int)(vByte[i]) % 16;
		tmp[i * 2 + 1] = (char)(tmp2 + ((tmp2 > 9) ? 'A' - 10 : '0'));
	}
	tmp[vLen * 2] = '\0';
}

// 把十六进制字符串，转为字节码，每两个十六进制字符作为一个字节
void HexToByte(const char* szHex, unsigned char* bufByte)
{
	if(!szHex) 
		return;
	int iLen = strlen(szHex);
	if (iLen<=0 || 0!=iLen%2) 
		return;

	unsigned char* pbBuf = bufByte;  // 数据缓冲区
	int tmp1, tmp2;
	for (int i=0;i<iLen/2;i++)
	{
		tmp1 = (int)szHex[i*2] - (((int)szHex[i*2]>='A')?'A'-10:'0');
		if(tmp1>=16) 
			return;
		tmp2 = (int)szHex[i*2+1] - (((int)szHex[i*2+1]>='A')?'A'-10:'0');
		if(tmp2>=16) 
			return;
		pbBuf[i] = (tmp1*16+tmp2);
	}
}

}// end of namespace rc4