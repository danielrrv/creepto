
#ifndef CREEPTO_UTILS_H
#define CREEPTO_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t ALPHABET_HEX[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void bytes_to_hex(uint8_t *bytes, uint8_t *hex, uint16_t size_of_bytes);
void bytes_to_hex(uint8_t *bytes, uint8_t *hex, uint16_t size_of_bytes)
{
	
	int i = 0;
	while (i < size_of_bytes)
	{
		// printf("left=%d\tright=%d\n", ALPHABET_HEX[(bytes[i] >> 4) & 0x0F], ALPHABET_HEX[(bytes[i] & 0x0F)]);
		hex[(i * 2)] = ALPHABET_HEX[(bytes[i] >> 4) & 0x0F];
		hex[(i * 2) + 1] = ALPHABET_HEX[(bytes[i] & 0x0F)];
		i++;
	}
}
#endif