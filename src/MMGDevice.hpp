//
// MMGDevice.hpp
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


#ifndef __MMGDEVICE_H__
#define __MMGDEVICE_H__

#include <string>

#define MMG_DEVICE_BINARY_SIZE 32


class MMGDevice
{
private:
	/// Device token
	std::string _token = "";
	/// Badge number
	unsigned int _badge = 0;
	/// Binary token
	char _binaryToken[MMG_DEVICE_BINARY_SIZE];

public:
	/**
	 * @brief Initialize token and badge number
	 * @param token [in] : Device token
	 * @param port [in] : Badge number
	 */
	MMGDevice(const std::string& token, const unsigned int badge);

	/**
	 * @brief Destructor
	 */
	~MMGDevice(void) {}

	/**
	 * @brief Set device token
	 * @param token [in] : Device token
	 */
	void SetToken(const std::string& token);

	/**
	 * @brief Set device badge number
	 * @param badge [in] : Badge number
	 */
	void SetBadge(const unsigned int badge);

	/**
	 * @brief Get the device token
	 * @returns Reference to the device token string
	 */
	const std::string& GetToken(void)const;

	/**
	 * @brief Get the device badge number
	 * @returns Badge number
	 */
	unsigned int GetBadge(void)const;

	/**
	 * @brief Get the binary token
	 * @returns Binary token as a char array
	 */
	const char* GetBinaryToken(void)const;

private:
	/**
	 * @brief Convert the 64b ASCII token to his binary representation
	 */
	void __CreateBinaryToken(void);
};

#endif /* __MMGDEVICE_H__ */
