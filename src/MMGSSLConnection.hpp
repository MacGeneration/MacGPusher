//
// MMGSSLConnection.hpp
//
// Copyright (c) 2013 @Nyx0uf. All rights reserved.
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
	std::string _hostname;
	std::string _certsPath;
	std::string _certFile;
	std::string _keyFile;
	std::string _keyPassword;
	unsigned short _port;
	/* Socket stuff */
	int _socket;
	struct sockaddr_in _addr;
	struct hostent* _hostent;
	/* SSL stuff */
	SSL_CTX* _sslCtx;
	SSL* _ssl;
	SSL_METHOD* _sslMethod;
	X509* _serverCert;
	EVP_PKEY* _privateKey;

public:
	/* Ctors/Dtors */
	MMGSSLConnection(const std::string&, const unsigned short, const std::string&, const std::string&, const std::string&, const std::string&);
	~MMGSSLConnection(void);
	/* Communication stuff */
	const bool IsConnected(void)const {return ((this->_socket != -1) && (this->_ssl != NULL) && (this->_sslCtx != NULL));}
	const MMGConnectionError OpenConnection(void);
	void CloseConnection(void);
	const bool SendBuffer(const unsigned char*, const size_t);
	/* Setters */
	void SetHostname(const std::string& hostname) {this->_hostname = hostname;}
	void SetPort(const unsigned short port) {this->_port = port;}
private:
	/// Close socket and SSL
	void __CloseSocket(void);
};

#endif /* __MMGSSLCONNECTION_H__ */
