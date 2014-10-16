#include "global.hpp"
#include "MMGFeedbackConnection.hpp"
#include "MMGDevice.hpp"
#include <cstdlib>


#ifdef __APPLE__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif


int main(void)
{
	// SLL init only once
	SSL_load_error_strings();
	SSL_library_init();

	std::vector<MMGDevice*> devices;
	MMGFeedbackConnection* feedbackConnection = new MMGFeedbackConnection(dbi._capath, dbi._cert, dbi._key, "", false);
	feedbackConnection->GetExpiredDevicesList(devices);
	delete feedbackConnection;

	for (MMGDevice* device : devices)
	{
		// Do your stuff here
		delete device;
	}

	return EXIT_SUCCESS;
}
