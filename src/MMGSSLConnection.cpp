//
// MMGSSLConnection.cpp
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


#include "MMGSSLConnection.hpp"
#include "global.hpp"
#include <openssl/err.h>


/* SSL_* calls are marked deprecated on OS X 10.7+ */
#ifdef __APPLE__
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma gcc diagnostic ignored "-Wdeprecated-declarations"
#endif


MMGSSLConnection::MMGSSLConnection(const std::string& hostname, const unsigned short port, const std::string& certsPath, const std::string& certFile, const std::string& keyFile, const std::string& keyPassword)
{
	this->_hostname = hostname;
	this->_port = port;
	this->_certsPath = certsPath;
	this->_certFile = certFile;
	this->_keyFile = keyFile;
	this->_keyPassword = keyPassword;
	this->_socket = -1;
	this->_hostent = NULL;
	this->_sslCtx = NULL;
	this->_ssl = NULL;
	this->_serverCert = NULL;
	this->_privateKey = NULL;
	// Choose a SSL/TLS protocol version
	this->_sslMethod = (SSL_METHOD*)SSLv3_method();
	// SSL init
	//SSL_library_init();
	//SSL_load_error_strings();
}

MMGSSLConnection::~MMGSSLConnection(void)
{
	// Tear down the connection
	this->CloseConnection();
}

bool MMGSSLConnection::IsConnected(void)const
{
	return ((this->_socket != -1) && (this->_ssl != NULL) && (this->_sslCtx != NULL));
}

MMGConnectionError MMGSSLConnection::OpenConnection(void)
{
	// If already connected, bye bye
	if (this->IsConnected())
		return MMGConnectionError::MMGAlreadyConnected;

    // Create a SSL context
	this->_sslCtx = SSL_CTX_new(this->_sslMethod);
	if (NULL == this->_sslCtx)
	{
		MMG_ERRLOG("[!] Failed to create a SSL context\n");
		return MMGConnectionError::MMGSSLContextCreateFail;
	}

	// Load the client certificate into the SSL context
	if (SSL_CTX_use_certificate_file(this->_sslCtx, this->_certFile.c_str(), SSL_FILETYPE_PEM) <= 0)
	{
		MMG_ERRLOG("[!] Cannot use certificate file <%s>\n", this->_certFile.c_str());
		ERR_print_errors_fp(stderr);
		return MMGConnectionError::MMGSSLInvalidCertificateFile;
	}

    // Load the private-key corresponding to the client certificate
	if (!this->_keyPassword.empty())
		SSL_CTX_set_default_passwd_cb_userdata(this->_sslCtx, (void*)this->_keyPassword.c_str());
	if (SSL_CTX_use_PrivateKey_file(this->_sslCtx, this->_keyFile.c_str(), SSL_FILETYPE_PEM) <= 0)
	{
		MMG_ERRLOG("[!] Cannot use private key file <%s>\n", this->_keyFile.c_str());
		ERR_print_errors_fp(stderr);
		return MMGConnectionError::MMGSSLInvalidPrivateKeyFile;
	}

	// Load the CA
	if (SSL_CTX_load_verify_locations(this->_sslCtx, NULL, this->_certsPath.c_str()) <= 0)
	{
        MMG_ERRLOG("[!] Failed to set CA location...\n");
        ERR_print_errors_fp(stderr);
		return MMGConnectionError::MMGSSLInvalidCALocation;
	}

	// Check if the client certificate and private-key matches
	if (!SSL_CTX_check_private_key(this->_sslCtx))
	{
		MMG_ERRLOG("[!] Private key does not match the certificate public key\n");
		return MMGConnectionError::MMGSSLInvalidPrivateKeyPair;
	}

    // Set up a TCP socket
	this->_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == this->_socket)
	{
		MMG_ERRLOG("[!] Failed to create socket\n");
		return MMGConnectionError::MMGSocketError;
	}

	memset(&this->_addr, 0x00, sizeof(this->_addr));
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(this->_port);
	this->_hostent = gethostbyname(this->_hostname.c_str());
	if (this->_hostent)
	{
		// Take the first IP
		struct in_addr* address = (struct in_addr*)this->_hostent->h_addr_list[0];
		this->_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*address));
	}
    else
	{
		MMG_ERRLOG("Could not resolve hostname %s\n", this->_hostname.c_str());
		return MMGConnectionError::MMGHostError;
	}

	// Establish a TCP/IP connection to the SSL client
	int err = connect(this->_socket, (struct sockaddr*)&this->_addr, sizeof(this->_addr));
	if (-1 == err)
	{
		MMG_ERRLOG("Could not connect\n");
		return MMGConnectionError::MMGConnectError;
	}

    // Create a SSL structure
	this->_ssl = SSL_new(this->_sslCtx);
	if (NULL == this->_ssl)
	{
		MMG_ERRLOG("Could not get SSL Socket\n");
		return MMGConnectionError::MMGSSLError;
	}

	// Assign the socket into the SSL structure (SSL and socket without BIO)
	SSL_set_fd(this->_ssl, this->_socket);

	// Perform SSL Handshake on the SSL client
	err = SSL_connect(this->_ssl);
	if (err <= 0)
	{
		MMG_ERRLOG("Could not connect to SSL Server\n");
		return MMGConnectionError::MMGSSLConnectError;
	}
	return MMGConnectionError::MMGNoError;
}

void MMGSSLConnection::CloseConnection(void)
{
	this->__CloseSocket();
}

bool MMGSSLConnection::SendBuffer(const unsigned char* buffer, const size_t size)
{
	if (!this->_ssl)
		return false;
	const int ret = SSL_write(this->_ssl, buffer, static_cast<int>(size));
#ifdef MMG_DEBUG
	if (ret <= 0)
	{
		ERR_print_errors_fp(stderr);
	}
#endif
	return (ret > 0);
}

void MMGSSLConnection::SetHostname(const std::string& hostname)
{
	this->_hostname = hostname;
}

void MMGSSLConnection::SetPort(const unsigned short port)
{
	this->_port = port;
}

void MMGSSLConnection::__CloseSocket(void)
{
	if (!this->IsConnected())
		return;

	// Shutdown the client side of the SSL connection
	SSL_shutdown(this->_ssl);

	// Terminate communication on a socket
	close(this->_socket), _socket = -1;

	// Free the SSL structure
	SSL_free(this->_ssl), this->_ssl = NULL;
	// Free the SSL_CTX structure
	SSL_CTX_free(this->_sslCtx), this->_sslCtx = NULL;
}
