#include "global.hpp"
#include "MMGFeedbackConnection.hpp"
#include "MMGDevice.hpp"
#include <cstdlib>


#ifdef __APPLE__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif


int main(void)
{
	// SSL init only once
	SSL_load_error_strings();
	SSL_library_init();

	std::vector<MMGDevice*> devices;
	MMGFeedbackConnection* feedbackConnection = new MMGFeedbackConnection(MMG_APNS_CA_PATH, MMG_APNS_CERT_PATH, MMG_APNS_PRIVATEKEY_PATH, "", false);
	feedbackConnection->GetExpiredDevicesList(devices);
	delete feedbackConnection;

	for (MMGDevice* device : devices)
	{
		// Do your stuff here
		delete device;
	}

	return EXIT_SUCCESS;
}
