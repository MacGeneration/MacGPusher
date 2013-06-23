#ifndef __MMGAPNSCONNECTION_H__
#define __MMGAPNSCONNECTION_H__

#include "MMGSSLConnection.hpp"
class MMGPayload;
class MMGDevice;


class MMGAPNSConnection : public MMGSSLConnection
{
private:
	/// Sandbox flag
	bool _sandbox;

public:
	/* Ctors/Dtors */
	MMGAPNSConnection(const std::string&, const std::string&, const std::string&, const std::string&, const bool);
	~MMGAPNSConnection(void) {}
	/// Send a payload to a device
	const bool SendPayloadToDevice(MMGPayload&, const MMGDevice&);
};

#endif /* __MMGAPNSCONNECTION_H__ */
