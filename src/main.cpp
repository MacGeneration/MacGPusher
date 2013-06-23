//
//  main.cpp
//  MacGPusher
//
//  Created by Nyxouf on 6/23/13.
//  Copyright (c) 2013 MacGeneration. All rights reserved.
//

#include "global.hpp"
#include "MMGAPNSConnection.hpp"
#include "MMGDevice.hpp"
#include "MMGPayload.hpp"


int main(int argc, const char* argv[])
{
	// Create a device object
	const unsigned int badge = 1;
	MMGDevice device("device-token", badge);

	// Create a payload object
	MMGPayload payload("Push message", device.GetBadge(), "sound.caf", "Slider LABEL");

	// Create the APNS connection
	MMGAPNSConnection connection(MMG_APNS_CA_PATH, MMG_APNS_CERT_PATH, MMG_APNS_PRIVATEKEY_PATH, true);
	// Open the connection
	if (connection.OpenConnection() != MMGConnectionError::MMGNoError)
		return -1;

	// Send the payload
	connection.SendPayloadToDevice(payload, device);

	// Close the connection
	connection.CloseConnection();
	
	return 0;
}
