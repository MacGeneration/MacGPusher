//
// MMGAPNSConnection.hpp
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


#ifndef __MMGAPNSCONNECTION_H__
#define __MMGAPNSCONNECTION_H__

#include "MMGSSLConnection.hpp"
class MMGPayload;
class MMGDevice;


enum class MMGNotificationPriority : uint8_t
{
	MMGNotificationPrioritySendLater = 5,
	MMGNotificationPrioritySendNow = 10,
};


class MMGAPNSConnection : public MMGSSLConnection
{
private:
	/// Sandbox flag
	bool _sandbox;

public:
	/**
	 * @brief Initialize with APNS params
	 * @param certsPath [in] : Path of the directory containing the certs
	 * @param certFile [in] : Path of the certificate file
	 * @param keyFile [in] : Path of the private key file
	 * @param keyPassword [in] : Password for the private key, pass an empty string in there is none
	 * @param sandbox [in] : Sandbox env
	 */
	MMGAPNSConnection(const std::string& certsPath, const std::string& certFile, const std::string& keyFile, const std::string& keyPassword, const bool sandbox);

	/**
	 * @brief Destructor
	 */
	~MMGAPNSConnection(void) {}

	/**
	 * @brief Send a payload to a given device
	 * @param payload [in] : Payload to send
	 * @param device [in] : Device
	 * @returns true if send OK
	 */
	bool SendPayloadToDevice(MMGPayload& payload, const MMGDevice& device);

	/**
	 * @brief Send a payload to a given device, using the last spec from Apple
	 * @param payload [in] : Payload to send
	 * @param device [in] : Device
	 * @param notificationId [in] : ID of the notification
	 * @param expiration [in] : UNIX epoch time indicating when the notification should expires (default=0, immediately). For example, if you want to keep it for a day you want to pass time(NULL) + 86400
	 * @param priority [in] : Notification priority, MMGNotificationPrioritySendNow will send immediately, MMGNotificationPrioritySendLater will let Apple decide what's best
	 * @param notificationId [in] : ID of the notification
	 * @returns true if send OK
	 */
	bool SendPayloadToDevice_new(MMGPayload& payload, const MMGDevice& device, const uint32_t notificationId, const uint32_t expiration = 0, const MMGNotificationPriority priority = MMGNotificationPriority::MMGNotificationPrioritySendNow);
};

#endif /* __MMGAPNSCONNECTION_H__ */
