//
// global.hpp
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


#ifndef __MMGGLOBAL_H_
#define __MMGGLOBAL_H_


/* DEBUG FLAG */
//#define MMG_DEBUG
#undef MMG_DEBUG


#ifdef MMG_DEBUG
#define MMG_DLOG(...) fprintf(stdout, __VA_ARGS__)
#else
#define MMG_DLOG(...) ((void)0)
#define NDEBUG
#endif /* MMG_DEBUG */

/* Error log macro */
#define MMG_ERRLOG(...) fprintf(stderr, __VA_ARGS__)


/* APNS */
#define MMG_APNS_SERVER "gateway.push.apple.com"
#define MMG_APNS_SERVER_SANDBOX "gateway.sandbox.push.apple.com"
#define MMG_APNS_PORT 2195
/* APNS - FEEDBACK */
#define MMG_APNS_FEEDBACK_SERVER "feedback.push.apple.com"
#define MMG_APNS_FEEDBACK_SERVER_SANDBOX "feedback.sandbox.push.apple.com"
#define MMG_APNS_FEEDBACK_PORT 2196
/* Certificates paths */
#define MMG_APNS_CA_PATH "/path/to/certs/dir/"
#define MMG_APNS_CERT_PATH "/path/to/certs/dir/cert.pem"
#define MMG_APNS_PRIVATEKEY_PATH "/path/to/certs/dir/key.pem"

#endif /* __MMGGLOBAL_H_ */
