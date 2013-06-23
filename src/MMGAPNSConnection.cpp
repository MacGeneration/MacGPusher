#include "MMGAPNSConnection.hpp"
#include "global.hpp"
#include "MMGPayload.hpp"
#include "MMGDevice.hpp"


#define MMG_MAXPAYLOAD_SIZE 256
#define MMG_DEVICE_BINARY_SIZE 32


#pragma mark - Constructor
/**
 * @brief Initialize with APNS params
 * @param certsPath [in] : Path of the directory containing the certs
 * @param certFile [in] : Path of the certificate file
 * @param keyFile [in] : Path of the private key file
 * @param sandbox [in] : Sandbox env
 */
MMGAPNSConnection::MMGAPNSConnection(const std::string& certsPath, const std::string& certFile, const std::string& keyFile, const bool sandbox) : MMGSSLConnection((sandbox) ? MMG_APNS_SERVER_SANDBOX : MMG_APNS_SERVER, MMG_APNS_PORT, certsPath, certFile, keyFile)
{
	_sandbox = sandbox;
}

#pragma mark - Public
/**
 * @brief Send a payload to a given device
 * @param payload [in] : Payload to send
 * @param device [in] : Device
 * @return true if send OK
 */
const bool MMGAPNSConnection::SendPayloadToDevice(MMGPayload& payload, const MMGDevice& device)
{
	const std::string& token = device.GetToken();
	const std::string::size_type tokenLen = token.size();
	if (0 == tokenLen)
		return false;

	const char* payloadBuffer = payload.GetPayload().c_str();
	const size_t payloadLen = strlen(payloadBuffer);
	char binaryMessageBuff[sizeof(uint8_t) + sizeof(uint16_t) + MMG_DEVICE_BINARY_SIZE + sizeof(uint16_t) + MMG_MAXPAYLOAD_SIZE];
	
	// Message format: |COMMAND|TOKENLEN|TOKEN|PAYLOADLEN|PAYLOAD|
	char* binaryMessagePt = binaryMessageBuff;

	// Command
	const uint8_t command = 0; // command number
	*binaryMessagePt++ = command;

	// Token length network order
	const uint16_t networkOrderTokenLen = htons(MMG_DEVICE_BINARY_SIZE);
	memcpy(binaryMessagePt, &networkOrderTokenLen, sizeof(uint16_t));
	binaryMessagePt += sizeof(uint16_t);

	// Convert the device token
	size_t i = 0, j = 0;
	int tmpi;
	char tmp[3] = {0x00};
	char deviceTokenBinary[MMG_DEVICE_BINARY_SIZE];
	while (i < tokenLen)
	{
		if (token[i] == ' ')
			i++;
		else
		{
			tmp[0] = token[i];
			tmp[1] = token[i + 1];
			
			sscanf(tmp, "%x", &tmpi);
			deviceTokenBinary[j] = (char)tmpi;
			
			i += 2;
			j++;
		}
	}
	memcpy(binaryMessagePt, deviceTokenBinary, MMG_DEVICE_BINARY_SIZE);
	binaryMessagePt += MMG_DEVICE_BINARY_SIZE;
	
	// Payload length network order
	const uint16_t networkOrderPayloadLen = htons(payloadLen);
	memcpy(binaryMessagePt, &networkOrderPayloadLen, sizeof(uint16_t));
	binaryMessagePt += sizeof(uint16_t);
	
	// Payload
	memcpy(binaryMessagePt, payloadBuffer, payloadLen);
	binaryMessagePt += payloadLen;
	return this->SendBuffer((unsigned char*)binaryMessageBuff, (size_t)(binaryMessagePt - binaryMessageBuff));
}
