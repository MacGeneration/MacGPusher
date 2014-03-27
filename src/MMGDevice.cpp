//
// MMGDevice.cpp
//
// Copyright (c) 2013 MacGeneration. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
// conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
// of conditions and the following disclaimer in the documentation and/or other materials
// provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//


#include "MMGDevice.hpp"
#include <cstring>


MMGDevice::MMGDevice(const std::string& token, const unsigned int badge)
{
	this->_token = token;
	this->_badge = badge;
	this->__CreateBinaryToken();
}

MMGDevice::MMGDevice(const MMGDevice& device)
{
	this->_token = device.GetToken();
	this->_badge = device.GetBadge();
	this->__CreateBinaryToken();
}

void MMGDevice::SetToken(const std::string& token)
{
	this->_token = token;
	this->__CreateBinaryToken();
}

void MMGDevice::SetBadge(const unsigned int badge)
{
	this->_badge = badge;
}

const std::string& MMGDevice::GetToken(void)const
{
	return this->_token;
}

unsigned int MMGDevice::GetBadge(void)const
{
	return this->_badge;
}

const char* MMGDevice::GetBinaryToken(void)const
{
	return this->_binaryToken;
}

bool operator==(const MMGDevice& d1, const MMGDevice& d2)
{
	return (d1.GetToken() == d2.GetToken());
}

void MMGDevice::__CreateBinaryToken(void)
{
	const size_t tokenLen = this->_token.size();
	size_t i = 0, j = 0;
	int tmpi;
	char tmp[3] = {0x00};
	memset(this->_binaryToken, 0x00, MMG_DEVICE_BINARY_SIZE);
	while (i < tokenLen)
	{
		if (this->_token[i] == ' ')
			i++;
		else
		{
			tmp[0] = this->_token[i];
			tmp[1] = this->_token[i + 1];
			sscanf(tmp, "%x", &tmpi);
			this->_binaryToken[j] = static_cast<char>(tmpi);
			i += 2;
			j++;
		}
	}
}
