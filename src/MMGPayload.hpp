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


class MMGPayload
{
protected:
	/// Message displayed to the user
	std::string _body;
	/// Label of the action button
	std::string _actionKeyLabel;
	/// Formatted APNS payload as JSON
	std::string _formattedPayload;

public:
	/**
	 * @brief Set message body, badge number, sound name to play and action button label
	 * @param body [in] : Message body
	 * @param actionKeyLabel [in] : Label of the action button
	 */
	MMGPayload(const std::string& body = "", const std::string& actionKeyLabel = "");

	/**
	 * @brief Destructor
	 */
	virtual ~MMGPayload(void) {}

	/**
	 * @brief Get a reference to the the message body
	 * @returns Message body as a std::string
	 */
	const std::string& GetBody(void)const;

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
	 * @param body [in] : Message body
	 */
	void SetBody(const std::string& body);

	/**
	 * @brief Set action button label and reconstruct the JSON payload
	 * @param actionKeyLabel [in] : Label of the action button
	 */
	void SetActionKeyLabel(const std::string& actionKeyLabel);

protected:
	/**
	 * @brief Create the JSON payload according to the ivars
	 */
	virtual void _FormatPayload(void) = 0;
};

#endif /* __MMGPAYLOAD_H__ */
