

#include "big_int.h"

int main(){

	uint8_t message[MAX_DIGIT_LENGHT], output[MAX_DIGIT_LENGHT];
	memset(message, 0, MAX_DIGIT_LENGHT);
	uint64_t bytesRead = read(0, message, MAX_DIGIT_LENGHT);
	BIG_INT * value = ct_char(message);
	BIG_INT * integer = ct_int(61651);
	BIG_INT * integer2 = ct_int(-100001);
	BIG_INT * valueA = ct_char("616512316543123165465636565231654065");
	BIG_INT * valueB = ct_char("616512316543123165465416545405640645");
	if(big_int_greater_than(valueB, valueA) == 0){
			printf("Failed!\n");
			return 1;	
	}
	if(big_int_greater_than(integer, integer2) == 0){
			printf("Failed!\n");
			return 1;
	}
	
	BIG_INT * sum = big_int_sum(valueA,
	 valueB);
	// printf("%s\n",message);
	if(value==NULL){
		printf("Failed!\n");
		return 1;
	}
	printf("digits-char: %s\n", value->digits);
	printf("digits-int1: %s\tsign:%c\n", integer->digits, integer->sign);
	printf("digits-int2: %s\tsign:%c\n", integer2->digits, integer2->sign);
	printf("Sum of valueA + ValueB: %s\n", sum->digits);
	printf("success\n");
	return 0;
}