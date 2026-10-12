#ifndef	__SECURITY__H
#define __SECURITY__H
#define	RSA_KEY_LEN		526	// DER format of RSA-4096
#define RSA_SIGN_LEN		512

#define SIFLOWER_SCB_BASE	0x0E010000

#define PKT_SHA0		(SIFLOWER_SCB_BASE + 0x840)	// sha256 input, 16 words
#define PKT_SHA(n)		(PKT_SHA0 + (n) * 4)
#define SHA_RESULT0		(SIFLOWER_SCB_BASE + 0x880)	// sha256 result, 8 words
#define SHA_RESULT(n)		(SHA_RESULT0 + (n) * 4)
#define SHA_STATUS_ADDR		(SIFLOWER_SCB_BASE + 0x8a0)
#define SHA_CTRL_REG_ADDR	(SIFLOWER_SCB_BASE + 0x8a4)

#define RSA_CTRL		(SIFLOWER_SCB_BASE + 0x0)
#define RSA_CIPHER0		(SIFLOWER_SCB_BASE + 0x440)	// rsa4096 decrypt result, 8 words
#define RSA_CIPHER(n)		(RSA_CIPHER0 + (n) * 4)
#define RSA_KEY_E0		(SIFLOWER_SCB_BASE + 0x640)	// rsa pub key exponent
#define RSA_KEY_E(n)		(RSA_KEY_E0 + (n) * 4)
#define RSA_KEY_N0		(SIFLOWER_SCB_BASE + 0x40)	// rsa pub key modulus, 128 words
#define RSA_KEY_N(n)		(RSA_KEY_N0 + (n) * 4)
#define RSA_PLAIN0		(SIFLOWER_SCB_BASE + 0x240)	// rsa signature, 128 words
#define RSA_PLAIN(n)		(RSA_PLAIN0 + (n) * 4)

#endif