////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: RC4.h
// Author: ������(Peng Wenqi)
// Created: 2015-1-13
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_SAVE_DATA_RC4_
#define _JYP_SAVE_DATA_RC4_

#include <stdint.h>
#include <string>

namespace rc4
{
	std::string Encrypt(const char* szSource, const char* szPassWord); // ���ܣ����ؼ��ܽ��
	std::string Decrypt(const char* szSource, const char* szPassWord); // ���ܣ����ؽ��ܽ��
	int RC4(const unsigned char* data, uint32_t data_len, const unsigned char* key, uint32_t key_len, unsigned char* out, uint32_t* out_len);
}// end of namespace rc4

#endif // end of _JYP_SAVE_DATA_RC4_