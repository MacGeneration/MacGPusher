//
// MMGFeedbackConnection.hpp
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


#ifndef __MMGFEEDBACKCONNECTION_H__
#define __MMGFEEDBACKCONNECTION_H__

#include "MMGSSLConnection.hpp"
#include <vector>
class MMGDevice;


class MMGFeedbackConnection : public MMGSSLConnection
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
	MMGFeedbackConnection(const std::string& certsPath, const std::string& certFile, const std::string& keyFile, const std::string& keyPassword, const bool sandbox);

	/**
	 * @brief Destructor
	 */
	~MMGFeedbackConnection(void) {}

	/**
	 * @brief Get a list of expired devices
	 * @param devices [out] : List of expired devices
	 * @returns true if list was successfully retrieved
	 */
	bool GetExpiredDevicesList(std::vector<MMGDevice*>& devices);
};


#endif /* __MMGFEEDBACKCONNECTION_H__ */
