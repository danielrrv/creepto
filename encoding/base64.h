#ifndef CREEPTO_BASE64_H
#define CREEPTO_BASE64_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// https://datatracker.ietf.org/doc/html/rfc4648

//         Table 2: The "URL and Filename safe" Base 64 Alphabet

//     Value Encoding  Value Encoding  Value Encoding  Value Encoding
//         0 A            17 R            34 i            51 z
//         1 B            18 S            35 j            52 0
//         2 C            19 T            36 k            53 1
//         3 D            20 U            37 l            54 2
//         4 E            21 V            38 m            55 3
//         5 F            22 W            39 n            56 4
//         6 G            23 X            40 o            57 5
//         7 H            24 Y            41 p            58 6
//         8 I            25 Z            42 q            59 7
//         9 J            26 a            43 r            60 8
//        10 K            27 b            44 s            61 9
//        11 L            28 c            45 t            62 - (minus)
//        12 M            29 d            46 u            63 _
//        13 N            30 e            47 v           (underline)
//        14 O            31 f            48 w
//        15 P            32 g            49 x
//        16 Q            33 h            50 y         (pad) =

const uint8_t ALPHABET[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

enum
{
	QUANTUM_SIZE = 24,
	QUANTUM_SIZE_INVERSED = 32
};

/**
 * @brief encodes an array of bytes - rfc4648.
 * 
 * @param text 
 * @param text_size 
 * @return uint8_t* 
 */
static uint8_t *encode_base64(uint8_t *text, uint64_t text_size)
{

	// How many block of 24 bits I can take from the text.
	int blocks_size = (text_size * 8) / QUANTUM_SIZE;
	// How many bits are off from the quantum packets. 8, 16.
	int quantum_in_24 = (text_size * 8) % QUANTUM_SIZE;
	// Knowing the quantity of regular quantum  that can be form, let's allocate memory fo the final encoded-text.
	uint8_t *block = (uint8_t *)malloc(((blocks_size * 4) + 4) * sizeof(uint8_t));
	memset(block, 0, ((blocks_size * 4) + 4) * sizeof(uint8_t));
	// Process the regular quantuams.
	for (size_t i = 0; i < blocks_size; i++)
	{

		block[i * 4] = ALPHABET[(text[(i * 3)] >> 2) & 0xFF];
		block[(i * 4) + 1] = ALPHABET[(((text[(i * 3)] & 0x03) << 4) | (text[(i * 3) + 1] >> 4)) & 0xFF];
		block[(i * 4) + 2] = ALPHABET[((text[(i * 3) + 1] & 0x0F) << 2) | (text[(i * 3) + 2] >> 6)];
		block[(i * 4) + 3] = ALPHABET[(text[(i * 3) + 2] & 0x3F) & 0xFF];
	}

	// (1) The final quantum of encoding input is an integral multiple of 24
	//    bits; here, the final unit of encoded output will be an integral
	//    multiple of 4 characters with no "=" padding.
	if (quantum_in_24 == 0)
	{
		return block;
	}
	// (2) The final quantum of encoding input is exactly 8 bits; here, the
	//    final unit of encoded output will be two characters followed by
	//    two "=" padding characters.
	else if (quantum_in_24 == 8)
	{
		block[(blocks_size * 4)] = ALPHABET[(text[(blocks_size * 3) + 0] >> 2) & 0xFF];
		block[(blocks_size * 4) + 1] = ALPHABET[((text[(blocks_size * 3) + 0] & 0x03))];
		block[(blocks_size * 4) + 2] = '=';
		block[(blocks_size * 4) + 3] = '=';
		return block;
	}
	//    (3) The final quantum of encoding input is exactly 16 bits; here, the
	//    final unit of encoded output will be three characters followed by
	//    one "=" padding character.
	else if (quantum_in_24 == 16)
	{ // 00010000 11001100
		block[(blocks_size * 4)] = ALPHABET[(text[(blocks_size * 3) + 0] >> 2) & 0xFF];
		block[(blocks_size * 4) + 1] = ALPHABET[(((text[(blocks_size * 3) + 0] & 0x03) << 4) | (text[(blocks_size * 3) + 1] >> 4)) & 0xFF];
		block[(blocks_size * 4) + 2] = ALPHABET[(((text[(blocks_size * 3) + 1] & 0x0F) << 2) | 0x00) & 0xFF];
		block[(blocks_size * 4) + 3] = '=';
		return block;
	}
};

/**
 * @brief decodes base64 string encoded based on rfc4648
 * 
 * @param text 
 * @param text_size 
 * @return uint8_t* 
 */
static uint8_t *decode_base64(uint8_t *text, uint64_t text_size)
{


	/**
	 * Implementation to get the Alphabet back from indexes.
	 * 
	 * @example the character encoded `Z` in `ALPHABET` is index=25
	 * 
	 */
	uint8_t ALPHABET_INVERSED[122];
	#ifdef DEBUG
		printf("index:\tchar:\tcode:\n");
	#endif
	for (size_t i = 0; i < sizeof(ALPHABET); i++)
	{
		ALPHABET_INVERSED[ALPHABET[i]] = i;
		#ifdef DEBUG
			printf("%ld\t%c\t%d\n", i , ALPHABET[i], ALPHABET[i]);
		#endif
	}

	/**
	 * Discards the padding. The `=` is not required to reconstruct the decode.
	 * Maximium loops are 2. A base64 should have more than `=` x 2.
	 * 
	 */
	while (text[text_size - 1] == '=')
	{
		text_size--;
	}
	/**
	 * number of group of 4 characters that can be formed from the base64 encoded string. 
	 */
	uint64_t packages_size = ((text_size * 8) / QUANTUM_SIZE_INVERSED);
	/**
	 *  After forming group of 4 characters/bytes. There are bits that need to be consider at decoding.
	 * Those bits can be  either 16 bits or 24 bits;
	 * 16 bits means at least there's one original byte.
	 * 24 bits means at least there are two origina bytes.
	 * 8 bits is not case because: Base64 will have at least 2 characters in a group and at most 2 `=`.
	 * 
	 */
	uint8_t remain_bits_after_last_quantum = (text_size * 8) % QUANTUM_SIZE_INVERSED;

	/**
	 * base64 is 4 / 3 greater than original array of char / bytes.
	 * The decoded_size = (3/4) encoded_size;
	 */
	uint64_t original_decode_size = (3 * text_size) / 4;
	/**
	 * Implementation to allocate the exact memory to decode array of char/bytes.
	 */
	uint8_t *block = (uint8_t *)malloc(sizeof(uint8_t) * original_decode_size);
	memset(block, 0, sizeof(uint8_t) * original_decode_size);
	#ifdef DEBUG
		printf("Package sizes: %ld\toriginal_size:%ld\t remain_bits:%d\n", packages_size, original_decode_size, remain_bits_after_last_quantum);
	#endif
	/**
	 * Implementation to form the decoding 
	 * 
	 * Some developer's nightmares aids.
	 * 00010100 11111011 10011100
	 * 00-000101 00-001111 00-101110 00-011100
	 * 
	 * 0x61 01100001
	 * 1 0001 
	 * 8 1000
	 * 00-011000->01100000
	 * 0x57 01010111 -> 00000101
	 * ENC 0x61 01100001  01010111
	 * DEC 0x69 01101001
	 */
	for (size_t i = 0; i < packages_size; i++)
	{
		block[i * 3] = (ALPHABET_INVERSED[text[(i * 4)]]  << 2 ) & 0xFC | ((ALPHABET_INVERSED[text[(i * 4) + 1]]) >> 4) & 0x03;
		block[(i * 3) + 1] = (ALPHABET_INVERSED[text[(i * 4) + 1]] << 4) | ((ALPHABET_INVERSED[text[(i * 4) + 2]] >> 2) & 0xF);
		block[(i * 3) + 2] = ALPHABET_INVERSED[text[(i * 4) + 2]] << 6 | ALPHABET_INVERSED[text[(i * 4) + 3]] & 0x3F;
	}

	/**
	 * Implemetation to treat the remaining bits when they are 16.
	 */
	if (remain_bits_after_last_quantum == 16)
	{
		#ifdef DEBUG
			printf("remaining 16 bits\n");
		#endif
		
		block[packages_size * 3] = ALPHABET_INVERSED[(text[packages_size * 4])] & 0xFF << 2;
		block[packages_size * 3] |= ALPHABET_INVERSED[(text[(packages_size * 4) + 1] >> 4) & 0x03];

		block[(packages_size * 3) + 1] = ALPHABET_INVERSED[text[(packages_size * 4) + 1] << 4];
		block[(packages_size * 3) + 1] |= ALPHABET_INVERSED[text[(packages_size * 4) + 2] >> 2];
	}

	/**
	 * Implementation to treat the remaining bits where they are 24.
	 *
	 *  00010100 11111011 
	 * 00-010100 00-001111 00-101100
	 * 6C 01101100
	 * 1B 00011011 011011
	 * // 'b' 
	 */

	if (remain_bits_after_last_quantum == 24)
	{
		#ifdef DEBUG
			printf("remaining 24 bits\n");
		#endif
		block[(packages_size * 3)] = ((ALPHABET_INVERSED[text[(packages_size * 4) & 0xFF]]) << 2) & 0xFC;
		block[(packages_size * 3) + 1] = ALPHABET_INVERSED[text[(packages_size * 4) + 1]] << 4;
		block[(packages_size * 3) + 1] |= ALPHABET_INVERSED[text[(packages_size * 4) + 2]] >> 2;
	}

	#ifdef DEBUG 
		for (size_t i = 0; i < text_size; i++)
		{
			printf("%c(%02x)", text[i],text[i]);
		}
		printf("\n");
		for (size_t i = 0; i < original_decode_size; i++)
		{
			printf("%02x,", block[i]);
		}
		printf("\n");
	#endif
	return block;
}

#endif