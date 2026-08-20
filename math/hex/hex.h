#ifndef CREEPTO_HEX_H
#define CREEPTO_HEX_H


#ifndef IS_DIGIT
#define IS_DIGIT(c) (('0' <= c && c <= '9') ? 1 : 0)
#endif
#ifndef IS_HEXALPH
#define IS_HEXALPH(c) ((('a' <= c && c <= 'f') || ('A' <= c && c <= 'F')) ? 1 : 0)
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t ALPHABET_HEX[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};


void bytes_to_hex(uint8_t *bytes, uint8_t *hex, uint16_t size_of_bytes)
{

	int i = 0;
	while (i  <= size_of_bytes - 1)
	{
		// printf("left=%d\tright=%d\n", ALPHABET_HEX[(bytes[i] >> 4) & 0x0F], ALPHABET_HEX[(bytes[i] & 0x0F)]);
		hex[(i * 2)] = ALPHABET_HEX[(bytes[i] >> 4) & 0x0F];
		hex[(i * 2) + 1] = ALPHABET_HEX[(bytes[i] & 0x0F)];
		i++;
	}
}

uint8_t is_valid_hex_string(uint8_t *str, uint16_t len)
{
	for (int i = 0; i < len; i++)
	{
		if (0x01 ^ (IS_DIGIT(str[i]) | IS_HEXALPH(str[i])) == 1)
		{
			printf("Invalid Hex:%s \n", str);

			return 0x00;
		}
	}
	return 0x01;
}
#endif
