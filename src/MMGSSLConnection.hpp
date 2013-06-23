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
