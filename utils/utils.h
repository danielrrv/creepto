
#ifndef CREEPTO_UTILS_H
#define CREEPTO_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint8_t ALPHABET_HEX[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};


void bytes_to_hex(uint8_t *bytes, uint8_t *hex, uint16_t size_of_bytes)
{

	int i = 0;
	while (i  < size_of_bytes - 1)
	{
	
		// printf("left=%d\tright=%d\n", ALPHABET_HEX[(bytes[i] >> 4) & 0x0F], ALPHABET_HEX[(bytes[i] & 0x0F)]);
		hex[(i * 2)] = ALPHABET_HEX[(bytes[i] >> 4) & 0x0F];
		hex[(i * 2) + 1] = ALPHABET_HEX[(bytes[i] & 0x0F)];
		i++;
	}
}

void reverse_array_of_uint8(uint8_t *arr, size_t size)
{
	for (int i = 0; i < size / 2; i++)
	{
		int temp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = temp;
	}
}

uint8_t *bytes_to_bits(uint8_t *bytes) {};
uint8_t *bits_to_bytes(uint8_t *bits) {};

#endif