#ifndef CREEPTO_SHA1_H
#define CREEPTO_SHA1_H

// https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "sha256.h"

enum
{
	SHA1_MESSAGE_BLOCK_SIZE = 64,
	SHA1_HASH_SIZE = 20
};

// SHA-1 uses a sequence of logical functions, f0, f1,…, f79. Each function ft, where 0 £ t < 79,
// operates on three 32-bit words, x, y, and z, and produces a 32-bit word as output. The function ft
// (x, y, z) is defined as follows:
typedef struct sha1_message_t
{
	uint8_t *message;
	uint64_t message_length;
	uint64_t bits_length;
	uint32_t last_block;
} sha1_message_t;

typedef struct SHA1_t
{
	uint32_t H[SHA1_HASH_SIZE / 4];
	uint32_t message_block_index;
	sha1_message_t sha256_message;
} SHA1_t_ctx;

static uint32_t function_t(uint32_t x, uint32_t y, uint32_t z, uint8_t t)
{
	if (60 <= t)
	{
		return x ^ y ^ z;
	}
	if (40 <= t)
	{
		return (x & y) ^ (x & z) ^ (y & z);
	}
	if (20 <= t)
	{
		return x ^ y ^ z;
	}
	if (0 <= t)
	{
		return (x & y) ^ ((~x) & z);
	}
}
// ROTL n(x) = (x << n) v (x >> w - n).
static uint32_t SHA1_ROTL(uint32_t n, uint32_t x)
{
	return (x << n) | (x >> (32 - n));
}
// SHA-1 uses a sequence of eighty constant 32-bit words, K0, K1,…, K79, which are given b
static uint32_t sha1_K(uint8_t t)
{
	if (60 <= t)
	{
		return 0xca62c1d6;
	}
	if (40 <= t)
	{
		return 0x8f1bbcdc;
	}
	if (20 <= t)
	{
		return 0x6ed9eba1;
	}
	if (0 <= t)
	{
		return 0x5a827999;
	}
}

static void sha1_process_input(sha1_message_t *sha1_message, uint8_t *message, size_t message_length)
{
	sha1_message->message = (uint8_t *)malloc(sizeof(uint8_t) * message_length);
	memcpy(sha1_message->message, message, message_length * sizeof(uint8_t));
	sha1_message->message_length = message_length;
	sha1_message->bits_length = message_length * 8;
}

// The message, M, shall be padded before hash computation begins. The purpose of this padding
// is to ensure that the padded message is a multiple of 512 or 1024 bits, depending on the
// algorithm.
static void sha1_padd_message(sha1_message_t *sha1_message)
{
	uint32_t last_block = (sha1_message->message_length / SHA1_MESSAGE_BLOCK_SIZE);
	uint8_t block_bytes_to_padd;

	if (block_bytes_to_padd = (uint8_t)(sha1_message->message_length % SHA1_MESSAGE_BLOCK_SIZE))
	{
		uint8_t bytes_left = SHA1_MESSAGE_BLOCK_SIZE - block_bytes_to_padd;

		uint8_t block_message[SHA1_MESSAGE_BLOCK_SIZE];
		memset(block_message, 0, SHA1_MESSAGE_BLOCK_SIZE * sizeof(uint8_t));
		memcpy(block_message, sha1_message->message + (SHA1_MESSAGE_BLOCK_SIZE * last_block), block_bytes_to_padd * sizeof(uint8_t));
		block_message[block_bytes_to_padd] = 0x80;

		block_message[56] = (uint8_t)((sha1_message->bits_length >> 56) & 0xFF);
		block_message[57] = (uint8_t)((sha1_message->bits_length >> 48) & 0xFF);
		block_message[58] = (uint8_t)((sha1_message->bits_length >> 40) & 0xFF);
		block_message[59] = (uint8_t)((sha1_message->bits_length >> 32) & 0xFF);
		block_message[60] = (uint8_t)((sha1_message->bits_length >> 24) & 0xFF);
		block_message[61] = (uint8_t)((sha1_message->bits_length >> 16) & 0xFF);
		block_message[62] = (uint8_t)((sha1_message->bits_length >> 8) & 0xFF);
		block_message[63] = (uint8_t)(sha1_message->bits_length & 0xFF);
		uint8_t *ptr = (uint8_t *)realloc(sha1_message->message, sizeof(uint8_t) * (sha1_message->message_length + bytes_left));
		sha1_message->message = ptr;
		memcpy(sha1_message->message + (SHA1_MESSAGE_BLOCK_SIZE * last_block), block_message, SHA1_MESSAGE_BLOCK_SIZE * sizeof(uint8_t));
		sha1_message->last_block = last_block + 1;
	}
}

void sha1_prepare_w(uint32_t *W, uint8_t *block_message)
{
	for (size_t t = 0; t < 16; t++)
	{
		W[t] = (uint32_t)(block_message[t * 4] << 24);
		W[t] |= (uint32_t)(block_message[(t * 4) + 1] << 16);
		W[t] |= (uint32_t)(block_message[(t * 4) + 2] << 8);
		W[t] |= (uint32_t)(block_message[(t * 4) + 3]);
	}
	for (size_t t = 16; t < 80; t++)
	{
		W[t] = SHA1_ROTL(1, (W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]));
	}
}

void sha1_digest_hash(SHA1_t_ctx *sha1_ctx, sha1_message_t *sha1_message)
{
	uint32_t W[80];

	// For SHA-1, the initial hash value, H(0), shall consist of the following five 32-bit words, in hex:
	sha1_ctx->H[0] = 0x67452301;
	sha1_ctx->H[1] = 0xefcdab89;
	sha1_ctx->H[2] = 0x98badcfe;
	sha1_ctx->H[3] = 0x10325476;
	sha1_ctx->H[4] = 0xc3d2e1f0;

	for (uint32_t i = 0; i < sha1_message->last_block; i++)
	{
		memset(W, 0, 80 * sizeof(uint32_t));

		sha1_prepare_w(W, sha1_message->message + (SHA1_MESSAGE_BLOCK_SIZE * i));

		// Initialize the five working variables, a, b, c, d, and e, with the (i-1) st hash value:
		uint32_t a = sha1_ctx->H[0];
		uint32_t b = sha1_ctx->H[1];
		uint32_t c = sha1_ctx->H[2];
		uint32_t d = sha1_ctx->H[3];
		uint32_t e = sha1_ctx->H[4];
		uint32_t T;

		for (size_t t = 0; t < 80; t++)
		{

			// T = ROTL5 (a) + function_t(b,c, d) + e + K + W
			T = SHA1_ROTL(5, a) + function_t(b, c, d, t) + e + sha1_K(t) + W[t];
			e = d;
			d = c;
			c = SHA1_ROTL(30, b);
			b = a;
			a = T;
		}
		sha1_ctx->H[0] += a;
		sha1_ctx->H[1] += b;
		sha1_ctx->H[2] += c;
		sha1_ctx->H[3] += d;
		sha1_ctx->H[4] += e;
	}
	// for (size_t k = 0; k < 5; k++)
	// {
	// 	printf("%02x", sha1_ctx->H[k]);
	// }
	// printf("\n");
}



void hash_sha1(uint8_t *message, uint8_t sha1_digest[SHA1_HASH_SIZE], uint64_t message_length)
{
	sha1_message_t sha1_message;
	SHA1_t_ctx context;
	sha1_process_input(&sha1_message, message, message_length);
	sha1_padd_message(&sha1_message);
	sha1_digest_hash(&context, &sha1_message);

	from_32_to_8(context.H, sha1_digest, SHA1_HASH_SIZE);
}

#endif