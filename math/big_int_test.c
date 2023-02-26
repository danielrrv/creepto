
#include "assert.h"
#include "big_int.h"


void greater_than(){
	BIG_INT * A = base_ctor();
	BIG_INT * B = base_ctor();

	ctor_char("2", A);
	ctor_char("0", B);

	assert(big_int_greater_than(A,  B)==0x01);
	clear_digit(A);
	clear_digit(B);

	ctor_char("0", A);
	ctor_char("2", B);

	assert(big_int_greater_than(A,  B)==0x00);
	clear_digit(A);
	clear_digit(B);

	ctor_char("0", A);
	ctor_char("0", B);

	assert(big_int_greater_than(A,  B)==0x00);
	clear_digit(A);
	clear_digit(B);
	printf("==> test_should_greater than[passed]\n");

}

void test_should_ctor_int(){
	//Case #1
	BIG_INT * bg_int = base_ctor(); 
	ctor_int(61651, bg_int);
	uint8_t integer_as_text[] = {'6', '1', '6', '5', '1'};
	assert(strcmp(bg_int->digits,  integer_as_text)==0);
	assert(bg_int->sign=='+');
	free(bg_int);
	//Case #2
	BIG_INT * bg_int_2 = base_ctor(); 
	ctor_int(10, bg_int_2);
	uint8_t second[] = {'1', '0'};
	assert(strncmp(bg_int_2->digits,  second, 2) == 0);
	free(bg_int_2);
	//Case #3
	BIG_INT * bg_int10 = base_ctor(); 
	ctor_int(100, bg_int10);
	uint8_t integer10_as_text[] = {'1', '0', '0'};
	assert(strncmp(bg_int10->digits,  integer10_as_text, 2)==0);
	free(bg_int10);

		//Case #4
	BIG_INT * bg_int4 = base_ctor(); 
	ctor_int(5, bg_int4);
	uint8_t integer4_as_text[] = {'5'};
	assert(strncmp(bg_int4->digits,  integer4_as_text, 1)==0);
	free(bg_int4);
	printf("==> test_should_ctor_int[passed]\n");
}

void test_should_ctor_char(){
	//case #1.
	BIG_INT * bg_int = base_ctor();
	ctor_char("-61651", bg_int);
	uint8_t integer_as_text[] = {'6', '1', '6', '5', '1'};
	assert(strcmp(bg_int->digits,  integer_as_text)==0);
	assert(bg_int->sign=='-');
	free(bg_int);
	//Case#2.
	BIG_INT * bg_int10 = base_ctor(); 
	ctor_char("100", bg_int10);
	uint8_t integer10_as_text[] = {'1', '0', '0'};
	assert(strncmp(bg_int10->digits,  integer10_as_text, 3)==0);

	free(bg_int10);
	printf("==> test_should_ctor_char[passed]\n");
	
}
void test_should_sum(){
	BIG_INT * A = base_ctor();
	BIG_INT * B = base_ctor();
	BIG_INT * R = base_ctor();
	BIG_INT * T = base_ctor();

	ctor_char("20003", A);
	ctor_char("2456", B);
	ctor_char("22459", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("96643", A);
	ctor_char("75754", B);
	ctor_char("172397", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("99900", A);
	ctor_char("6006", B);
	ctor_char("105906", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("9984", A);
	ctor_char("2556", B);
	ctor_char("12540", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("8974", A);
	ctor_char("2554336", B);
	ctor_char("2563310", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("9984", A);
	ctor_char("5112556", B);
	ctor_char("5122540", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", A);
	ctor_char("0", B);
	ctor_char("0", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3481923779495873470699961441127886115309787790054947458822752617", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("-3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("-3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("-3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("-3481923779495873470699961441127886115309787790054947458822752617", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("2556", A);
	ctor_char("9984", B);
	ctor_char("12540", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-9984", A);
	ctor_char("2556", B);
	ctor_char("-7428", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-998422", A);
	ctor_char("2556", B);
	ctor_char("-995866", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-9984", A);
	ctor_char("255622", B);
	ctor_char("-245638", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-998422", A);
	ctor_char("-2556", B);
	ctor_char("-1000978", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-9984", A);
	ctor_char("-255622", B);
	ctor_char("-265606", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("9984", A);
	ctor_char("0", B);
	ctor_char("9984", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", A);
	ctor_char("2556", B);
	ctor_char("2556", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", A);
	ctor_char("1000150", B);
	ctor_char("1000150", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("191502086816040508058769501485429142358480752283393809010901812903019017421636531501658722091387723965207369835613458680419152", A);
	ctor_char("32429895406264297993771527300008845774187146823839192918821268800000000000000000000000000000000000000000000000000000000000000", B);
	ctor_char("223931982222304806052541028785437988132667899107233001929723081703019017421636531501658722091387723965207369835613458680419152", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	free(A);
	free(B);
	free(T);
	free(R);


printf("==> test_should_sum[passed]\n");
}
// void test_should_get_sign(){
// 	assert(ctor_int(-100001)->sign =='-');
// 	assert(ctor_char("-100001")->sign =='-');
// }

void test_should_substract(){
	BIG_INT * A = base_ctor();
	BIG_INT * B = base_ctor();
	BIG_INT * R = base_ctor();
	BIG_INT * T = base_ctor();

	ctor_char("20003", A);
	ctor_char("2456", B);
	ctor_char("17547", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("1", A);
	ctor_char("1", B);
	ctor_char("0", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", A);
	ctor_char("1", B);
	ctor_char("-1", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("2", A);
	ctor_char("1", B);
	ctor_char("1", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("96643", A);
	ctor_char("75754", B);
	ctor_char("20889", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("99900", A);
	ctor_char("6006", B);
	ctor_char("93894", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("9984", A);
	ctor_char("2556222", B);
	ctor_char("-2546238", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", A);
	ctor_char("0", B);
	ctor_char("0", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-998444", A);
	ctor_char("2556", B);
	ctor_char("-1001000", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-9984", A);
	ctor_char("255622", B);
	ctor_char("-265606", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-9984", A);
	ctor_char("-255622", B);
	ctor_char("-245638", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", A);
	ctor_char("157624825433230490762246168127797657567916321816555529634539929", B);
	ctor_char("3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3481923779495873470699961441127886115309787790054947458822752617", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("-3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3481923779495873470699961441127886115309787790054947458822752617", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("-3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("-3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("-9984", A);
	ctor_char("2556", B);
	ctor_char("-12540", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("993399393090909099393090", A);
	ctor_char("964046696678166464181933", B);
	ctor_char("29352696412742635211157", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	free(A);	
	free(B);
	free(T);
	free(R);

	printf("==> test_should_substract[passed]\n");
}
void test_should_multiply(){
	BIG_INT * A = base_ctor();
	BIG_INT * B = base_ctor();
	BIG_INT * R = base_ctor();
	BIG_INT * T = base_ctor();

	ctor_char("0", R);
	ctor_char("2456", A);
	ctor_char("20003", B);
	ctor_char("49127368", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("2456", A);
	ctor_char("0", B);
	ctor_char("0", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);
	
	ctor_char("0", R);
	ctor_char("1111111111111111111111", A);
	ctor_char("1111111111111111111111", B);
	ctor_char("1234567901234567901234320987654320987654321", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("99339939309090909939309036434567534789534566322555599965352468877", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("330235656341857344427306467991636173969355735344993753690588034171903458530046727041675524180340518694179474155432188767776511376", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", A);
	ctor_char("157624825433230490762246168127797657567916321816555529634539929", B);
	ctor_char("523992042321994806059141329145437988132698862137233062019813141703019017421636531501658722091387723965207369835613458680419152", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", A);
	ctor_char("1", B);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("1", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("1", A);
	ctor_char("33242989540626429799377", B);
	ctor_char("33242989540626429799377", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("33242989540626429799377", A);
	ctor_char("1", B);
	ctor_char("33242989540626429799377", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("33242989540626429799377", A);
	ctor_char("10", B);
	ctor_char("332429895406264297993770", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	ctor_char("0", R);
	ctor_char("33242989540626429799377", A);
	ctor_char("100", B);
	ctor_char("3324298954062642979937700", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);
	
	ctor_char("0", R);
	ctor_char("33242989540626429799377", A);
	ctor_char("0", B);
	ctor_char("0", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(B);
	clear_digit(T);
	clear_digit(R);

	free(A);
	free(B);
	free(T);
	free(R);
	printf("==> test_should_multiply[passed]\n");
}

void test_should_pow(){
	BIG_INT * A = base_ctor();
	BIG_INT * X = base_ctor();
	BIG_INT * R = base_ctor();
	BIG_INT * T = base_ctor();
	//case #1:  x is zero, then r is 1. 
	ctor_char("10", A);
	ctor_char("0", X);
	ctor_char("1", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(X);
	clear_digit(T);
	clear_digit(R);

	//case #2:  x is 1, then r is a.
	ctor_char("123", A);
	ctor_char("1", X);
	ctor_char("123", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(X);
	clear_digit(T);
	clear_digit(R);

	//case #3:  a is zero, then r is zero.
	ctor_char("0", A);
	ctor_char("2", X);
	ctor_char("0", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(X);
	clear_digit(T);
	// clear_digit(R);

	// //case # 
	ctor_char("10", A);
	ctor_char("2", X);
	ctor_char("100", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(X);
	clear_digit(T);
	clear_digit(R);
	
	
	//case # 
	ctor_char("2", A);
	ctor_char("5", X);
	ctor_char("32", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(X);
	clear_digit(T);
	clear_digit(R);

	ctor_char("33242989540626429799377", A);
	ctor_char("3", X);
	ctor_char("36736706524049309749503140261766410950369518374281734279955290795633", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits,T->digits)==0);
	clear_digit(A);
	clear_digit(X);
	clear_digit(T);
	clear_digit(R);
	printf("==> test_should_pow[passed]\n");
}

void test_should_divide(){

	BIG_INT * A = base_ctor();
	BIG_INT * B = base_ctor();
	BIG_INT * T = base_ctor();

	ctor_char("99339939309090909939309036434567534789534566322555599965352468877", A);
	ctor_char("33242989540626429799377", B);
	ctor_char("33242989540626429799377", T);


		//Initialize a BIG_INT instance;
	division_result_t * division_result = (division_result_t *)malloc(sizeof(division_result_t));
	division_result->quotient = base_ctor();
	ctor_char("0", division_result->quotient);

	division_result->remaining = base_ctor();
	ctor_char("0", division_result->remaining);

	big_int_divide(A, B, division_result);
	// assert(strcmp(big_int_divide( ctor_char("993"), ctor_char("33"))->quotient->digits, ctor_char("1")->digits)==0);
	// assert(strcmp(big_int_divide( ctor_char("3324298954062642979937715273000088457741871468238391929188212688"), ctor_char("0"))->quotient->digits, ctor_char("523992042321994806059141329145437988132698862137233062019813141703019017421636531501658722091387723965207369835613458680419152")->digits)==0);
	assert(strcmp(division_result->quotient->digits, T->digits)==0);
	printf("==> test_should_divide[passed]\n");//993399393090909099393090
}

int main(){
	// greater_than();
	// test_should_ctor_int();
	// test_should_ctor_char();
	// test_should_sum();p
	// test_should_substract();
	// test_should_multiply();
	// test_should_divide();
	 test_should_pow();
	return 0;
}