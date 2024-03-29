
// https://datatracker.ietf.org/doc/html/rfc4634

#ifndef CREEPTO_SHA256_H
#define CREEPTO_SHA256_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

enum
{
	SHA256_WORD_SIZE = 32,
	SHA256_MESSAGE_BLOCK_SIZE = 64,
	X_0X80 = 0x80
};

enum
{
	SHA256_MESSAGE_ERROR_TOO_LONG = 0x1
};

typedef struct sha256_message_t
{
	uint8_t *message;
	uint64_t message_length;
	uint64_t bits_length;
	uint32_t last_block;
} sha256_message_t;

typedef struct SHA256_t
{
	uint32_t H[SHA256_WORD_SIZE / 4];
	uint32_t message_block_index;
	sha256_message_t sha256_message;
} SHA256_t_ctx;

static const uint32_t K[SHA256_MESSAGE_BLOCK_SIZE] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
	0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
	0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
	0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
	0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
	0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
	0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
	0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

// ROTR^n(x) = (x>>n) OR (x<<(w-n))
static uint32_t ROTR(uint32_t n, uint32_t x)
{
	return (x >> n) | (x << (SHA256_WORD_SIZE - n));
}
// CH( x, y, z) = (x AND y) XOR ( (NOT x) AND z)
static uint32_t CH(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ ((~x) & z);
}
// MAJ( x, y, z) = (x AND y) XOR (x AND z) XOR (y AND z)
static uint32_t MAJ(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}
// BSIG0(x) = ROTR^2(x) XOR ROTR^13(x) XOR ROTR^22(x)
static uint32_t BSIG0(uint32_t x)
{
	return ROTR(2, x) ^ ROTR(13, x) ^ ROTR(22, x);
}
// BSIG1(x) = ROTR^6(x) XOR ROTR^11(x) XOR ROTR^25(x)
static uint32_t BSIG1(uint32_t x)
{
	return ROTR(6, x) ^ ROTR(11, x) ^ ROTR(25, x);
}
// SSIG0(x) = ROTR^7(x) XOR ROTR^18(x) XOR SHR^3(x)
static uint32_t SSIG0(uint32_t x)
{
	return ROTR(7, x) ^ ROTR(18, x) ^ (x >> 3);
}
// SSIG1(x) = ROTR^17(x) XOR ROTR^19(x) XOR SHR^10(x)
static uint32_t SSIG1(uint32_t x)
{
	return ROTR(17, x) ^ ROTR(19, x) ^ (x >> 10);
}

// Initialize the message buffer at the moment the context is instaciate
static void start_message_buffer(SHA256_t_ctx *context)
{
	context->sha256_message.last_block = 0;
	context->sha256_message.bits_length = 0;
	context->sha256_message.message_length = 0;
	context->sha256_message.message = NULL;
}

// Start the hash context.
static void start_context_sha256(SHA256_t_ctx *context)
{
	context->message_block_index = 0;
	context->H[0] = 0x6a09e667UL;
	context->H[1] = 0xbb67ae85UL;
	context->H[2] = 0x3c6ef372UL;
	context->H[3] = 0xa54ff53aUL;
	context->H[4] = 0x510e527fUL;
	context->H[5] = 0x9b05688cUL;
	context->H[6] = 0x1f83d9abUL;
	context->H[7] = 0x5be0cd19UL;
	start_message_buffer(context);
}

/// @brief Deprecated. it only considered just one message in the context.
/// @param sha256_message
/// @param message
/// @param message_length
static void process_input(sha256_message_t *sha256_message, uint8_t *message, size_t message_length)
{
	sha256_message->message = (uint8_t *)malloc(sizeof(uint8_t) * message_length);
	memcpy(sha256_message->message, message, message_length * sizeof(uint8_t));
	sha256_message->message_length = message_length;
	sha256_message->bits_length = message_length * 8;
}

/// @brief essage padding
/// @param sha256_message
static void padd_message(sha256_message_t *sha256_message)
{
	uint32_t last_block = (sha256_message->message_length / SHA256_MESSAGE_BLOCK_SIZE);
	uint8_t block_bytes_to_padd;

	if (block_bytes_to_padd = (uint8_t)(sha256_message->message_length % SHA256_MESSAGE_BLOCK_SIZE))
	{
		uint8_t bytes_left = SHA256_MESSAGE_BLOCK_SIZE - block_bytes_to_padd;

		uint8_t block_message[SHA256_MESSAGE_BLOCK_SIZE];
		memset(block_message, 0, SHA256_MESSAGE_BLOCK_SIZE * sizeof(uint8_t));
		memcpy(block_message, sha256_message->message + (SHA256_MESSAGE_BLOCK_SIZE * last_block), block_bytes_to_padd * sizeof(uint8_t));
		block_message[block_bytes_to_padd] = 0x80;
		block_message[56] = (uint8_t)((sha256_message->bits_length >> 56) & 0xFF);
		block_message[57] = (uint8_t)((sha256_message->bits_length >> 48) & 0xFF);
		block_message[58] = (uint8_t)((sha256_message->bits_length >> 40) & 0xFF);
		block_message[59] = (uint8_t)((sha256_message->bits_length >> 32) & 0xFF);
		block_message[60] = (uint8_t)((sha256_message->bits_length >> 24) & 0xFF);
		block_message[61] = (uint8_t)((sha256_message->bits_length >> 16) & 0xFF);
		block_message[62] = (uint8_t)((sha256_message->bits_length >> 8) & 0xFF);
		block_message[63] = (uint8_t)(sha256_message->bits_length & 0xFF);

		sha256_message->message = (uint8_t *)realloc(sha256_message->message, sizeof(uint8_t) * (sha256_message->message_length + bytes_left));
		memcpy(sha256_message->message + (SHA256_MESSAGE_BLOCK_SIZE * last_block), block_message, SHA256_MESSAGE_BLOCK_SIZE * sizeof(uint8_t));
		sha256_message->last_block = last_block + 1;
	}
}

/// @brief Preprate the blocks to be processed on hash function.
/// @param W
/// @param block_message
static void prepare_W(uint32_t *W, uint8_t *block_message)
{
	//   1. Prepare the message schedule W:
	//      For t = 0 to 15
	//         Wt = M(i)t
	//      For t = 16 to 63
	//         Wt = SSIG1(W(t-2)) + W(t-7) + SSIG0(t-15) + W(t-16)
	for (uint8_t t = 0; t < 16; t++)
	{
		W[t] = (uint32_t)block_message[t * 4] << 24;
		W[t] |= (uint32_t)block_message[(t * 4) + 1] << 16;
		W[t] |= (uint32_t)block_message[(t * 4) + 2] << 8;
		W[t] |= (uint32_t)block_message[(t * 4) + 3];
	}

	for (size_t t = 16; t < 64; t++)
	{

		W[t] = SSIG1(W[t - 2]) + W[t - 7] + SSIG0(W[t - 15]) + W[t - 16];
	}
}

/// @brief Computes the hash based on message blocks.
/// @param sha256_ctx
/// @param sha256_message
void process_hash(SHA256_t_ctx *sha256_ctx, sha256_message_t *sha256_message)
{
	uint32_t W[SHA256_MESSAGE_BLOCK_SIZE];
	for (uint32_t i = 0; i < sha256_message->last_block; i++)
	{
		memset(W, 0, SHA256_MESSAGE_BLOCK_SIZE * sizeof(uint32_t));
		prepare_W(W, sha256_message->message + (i * SHA256_MESSAGE_BLOCK_SIZE));
		uint32_t T1;
		uint32_t T2;
		uint32_t a = sha256_ctx->H[0];
		uint32_t b = sha256_ctx->H[1];
		uint32_t c = sha256_ctx->H[2];
		uint32_t d = sha256_ctx->H[3];
		uint32_t e = sha256_ctx->H[4];
		uint32_t f = sha256_ctx->H[5];
		uint32_t g = sha256_ctx->H[6];
		uint32_t h = sha256_ctx->H[7];

		for (uint8_t j = 0; j < 64; j++)
		{
			T1 = h + BSIG1(e) + CH(e, f, g) + K[j] + W[j];
			T2 = BSIG0(a) + MAJ(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}
		sha256_ctx->H[0] += a;
		sha256_ctx->H[1] += b;
		sha256_ctx->H[2] += c;
		sha256_ctx->H[3] += d;
		sha256_ctx->H[4] += e;
		sha256_ctx->H[5] += f;
		sha256_ctx->H[6] += g;
		sha256_ctx->H[7] += h;
	}
}

/// @brief turns 32 bits blocks into 8 bits each.
/// @param in
/// @param out
/// @param byte_length
void from_32_to_8(uint32_t *in, uint8_t *out, uint64_t byte_length)
{
	for (size_t i = 0; i < byte_length / 4; i++)
	{
		out[(i * 4)] = (uint8_t)((in[i] >> 24) & 0xFF);
		out[(i * 4) + 1] = (uint8_t)((in[i] >> 16) & 0xFF);
		out[(i * 4) + 2] = (uint8_t)((in[i] >> 8) & 0xFF);
		out[(i * 4) + 3] = (uint8_t)(in[i] & 0xFF);
	}
}

/// @brief Convert bytes uint8_t into hex encoding.
/// @param in
/// @param out
void hex_to_char_buffer(uint8_t *in, uint8_t *out)
{
	for (size_t i = 0; i < SHA256_MESSAGE_BLOCK_SIZE / 2; i++)
	{
		sprintf(out + (i * 2), "%02x", in[i]);
	}
}

/// @brief Deprecated function
/// @param message
/// @param digest
/// @param message_length
void hash_256(uint8_t *message, uint8_t digest[SHA256_MESSAGE_BLOCK_SIZE / 2], uint64_t message_length)
{
	sha256_message_t sha256_message;
	SHA256_t_ctx context;
	process_input(&sha256_message, message, message_length);
	start_context_sha256(&context);
	padd_message(&sha256_message);
	process_hash(&context, &sha256_message);
	from_32_to_8(context.H, digest, SHA256_MESSAGE_BLOCK_SIZE / 2);
}

// Start a hash context to keep track of the update & digest.
void SHA256(SHA256_t_ctx *context)
{
	start_context_sha256(context);
}

/// @brief appends messages payloads(uint8_t *) to context's message.
/// @param context
/// @param message
/// @param message_length
void sha256_update(SHA256_t_ctx *context, uint8_t *message, uint64_t message_length)
{
	// Implementation to initialize the first message block into the context.
	if (context->sha256_message.message == NULL || context->sha256_message.message_length == 0)
	{
		context->sha256_message.message = (uint8_t *)malloc(message_length * sizeof(uint8_t));
		memcpy(context->sha256_message.message, message, message_length * sizeof(uint8_t));
		context->sha256_message.message_length = message_length;
		context->sha256_message.bits_length = message_length * 8;
	}
	else
	{
		context->sha256_message.message = (uint8_t *)realloc(context->sha256_message.message, context->sha256_message.message_length + message_length);
		memcpy(context->sha256_message.message + context->sha256_message.message_length, message, message_length);
		context->sha256_message.message_length += message_length;
		context->sha256_message.bits_length = context->sha256_message.message_length * 8;
	}
}

/// @brief Computes the hash function onto the messages blocks.
/// @param context
/// @param digest_output
void sha256_digest(SHA256_t_ctx *context, uint8_t digest_output[SHA256_MESSAGE_BLOCK_SIZE / 2])
{
	padd_message(&context->sha256_message);
	process_hash(context, &context->sha256_message);
	from_32_to_8(context->H, digest_output, SHA256_MESSAGE_BLOCK_SIZE / 2);
}
#endif