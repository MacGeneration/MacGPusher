//
// MMGPayload.hpp
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
    /// Custom dictionary accessible from the app
	std::map<std::string, std::string> _dict;
	/// Formatted APNS payload as JSON
	std::string _formattedPayload;
public:
	/* Ctors/Dtors */
	MMGPayload(void);
	MMGPayload(const std::string&);
	MMGPayload(const std::string&, const unsigned int);
	MMGPayload(const std::string&, const unsigned int, const std::string&);
	MMGPayload(const std::string&, const unsigned int, const std::string&, const std::string&);
	~MMGPayload(void) {}
	/* Getters */
	const std::string& GetMessageBody(void)const {return this->_messageBody;}
	const unsigned int GetBadgeNumber(void)const {return this->_badgeNumber;}
	const std::string& GetSoundName(void)const {return this->_soundName;}
	const std::string& GetActionKeyLabel(void)const {return this->_actionKeyLabel;}
	const std::string& GetPayload(void);
	/* Setters */
	void SetMessageBody(const std::string&);
	void SetBadgeNumber(const unsigned int);
	void SetSoundName(const std::string&);
	void SetActionKeyLabel(const std::string&);
	void SetAllProperties(const std::string&, const unsigned int, const std::string&, const std::string&);
	/* */
	const bool AddKeyValuePair(const std::string&, const std::string&);
	void RemoveValueForKey(const std::string&);
private:
	/// Create the payload as JSON
	void _FormatPayload(void);
};

#endif /* __MMGPAYLOAD_H__ */
