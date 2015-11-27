////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: RC4.cpp
// Author: ������(Peng Wenqi)
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


void ByteToHex(const unsigned char* vByte, const uint32_t vLen, char* bufHex); // ���ֽ���pbBufferתΪʮ�������ַ��������㴫��
void HexToByte(const char* szHex, unsigned char* bufByte); // ��ʮ�������ַ���תΪ�ֽ���pbBuffer������


////////////////////////////////////////////////////////////////////////
// Description: ���ܣ����ؼ��ܽ��
// Arguments:
// Author: ������(Peng Wenqi)
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
// Description: ���ܣ����ؽ��ܽ��
// Arguments:
// Author: ������(Peng Wenqi)
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


// ���ֽ���תΪʮ�������룬һ���ֽ�����ʮ�����ƣ��ڲ�Ϊ�ַ�������ռ�
void ByteToHex(const unsigned char* vByte, const uint32_t vLen, char* bufHex)
{
	if (!vByte) 
		return;
	char* tmp = bufHex; // һ���ֽ�����ʮ�������룬���Ҫ��һ��'/0'
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

// ��ʮ�������ַ�����תΪ�ֽ��룬ÿ����ʮ�������ַ���Ϊһ���ֽ�
void HexToByte(const char* szHex, unsigned char* bufByte)
{
	if(!szHex) 
		return;
	int iLen = strlen(szHex);
	if (iLen<=0 || 0!=iLen%2) 
		return;

	unsigned char* pbBuf = bufByte;  // ���ݻ�����
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