//
// MMGPayload.hpp
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


#ifndef __MMGPAYLOAD_H__
#define __MMGPAYLOAD_H__

#include <string>
#include <map>


class MMGPayload
{
private:
	/// Message displayed to the user
	std::string _messageBody;
	/// Number in the bubble
	unsigned int _badgeNumber;
	/// Name of the sound file to play
	std::string _soundName;
	/// Label of the action button
	std::string _actionKeyLabel;
	/// Formatted APNS payload as JSON
	std::string _formattedPayload;
	/// Custom dictionary accessible from the app
	std::map<std::string, std::string> _dict;

public:
	/**
	 * @brief Set message body, badge number, sound name to play and action button label
	 * @param messageBody [in] : Message body
	 * @param badgeNumber [in] : Badge number
	 * @param soundName [in] : Name of the sound file to play on the device
	 * @param actionKeyLabel [in] : Label of the action button
	 */
	MMGPayload(const std::string& messageBody = "", const unsigned int badgeNumber = 0, const std::string& soundName = "default", const std::string& actionKeyLabel = "");

	/**
	 * @brief Destructor
	 */
	~MMGPayload(void) {}

	/**
	 * @brief Get a reference to the the message body
	 * @returns Message body as a std::string
	 */
	const std::string& GetMessageBody(void)const;

	/**
	 * @brief Get the badge number
	 * @returns Badge number
	 */
	unsigned int GetBadgeNumber(void)const;

	/**
	 * @brief Get a reference to the sound name
	 * @returns Sound name as a std::string
	 */
	const std::string& GetSoundName(void)const;

	/**
	 * @brief Get a reference to the the action key label
	 * @returns Action key label as a std::string
	 */
	const std::string& GetActionKeyLabel(void)const;

	/**
	 * @brief Get a reference to the formatted payload, create it if needed
	 * @returns Payload as a json std::string
	 */
	const std::string& GetPayload(void);

	/**
	 * @brief Set message body and reconstruct the JSON payload
	 * @param messageBody [in] : Message body
	 */
	void SetMessageBody(const std::string& messageBody);

	/**
	 * @brief Set badge number and reconstruct the JSON payload
	 * @param badgeNumber [in] : Badge number
	 */
	void SetBadgeNumber(const unsigned int badgeNumber);

	/**
	 * @brief Set sound name and reconstruct the JSON payload
	 * @param soundName [in] : Name of the sound file to play on the device
	 */
	void SetSoundName(const std::string& soundName);

	/**
	 * @brief Set action button label and reconstruct the JSON payload
	 * @param actionKeyLabel [in] : Label of the action button
	 */
	void SetActionKeyLabel(const std::string& actionKeyLabel);

	/**
	 * @brief Set message body, badge number, sound name to play and action button label and reconstruct the JSON payload
	 * @param messageBody [in] : Message body
	 * @param badgeNumber [in] : Badge number
	 * @param soundName [in] : Name of the sound file to play on the device
	 * @param actionKeyLabel [in] : Label of the action button
	 */
	void SetAllProperties(const std::string& messageBody, const unsigned int badgeNumber, const std::string& soundName, const std::string& actionKeyLabel);

	/**
	 * @brief Set a pair of custom key/value
	 * @param key [in] : key
	 * @param value [in] : Value associated to key
	 * @returns true if the key/value pair was set, false if max limit
	 */
	bool AddKeyValuePair(const std::string& key, const std::string& value);

	/**
	 * @brief Remove a pair of key/value
	 * @param key [in] : key
	 */
	void RemoveValueForKey(const std::string& key);

private:
	/**
	 * @brief Create the JSON payload according to the ivars
	 */
	void _FormatPayload(void);
};

#endif /* __MMGPAYLOAD_H__ */
