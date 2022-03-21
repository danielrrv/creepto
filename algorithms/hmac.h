// RFC[2104]https://datatracker.ietf.org/doc/html/rfc2104
#ifndef CREEPTO_HMAC_H
#define CREEPTO_HMAC_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "sha256.h"

enum
{
	B = 64
};
// H(K XOR opad, H(K XOR ipad, text))
void sha256_hmac(uint8_t *l_key, size_t key_length, uint8_t *message, size_t message_length, uint8_t digest[SHA256_MESSAGE_BLOCK_SIZE / 2])
{
	uint8_t *key = (uint8_t *)malloc(sizeof(uint8_t) * key_length);
	memset(key, 0, key_length);
	memcpy(key, l_key, key_length);

	// ipad = the byte 0x36 repeated B times
	uint8_t ipad[B], opad[B];
	memset(ipad, 0x36, sizeof(uint8_t) * B);
	// opad = the byte 0x5C repeated B times.
	memset(opad, 0x5C, sizeof(uint8_t) * B);
	// 	 The key for HMAC can be of any length (keys longer than B bytes are
	//    first hashed using H)
	if (key_length > B)
	{
		hash_256(key, key, key_length);
		key_length = 32;
	}
	// (1) append zeros to the end of K to create a B byte string
	//     (e.g., if K is of length 20 bytes and B=64, then K will be
	//      appended with 44 zero bytes 0x00)
	key = (uint8_t *)realloc(key, B);
	memset(key + key_length, 0x00, B - key_length);
	key_length = 64;

	uint8_t key_ipad[B], key_opad[B];
	for (size_t i = 0; i < key_length; i++)
	{
		//  (2) XOR (bitwise exclusive-OR) the B byte string computed in step
		//     (1) with ipad
		key_ipad[i] = key[i] ^ 0x36;
		//  (5) XOR (bitwise exclusive-OR) the B byte string computed in
		// step (1) with opad
		key_opad[i] = key[i] ^ 0x5C;
	}
	// (3) append the stream of data 'text' to the B byte string resulting
	//     from step (2)
	uint8_t *key_ipad_message = (uint8_t *)malloc(sizeof(uint8_t) * (B + message_length));

	memcpy(key_ipad_message, key_ipad, B);
	memcpy(key_ipad_message + B, message, message_length);
	// apply H to the stream generated in step (3)
	uint8_t H_key_ipad_message[B / 2];
	hash_256(key_ipad_message, H_key_ipad_message, B + message_length);
	//   (6) append the H result from step (4) to the B byte string
	//     resulting from step (5)
	uint8_t *key_opad_H_key_ipad_message = (uint8_t *)malloc(sizeof(uint8_t) * ((B / 2) + B));
	// memset(key_opad_H_key_ipad_message, 0, sizeof(uint8_t) * ((B / 2) + B));
	memcpy(key_opad_H_key_ipad_message, key_opad, B);
	memcpy(key_opad_H_key_ipad_message + B, H_key_ipad_message, B / 2);
	// (7) apply H to the stream generated in step (6) and output
	//     the result
	uint8_t H_key_opad_H_key_ipad_message[B / 2];
	// printf("[%s]\n", key_opad_H_key_ipad_message);
	hash_256(key_opad_H_key_ipad_message, H_key_opad_H_key_ipad_message, (B / 2) + B);
	// memcpy(&digest,H_key_opad_H_key_ipad_message, 32);
	free(key);
	free(key_ipad_message);
	free(key_opad_H_key_ipad_message);
	// return H_key_opad_H_key_ipad_message;
}

#endif