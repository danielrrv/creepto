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

const uint8_t QUANTUM_SIZE = 24;

static uint8_t *encode_base64(uint8_t *text, uint64_t text_size)
{

	int blocks_size = (text_size * 8) / QUANTUM_SIZE;

	int quantum_in_24 = (text_size * 8) % QUANTUM_SIZE;

	uint8_t *block = (uint8_t *)malloc(((blocks_size * 4) + 4) * sizeof(uint8_t));
	for (size_t i = 0; i < blocks_size; i++)
	{
		block[i * 4] = ALPHABET[(text[(i * 3)] >> 2) & 0xFF];									 // OK
		block[(i * 4) + 1] = ALPHABET[((text[(i * 3)] << 6) | (text[(i * 3) + 1] >> 4)) & 0xFF]; // OK
		block[(i * 4) + 2] = ALPHABET[((text[(i * 3) + 1] & 0x0F) << 2) | (text[(i * 3) + 2] >> 6)];
		block[(i * 4) + 3] = ALPHABET[(text[(i * 3) + 2] & 0x3F) & 0xFF];
	}

	if (quantum_in_24 == 0)
	{
		return block;
	}
	else if (quantum_in_24 == 8)
	{
		block[(blocks_size * 4)] = ALPHABET[(text[(blocks_size * 3) + 0] >> 2) & 0xFF];
		block[(blocks_size * 4) + 1] = ALPHABET[((text[(blocks_size * 3) + 0] << 6) | (text[(blocks_size * 3) + 1] >> 4)) & 0xFF];
		block[(blocks_size * 4) + 2] = '=';
		block[(blocks_size * 4) + 3] = '=';
		return block;
	}
	else if (quantum_in_24 == 16)
	{
		block[(blocks_size * 4)] = ALPHABET[(text[(blocks_size * 3) + 0] >> 2) & 0xFF];
		block[(blocks_size * 4) + 1] = ALPHABET[((text[(blocks_size * 3) + 0] << 6) | (text[(blocks_size * 3) + 1] >> 4)) & 0xFF];
		block[(blocks_size * 4) + 2] = ALPHABET[(((text[(blocks_size * 3) + 1] & 0x0F) << 2) | (text[(blocks_size * 3) + 2] >> 6)) & 0xFF];
		block[(blocks_size * 4) + 3] = '=';
		return block;
	}
};

#endif