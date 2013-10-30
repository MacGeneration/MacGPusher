//
// MMGSafariPayload.cpp
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


#include "MMGSafariPayload.hpp"
#include "global.hpp"


MMGSafariPayload::MMGSafariPayload(const std::string& body, const std::string& actionKeyLabel, const std::string& title, const std::vector<std::string>& urlArguments)
: MMGPayload(body, actionKeyLabel), _title(title), _urlArguments(urlArguments)
{
}

const std::string& MMGSafariPayload::GetTitle(void)const
{
	return this->_title;
}

const std::vector<std::string>& MMGSafariPayload::GetURLArguments(void)const
{
	return this->_urlArguments;
}

void MMGSafariPayload::SetTitle(const std::string& title)
{
	this->_title = title;
	this->_FormatPayload();
}

void MMGSafariPayload::SetURLArguments(const std::vector<std::string>& urlArguments)
{
	this->_urlArguments = urlArguments;
	this->_FormatPayload();
}

void MMGSafariPayload::_FormatPayload(void)
{
	// Ignore empty messages
	if ((this->_body.empty()) || (this->_title.empty()))
	{
		this->_formattedPayload = "";
		return;
	}
	
	// Begin JSON
	this->_formattedPayload = std::string("{\"aps\":{\"alert\":{\"title\":");
	// Title
	this->_formattedPayload += std::string("\"" + this->_title + "\"");

	// Body
	this->_formattedPayload += std::string(",\"body\":\"" + this->_body + "\"");

	// Custom action button label
	this->_formattedPayload += std::string(",\"action\":\"" + (_actionKeyLabel.empty() ? "Show" : this->_actionKeyLabel) + "\"}");

	// URL args
	if (_urlArguments.size() > 0)
	{
		this->_formattedPayload += ",\"url-args\":[";
		for (auto str : this->_urlArguments)
		{
			this->_formattedPayload += std::string("\"" + str + "\",");
		}
		this->_formattedPayload.erase(this->_formattedPayload.size() - 1); // Remove last ','
		this->_formattedPayload += "]}";
	}
	else
		this->_formattedPayload += "}";

	// End JSON
	this->_formattedPayload += "}";

	MMG_DLOG("[+] PAYLOAD: %s\n", this->_formattedPayload.c_str());
}
