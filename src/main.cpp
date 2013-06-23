//
//  main.cpp
//  MacGPusher
//
//  Created by Nyx0uf on 6/23/13.
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
	MMGPayload payload("Push message", device.GetBadge(), "sound.caf", "Slider label");

	// Create the APNS connection, empty string if no password for the private key
	MMGAPNSConnection connection(MMG_APNS_CA_PATH, MMG_APNS_CERT_PATH, MMG_APNS_PRIVATEKEY_PATH, "private-key-password", true);
	// Open the connection
	if (connection.OpenConnection() != MMGConnectionError::MMGNoError)
		return -1;

	// Send the payload
	connection.SendPayloadToDevice(payload, device);

	// Close the connection
	connection.CloseConnection();
	
	return 0;
}
