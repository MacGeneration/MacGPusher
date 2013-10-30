//
// main.cpp
//
// Copyright (c) 2013 MacGeneration. All rights reserved.
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


#include "global.hpp"
#include "MMGAPNSConnection.hpp"
#include "MMGDevice.hpp"
#include "MMGPayload.hpp"
#include "MMGTools.hpp"
#include <vector>
#include <cstdlib>


#ifdef __APPLE__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma gcc diagnostic ignored "-Wdeprecated-declarations"
#endif


static size_t get_devices_list(std::vector<MMGDevice*>& vec)
{
	// Implement your code logic to grab a list of devices
	const unsigned int badge = 1;
	MMGDevice* device = new MMGDevice("token", badge);
	vec.push_back(device);
	return vec.size();
#if 0
	/* MySQL bridging example
	 
	 need to link with libmysqlclient or libmysqclient_r (multithread)
	 also #include <mysql/mysql.h>

	 let's assume we have a simple table like that
	 --------------
	 |   devices  |
	 |------------|
	 |token       |
	 |unread_count|
	 --------------
	 */

	mysql_library_init(0, NULL, NULL);

	// Connect to db
	MYSQL* conn = mysql_init(NULL);
	if (NULL == conn)
	{
		MMG_ERRLOG("[!] Not enough memory to allocate the MySQL connection\n");
		return 0;
	}
	mysql_options(conn, MYSQL_SET_CHARSET_NAME, "utf8");
	if (!mysql_real_connect(conn, "host-or-ip", "user", "password", "database", 0, NULL, 0))
	{
		MMG_ERRLOG("[!] mysql_real_connect: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	
	// SELECT devices list
	const char* query = "SELECT token, unread_count FROM devices";
	if (mysql_query(conn, query) != 0)
	{
		MMG_ERRLOG("[!] mysql_query: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	MYSQL_RES* res = mysql_use_result(conn);
	if (NULL == res)
	{
		MMG_ERRLOG("[!] mysql_use_result: %s\n", mysql_error(conn));
		mysql_close(conn);
		return 0;
	}
	
	// Build the list of MMGDevices
	MYSQL_ROW row = NULL;
	while ((row = mysql_fetch_row(res)))
	{
		MMGDevice* device = new MMGDevice(row[0], MMGTools::StringToUnsignedInteger(row[1]));
		vec.push_back(device);
    }
	
	mysql_free_result(res);
	mysql_close(conn);
	
	return vec.size();
#endif
}

int main(void)
{
	// SLL init only once
	SSL_load_error_strings();
	SSL_library_init();

	// Get a list of devices
	std::vector<MMGDevice*> devices;
	get_devices_list(devices);

	// Create a payload object
	MMGPayload payload("Push message", 1, "sound.caf", "Slider label");

	// Create the APNS connection, empty string if no password for the private key
	MMGAPNSConnection connection(MMG_APNS_CA_PATH, MMG_APNS_CERT_PATH, MMG_APNS_PRIVATEKEY_PATH, "private-key-password", true);
	// Open the connection
	if (connection.OpenConnection() != MMGConnectionError::MMGNoError)
		return EXIT_FAILURE;

	// Send the payload
	for (MMGDevice* device : devices)
	{
		// Update payload badge number to reflect device's one
		payload.SetBadgeNumber(device->GetBadge());
		// Send payload to the device
		connection.SendPayloadToDevice(payload, *device);
	}

	// Free up memory
	for (MMGDevice* device : devices)
		delete device;

	// Close the connection
	connection.CloseConnection();

	return EXIT_SUCCESS;
}
