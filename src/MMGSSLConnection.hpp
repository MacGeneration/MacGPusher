//
// MMGSSLConnection.hpp
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


#ifndef __MMGSSLCONNECTION_H__
#define __MMGSSLCONNECTION_H__

#include <string>
#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openssl/crypto.h>
#include <openssl/ssl.h>


enum class MMGConnectionError : unsigned short
{
	MMGNoError = 0,
	MMGAlreadyConnected,
	MMGSSLError,
	MMGSSLConnectError,
	MMGSSLContextCreateFail,
	MMGSSLInvalidCALocation,
	MMGSSLInvalidCertificateFile,
	MMGSSLInvalidPrivateKeyFile,
	MMGSSLInvalidPrivateKeyPair,
	MMGSocketError,
	MMGConnectError,
	MMGHostError,
};


class MMGSSLConnection
{
private:
	/// Hostname or IP of the server to connect
	std::string _hostname;
	/// Server port
	unsigned short _port;
	/// Certificates & keys directory path
	std::string _certsPath;
	/// Certificate path
	std::string _certFile;
	/// Private key path
	std::string _keyFile;
	/// Private key password
	std::string _keyPassword;
	/// Socket
	int _socket;
	/// sockaddr_in
	struct sockaddr_in _addr;
	/// Host info
	struct hostent* _hostent;
	/// SSL context
	SSL_CTX* _sslCtx;
	/// SSL struct
	SSL* _ssl;
	/// SSL method
	SSL_METHOD* _sslMethod;
	/// Server certificate
	X509* _serverCert;
	/// Private key
	EVP_PKEY* _privateKey;

public:
	/**
	 * @brief Initialize
	 * @param hostname [in] : Hostname or ip address of the server
	 * @param port [in] : Server port
	 * @param certsPath [in] : Path of the directory containing the certs
	 * @param certFile [in] : Path of the certificate file
	 * @param keyFile [in] : Path of the private key file
	 * @param keyPassword [in] : Password for the private key, pass an empty string in there is none
	 */
	MMGSSLConnection(const std::string& hostname, const unsigned short port, const std::string& certsPath, const std::string& certFile, const std::string& keyFile, const std::string& keyPassword);

	/**
	 * @brief Destructor: Close the socket and SSL stuff
	 */
	~MMGSSLConnection(void);

	/**
	 * @brief Returns the connection status
	 * @returns true if we are connected to the server, false otherwise
	 */
	bool IsConnected(void)const
	{
	  return ((this->_socket != -1) && (this->_ssl != NULL) && (this->_sslCtx != NULL));
	}

	/**
	 * @brief Connect to the server
	 * @returns MMGConnectionError error code, see enum
	 */
	MMGConnectionError OpenConnection(void);

	/**
	 * @brief Close the connection
	 */
	void CloseConnection(void);

	/**
	 * @brief Send a buffer to the server
	 * @param buffer [in] : Buffer to send
	 * @param size [in] : Size of the buffer
	 * @returns true if OK
	 */
	bool SendBuffer(const unsigned char* buffer, const size_t size);

	/**
	 * @brief Set hostname or IP address of the server
	 * @param hostname [in] : Hostname or IP address
	 */
	void SetHostname(const std::string& hostname) {this->_hostname = hostname;}

	/**
	 * @brief Set the port of the server
	 * @param port [in] : Port number
	 */
	void SetPort(const unsigned short port) {this->_port = port;}

private:
	/**
	 * @brief Close the socket and SSL
	 */
	void __CloseSocket(void);
};

#endif /* __MMGSSLCONNECTION_H__ */
