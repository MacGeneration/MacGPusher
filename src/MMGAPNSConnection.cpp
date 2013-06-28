//
// MMGAPNSConnection.cpp
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


#include "MMGAPNSConnection.hpp"
#include "global.hpp"
#include "MMGPayload.hpp"
#include "MMGDevice.hpp"


#define MMG_MAXPAYLOAD_SIZE 256


MMGAPNSConnection::MMGAPNSConnection(const std::string& certsPath, const std::string& certFile, const std::string& keyFile, const std::string& keyPassword, const bool sandbox) : MMGSSLConnection((sandbox) ? MMG_APNS_SERVER_SANDBOX : MMG_APNS_SERVER, MMG_APNS_PORT, certsPath, certFile, keyFile, keyPassword)
{
	_sandbox = sandbox;
}

bool MMGAPNSConnection::SendPayloadToDevice(MMGPayload& payload, const MMGDevice& device)
{
	const char* payloadBuffer = payload.GetPayload().c_str();
	const size_t payloadLen = strlen(payloadBuffer);
	char binaryMessageBuff[sizeof(uint8_t) + sizeof(uint16_t) + MMG_DEVICE_BINARY_SIZE + sizeof(uint16_t) + MMG_MAXPAYLOAD_SIZE];

	// Message format: |COMMAND|TOKENLEN|TOKEN|PAYLOADLEN|PAYLOAD|
	char* binaryMessagePt = binaryMessageBuff;

	// Command
	const uint8_t command = 0; // command number
	*binaryMessagePt++ = command;

	// Token length network order
	const uint16_t networkOrderTokenLen = htons(MMG_DEVICE_BINARY_SIZE);
	memcpy(binaryMessagePt, &networkOrderTokenLen, sizeof(uint16_t));
	binaryMessagePt += sizeof(uint16_t);

	// Device binary token
	memcpy(binaryMessagePt, device.GetBinaryToken(), MMG_DEVICE_BINARY_SIZE);
	binaryMessagePt += MMG_DEVICE_BINARY_SIZE;

	// Payload length network order
	const uint16_t networkOrderPayloadLen = htons(payloadLen);
	memcpy(binaryMessagePt, &networkOrderPayloadLen, sizeof(uint16_t));
	binaryMessagePt += sizeof(uint16_t);

	// Payload
	memcpy(binaryMessagePt, payloadBuffer, payloadLen);
	binaryMessagePt += payloadLen;
	return this->SendBuffer((unsigned char*)binaryMessageBuff, (size_t)(binaryMessagePt - binaryMessageBuff));
}
