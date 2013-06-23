#include "MMGPayload.hpp"
#include "global.hpp"
#include "MMGTools.hpp"
#include <cstdio>
#include <cstring>


#define MMG_MAX_KEYVALUE 3


#pragma mark - Constructors
/**
 * @brief Initialize ivars to default values
 */
MMGPayload::MMGPayload(void)
{
	this->_messageBody = "";
	this->_badgeNumber = 0;
	this->_soundName = "default";
	this->_actionKeyLabel = "";
	this->_formattedPayload = "";
}

/**
 * @brief Set message body
 * @param messageBody [in] : Message body
 */
MMGPayload::MMGPayload(const std::string& messageBody) : MMGPayload()
{
	this->_messageBody = messageBody;
}

/**
 * @brief Set message body and badge number
 * @param messageBody [in] : Message body
 * @param badgeNumber [in] : Badge number
 */
MMGPayload::MMGPayload(const std::string& messageBody, const unsigned int badgeNumber) : MMGPayload(messageBody)
{
	this->_badgeNumber = badgeNumber;
}

/**
 * @brief Set message body, badge number and sound name to play
 * @param messageBody [in] : Message body
 * @param badgeNumber [in] : Badge number
 * @param soundName [in] : Name of the sound file to play on the device
 */
MMGPayload::MMGPayload(const std::string& messageBody, const unsigned int badgeNumber, const std::string& soundName) : MMGPayload(messageBody, badgeNumber)
{
	this->_soundName = (soundName.empty()) ? "default" : soundName;
}

/**
 * @brief Set message body, badge number, sound name to play and action button label
 * @param messageBody [in] : Message body
 * @param badgeNumber [in] : Badge number
 * @param soundName [in] : Name of the sound file to play on the device
 * @param actionKeyLabel [in] : Label of the action button
 */
MMGPayload::MMGPayload(const std::string& messageBody, const unsigned int badgeNumber, const std::string& soundName, const std::string& actionKeyLabel) : MMGPayload(messageBody, badgeNumber, soundName)
{
	this->_actionKeyLabel = actionKeyLabel;
}

#pragma mark - Setters
/**
 * @brief Set message body and reconstruct the JSON payload
 * @param messageBody [in] : Message body
 */
void MMGPayload::SetMessageBody(const std::string& messageBody)
{
	this->_messageBody = messageBody;
	this->_FormatPayload();
}

/**
 * @brief Set badge number and reconstruct the JSON payload
 * @param badgeNumber [in] : Badge number
 */
void MMGPayload::SetBadgeNumber(const unsigned int badgeNumber)
{
	this->_badgeNumber = badgeNumber;
	this->_FormatPayload();
}

/**
 * @brief Set sound name and reconstruct the JSON payload
 * @param soundName [in] : Name of the sound file to play on the device
 */
void MMGPayload::SetSoundName(const std::string& soundName)
{
	this->_soundName = (soundName.empty()) ? "default" : soundName;
	this->_FormatPayload();
}

/**
 * @brief Set action button label and reconstruct the JSON payload
 * @param actionKeyLabel [in] : Label of the action button
 */
void MMGPayload::SetActionKeyLabel(const std::string& actionKeyLabel)
{
	this->_actionKeyLabel = actionKeyLabel;
	this->_FormatPayload();
}

/**
 * @brief Set message body, badge number, sound name to play and action button label and reconstruct the JSON payload
 * @param messageBody [in] : Message body
 * @param badgeNumber [in] : Badge number
 * @param soundName [in] : Name of the sound file to play on the device
 * @param actionKeyLabel [in] : Label of the action button
 */
void MMGPayload::SetAllProperties(const std::string& messageBody, const unsigned int badgeNumber, const std::string& soundName, const std::string& actionKeyLabel)
{
	this->_messageBody = messageBody;
	this->_badgeNumber = badgeNumber;
	this->_soundName = (soundName.empty()) ? "default" : soundName;
	this->_actionKeyLabel = actionKeyLabel;
	this->_FormatPayload();
}

/**
 * @brief Set a pair of custom key/value 
 * @param key [in] : key
 * @param value [in] : Value associated to key
 * @return true if the key/value pair was set, false if max limit
 */
const bool MMGPayload::AddKeyValuePair(const std::string& key, const std::string& value)
{
	if (this->_dict.size() >= MMG_MAX_KEYVALUE)
		return false;
	this->_dict.insert(std::pair<std::string, std::string>(key, value));
	return true;
}

/**
 * @brief Remove a pair of key/value
 * @param key [in] : key
 */
void MMGPayload::RemoveValueForKey(const std::string& key)
{
	this->_dict.erase(key);
}

#pragma mark - Getters
/**
 * @brief Get the formatted payload, create it if needed
 * @return Payload as a json std::string
 */
const std::string& MMGPayload::GetPayload(void)
{
	if (this->_formattedPayload.empty())
		this->_FormatPayload();
	return this->_formattedPayload;
}

#pragma mark - Private
/**
 * @brief Create the JSON payload according to the ivars
 */
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
