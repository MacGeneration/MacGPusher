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
