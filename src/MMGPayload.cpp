//
// MMGPayload.cpp
//
// Copyright (c) 2013 @Nyx0uf. All rights reserved.
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


#include "MMGPayload.hpp"
#include "global.hpp"
#include "MMGTools.hpp"
#include <cstdio>
#include <cstring>


#define MMG_MAX_KEYVALUE 3


#pragma mark - Constructors
MMGPayload::MMGPayload(void)
{
	this->_messageBody = "";
	this->_badgeNumber = 0;
	this->_soundName = "default";
	this->_actionKeyLabel = "";
	this->_formattedPayload = "";
}

MMGPayload::MMGPayload(const std::string& messageBody) : MMGPayload()
{
	this->_messageBody = messageBody;
}

MMGPayload::MMGPayload(const std::string& messageBody, const unsigned int badgeNumber) : MMGPayload(messageBody)
{
	this->_badgeNumber = badgeNumber;
}

MMGPayload::MMGPayload(const std::string& messageBody, const unsigned int badgeNumber, const std::string& soundName) : MMGPayload(messageBody, badgeNumber)
{
	this->_soundName = (soundName.empty()) ? "default" : soundName;
}

MMGPayload::MMGPayload(const std::string& messageBody, const unsigned int badgeNumber, const std::string& soundName, const std::string& actionKeyLabel) : MMGPayload(messageBody, badgeNumber, soundName)
{
	this->_actionKeyLabel = actionKeyLabel;
}

#pragma mark - Setters
void MMGPayload::SetMessageBody(const std::string& messageBody)
{
	this->_messageBody = messageBody;
	this->_FormatPayload();
}

void MMGPayload::SetBadgeNumber(const unsigned int badgeNumber)
{
	this->_badgeNumber = badgeNumber;
	this->_FormatPayload();
}

void MMGPayload::SetSoundName(const std::string& soundName)
{
	this->_soundName = (soundName.empty()) ? "default" : soundName;
	this->_FormatPayload();
}

void MMGPayload::SetActionKeyLabel(const std::string& actionKeyLabel)
{
	this->_actionKeyLabel = actionKeyLabel;
	this->_FormatPayload();
}

void MMGPayload::SetAllProperties(const std::string& messageBody, const unsigned int badgeNumber, const std::string& soundName, const std::string& actionKeyLabel)
{
	this->_messageBody = messageBody;
	this->_badgeNumber = badgeNumber;
	this->_soundName = (soundName.empty()) ? "default" : soundName;
	this->_actionKeyLabel = actionKeyLabel;
	this->_FormatPayload();
}

const bool MMGPayload::AddKeyValuePair(const std::string& key, const std::string& value)
{
	if (this->_dict.size() >= MMG_MAX_KEYVALUE)
		return false;
	this->_dict.insert(std::pair<std::string, std::string>(key, value));
	return true;
}

void MMGPayload::RemoveValueForKey(const std::string& key)
{
	this->_dict.erase(key);
}

#pragma mark - Getters
const std::string& MMGPayload::GetPayload(void)
{
	if (this->_formattedPayload.empty())
		this->_FormatPayload();
	return this->_formattedPayload;
}

#pragma mark - Private
void MMGPayload::_FormatPayload(void)
{
	// Ignore empty messages
	if (this->_messageBody.empty())
	{
		this->_formattedPayload = "";
		return;
	}

	// Begin JSON
	// see: http://developer.apple.com/library/ios/#documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/Chapters/ApplePushService.html#//apple_ref/doc/uid/TP40008194-CH100-SW9
	this->_formattedPayload = std::string("{\"aps\":{\"alert\":");

	// Custom action button label
	if (!this->_actionKeyLabel.empty())
		this->_formattedPayload += "{\"body\":\"" + this->_messageBody + "\",\"action-loc-key\":\"" + this->_actionKeyLabel + "\"},";
	else
		this->_formattedPayload += "\"" + this->_messageBody + "\",";

	// Badge number
	this->_formattedPayload += (std::string("\"badge\":") + MMGTools::UnsignedIntegerToString(this->_badgeNumber));

	// Sound
	this->_formattedPayload += ",\"sound\":\"" + this->_soundName + "\"}";
	
	// Custom key/values
	const std::map<std::string, std::string>::size_type size = _dict.size();
	if ((size > 0) && (size < MMG_MAX_KEYVALUE))
	{
		this->_formattedPayload += ",";
		unsigned int i = 0;
		for (const auto& kv : this->_dict)
		{
			this->_formattedPayload += "\"" + kv.first + "\":\"" + kv.second + "\"";
			if (i < (MMG_MAX_KEYVALUE - 1))
				this->_formattedPayload += ",";
			i++;
		}
	}

	// End JSON
	this->_formattedPayload += "}";
	MMG_DLOG("PAYLOAD: %s\n", this->_formattedPayload.c_str());
}
