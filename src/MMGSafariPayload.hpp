//
// MMGSafariPayload.hpp
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


#ifndef __MMGSAFARIPAYLOAD_H__
#define __MMGSAFARIPAYLOAD_H__

#include "MMGPayload.hpp"
#include <vector>


class MMGSafariPayload : public MMGPayload
{
private:
	/// Notification title
	std::string _title;
	/// URL arguments
	std::vector<std::string> _urlArguments;

public:
	/**
	 * @brief Set message body, badge number, sound name to play and action button label
	 * @param body [in] : Message body
	 * @param actionKeyLabel [in] : Action button label
	 * @param title [in] : Message title
	 * @param urlArguments [in] : URL arguments for the URL to open when notification is clicked
	 */
	MMGSafariPayload(const std::string& body = "", const std::string& actionKeyLabel = "Show", const std::string& title = "", const std::vector<std::string>& urlArguments = std::vector<std::string>());

	/**
	 * @brief Destructor
	 */
	~MMGSafariPayload(void) {}

	/**
	 * @brief Get a reference to the the title
	 * @returns title as a std::string
	 */
	const std::string& GetTitle(void)const;

	/**
	 * @brief Get a reference to URL arguments
	 * @returns URL arguments as a std::vector<std::string>
	 */
	const std::vector<std::string>& GetURLArguments(void)const;

	/**
	 * @brief Set title and reconstruct the JSON payload
	 * @param title [in] : Message body
	 */
	void SetTitle(const std::string& title);

	/**
	 * @brief Set URL arguments and reconstruct the JSON payload
	 * @param urlArguments [in] : URL arguments
	 */
	void SetURLArguments(const std::vector<std::string>& urlArguments);

protected:
	/**
	 * @brief Create the JSON payload according to the ivars
	 */
	void _FormatPayload(void);
};

#endif /* __MMGSAFARIPAYLOAD_H__ */