#ifndef CREEPTO_BIG_INT_H
#define CREEPTO_BIG_INT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "assert.h"
// const a = 'd'
#define IS_DIGIT(c) (('0' <= c && c <= '9') ? 1 : 0)
#define IS_HEXALPH(c) ((('a' <= c && c <= 'f') || ('A' <= c && c <= 'F')) ? 1 : 0)

#define ARRAY_LEN(array, length_name) \
	uint16_t##length_name;            \
	while (*array != '\0')            \
		##length_name++;

#define BIG_INT_IS_ZERO(big_int) (big_int->length == 1 && big_int->digits[0] == '0')
#define BIG_INT_IS_ONE(big_int) (big_int->length == 1 && big_int->digits[0] == '1')
#define BIG_INT_ARE_SAME(A, B) (A->length == B->length && strncmp(A->digits, B->digits, A->length) == 0)

// Initialize less than 10 number. DO NOT USE this with number langer than 10.
#define INITIALIZE_BIG_INT_TO(big_int, value, lenght)                  \
	memset(big_int->digits, '\0', sizeof(uint8_t) * MAX_DIGIT_LENGHT); \
	big_int->digits[0] = value;                                        \
	big_int->length = lenght;

#define BIG_INT_COPY_FROM_TO(a, b)           \
	memcpy(b->digits, a->digits, a->length); \
	b->length = a->length;                   \
	b->sign = a->sign;

#define STR(S) #S
#define PRINT_BIG_INT(A) printf("name=%s\t digits=%s\tlen(%s)=%d\n", STR(A), A->digits, STR(A), A->length)

#define DIVISION_RESULT_FACTORY(division_result)                              \
	division_result = (division_result_t *)malloc(sizeof(division_result_t)); \
	division_result->quotient = base_ctor();                                  \
	division_result->remaining = base_ctor();                                 \
	ctor_char("0", division_result->remaining);

#define TO_BOOL(c) (c == 0x01)
typedef enum error_type
{
	DIVISION_BY_ZERO = 1,
	DIVISOR_GREATER_THAN_DIVIDEND
} error_type_e;

typedef struct BIG_INT
{
	uint8_t *digits;
	uint32_t length;
	uint8_t sign;
} BIG_INT;

typedef struct division_result
{
	BIG_INT *quotient;
	BIG_INT *remaining;
	error_type_e error;
} division_result_t;

typedef struct divisors
{
	BIG_INT **divisors;
	BIG_INT *count;
} divisors_t;

const uint8_t ZERO = '0';
const uint8_t NINE = '9';
const uint8_t BASE10 = 10;
const uint16_t MAX_DIGIT_LENGHT = 4096;
const uint8_t MAX_INT_DIGIT = 22;

/**
 * @brief Create a simple BIG_INT object with ->length zero, ->digits undefined(allocate before accessing).
 * @since 07/05/2022
 * @return BIG_INT*
 */
BIG_INT *base_ctor();
/**
 * @brief
 *
 * @return BIG_INT*
 */
void ctor_char(char *, BIG_INT *);
void ctor_int(int, BIG_INT *);
void ctor_long(long, BIG_INT *);
void ctor_hex(uint8_t *, BIG_INT *);
void big_int_reset(BIG_INT *);
void big_int_free(BIG_INT *);

/**
 * @brief add two big(A + B) integer and returns a BIG_INT instance as pointer..
 * @since 10/05/2022
 * @param A BIG_INT instance first.
 * @param B BIG_INT instance second
 * @param C BIG_INT instance result.
 * @return BIG_INT*
 *
 *
 */
void big_int_sum(BIG_INT *, BIG_INT *, BIG_INT *);
/**
 * @brief  substract A - B. It considers sign rules.
 * @since 10/05/2022
 * @param A
 * @param B
 * @param C
 * @return BIG_INT*
 */
void big_int_substract(BIG_INT *, BIG_INT *, BIG_INT *);
void big_int_multiply(BIG_INT *, BIG_INT *, BIG_INT *);
void big_int_divide(BIG_INT *, BIG_INT *, division_result_t *);
void big_int_modulo(BIG_INT *n, BIG_INT *m);
void big_int_power(BIG_INT *a, BIG_INT *x, BIG_INT *);
void big_int_root_square(BIG_INT *, BIG_INT *);
void big_int_mod(BIG_INT *M, BIG_INT *N, BIG_INT *R);
void big_int_gcd(BIG_INT *, BIG_INT *, BIG_INT *);
int max_divisor(BIG_INT *A, BIG_INT *B, int low, int high);

// Primitives
static void add(uint8_t *sum, uint8_t a, uint8_t b, uint8_t *carry);
static void substract(uint8_t *needs_borrow, uint8_t *substraction, uint8_t a, uint8_t b, uint8_t *carry);
static uint8_t primitive_substraction(uint8_t, uint8_t, uint8_t);
static uint8_t apply_borrowing_if_apply(uint8_t *, uint8_t, uint8_t, const uint8_t);
static uint8_t primitive_sum(uint8_t, uint8_t, uint8_t);
static uint8_t apply_carry_if_apply(uint8_t *, uint8_t *);
static void big_int_divide_by_2(BIG_INT *N, division_result_t *division_result);
static bool is_even(char c);
static void big_int_factor_between_m_and_n(BIG_INT *M, BIG_INT *N, BIG_INT *high, BIG_INT *low, BIG_INT *factor);

// uint8_t valid_integer_at()

// Comparisons

uint8_t big_int_greater_than(const BIG_INT *a, const BIG_INT *b);
uint8_t big_int_greater_than_abs(BIG_INT *A, BIG_INT *B);
uint8_t big_int_equal_to(BIG_INT *a, BIG_INT *b);
void toString(int number, uint8_t *str);

// Utils
static uint16_t insert_at(BIG_INT *, uint8_t, uint16_t);
uint8_t invert_sign(uint8_t sign)
{
	return sign == '+' ? '-' : '+';
}

void clean_zero_in_front(BIG_INT *);
static uint8_t is_valid_hex_string(uint8_t *str, uint16_t len);

/**
 * @brief Simple BIG_INT constructor.  ->digits allocated memset(0)
 *
 * @return BIG_INT*
 */
BIG_INT *base_ctor()
{
	BIG_INT *value = (BIG_INT *)malloc(sizeof(BIG_INT));
	if (value == NULL)
		return NULL;
	value->length = 0;
	value->sign = '+';
	value->digits = (uint8_t *)malloc(sizeof(uint8_t) * MAX_DIGIT_LENGHT);
	if (value->digits == NULL)
		return NULL;
	memset(value->digits, '\0', MAX_DIGIT_LENGHT);
	return value;
}

void big_int_reset(BIG_INT *value)
{
	value->length = 0;
	value->sign = '+';
	memset(value->digits, '\0', MAX_DIGIT_LENGHT);
}

void big_int_free(BIG_INT *value)
{
	free(value->digits);
	free(value);
}

/**
 * @brief Constructs a BIG_INT from array of characters.
 *
 * @param r pointer of array of bytes(uint8_t).
 * @return BIG_INT*
 */
void ctor_char(char *cc, BIG_INT *R)
{
	char *rr = cc;
	if (rr == NULL)
	{
		return;
	}
	int i = 0;

	while (*rr != '\0')
	{

		if (i > MAX_DIGIT_LENGHT)
		{
			return;
		}
		if (*rr == '\0')
		{

			return;
		}
		// *rr is not digit.
		if (IS_DIGIT(*rr) == 0)
		{
			if ((*rr == '+' || *rr == '-') && i == 0)
			{
				R->sign = *rr;
			}
			// Escape the character.
			rr++;
			continue;
		}
		// rr is lvalue..It must be inserted in the array directly.
		memcpy(R->digits + i, (uint8_t *)rr, sizeof(uint8_t));
		R->length++;
		i++;
		rr++;
	}
#ifdef DEBUG
	printf("char BIGINT [%s]\n", R->digits);
#endif
}
/**
 * @brief constructs a BIG_INT from a int.
 *
 * @param number
 * @return BIG_INT*
 */
void ctor_int(int number, BIG_INT *R)
{
	BIG_INT *r = base_ctor();
	if (0 > number)
	{
		R->sign = '-';
		number *= -1;
	}
	uint8_t tmp[MAX_INT_DIGIT];
	memset(tmp, '\0', MAX_INT_DIGIT);
	int i = 0;
	if (number >= 10)
	{
		while ((number / 10) != 0)
		{
			int mod = number % 10;
			number -= mod;
			if ((number % 10) == 0)
			{
				number /= 10;
			}
			r->digits[MAX_DIGIT_LENGHT - i - 1] = mod + '0';
			i++;
		}
		insert_at(r, (number % 10) + '0', MAX_DIGIT_LENGHT - i - 1);
		r->length = i + 1;
	}
	else
	{
		r->digits[MAX_DIGIT_LENGHT - 1] = number % 10 + '0';
		r->length = 1;
		// i++;
	}
	r->digits = r->digits + (MAX_DIGIT_LENGHT - i - 1);

	BIG_INT_COPY_FROM_TO(r, R);
	free(r);
#ifdef DEBUG
	printf("in:%d out:%s\ti:%d\n", number, R->digits, i);
#endif
}
/**
 * @brief convert a hex to big number represented by array of bytes
 *
 * 0x4A8F62D431BA5F12D4704ACF25D4214A5F22D4502D4204A5F22D2D4204E5B26A4A5F2E5F12D4404
 *
 * @param hex
 * @param r
 */
void ctor_hex(uint8_t *hex, BIG_INT *r)
{

	// Exception #1: hex shouldn't be null.
	if (hex == NULL)
	{
		r = NULL;
		return;
	}

	// Implementation to discard and the first 2 characters of hex validation.
	if (*hex == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		hex += 2;
	// Exception #2: Implementation to return fast in case the string character haven't started by [0x]
	else
	{
		r = NULL;
		printf("///%d\n", r == NULL);
		return;
	}

	// implementation to get the length of the array. TODO: Move it to MACRS
	uint16_t len;
	while (*(hex++) != '\0')
		len++;
	// Implementation to move back the pointer to the original position.
	hex -= len + 1;
	printf("%s\n", hex);

	// Exception # 3: the characters must be alphanumeric from [0-9][aA-fF].
	if (is_valid_hex_string(hex, len) == 0x00)
	{
		r = NULL;
		printf("///%d\n", r == NULL);
		return;
	}
	// What it is for: track the power result as intermidiate factor for the final multiplication later on.
	BIG_INT *power = base_ctor();
	// What it is for: track the decimal result which is the function pointer return.
	BIG_INT *decimal = base_ctor();
	BIG_INT *sixteen = base_ctor();
	// As long as we move down, we elevate sixteen at the power of length.
	BIG_INT *length = base_ctor();
	// What it is for: track the value from the conversion from hex to decimal.
	BIG_INT *val = base_ctor();

	// What it is for; track the final product of iteration.
	BIG_INT *product = base_ctor();
	ctor_char("0", decimal);
	ctor_char("0", power);
	ctor_char("16", sixteen);
	ctor_char("1", product);
	// Each digit of the hex array it is a value for the computation.
	for (size_t i = 0; 0 < len; i++, len--)
	{
		// Implementation to convert hexadecimal to decimal based on ascii code.
		uint8_t _val = 0;
		if (IS_DIGIT(hex[i]))
		{
			_val = hex[i] - 48;
		}
		else if (hex[i] >= 'a' && hex[i] <= 'f')
		{
			_val = hex[i] - 97 + 10;
		}
		else if (hex[i] >= 'A' && hex[i] <= 'F')
		{
			_val = hex[i] - 65 + 10;
		}
#ifdef DEBUGCTORHEX
		printf("i=%d\thex[i]=%c\tval=%d\t", i, hex[i], _val);
#endif
		// Prevent data corruption and save the program to allocate new memory in each iteration.
		big_int_reset(val);
		// Let's move _val into a BIG INT to over on BIG INT functions.
		ctor_int(_val, val);
		// Prevent data corruption and save the program to allocate new memory in each iteration.
		big_int_reset(power);
		big_int_reset(length);
		// Let's move len into a BIG INT to over on BIG INT functions.
		ctor_int(len - 1, length);

		// Implementation to apply the first operation: 16^ length
		big_int_power(sixteen, length, power);

		// Prevent data corruption and save the program to allocate new memory in each iteration.
		big_int_reset(product);
		// Implementation to apply the second of the opetation: val * (16 ^ lengh)
		big_int_multiply(val, power, product);

		// Implementation to apply the third and last part of the operation: summing up the product to decimal and keep it up.
		big_int_sum(decimal, product, decimal);
// BIG_INT_COPY_FROM_TO(trailer, decimal);
#ifdef DEBUGCTORHEX
		printf("%d * 16 ** %d\n", _val, len - 1);
#endif
	}

	// Finally move decimal to r.
	BIG_INT_COPY_FROM_TO(decimal, r);

#ifdef DEBUGCTORHEX
	printf("hex:%s, %s\n", hex, r->digits);
#endif
	free(decimal);
	free(sixteen);
	free(power);
	free(product);
}

//To deprecate.
void toString(int number, uint8_t *str)
{
	if (str == NULL)
		return;

	int i = 0;
	if (number > 10)
	{
		while ((number / 10) != 0)
		{
			int mod = number % 10;
			number -= mod;
			if ((number % 10) == 0)
			{
				number /= 10;
			}
			str[MAX_DIGIT_LENGHT - i - 1] = mod + '0';
			i++;
		}
		str[MAX_DIGIT_LENGHT - i - 1] = (number % 10) + '0';
	}
	else
	{
		str[MAX_DIGIT_LENGHT - 1] = number % 10 + '0';
	}
	memmove(str, str + (MAX_DIGIT_LENGHT - i - 1), i + 1);
}

/**
 * @brief Constructs a BIG_INT from a long.
 *
 * @param number
 * @return BIG_INT*
 */
void ctor_long(long number, BIG_INT *R)
{
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
		R->digits[MAX_DIGIT_LENGHT - i - 1] = mod + '0';
		i++;
	}
	insert_at(R, (number % 10) + '0', MAX_DIGIT_LENGHT - i - 1);
	R->digits = R->digits + (MAX_DIGIT_LENGHT - i - 1);
	R->length = number > 10 ? i : 1;
}

void big_int_sum(BIG_INT *A, BIG_INT *B, BIG_INT *R)
{
	// DRY the length of the big integer.
	uint32_t Blen = B->length, Alen = A->length, max_length = Blen > Alen ? Blen : Alen;
	uint8_t carry = 0;
	size_t i;
	uint8_t is_A_greater_than_B_abs = big_int_greater_than_abs(A, B) == 0x01;
	for (i = 0; i < Blen || i < Alen || carry > 0; i++)
	{
#ifdef DEBUGSUM
		printf("DEBUG[INPUT]: A'%d(%c) + B'%d(%c) + T'%d(%c)\n",
			   A->digits[Alen - i - 1], A->digits[Alen - i - 1], B->digits[Blen - i - 1], B->digits[Blen - i - 1], carry + '0', carry + '0');
#endif
		// DRY the digit at the determited position.
		uint8_t valid_integer_A_at_i = Alen > i ? A->digits[Alen - i - 1] - '0' : 0, valid_integer_B_at_i = Blen > i ? B->digits[Blen - i - 1] - '0' : 0,
				needs_borrow = 0,
				sum = 0;
		// Case #1. A is greater than B(absolute value).
		if (is_A_greater_than_B_abs)
		{
			// Case #1.1. If signs marks are different this is a substraction.
			if ((A->sign == '+' && B->sign == '-') || (A->sign == '-' && B->sign == '+'))
			{
				substract(&needs_borrow, &sum, valid_integer_A_at_i, valid_integer_B_at_i, &carry);
			}
			else
			{
				// Case #1.2. If signs are equals, then this is adding up.
				add(&sum, valid_integer_A_at_i, valid_integer_B_at_i, &carry);
			}
		}
		else
		{
			// Case #2.1. If B is greater than A and the signs marks are equal. That is a sum.
			if (B->sign == '+' && A->sign == '+' || B->sign == '-' && A->sign == '-')
			{
				add(&sum, valid_integer_B_at_i, valid_integer_A_at_i, &carry);
			}
			else
			{
				// Case #2.2. If B is greater than A and the signs marks are different. That is a substraction.
				substract(&needs_borrow, &sum, valid_integer_B_at_i, valid_integer_A_at_i, &carry);
			}
		}
		// Implementation to inser the digit ij the desired position. From back to front.
		uint16_t index = insert_at(R, sum % 10 + '0', MAX_DIGIT_LENGHT - i - 1);

#ifdef DEBUGSUM
		printf("DEBUG[INSERTED1]: %d(%c)\t carry: %c\tindex:%d\n", (sum % 10) + '0', (sum % 10) + '0', carry + '0', index);
#endif
	}
	// Implementation to advance the pointer because was filled from back to front.
	BIG_INT *ptr = (BIG_INT *)(R->digits + (MAX_DIGIT_LENGHT - i - carry));
	memcpy(R->digits, ptr, i + carry);
	R->length = i + carry;
	// Implementation to decide the sign of the final BIG INT.
	R->sign = is_A_greater_than_B_abs ? A->sign : B->sign;
#ifdef DEBUGSUM
	printf("big_int_sum([%s] + [%s]) = [%s]\n", A->digits, B->digits, R->digits);
#endif
}

/**
 * @brief  substract A - B. It considers sign rules.
 * @since 10/05/2022
 * @param A
 * @param B
 * @return BIG_INT*
 */
void big_int_substract(BIG_INT *A, BIG_INT *B, BIG_INT *R)
{
#ifdef DEBUGSUBSTRACT
	printf("Substracting A:[%s]\tB:[%s]\n", A->digits, B->digits);
#endif
	// BIG_INT *value = base_ctor();
	uint32_t Blen = B->length, Alen = A->length;
	uint8_t borrow = 0;
	size_t i;
	uint8_t is_A_greater_than_B_abs = big_int_greater_than_abs(A, B) == 0x01;
	for (i = 0; i < Alen || i < Blen || borrow > 0; i++)
	{
#ifdef DEBUGSUBSTRACT
		printf("DEBUG[INPUT]: A'%d(%c) - B'%d(%c) - T'%d(%c)\n",
			   A->digits[A->length - i - 1], A->digits[A->length - i - 1],
			   B->digits[B->length - i - 1], B->digits[B->length - i - 1], borrow + '0', borrow + '0');
#endif
		uint8_t valid_integer_A_at_i = Alen > i ? A->digits[Alen - i - 1] - '0' : 0,
				valid_integer_B_at_i = Blen > i ? B->digits[Blen - i - 1] - '0' : 0;
		uint8_t needs_borrow = 0;
		int8_t substraction = 0;
		// Case #1. A is greater than B(absolute).
		if (is_A_greater_than_B_abs)
		{
			// If A is greater than B and the A sign mark is negative and B is positive, that is a sum.
			if (A->sign == '-' && B->sign == '+')
			{
				add(&substraction, valid_integer_A_at_i, valid_integer_B_at_i, &borrow);
			}
			else
			{
				// If A is greater than B and the (-A + (-B) or (A - B )), that is a sum.
				substract(&needs_borrow, &substraction, valid_integer_A_at_i, valid_integer_B_at_i, &borrow);
			}
			// Case #2. B is greater than A(absolute).
		}
		else
		{
			if (B->sign == '-' && A->sign == '+' || B->sign == '+' && A->sign == '-')
			{
				// Case #2.1. If both marks signs are different, then this is a sum.
				add(&substraction, valid_integer_B_at_i, valid_integer_A_at_i, &borrow);
			}
			else
			{
				// Case #2.2. (B-(+A). THen that is a substraction.
				substract(&needs_borrow, &substraction, valid_integer_B_at_i, valid_integer_A_at_i, &borrow);
			}
		}
		uint16_t index = insert_at(R, (substraction % BASE10) + '0', MAX_DIGIT_LENGHT - i - 1);
#ifdef DEBUGSUBSTRACT
		printf("%d = A(%d) - B(%d) - borrow(%d)\n", substraction, (A->digits[Alen - i - 1] - '0'), (B->digits[Blen - i - 1] - '0'), borrow);
		printf("DEBUG[SUB][INSERTED]: value:%d(%c)\tborrow:%c\tindex:%d\n",
			   substraction % BASE10 + '0', substraction % BASE10 + '0', borrow + '0', index);
#endif
	}
	// Implementation to advance the pointer because was filled from back to front.
	// R->digits = R->digits + (MAX_DIGIT_LENGHT - i);

	BIG_INT *ptr = (BIG_INT *)(R->digits + (MAX_DIGIT_LENGHT - i));
	memcpy(R->digits, ptr, i);
	R->length = i;
	// Implementation to decide the sign of the final BIG INT.
	R->sign = is_A_greater_than_B_abs == 0x01 ? A->sign : B->sign;
	clean_zero_in_front(R);
#ifdef DEBUGSUBSTRACT
	printf("[%s] - [%s]=[%c%s]\n", A->digits, B->digits, R->sign, R->digits);
#endif
	// return value;
}

/**
 * @brief Multiplies two big integers (A * B).
 * @since 10/05/2022
 * @param A number first.
 * @param B number second.
 * @return BIG_INT*
 */
void big_int_multiply(BIG_INT *A, BIG_INT *B, BIG_INT *R)
{

	// Case #1: If any is zero, then R is zero too.
	if (A->digits[0] == '0' || B->digits[0] == '0')
	{
		R->digits[0] = '0';
		R->length = 1;
		return;
	}

	// Initialize a temporal BIG_INT to store each multiplication.
	BIG_INT *temporal_big_int = base_ctor("0");
	// DRY the big_int length.
	uint32_t Alen = A->length;
	uint32_t Blen = B->length;
	// Why are they declared here: They act as tmp local intermediate pointers use to neatly copy of references.
	BIG_INT *tmp = base_ctor();
	// Why are they declared here: They act as tmp local intermediate pointers use to neatly copy of references.
	BIG_INT *ptr = base_ctor();
	// Case #2. B is greater than A by absolute value.
	if (big_int_greater_than_abs(A, B) == 0x00)
	{
		// Variable declare to coun the padding zeros needed to sum up the each iteration.
		uint32_t padding = 0;
		// Going through O(N2) iteration on A to muliply each element of A with B ones.
		// Each iteration create a new intermediate output.
		for (size_t i = 0; i < A->length; i++)
		{
			// DRY the primary factor.
			uint8_t primary_factor = Alen > i ? A->digits[A->length - i - 1] - '0' : 0;

			// Implementation to carry the value to be possibly added to next multiplication.
			uint64_t carry = 0;
			// Implementation to avoid pre-populated pointer.
			memset(temporal_big_int->digits, 0, MAX_DIGIT_LENGHT);
			// Implementation to initialize the length of the pointer.
			temporal_big_int->length = 0;
			// Implementation to add padding to the intermediate value.
			for (size_t k = 0; k < padding; k++)
			{
				insert_at(temporal_big_int, '0', MAX_DIGIT_LENGHT - k - 1);
			}

			size_t j = 0;
			if (primary_factor != 0)
			{
				// Primary factor multiplies every value of the B(Second big integer).
				for (; j < B->length || carry > 0; j++)
				{
#ifdef DEBUG
					printf("A(%d)*B(%d)\n",
						   (Blen > j ? B->digits[B->length - j - 1] - '0' : 0), Alen > i ? A->digits[A->length - i - 1] - '0' : 0);
#endif
					// Implementation to multuiply digit of A with digit of B plus any carried value from previous multiplication.
					uint8_t multiplication = (Blen > j ? B->digits[B->length - j - 1] - '0' : 0) * primary_factor + carry;
					// What is it for: we get the last digit of the multiplication. Example 34, we save 4 and carry 3.
					uint8_t mod10 = multiplication % BASE10;
					// Implementation to stick the carry value for the next inner iteration.
					carry = multiplication - mod10 > 0 ? (multiplication - mod10) / BASE10 : 0;
					// For debugging purposes, we validate the index and the value inserted.
					// Inserted from the back to front.
					uint64_t index = insert_at(temporal_big_int, (mod10) + '0', MAX_DIGIT_LENGHT - j - padding - 1);
#ifdef DEBUG
					printf("multiplication:%d\tmod:%d\tcarry:%ld\n", multiplication, mod10, carry);
#endif
				}
#ifdef DEBUG
				printf("[%s]:len:%d\n", temporal_big_int->digits + (MAX_DIGIT_LENGHT - j - padding), temporal_big_int->length);
#endif
			}
			else
			{
				insert_at(temporal_big_int, '0', MAX_DIGIT_LENGHT);
			}
			// Implementation to move the pointer to the from back to front.
			ptr->digits = temporal_big_int->digits + (MAX_DIGIT_LENGHT - j - padding);
			ptr->length = j + padding;
			// Implementation to clear the pointer from previous loop iterations.
			big_int_reset(tmp);
			// Implemetation to add up the current big_integer in temporal_big_int into value(accumulate).
			big_int_sum(R, ptr, tmp);
			// Copy blocks into the output value.
			memcpy(R->digits, tmp->digits, tmp->length);
			// Preserve the length.
			R->length = tmp->length;
			// Implementation to add a new zero to next temporal big_integer.
			padding++;
			// free(tmp);
		}
#ifdef DEBUG
		printf("[%s] * [%s] = [%s]:len%d\n", A->digits, B->digits, R->digits, R->length);
#endif
	}
	else
	{
#ifdef DEBUG
		printf("ADig:%s|Alen:%d\tBdigit:%s|Blen:%d\n", A->digits, Alen, B->digits, Blen);
#endif
		// Variable declare to coun the padding zeros needed to sum up the each iteration.
		uint32_t padding = 0;

		for (size_t i = 0; i < B->length; i++)
		{
			// DRY the primary factor.
			uint8_t primary_factor = Blen > i ? B->digits[B->length - i - 1] - '0' : 0;
			// Implementation to carry the value to be possibly added to next multiplication.
			uint64_t carry = 0;
			// Implementation to avoid pre-populated pointer.
			memset(temporal_big_int->digits, 0, MAX_DIGIT_LENGHT);
			// Implementation to initialize the length of the pointer.
			temporal_big_int->length = 0;
			// Implementation to add padding to the intermediate value.
			for (size_t k = 0; k < padding; k++)
			{
				insert_at(temporal_big_int, '0', MAX_DIGIT_LENGHT - k - 1);
			}
			size_t j = 0;
			// Primary factor multiplies every value of the B(Second big integer).
			if (primary_factor != 0)
			{
				for (; j < A->length || carry > 0; j++)
				{
#ifdef DEBUG
					printf("A(%d)*B(%d)\n",
						   (Alen > j ? A->digits[A->length - j - 1] - '0' : 0), Blen > i ? B->digits[B->length - i - 1] - '0' : 0);
#endif
					// Implementation to multuiply digit of A with digit of B plus any carried value from previous multiplication.
					uint8_t multiplication = (Alen > j ? A->digits[A->length - j - 1] - '0' : 0) * primary_factor + carry;
					// What is it for: we get the last digit of the multiplication. Example 34, we save 4 and carry 3.
					uint8_t mod10 = multiplication % BASE10;
					// Implementation to stick the carry value for the next inner iteration.
					carry = multiplication - mod10 > 0 ? (multiplication - mod10) / BASE10 : 0;
					// For debugging purposes, we validate the index and the value inserted.
					// Inserted from the back to front.
					uint64_t index = insert_at(temporal_big_int, (mod10) + '0', MAX_DIGIT_LENGHT - j - padding - 1);
#ifdef DEBUG
					printf("multiplication:%d\tmod:%d\tcarry:%ld\n", multiplication, mod10, carry);
#endif
				}
#ifdef DEBUG
				printf("[%s]:len:%d\n", temporal_big_int->digits + (MAX_DIGIT_LENGHT - j - padding), temporal_big_int->length);
#endif
			}
			else
			{

#ifdef DEBUG
				printf("Factor is zero\n");
#endif
				insert_at(temporal_big_int, '0', MAX_DIGIT_LENGHT);
			}
			// Implementation to move the pointer to the from back to front.
			ptr->digits = temporal_big_int->digits + (MAX_DIGIT_LENGHT - j - padding);
			ptr->length = j + padding;
			// Implementation to clear the pointer from previous loop iterations.
			big_int_reset(tmp);
			// Implemetation to add up the current big_integer in temporal_big_int into value(accumulate).
			big_int_sum(R, ptr, tmp);
			// Copy blocks into the output value.
			memcpy(R->digits, tmp->digits, tmp->length);
			// Preserve the length.
			R->length = tmp->length;
			// Implementation to add a new zero to next temporal big_integer.
			padding++;
		}
		free(tmp);
		free(ptr);
		free(temporal_big_int);
#ifdef DEBUG
		printf("big_int_multiply([%s] * [%s]) = [%s]:lenElse: %d\n", A->digits, B->digits, R->digits, R->length);
#endif
	}
}

/// @brief A divided by B.
/// @param A numerator
/// @param B divident
/// @param division_result
void big_int_divide(BIG_INT *A, BIG_INT *B, division_result_t *division_result)
{

	//![Exception # 1] Division by zero.
	if (BIG_INT_IS_ZERO(B))
	{
		printf("Exception: Divinding by zero.\n");
		division_result->quotient = base_ctor();
		ctor_char("0", division_result->quotient);
		division_result->remaining = base_ctor();
		ctor_char("0", division_result->remaining);
		division_result->error = DIVISION_BY_ZERO;

		// return division_result;
	}
	// Case: A and B are the same big_int. Return 1 then.
	if (BIG_INT_ARE_SAME(A, B))
	{
		BIG_INT *one = base_ctor();
		ctor_char("0", one);
		BIG_INT_COPY_FROM_TO(one, division_result->quotient);
		BIG_INT_COPY_FROM_TO(B, division_result->remaining);
		free(one);
		return;
	}
	// Case # A is not larger than B. Return zero.
	if (big_int_greater_than_abs(A, B) == 0x00)
	{
		BIG_INT *zero = base_ctor();
		ctor_char("0", zero);
		BIG_INT_COPY_FROM_TO(zero, division_result->quotient);
		BIG_INT_COPY_FROM_TO(B, division_result->remaining);
		free(zero);
		return;
	}

	// high
	BIG_INT *high = base_ctor();
	BIG_INT_COPY_FROM_TO(A, high);
	// Low
	BIG_INT *low = base_ctor();
	ctor_char("0", low);
	BIG_INT *factor = base_ctor();

	big_int_factor_between_m_and_n(A, B, high, low, factor);

	BIG_INT *factor_x_A = base_ctor();
	BIG_INT *diff = base_ctor();
	big_int_multiply(factor, A, factor_x_A);
	big_int_substract(B, factor_x_A, diff);
	BIG_INT_COPY_FROM_TO(factor, division_result->quotient);
	BIG_INT_COPY_FROM_TO(diff, division_result->remaining);

	free(factor);
	free(factor_x_A);
	free(high);
	free(low);
}

/**
 * @brief Find the maximum divisor. Recursive function.
 * @since 08/08/2023
 * @param A numerator
 * @param B possible divisior
 * @return int mid
 */
int max_divisor(BIG_INT *A, BIG_INT *B, int low, int high)
{
	BIG_INT *D = base_ctor();
	BIG_INT *C = base_ctor();
	BIG_INT *BI_mid = base_ctor();

	int mid = (high + low) / 2;

	ctor_int(mid, BI_mid);
	big_int_multiply(B, BI_mid, C);

	big_int_substract(A, C, D);

#ifdef DEBUG_MAX_DIVISOR
	printf("h=%d\tl=%d\tA=%s\tB=%s\tC=%s\tD=%s\tmid=%d\n", high, low, A->digits, B->digits, C->digits, D->digits, mid);
#endif
	// Base case
	if (big_int_greater_than_abs(B, D) == 0x01 && big_int_greater_than_abs(C, A) == 0x00)
	{
		return mid;
	}

	if (big_int_greater_than_abs(C, A) == 0x01)
	{
		free(BI_mid);
		free(C);
		free(D);
		return max_divisor(A, B, low, mid - 1);
	}
	else
	{
		free(BI_mid);
		free(C);
		free(D);
		return max_divisor(A, B, mid + 1, high);
	}
}

/**
 * @brief BIG_INT a power  BIG_INT x
 *
 *
 *
 * @param a
 * @param x
 *
 */
void big_int_power(BIG_INT *a, BIG_INT *x, BIG_INT *R)
{

#ifdef DEBUG
	printf("x.lenght=%d, x.digits=%s\n", x->length, x->digits);
	printf("a.lenght=%d, a.digits=%s\n", a->length, a->digits);
#endif
	// #case 1: x is zero, then r is 1.
	if (BIG_INT_IS_ZERO(x))
	{
		INITIALIZE_BIG_INT_TO(R, '1', 1);
		return;
	}
	// #case 2: x is 1, then r is a.
	if (BIG_INT_IS_ONE(x))
	{
		BIG_INT_COPY_FROM_TO(a, R);
		return;
	}
	// #case 3: a is zero, then r is zero.
	if (BIG_INT_IS_ZERO(a))
	{
		INITIALIZE_BIG_INT_TO(R, '0', 1);
		return;
	}

	// What it is for: To carry product BIG_INT pointer.
	BIG_INT *product = base_ctor();
	// What it is for: To carry iteration in do-while block. big_int_substract does data corruption. Map temporal local pointer to avoid corrupt.
	BIG_INT *counter = base_ctor();
	ctor_char("0", counter);

	BIG_INT *zero = base_ctor();
	ctor_char("0", zero);
	BIG_INT *one = base_ctor();
	ctor_char("1", one);
	BIG_INT *tmp = base_ctor();
	// tmp starts being the power exponetial so that we can substract until tmp zero and stop.
	BIG_INT_COPY_FROM_TO(x, tmp);
	// R(result) starts being a, which is arbitrary.
	BIG_INT_COPY_FROM_TO(a, R);
	do
	{

		// What is it for: to avoid data corruption at multiply. big_int_resets reuses the memory blocks already allocated.
		big_int_reset(product);
		// As R be initially a, we apply power algorith a*a*...*a(n)
		big_int_multiply(R, a, product);
		// What it does: accummulate the product into R safely.
		BIG_INT_COPY_FROM_TO(product, R);
		// Prevent counter being contaminated.
		big_int_reset(counter);
		// Discount one to the counter. as tmp be counter later on.
		big_int_substract(tmp, one, counter);
		// Move counter to tmp to valid it later in the loop condition at while.
		BIG_INT_COPY_FROM_TO(counter, tmp);
	} while (TO_BOOL(big_int_greater_than(tmp, one)));

#ifdef DEBUG
	printf("%s^%s=%s\n", a->digits, x->digits, R->digits);
#endif
	free(counter);
	free(zero);
	free(one);
	free(product);
}

/**
 * @brief Divides a big integer by 2.
 * @param N
 * @param division_result
 * @return void
 */
static void big_int_divide_by_2(BIG_INT *N, division_result_t *division_result)
{

	if (is_even(N->digits[N->length - 1]))
	{

		uint8_t carry = 0;
		uint8_t remaining = 0;
		for (int i = 0; i < N->length; i++)
		{
			uint8_t need_to_be_divided = ((N->digits[i] - '0') + carry + remaining);
			uint8_t quotient = need_to_be_divided / 2;

			// Implementation to clear the carry after usage.
			if (carry > 0)
				carry = 0;

			if (quotient == 0 && (N->digits[i] - '0') != 0)
			{
				carry = 10;
				continue;
			}
			remaining = (need_to_be_divided - quotient * 2) * 10;
#ifdef DEBUG_DIVIDE_BY_2
			printf("digit=%d\tcarry=%d\tremaining=%d\tquotient=%d\n", (N->digits[i] - '0'), carry, remaining, quotient);
#endif
			insert_at(division_result->quotient, quotient + '0', division_result->quotient->length);

			// PRINT_BIG_INT(division_result->quotient);
		}
		INITIALIZE_BIG_INT_TO(division_result->remaining, '0', 1);
	}
	else
	{

		BIG_INT *ONE = base_ctor();
		BIG_INT *SUM = base_ctor();

		ctor_char("1", ONE);

		big_int_substract(N, ONE, SUM);

		// Rest a number and return the number and the remaining of 1.
		int carry = 0;
		int remaining = 0;
		for (int i = 0; i < SUM->length; i++)
		{
			uint8_t need_to_be_divided = ((SUM->digits[i] - '0') + carry + remaining);
			uint8_t quotient = need_to_be_divided / 2;
			// Implementation to clear the carry after usage.
			if (carry > 0)
				carry = 0;
			// if(remaining > 0) remaining = 0;
			if (quotient == 0 && (SUM->digits[i] - '0') != 0)
			{
				carry = 10;
				continue;
			}
			remaining = (need_to_be_divided - quotient * 2) * 10;
#ifdef DEBUG_DIVIDE_BY_2
			printf("digit=%d\tcarry=%d\tremaining=%d\tquotient=%d\n", (N->digits[i] - '0'), carry, remaining, quotient);
#endif
			insert_at(division_result->quotient, quotient + '0', division_result->quotient->length);

			// PRINT_BIG_INT(division_result->quotient);;
		}

		INITIALIZE_BIG_INT_TO(division_result->remaining, '1', 1);
		free(ONE);
		free(SUM);
	}
}
/**
 * @brief finds the closer factor so that M > Factor * N > M - N.
 * This utility function serves to find the mod(M, N)
 * since mod(M, N) =  M - Factor * N where  (M - Factor * N) < N
 * @param M
 * @param N
 * @param high
 * @param low
 * @param factor
 */
static void big_int_factor_between_m_and_n(BIG_INT *M, BIG_INT *N, BIG_INT *high, BIG_INT *low, BIG_INT *factor)
{
#ifdef DEBUG_FACTOR
	PRINT_BIG_INT(M);
	PRINT_BIG_INT(N);
	PRINT_BIG_INT(high);
	PRINT_BIG_INT(low);
#endif

	BIG_INT *ONE = base_ctor();
	ctor_char("1", ONE);
	// difference between max value of factor and min value of factor.
	BIG_INT *range = base_ctor();

	// The product of the factor x N.
	BIG_INT *factor_x_N = base_ctor();
	// Always clean this before usage.
	big_int_reset(factor_x_N);
	// Constant difference between M and N.
	BIG_INT *diff_M_minus_N = base_ctor();
	// Implementation to obtain difference between M and N.
	big_int_substract(M, N, diff_M_minus_N);
	// Implementation to obtain the range of values of factor.
	big_int_substract(high, low, range);

	// Container for storing the division result.
	division_result_t *division_result;

	DIVISION_RESULT_FACTORY(division_result);

	big_int_divide_by_2(range, division_result);
	// Clear before setting it again.
	big_int_reset(factor);
	// Implementation to calculate the factor considering the lower limit.
	// Being factor + lower_limit. For instance high=14, low=2 quotient=5, then factor =7
	big_int_sum(division_result->quotient, low, factor);
	// Implementation to obtain the factor x N.
	big_int_multiply(N, factor, factor_x_N);
	/**
	 * Mathematical prove of getting the closer factor of M based on N.
	 * Factor * N  > (M - N)
	 *  M > F * N > M - N
	 *
	 */
	if (big_int_greater_than_abs(factor_x_N, diff_M_minus_N) == 0x01 && big_int_greater_than_abs(M, factor_x_N) == 0x01)
	{
		{
			free(ONE);
			free(range);
			free(factor_x_N);
			free(diff_M_minus_N);
		}
		return;
	}
	else
	{
		// Binary search of the factor that fulfills the mathematical inference.
		if (big_int_greater_than_abs(factor_x_N, M) == 0x01)
		{

			BIG_INT *tmp = base_ctor();
			BIG_INT_COPY_FROM_TO(factor, tmp);

			big_int_reset(high);

			big_int_substract(tmp, ONE, high);
			{
				free(tmp);
				free(ONE);
				free(range);
				free(factor_x_N);
				free(diff_M_minus_N);
			}
			big_int_reset(factor);
			return big_int_factor_between_m_and_n(M, N, high, low, factor);
		}
		else
		{

			BIG_INT *tmp = base_ctor();
			BIG_INT_COPY_FROM_TO(factor, tmp);
			big_int_reset(low);

			big_int_sum(tmp, ONE, low);

			{
				free(tmp);
				free(ONE);
				free(range);
				free(factor_x_N);
				free(diff_M_minus_N);
			}
			big_int_reset(factor);
			return big_int_factor_between_m_and_n(M, N, high, low, factor);
		}
	}
}

/**
 * @brief adds up two number and validate and update the carry value.
 *
 * @param sum reference that stores the sum accumulated
 * @param a number first.
 * @param b number second
 * @param carry reference that carries the carried value to next sum operation.
 */
static void add(uint8_t *sum, uint8_t a, uint8_t b, uint8_t *carry)
{
	*sum += primitive_sum(a, b, *carry);
	apply_carry_if_apply(sum, carry);
}
/**
 * @brief substracts two values, apply the borrowing and apply a simple substraction.
 *
 * @param needs_borrow reference that stores the need of the borrowing
 * @param substraction reference thtt stores the result.
 * @param a number first to substract from.
 * @param b number second to be substrated from a.
 * @param borrow if needs_borrowing is true, then take the borrow to the next substraction.
 */
static void substract(uint8_t *needs_borrow, uint8_t *substraction, uint8_t a, uint8_t b, uint8_t *borrow)
{
	*needs_borrow = apply_borrowing_if_apply(substraction, a, b, *borrow);
	*substraction += primitive_substraction(a, b, *borrow);
	*borrow = *needs_borrow ? 1 : 0;
}

/**
 * @brief add up two numbers plus the carried value from previous operation.
 *
 * @param a number first
 * @param b number second
 * @param carry The carried value to the next adding up.
 * @return uint8_t
 */
static uint8_t primitive_sum(uint8_t a, uint8_t b, uint8_t carry)
{
	return a + b + carry;
}

/**
 * @brief substracts out two numbers less the borrowed value from previous opeation.
 *
 * @param a number first.
 * @param b number second.
 * @param initial_borrow borrowed value from previous operation.
 * @return uint8_t
 */
static uint8_t primitive_substraction(uint8_t a, uint8_t b, uint8_t initial_borrow)
{
	return a - b - initial_borrow;
}

/**
 * @brief Applies borrowing when applies. Update the references.
 *
 * @param substraction references that stores the borrowed value 10 or 0.
 * @param a number first.
 * @param b number second.
 * @param initial_borrow initial borrow (readonly)
 * @return uint8_t
 */
static uint8_t apply_borrowing_if_apply(uint8_t *substraction, uint8_t a, uint8_t b, const uint8_t initial_borrow)
{
	uint8_t needs_borrowing = (a - initial_borrow < b || a == 0 && b != 0);
	*substraction += needs_borrowing ? 10 : 0;
	return needs_borrowing;
}
/**
 * @brief validates that the operation carries a value or not.
 *
 * @param sum reference that store the sum (readonly)
 * @param carry
 * @return uint8_t
 */
static uint8_t apply_carry_if_apply(uint8_t *sum, uint8_t *carry)
{
	*carry = *sum >= 10 ? 1 : 0;
}

/**
 * @brief Compares the two BIG_INTs (A > B)
 *
 * @param A number first.
 * @param B number second.
 * @return uint8_t 1(true)|0(false)
 */
uint8_t big_int_greater_than(const BIG_INT *A, const BIG_INT *B)
{
#ifdef DEBUGGREATERTHAN
	printf("%c%s > %c%s = %d\n", A->sign, A->digits, B->sign, B->digits, A->length > B->length);
#endif
	// Case #1. A is positive and B is negative, then A is greater.
	if (A->sign == '+' && B->sign == '-')
		return 0x01;
	// Case #2. A length is larger than B length, then A is greater.
	else if ((A->length > B->length) && A->sign == '+')
		return 0x01;
	// Case #3. Both Big_int are equals.
	else if (A->length == B->length)
	{
		int j = 0;
		// O(n) to find where the number are different,
		while (j < A->length)
		{
#ifdef DEBUGGREATERTHAN
			printf("Case #3.2Iqual len: [%c%c > %c%c]\n", A->sign, A->digits[j], B->sign, B->digits[j]);
#endif
			// Case #3.1. The digits are equals, then continue.
			if ((A->digits[j] == B->digits[j]))
			{
				j++;
				continue;
			}
			// Case #3.2. The digit in A is larger than B.
			else if ((A->digits[j] > B->digits[j]) && (A->sign == '+'))
				return 0x01;
			// Case #3.3. otherwise.
			else
				return 0x00;
			j++;
		}
		// Case #3.4: A and B are equal. Then A isn't greater than B.
		return 0x00;
	}
	// Default case: A is not greater B.
	else
		return 0x00;
}
/**
 * @brief Compares two big integers as absolute values.
 *
 * @param A
 * @param B
 * @return uint8_t
 */
uint8_t big_int_greater_than_abs(BIG_INT *A, BIG_INT *B)
{
	const uint8_t tmp_signA = A->sign;
	const uint8_t tmp_signB = B->sign;
	A->sign = '+';
	B->sign = '+';
	uint8_t is_A_greater_than_B = big_int_greater_than(A, B);
	A->sign = tmp_signA;
	B->sign = tmp_signB;
	return is_A_greater_than_B;
}
/**
 * @brief insert digit in the index stated and update the length of the big integer.
 *
 * @param big_int
 * @param value
 * @param index
 * @return uint16_t
 */
static uint16_t insert_at(BIG_INT *big_int, uint8_t value, uint16_t index)
{
	big_int->digits[index] = value;
	big_int->length++;
	return index;
}
#endif //  CREEPTO_BIG_INT_H

/**
 * @brief  clear any zero at front of the array of digits.
 *
 * @param big_int
 */
void clean_zero_in_front(BIG_INT *big_int)
{
	while (big_int->digits[0] == '0' && big_int->length > 1)
	{
		big_int->digits++;
		big_int->length--;
	}
}

static uint8_t is_valid_hex_string(uint8_t *str, uint16_t len)
{
	for (int i = 0; i < len; i++)
	{
		if (0x01 ^ (IS_DIGIT(str[i]) | IS_HEXALPH(str[i])) == 1)
		{
			printf("Invalid Hex\n");
			return 0x00;
		}
	}
	return 0x01;
}


/**
 * @brief mod of M % N
 * @param M
 * @param N
 * @param R
 *
 */
void big_int_mod(BIG_INT *M, BIG_INT *N, BIG_INT *R)
{
	// When M % N and N larger than M then, M % N is M.
	if (big_int_greater_than_abs(N, M) == 0x01)
	{
		BIG_INT_COPY_FROM_TO(M, R);
		return;
	}
	// high
	BIG_INT *high = base_ctor();
	BIG_INT_COPY_FROM_TO(M, high);
	// Low
	BIG_INT *low = base_ctor();
	ctor_char("0", low);

	BIG_INT *factor = base_ctor();
	big_int_factor_between_m_and_n(M, N, high, low, factor);
	// PRINT_BIG_INT(factor);

	BIG_INT *factor_x_N = base_ctor();
	big_int_multiply(N, factor, factor_x_N);

	BIG_INT *diff_with_M = base_ctor();
	big_int_substract(M, factor_x_N, diff_with_M);

	BIG_INT_COPY_FROM_TO(diff_with_M, R);

	free(factor);
	free(factor_x_N);
	free(diff_with_M);
}

void big_int_gcd(BIG_INT *A, BIG_INT *B, BIG_INT *R)
{
	while (BIG_INT_IS_ZERO(A))
	{
		// PRINT_BIG_INT(B);
		BIG_INT *modulus_of_B_and_A = base_ctor();
		big_int_mod(B, A,modulus_of_B_and_A);
	
		big_int_reset(A);
		
		BIG_INT_COPY_FROM_TO(A, B);
		
		big_int_reset(B);
		// PRINT_BIG_INT(modulus_of_A_and_B);
		BIG_INT_COPY_FROM_TO(modulus_of_B_and_A, A);
		
		free(modulus_of_B_and_A);
	}

	BIG_INT_COPY_FROM_TO(A, R);
	return;
}

/**
 * @description:  A function to find the greatest common divisor of two big integers.
 * @param c
 *
 */
static bool is_even(char c)
{
	return (c == '0' ||
			c == '2' ||
			c == '4' ||
			c == '6' ||
			c == '8');
}
