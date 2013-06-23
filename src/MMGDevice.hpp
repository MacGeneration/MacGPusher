#ifndef __MMGDEVICE_H__
#define __MMGDEVICE_H__

#include <string>


class MMGDevice
{
private:
	/// Device token
	std::string _token;
	/// Badge number
	unsigned int _badge;

public:
	/* Ctors/Dtors */
	MMGDevice(void);
	MMGDevice(const std::string&, const unsigned int);
	~MMGDevice(void) {}
	/* Setters */
	void SetToken(const std::string&);
	void SetBadge(const unsigned int);
	/* Getters */
	const std::string& GetToken(void)const {return this->_token;}
	const unsigned int GetBadge(void)const {return this->_badge;}
};

#endif /* __MMGDEVICE_H__ */
