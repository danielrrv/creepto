#ifndef CREEPTO_BIG_INT_H
#define CREEPTO_BIG_INT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_DIGIT(c) ((c >= '0' && '9' >= c) ? 1 : 0)

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
BIG_INT *base_ctor();
BIG_INT *ctor_char(char *);
BIG_INT *ctor_int(int);
BIG_INT *ctor_long(long);

// Operations
BIG_INT *big_int_sum(BIG_INT *, BIG_INT *);
BIG_INT *big_int_substract(BIG_INT *, BIG_INT *);
BIG_INT *big_int_multiply(BIG_INT *, BIG_INT *);
BIG_INT *big_int_divide(BIG_INT *, BIG_INT *);
BIG_INT *big_int_modulo(BIG_INT *n, BIG_INT *m);
BIG_INT *big_int_power(BIG_INT *a, BIG_INT *x);
BIG_INT *big_int_root_square(BIG_INT *, BIG_INT *);

//Primitives
void add(uint8_t * sum, uint8_t a, uint8_t b, uint8_t * carry);
void substract(uint8_t * needs_borrow, uint8_t * substraction, uint8_t a, uint8_t b, uint8_t * carry);
uint8_t primitive_substraction(uint8_t, uint8_t, uint8_t);
uint8_t apply_borrowing_if_apply(uint8_t *, uint8_t, uint8_t, const uint8_t);
uint8_t primitive_sum(uint8_t, uint8_t, uint8_t);
uint8_t apply_carry_if_apply(uint8_t *, uint8_t *);


// uint8_t valid_integer_at()

// Comparisons

uint8_t big_int_greater_than(const BIG_INT * a, const BIG_INT *b);
uint8_t bit_int_greater_than_abs(BIG_INT  * A, BIG_INT *B);
uint8_t big_int_equal_to(BIG_INT *a, BIG_INT *b);


// Utils
uint16_t insert_at(BIG_INT *, uint8_t, uint16_t);
uint8_t invert_sign(uint8_t sign){
	return sign=='+' ? '-':'+';
}


BIG_INT *base_ctor()
{
	BIG_INT *value = (BIG_INT *)malloc(sizeof(BIG_INT));
	value->length = 0;
	value->sign = '+';
	value->digits = (uint8_t *)malloc(sizeof(uint8_t) * MAX_DIGIT_LENGHT);
	memset(value->digits, '\0', MAX_DIGIT_LENGHT);
	return value;
}

BIG_INT *ctor_char(char *r)
{
	BIG_INT *value = base_ctor();

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
		if(*rr=='\0'){
			
			return value;
		}
		if (IS_DIGIT(*rr) == 0)
		{	
			if ((*rr == '+' || *rr == '-') && i == 0){
				value->sign = *rr;
			}
			rr++;
			continue;
		}
		memcpy(value->digits + i, (uint8_t *)rr, sizeof(uint8_t));
		value->length++;
		i++;
		rr++;
	}
	return value;
}

BIG_INT *ctor_int(int number)
{
	BIG_INT *value = base_ctor();
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

BIG_INT *ctor_long(long number)
{
	BIG_INT *value = base_ctor();

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
	BIG_INT * value = base_ctor();
	uint32_t Blen = B->length, Alen = A->length, max_length = Blen > Alen ? Blen : Alen;
	uint8_t carry = 0;
	size_t i;
	uint8_t is_A_greater_than_B_abs = bit_int_greater_than_abs(A, B) == 0x01; 
	for (i = 0; i < Blen || i < Alen || carry > 0; i++)
	{
		#ifdef DEBUG
			printf("DEBUG[INPUT]: A'%d(%c) + B'%d(%c) + T'%d(%c)\n", A->digits[Alen- i - 1], A->digits[Alen - i - 1], B->digits[Blen - i - 1], B->digits[Blen - i - 1], carry + '0', carry + '0');
		#endif
		uint8_t valid_integer_A_at_i = Alen > i ? A->digits[Alen - i - 1] - '0' : 0,valid_integer_B_at_i = Blen > i ? B->digits[Blen - i - 1] - '0' : 0,
		needs_borrow = 0,
		sum = 0;
		if(is_A_greater_than_B_abs){
			if((A->sign=='+' && B->sign == '-') || (A->sign=='-' && B->sign == '+'))substract(&needs_borrow, &sum, valid_integer_A_at_i, valid_integer_B_at_i, &carry);
			else add(&sum, valid_integer_A_at_i, valid_integer_B_at_i, &carry );
		}else{
			if(B->sign=='+' && A->sign=='+'||B->sign=='-' && A->sign=='-')add(&sum, valid_integer_B_at_i, valid_integer_A_at_i, &carry);
			else substract(&needs_borrow, &sum, valid_integer_B_at_i, valid_integer_A_at_i, &carry);
		}
		uint16_t index = insert_at(value, sum % 10 + '0', MAX_DIGIT_LENGHT - i - 1);
		 
		#ifdef DEBUG
			printf("DEBUG[INSERTED1]: %d(%c)\t carry: %c\tindex:%d\n", (sum %10) + '0', (sum %10) + '0', carry + '0', index);
		#endif
	}
	value->digits = value->digits + (MAX_DIGIT_LENGHT - i - carry);
	value->sign = is_A_greater_than_B_abs ? A->sign: B->sign;
	#ifdef DEBUG
		printf("[%s] + [%s] = [%s]\n", A->digits, B->digits,value->digits);
	#endif
	return value;
}

BIG_INT *big_int_substract(BIG_INT *A, BIG_INT *B)
{
	BIG_INT *value = base_ctor();	
	uint32_t Blen = B->length, Alen = A->length;
	uint8_t borrow = 0;
	size_t i;
	uint8_t is_A_greater_than_B_abs = bit_int_greater_than_abs(A, B) == 0x01; 
	for (i = 0; i < Alen || i < Blen|| borrow > 0; i++)
	{
		#ifdef DEBUG
			printf("DEBUG[INPUT]: A'%d(%c) - B'%d(%c) - T'%d(%c)\n", A->digits[A->length - i - 1], A->digits[A->length - i - 1], B->digits[B->length - i - 1], B->digits[B->length - i - 1], borrow + '0', borrow + '0');
		#endif
		uint8_t valid_integer_A_at_i = Alen > i ? A->digits[Alen - i - 1] - '0' : 0,valid_integer_B_at_i = Blen > i ? B->digits[Blen - i - 1] - '0' : 0;
		uint8_t needs_borrow = 0;
		int8_t substraction = 0;
		if(is_A_greater_than_B_abs){
			if(A->sign=='-' && B->sign=='+') add(&substraction, valid_integer_A_at_i, valid_integer_B_at_i, &borrow);
			else substract(&needs_borrow, &substraction, valid_integer_A_at_i, valid_integer_B_at_i, &borrow);
		}else{
			if(B->sign=='-' && A->sign=='+'||B->sign=='+' && A->sign=='-') add(&substraction, valid_integer_B_at_i, valid_integer_A_at_i, &borrow);
			else substract(&needs_borrow, &substraction, valid_integer_B_at_i, valid_integer_A_at_i, &borrow);
			
		}
		uint16_t index = insert_at(value, (substraction % BASE10) + '0', MAX_DIGIT_LENGHT - i - 1);
		#ifdef DEBUG
			printf("%d = A(%d) - B(%d) - borrow(%d)\n",substraction,(A->digits[Alen - i - 1]-'0'),(B->digits[Blen - i - 1] - '0'), borrow);
			printf("DEBUG[SUB][INSERTED]: value:%d(%c)\tborrow:%c\tindex:%d\n", substraction % BASE10 + '0', substraction % BASE10 + '0', borrow + '0', index);
		#endif

		
	}
		
	value->digits = value->digits + (MAX_DIGIT_LENGHT - i);
	value->sign = is_A_greater_than_B_abs ? A->sign: B->sign;
	#ifdef DEBUG
		printf("[%s] - [%s]=[%s]\n", A->digits, B->digits,value->digits);
	#endif
	return value;
}

BIG_INT *big_int_multiply(BIG_INT * A, BIG_INT * B){
	//Initialize a BIG_INT instance;
	BIG_INT *value = ctor_char("0");
	//Initialize a temporal BIG_INT to store each multiplication.
	BIG_INT *temporal_big_int = base_ctor();
	// DRY the big_int length.
	uint32_t Alen = A->length;
	uint32_t Blen = B->length;
	//Case #1. B is greater than A by absolute value.
	if(bit_int_greater_than_abs(A, B)==0x00){
		//Variable declare to coun the padding zeros needed to sum up the each iteration.
		uint32_t padding = 0;
		//Going through O(N2) iteration on A to muliply each element of A with B ones.
		//Each iteration create a new intermediate output.
		for (size_t i = 0; i < A->length; i++){
			//DRY the primary factor.
			uint8_t primary_factor = Alen > i ? A->digits[A->length - i - 1] - '0' : 0 ;
			
			//Implementation to carry the value to be possibly added to next multiplication.
			uint64_t carry = 0;
			//Implementation to avoid pre-populated pointer.
			memset(temporal_big_int->digits, 0, MAX_DIGIT_LENGHT);
			//Implementation to initialize the length of the pointer.
			temporal_big_int->length = 0;
			//Implementation to add padding to the intermediate value.
			for (size_t k = 0; k < padding; k++)
			{
				insert_at(temporal_big_int, '0', MAX_DIGIT_LENGHT - k - 1);
			}

			size_t j = 0;
			if(primary_factor != 0){
			//Primary factor multiplies every value of the B(Second big integer).
				for (;j < B->length || carry > 0 ; j++ )
				{
					#ifdef DEBUG
						printf("A(%d)*B(%d)\n",(Blen > j ? B->digits[B->length - j - 1] - '0':0),  Alen > i ? A->digits[A->length - i - 1] - '0':0);
					#endif
					//Implementation to multuiply digit of A with digit of B plus any carried value from previous multiplication.
					uint8_t multiplication = (Blen > j ? B->digits[B->length - j - 1] - '0':0) * primary_factor + carry;
					//What is it for: we get the last digit of the multiplication. Example 34, we save 4 and carry 3.
					uint8_t mod10 = multiplication % BASE10;
					//Implementation to stick the carry value for the next inner iteration.
					carry = multiplication - mod10 > 0 ? (multiplication - mod10) / BASE10 : 0;
					//For debugging purposes, we validate the index and the value inserted.
					//Inserted from the back to front.
					uint64_t index = insert_at(temporal_big_int, (mod10) + '0', MAX_DIGIT_LENGHT - j - padding - 1);	
					#ifdef DEBUG
						printf("multiplication:%d\tmod:%d\tcarry:%ld\n", multiplication, mod10, carry);
					#endif
				}
				#ifdef DEBUG
					printf("[%s]:len:%d\n", temporal_big_int->digits + (MAX_DIGIT_LENGHT - j - padding), temporal_big_int->length);
				#endif
			}else{
				insert_at(temporal_big_int, '0', MAX_DIGIT_LENGHT);
			}
			// Implementation to move the pointer to the from back to front.
			temporal_big_int->digits = temporal_big_int->digits + (MAX_DIGIT_LENGHT - j - padding);
			//Implemetation to add up the current big_integer in temporal_big_int into value(accumulate).			
			BIG_INT * tmp = big_int_sum(value, temporal_big_int);
			//Set the value digits to the temporal out
			value->digits = tmp->digits;
			// Copy blocks into the output value.
			memcpy(value->digits,tmp->digits, tmp->length);
			//Preserve the length.
			value->length = tmp->length;
			//Implementation to add a new zero to next temporal big_integer.
			padding++;
		}
		#ifdef DEBUG
			printf("[%s] * [%s] = [%s]:len%d\n", A->digits, B->digits,value->digits, value->length);
		#endif
		return value;
	} else{
		//Variable declare to coun the padding zeros needed to sum up the each iteration.
		uint32_t padding = 0;
		for (size_t i = 0; i < B->length; i++){
			//DRY the primary factor.
			uint8_t primary_factor =   Blen > i ? B->digits[B->length - i - 1] - '0' : 0 ;
			//Implementation to carry the value to be possibly added to next multiplication.
			uint64_t carry = 0;
			//Implementation to avoid pre-populated pointer.
			memset(temporal_big_int->digits, 0, MAX_DIGIT_LENGHT);
			//Implementation to initialize the length of the pointer.
			temporal_big_int->length = 0;
			//Implementation to add padding to the intermediate value.
			for (size_t k = 0; k < padding; k++)
			{
				insert_at(temporal_big_int, '0', MAX_DIGIT_LENGHT - k - 1);
			}
			size_t j = 0;
			//Primary factor multiplies every value of the B(Second big integer).
			if(primary_factor!=0){
				for (; j < B->length || carry > 0 ; j++ )
				{
					#ifdef DEBUG
						printf("A(%d)*B(%d)\n",(Alen > j ? A->digits[A->length - j - 1] - '0':0),  Blen > i ? B->digits[B->length - i - 1] - '0': 0);
					#endif
					//Implementation to multuiply digit of A with digit of B plus any carried value from previous multiplication.
					uint8_t multiplication = (Alen > j ? A->digits[A->length - j - 1] - '0':0) * primary_factor + carry;
					//What is it for: we get the last digit of the multiplication. Example 34, we save 4 and carry 3.
					uint8_t mod10 = multiplication % BASE10;
					//Implementation to stick the carry value for the next inner iteration.
					carry = multiplication - mod10 > 0 ? (multiplication - mod10) / BASE10 : 0;
					//For debugging purposes, we validate the index and the value inserted.
					//Inserted from the back to front.
					uint64_t index = insert_at(temporal_big_int, (mod10) + '0', MAX_DIGIT_LENGHT - j - padding - 1);	
					#ifdef DEBUG
						printf("multiplication:%d\tmod:%d\tcarry:%ld\n", multiplication, mod10, carry);
					#endif
				}
				#ifdef DEBUG
					printf("[%s]:len:%d\n", temporal_big_int->digits + (MAX_DIGIT_LENGHT - j - padding), temporal_big_int->length);
				#endif
			}else{
				insert_at(temporal_big_int, '0', MAX_DIGIT_LENGHT);
			}
			// Implementation to move the pointer to the from back to front.
			temporal_big_int->digits = temporal_big_int->digits + (MAX_DIGIT_LENGHT - j - padding);
			//Implemetation to add up the current big_integer in temporal_big_int into value(accumulate).			
			BIG_INT * tmp = big_int_sum(value, temporal_big_int);
			//Set the value digits to the temporal out
			value->digits = tmp->digits;
			// Copy blocks into the output value.
			memcpy(value->digits, tmp->digits, tmp->length);
			//Preserve the length.
			value->length = tmp->length;
			padding++;
		}
		#ifdef DEBUG
			printf("[%s] * [%s] = [%s]:len%d\n", A->digits, B->digits,value->digits, value->length);
		#endif
		return value;
	}
}

void add(uint8_t * sum, uint8_t a, uint8_t b, uint8_t * carry){
	*sum+= primitive_sum(a, b, *carry);
	apply_carry_if_apply(sum, carry);
}
void substract(uint8_t * needs_borrow, uint8_t * substraction, uint8_t a, uint8_t b, uint8_t * borrow){
	*needs_borrow = apply_borrowing_if_apply(substraction, a, b, *borrow);
	*substraction += primitive_substraction(a, b, *borrow);
	*borrow = *needs_borrow ? 1 : 0;
}
uint8_t primitive_sum(uint8_t a, uint8_t b, uint8_t carry){
	return a + b + carry;
}

uint8_t primitive_substraction(uint8_t a, uint8_t b, uint8_t initial_borrow){
	return a - b  - initial_borrow;
}
uint8_t apply_borrowing_if_apply(uint8_t * substraction, uint8_t a, uint8_t b, const uint8_t initial_borrow){
	uint8_t needs_borrowing = (a - initial_borrow < b || a == 0 && b!=0) ;
	*substraction += needs_borrowing ? 10 : 0;
	return needs_borrowing;
}	
uint8_t apply_carry_if_apply(uint8_t * sum, uint8_t * carry){
		*carry = *sum >= 10 ? 1 : 0;
}

uint8_t big_int_greater_than(const BIG_INT * A, const BIG_INT * B)
{
	if (A->sign == '+' && B->sign == '-')return 1;
	else if ((A->length > B->length) && A->sign == '+')return 1;
	else if (A->length == B->length)
	{
		int j = 0;
		while (j < A->length)
		{
			if ((A->digits[j] - '0' == B->digits[j] - '0'))
			{
				j++;
				continue;
			}
			else if ((A->digits[j] - '0' > B->digits[j] - '0') && (A->sign == '+'))return 1;		
			else return 0;
			j++;
		}
	}
	else return 0;
}

uint8_t bit_int_greater_than_abs(BIG_INT  * A, BIG_INT *B){
	const uint8_t tmp_signA = A->sign;
	const uint8_t tmp_signB = B->sign;
	A->sign = '+';
	B->sign = '+';
	uint8_t is_A_greater_than_B = big_int_greater_than(A, B);
	A->sign = tmp_signA;
	B->sign = tmp_signB;
	return is_A_greater_than_B;
}

uint16_t insert_at(BIG_INT *big_int, uint8_t value, uint16_t index)
{
	big_int->digits[index] = value;
	big_int->length++;
	return index;
}
#endif //  CREEPTO_BIG_INT_H