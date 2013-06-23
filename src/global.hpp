#ifndef __MMGGLOBAL_H_
#define __MMGGLOBAL_H_


/* DEBUG FLAG */
//#define MMG_DEBUG
#undef MMG_DEBUG


#ifdef MMG_DEBUG
#define MMG_DLOG(...) fprintf(stdout, __VA_ARGS__)
#else
#define MMG_DLOG(...) ((void)0)
#define NDEBUG // Block assert
#endif /* MMG_DEBUG */

#define MMG_ERRLOG(...) fprintf(stderr, __VA_ARGS__)


/* APNS */
#define MMG_APNS_SERVER "gateway.push.apple.com"
#define MMG_APNS_SERVER_SANDBOX "gateway.sandbox.push.apple.com"
#define MMG_APNS_PORT 2195

#define MMG_APNS_FEEDBACK_SERVER "feedback.push.apple.com"
#define MMG_APNS_FEEDBACK_SERVER_SANDBOX "feedback.sandbox.push.apple.com"
#define MMG_APNS_FEEDBACK_PORT 2196

#define MMG_APNS_CA_PATH "/path/to/certs/dir/"
#define MMG_APNS_CERT_PATH "/path/to/certs/dir/cert.pem"
#define MMG_APNS_PRIVATEKEY_PATH "/path/to/certs/dir/key.pem"

#endif /* __MMGGLOBAL_H_ */
