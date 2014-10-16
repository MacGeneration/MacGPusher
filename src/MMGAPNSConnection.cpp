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

bool MMGAPNSConnection::SendPayloadToDevice(MMGPayload& payload, const MMGDevice& device, const uint32_t notificationId, const uint32_t expiration, const MMGNotificationPriority priority)
{
	// https://developer.apple.com/library/ios/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/Chapters/CommunicatingWIthAPS.html#//apple_ref/doc/uid/TP40008194-CH101-SW2
	// The new format for a single push payload looks like:
	// [command][frame length][frame data]
	//     1          4            XX
	// A frame is composed of 5 items:
	// [frame data] = [item1][item2][item3][item4][item5]
	//				 |-----------------------------------|
	//								frame
	// Each item is composed of 3 fields:
	// [itemN] = [item ID][item data length][item data]
	//               1            2              XX

	const char* payloadBuffer = payload.GetPayload().c_str();
	const size_t payloadLen = strlen(payloadBuffer);
	
	/*** 1: build the frame ***/
	uint8_t frame[512] = {0x00}; // 512 is just to let room (max length should be 297)
	uint8_t* framePtr = frame;
	uint8_t itemId = 1;
	
	/// Item 1 = token ///
	*framePtr++ = itemId++;
	// Item data length
	uint16_t itemDataLen_n = htons(MMG_DEVICE_BINARY_SIZE);
	memcpy(framePtr, &itemDataLen_n, sizeof(uint16_t));
	framePtr += sizeof(uint16_t);
	// Token
	memcpy(framePtr, device.GetBinaryToken(), MMG_DEVICE_BINARY_SIZE);
	framePtr += MMG_DEVICE_BINARY_SIZE;
	
	/// Item 2 = payload ///
	*framePtr++ = itemId++;
	// Item data length
	itemDataLen_n = htons(payloadLen);
	memcpy(framePtr, &itemDataLen_n, sizeof(uint16_t));
	framePtr += sizeof(uint16_t);
	// Payload
	memcpy(framePtr, payloadBuffer, payloadLen);
	framePtr += payloadLen;

	/// Item 3 = Notification Id ///
	*framePtr++ = itemId++;
	// Item data length
	itemDataLen_n = htons(4);
	memcpy(framePtr, &itemDataLen_n, sizeof(uint16_t));
	framePtr += sizeof(uint16_t);
	// Notif id
	const uint32_t notifId_n = htonl(notificationId);
	memcpy(framePtr, &notifId_n, sizeof(uint32_t));
	framePtr += sizeof(uint32_t);

	/// Item 4 = Expiration date ///
	*framePtr++ = itemId++;
	// Item data length
	itemDataLen_n = htons(4);
	memcpy(framePtr, &itemDataLen_n, sizeof(uint16_t));
	framePtr += sizeof(uint16_t);
	// Expiration date (0 = expires immediately)
	const uint32_t expirationDate_n = htonl(expiration);
	memcpy(framePtr, &expirationDate_n, sizeof(uint32_t));
	framePtr += sizeof(uint32_t);

	/// Item 5 = Priority ///
	*framePtr++ = itemId;
	// Item data length
	itemDataLen_n = htons(1);
	memcpy(framePtr, &itemDataLen_n, sizeof(uint16_t));
	framePtr += sizeof(uint16_t);
	// Priority (10 = send now)
	*framePtr++ = (uint8_t)priority;

	/*** 2: build payload ***/
	const size_t frameLength = (size_t)(framePtr - frame);
	const size_t total_length = (1 + 4 + frameLength);
	uint8_t* pl = (uint8_t*)malloc(sizeof(uint8_t) * total_length);
	uint8_t* pl_ptr = pl;

	// Command number
	const uint8_t command = 2;
	*pl_ptr++ = command;
	// Frame length
	const uint32_t frameLength_n = htonl(frameLength);
	memcpy(pl_ptr, &frameLength_n, sizeof(uint32_t));
	pl_ptr += sizeof(uint32_t);
	// Frame
	memcpy(pl_ptr, frame, frameLength);
	
	// Send
	const bool ret = this->SendBuffer(pl, total_length);
	free(pl);
	return ret;
}

MMGAPNSStatusCode MMGAPNSConnection::GetResponse(uint32_t* notificationId)
{
	if (!notificationId)
		return MMGAPNSStatusCode::MMGAPNSStatusCodeUnknown;
	*notificationId = 0;

	uint8_t buffer[8] = {0x00};
	ssize_t outSize = 0;

	const bool ret = this->ReceiveBuffer(buffer, 8, &outSize);
	if (!ret)
		return MMGAPNSStatusCode::MMGAPNSStatusCodeUnknown;

	// Response size should be 6 bytes
	if (outSize != 6)
		return MMGAPNSStatusCode::MMGAPNSStatusCodeUnknown;

	// First byte is always 8
	const uint8_t command = buffer[0];
	if (command != 8)
		return MMGAPNSStatusCode::MMGAPNSStatusCodeUnknown;

	// Get the status
	const uint8_t status = buffer[1];
	// Get the notification ID (don't forget the endianness)
	*notificationId = htonl(*(uint32_t*)(&(buffer[2])));

	return static_cast<MMGAPNSStatusCode>(status);
}
