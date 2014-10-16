//
// MMGFeedbackConnection.cpp
//
// Copyright (c) 2014 MacGeneration. All rights reserved.
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


#include "MMGFeedbackConnection.hpp"
#include "global.hpp"
#include "MMGDevice.hpp"
#include "MMGTools.hpp"


#define MMG_BUFSIZE 1048576


MMGFeedbackConnection::MMGFeedbackConnection(const std::string& certsPath, const std::string& certFile, const std::string& keyFile, const std::string& keyPassword, const bool sandbox) : MMGSSLConnection((sandbox) ? MMG_APNS_FEEDBACK_SERVER_SANDBOX : MMG_APNS_FEEDBACK_SERVER, MMG_APNS_FEEDBACK_PORT, certsPath, certFile, keyFile, keyPassword)
{
	_sandbox = sandbox;
}

bool MMGFeedbackConnection::GetExpiredDevicesList(std::vector<MMGDevice*>& devices)
{
	if (this->OpenConnection() != MMGConnectionError::MMGNoError)
	{
		MMG_ERRLOG("APNS feedback connect failed\n");
		return false;
	}

	uint8_t* buffer = (uint8_t*)calloc(MMG_BUFSIZE, sizeof(uint8_t));
	ssize_t outSize = 0;
	this->ReceiveBuffer(buffer, MMG_BUFSIZE, &outSize);

	// A tuple is 38 bytes.
	// https://developer.apple.com/library/ios/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/Chapters/CommunicatingWIthAPS.html#//apple_ref/doc/uid/TP40008194-CH101-SW3
	const size_t count = (size_t)outSize / 38;

	uint8_t* buf_ptr = buffer;
	for (size_t i = 0; i < count; i++)
	{
		// 1: 4 bytes timestamp
		uint32_t timestamp = 0;
		memcpy(&timestamp, buf_ptr, 4);
		buf_ptr += 4;

		// 2: 2 bytes token length, always == 32
		uint16_t token_len = 0;
		memcpy(&token_len, buf_ptr, 2);
		buf_ptr += 2;

		// 3: 32 bytes token
		uint8_t token[32] = {0x00};
		memcpy(token, buf_ptr, 32);
		buf_ptr += 32;

		// 4: Transform the binary token into a hexa representation
		const std::string token_str = MMGTools::Bin2Hex(token, 32, true);

		MMGDevice* device = new MMGDevice(token_str, 0);
		devices.push_back(device);
	}
	free(buffer);

	return true;
}
