#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BIG_INT
{
	uint8_t *digits;
	uint32_t length;
	uint8_t sign;
} BIG_INT;

const uint8_t ZERO = '0';
const uint8_t NINE = '9';
const uint8_t BASE10 = 10;
const uint16_t MAX_DIGIT_LENGHT = 4096;
const uint8_t MAX_INT_DIGIT = 22;

// Constructors
BIG_INT *base_ct();
BIG_INT *ct_char(char *);
BIG_INT *ct_int(int);
BIG_INT *ct_long(long);

// Operations
BIG_INT *big_int_sum(BIG_INT *, BIG_INT *);
BIG_INT *big_int_substract(BIG_INT *, BIG_INT *);
BIG_INT *big_int_multiply(BIG_INT *, BIG_INT *);
BIG_INT *big_int_divide(BIG_INT *, BIG_INT *);
BIG_INT *big_int_modulo(BIG_INT *n, BIG_INT *m);
BIG_INT *big_int_power(BIG_INT *a, BIG_INT *x);
BIG_INT *big_int_root_square(BIG_INT *, BIG_INT *);

// Comparisons

uint8_t big_int_greater_than(BIG_INT *a, BIG_INT *b);
uint8_t big_int_equal_to(BIG_INT *a, BIG_INT *b);

// Utils
uint8_t big_int_is_digit(uint8_t);
int insert_at(BIG_INT *, uint8_t, uint16_t);

BIG_INT *base_ct()
{
	BIG_INT *value = (BIG_INT *)malloc(sizeof(BIG_INT));
	value->length = 0;
	value->sign = '+';
	value->digits = (uint8_t *)malloc(sizeof(uint8_t) * MAX_DIGIT_LENGHT);
	memset(value->digits, '\0', MAX_DIGIT_LENGHT);
	return value;
}

BIG_INT *ct_char(char *r)
{
	BIG_INT *value = base_ct();

	char *rr = r;
	if (rr == NULL)
	{
		return NULL;
	}
	int i = 0;
	while (*rr != '\0')
	{
		if (i > MAX_DIGIT_LENGHT)
		{
			return value;
		}
		if (*rr == '\0' || big_int_is_digit(*rr) == 0)
		{
			if (*rr == '\t' || *rr == ' ')
				continue;
			if ((*rr = '+' || *rr == '-') && i == 0)
			{
				value->sign = *rr;
				continue;
			}
			return value;
		}
		memcpy(value->digits + i, (uint8_t *)rr, sizeof(uint8_t));
		value->length++;
		i++;
		rr++;
	}
	return value;
}

BIG_INT *ct_int(int number)
{
	BIG_INT *value = base_ct();
	if (0 > number)
	{
		value->sign = '-';
		number *= -1;
	}
	uint8_t tmp[MAX_INT_DIGIT];
	memset(tmp, 0, MAX_INT_DIGIT);
	int i = 0;
	while ((number / 10) != 0)
	{
		int mod = number % 10;
		number -= mod;
		if ((number % 10) == 0)
		{
			number /= 10;
		}
		value->digits[MAX_DIGIT_LENGHT - i - 1] = mod + '0';
		i++;
	}
	insert_at(value, (number % 10) + '0', MAX_DIGIT_LENGHT - i - 1);
	value->digits = value->digits + (MAX_DIGIT_LENGHT - i - 1);
	value->length = i;
	return value;
}

BIG_INT *ct_long(long number)
{
	BIG_INT *value = base_ct();

	uint8_t tmp[MAX_INT_DIGIT];
	memset(tmp, 0, MAX_INT_DIGIT);
	int i = 0;
	while ((number / 10) != 0)
	{
		int mod = number % 10;
		number -= mod;
		if ((number % 10) == 0)
		{
			number /= 10;
		}
		value->digits[MAX_DIGIT_LENGHT - i - 1] = mod + '0';
		i++;
	}
	insert_at(value, (number % 10) + '0', MAX_DIGIT_LENGHT - i - 1);
	value->digits = value->digits + (MAX_DIGIT_LENGHT - i - 1);
	value->length = i;
	return value;
}

BIG_INT *big_int_sum(BIG_INT *A, BIG_INT *B)
{

	if (A == NULL || B == NULL)
		return NULL;
	BIG_INT *value = base_ct();
	if (big_int_greater_than(A, B) == 1)
	{
		uint32_t Blen = B->length;
		uint8_t taken = 0;
		for (size_t i = 0; i < Blen; i++)
		{
			#ifdef DEBUG
				printf("DEBUG[INPUT]: A'%d(%c) + B'%d(%c) + T'%d(%c)\n", A->digits[A->length - i - 1], A->digits[A->length - i - 1], B->digits[Blen - i - 1], B->digits[Blen - i - 1], taken + '0', taken + '0');
			#endif
			uint8_t sum = (B->digits[Blen - i - 1] + A->digits[A->length - i - 1]) - (2 * '0') + taken;
			int mod10 = sum % 10;
			if (sum >= 10)
			{
				taken = 1;

				int index = insert_at(value, mod10 + '0', MAX_DIGIT_LENGHT - i - 1);
				#ifdef DEBUG
					printf("DEBUG[INSERTED]: %d(%c)\t taken: %c\tindex:%d\n", mod10 + '0', mod10 + '0', taken + '0', index);
				#endif
				continue;
			}
			else
			{
				taken = 0;
				int index = insert_at(value, mod10 + '0', MAX_DIGIT_LENGHT - i - 1);
				#ifdef DEBUG
					printf("DEBUG[INSERTED]: %d, %c\t taken:%c\tindex:%d\n", mod10 + '0', mod10 + '0', taken + '0', index);
				#endif
			}
		}
		for (size_t i = 0; i < A->length - Blen; i++)
		{
			int index = insert_at(value, A->digits[A->length - Blen - i - 1], MAX_DIGIT_LENGHT - Blen - i - 1);
			#ifdef DEBUG
				printf("DEBUG[INSERT]:%d(%c)\tindex: %d\n", A->digits[A->length - Blen - i - 1], A->digits[A->length - Blen - i - 1], index);
			#endif
		}
		value->digits = value->digits + (MAX_DIGIT_LENGHT - (A->length));
		value->sign = A->sign;
		return value;
	}
	else
	{
		uint32_t Alen = A->length;
		uint8_t taken = 0;
		for (size_t i = 0; i < Alen; i++)
		{
			#ifdef DEBUG
				printf("DEBUG[INPUT]: B'%d(%c) + A'%d(%c) + T'%d(%c)\n", A->digits[Alen - i - 1], A->digits[Alen - i - 1], B->digits[B->length - i - 1], B->digits[B->length - i - 1], taken + '0', taken + '0');
			#endif
			uint8_t sum = (A->digits[Alen - i - 1] + B->digits[B->length - i - 1]) - (2 * '0') + taken;
			int mod10 = sum % 10;
			if (sum >= 10)
			{
				taken = 1;

				int index = insert_at(value, mod10 + '0', MAX_DIGIT_LENGHT - i - 1);
				#ifdef DEBUG
					printf("DEBUG[INSERTED]: %d(%c)\t taken: %c\tindex:%d\n", mod10 + '0', mod10 + '0', taken + '0', index);
				#endif
				continue;
			}
			else
			{
				taken = 0;
				int index = insert_at(value, mod10 + '0', MAX_DIGIT_LENGHT - i - 1);
				#ifdef DEBUG
					printf("DEBUG[INSERTED]: %d, %c\t taken:%c\tindex:%d\n", mod10 + '0', mod10 + '0', taken + '0', index);
				#endif
			}
		}
		for (size_t i = 0; i < B->length - Alen; i++)
		{
			int index = insert_at(value, A->digits[A->length - Alen - i - 1], MAX_DIGIT_LENGHT - Alen - i - 1);
			#ifdef DEBUG
				printf("DEBUG[INSERT]:%d(%c)\tindex: %d\n", B->digits[B->length - Alen - i - 1], B->digits[B->length - Alen - i - 1], index);
			#endif
		}
		value->digits = value->digits + (MAX_DIGIT_LENGHT - (B->length));
		value->sign = B->sign;
		return value;
	}
}

BIG_INT *big_int_substract(BIG_INT *A, BIG_INT *B)
{
	//    4564355
	// 43445798766
	//------------
	//           9
}

uint8_t big_int_greater_than(BIG_INT *A, BIG_INT *B)
{
	if (A->sign == '+' && B->sign == '-')
	{
		return 1;
	}
	else if ((A->length > B->length) && A->sign == '+')
	{
		return 1;
	}
	else if (A->length == B->length)
	{
		int j = 0;
		while (j < A->length)
		{	if((A->digits[j] - '0' == B->digits[j] - '0')){
				j++;
				continue;
			}
			else if ((A->digits[j] - '0' > B->digits[j] - '0') && (A->sign == '+'))
			{
				return 1;
			}
			else
			{
				return 0;
			}
			j++;
		}
	}
	else
	{
		return 0;
	}
}

uint8_t big_int_is_digit(uint8_t digit)
{
	return (digit >= '0' && '9' >= digit) ? 1 : 0;
}

int insert_at(BIG_INT *big_int, uint8_t value, uint16_t index)
{
	big_int->digits[index] = value;
	big_int->length++;
	return index;
}