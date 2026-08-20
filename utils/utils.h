
#ifndef CREEPTO_UTILS_H
#define CREEPTO_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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