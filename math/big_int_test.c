

#include "big_int.h"

void greater_than()
{
	BIG_INT *A = base_ctor();
	BIG_INT *B = base_ctor();

	ctor_char("2", A);
	ctor_char("0", B);

	assert(big_int_greater_than(A, B) == 0x01);

	big_int_reset(A);
	big_int_reset(B);

	ctor_char("0", A);
	ctor_char("2", B);

	assert(big_int_greater_than(A, B) == 0x00);
	big_int_reset(A);
	big_int_reset(B);

	ctor_char("0", A);
	ctor_char("0", B);

	assert(big_int_greater_than(A, B) == 0x00);
	big_int_reset(A);
	big_int_reset(B);

	ctor_char("33242989540626429799377", A);
	ctor_char("29352696412742635211157", B);

	assert(big_int_greater_than(A, B) == 0x01);
	big_int_reset(A);
	big_int_reset(B);

	printf("==> test_should_greater than[passed]\n");
}

void test_should_ctor_int()
{
	// Case #1
	BIG_INT *bg_int = base_ctor();
	ctor_int(61651, bg_int);
	uint8_t integer_as_text[] = {'6', '1', '6', '5', '1'};
	assert(strncmp(bg_int->digits, integer_as_text, 5) == 0);
	assert(bg_int->sign == '+');
	free(bg_int);
	// Case #2
	BIG_INT *bg_int_2 = base_ctor();
	ctor_int(10, bg_int_2);
	uint8_t second[] = {'1', '0'};
	assert(strncmp(bg_int_2->digits, second, 2) == 0);
	free(bg_int_2);
	// Case #3
	BIG_INT *bg_int10 = base_ctor();
	ctor_int(100, bg_int10);
	uint8_t integer10_as_text[] = {'1', '0', '0'};
	assert(strncmp(bg_int10->digits, integer10_as_text, 2) == 0);
	free(bg_int10);

	// Case #4
	BIG_INT *bg_int4 = base_ctor();
	ctor_int(5, bg_int4);
	uint8_t integer4_as_text[] = {'5'};
	assert(strncmp(bg_int4->digits, integer4_as_text, 1) == 0);
	free(bg_int4);
	printf("==> test_should_ctor_int[passed]\n");
}

void test_should_ctor_char()
{
	// case #1.
	BIG_INT *bg_int = base_ctor();
	ctor_char("-61651", bg_int);
	uint8_t integer_as_text[] = {'6', '1', '6', '5', '1'};
	assert(strncmp(bg_int->digits, integer_as_text, 5) == 0);
	assert(bg_int->sign == '-');
	free(bg_int);
	// Case#2.
	BIG_INT *bg_int10 = base_ctor();
	ctor_char("100", bg_int10);
	uint8_t integer10_as_text[] = {'1', '0', '0'};
	assert(strncmp(bg_int10->digits, integer10_as_text, 3) == 0);

	free(bg_int10);
	printf("==> test_should_ctor_char[passed]\n");
}

void test_should_ctor_hex()
{
	BIG_INT *bg_hex = base_ctor();
	uint8_t hex[] = "0x12AF";
	ctor_hex(hex, bg_hex);
	assert(bg_hex != NULL);
	printf("%s\n", bg_hex->digits);
	assert(strncmp("4783", bg_hex->digits, 4) == 0);
	big_int_reset(bg_hex);

	uint8_t hex1[] = "0x1CFF4B";
	ctor_hex(hex1, bg_hex);
	assert(bg_hex != NULL);
	assert(strncmp("1900363", bg_hex->digits, 7) == 0);

	big_int_reset(bg_hex);

	uint8_t long_hex[] = "0x3077020101042032fcda8a20f7de2978ba5a7ad9887e7b81618f77514faf1eacfe7ddbe1187a7ca00a06082a8648ce3d030107a14403420004a0cffedb4cdd8553056bc7aa8a0314fe5483a319e916806312fc71f7ec6ac2b148ba5d422da43a566712d855b3b4ae01b699a71b5d70339c3948216aa52c27d7";
	ctor_hex(long_hex, bg_hex);
	assert(bg_hex != NULL);

	assert(strncmp("472305418843739925399625973718970121118085593821873518651594271086235015341628156078009264613178331080967081039326592229882390127680120708148032206144736185603283558283366416159253816347376070235256462268014720308344862496323012927047808841423456009880897273896486895472483359061615519213527", bg_hex->digits, 22) == 0);
	big_int_reset(bg_hex);

	uint8_t long_not_x_started[] = "307fe3e";
	ctor_hex(long_not_x_started, bg_hex);
	// assert(bg_hex == NULL);
	big_int_reset(bg_hex);

	uint8_t incorrect[] = "0x1CFT4B";
	ctor_hex(incorrect, bg_hex);
	printf("[%d]\n", bg_hex == NULL);
	// assert(bg_hex == NULL);
	printf("==> test_should_ctor_hex[passed]\n");

	free(bg_hex);
}
void test_should_sum()
{
	BIG_INT *A = base_ctor();
	BIG_INT *B = base_ctor();
	BIG_INT *R = base_ctor();
	BIG_INT *T = base_ctor();

	ctor_char("20003", A);
	ctor_char("2456", B);
	ctor_char("22459", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("96643", A);
	ctor_char("75754", B);
	ctor_char("172397", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("99900", A);
	ctor_char("6006", B);
	ctor_char("105906", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("9984", A);
	ctor_char("2556", B);
	ctor_char("12540", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("8974", A);
	ctor_char("2554336", B);
	ctor_char("2563310", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("9984", A);
	ctor_char("5112556", B);
	ctor_char("5122540", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", A);
	ctor_char("0", B);
	ctor_char("0", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3481923779495873470699961441127886115309787790054947458822752617", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("-3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("-3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("-3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("-3481923779495873470699961441127886115309787790054947458822752617", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("2556", A);
	ctor_char("9984", B);
	ctor_char("12540", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-9984", A);
	ctor_char("2556", B);
	ctor_char("-7428", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-998422", A);
	ctor_char("2556", B);
	ctor_char("-995866", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-9984", A);
	ctor_char("255622", B);
	ctor_char("-245638", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-998422", A);
	ctor_char("-2556", B);
	ctor_char("-1000978", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-9984", A);
	ctor_char("-255622", B);
	ctor_char("-265606", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("9984", A);
	ctor_char("0", B);
	ctor_char("9984", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", A);
	ctor_char("2556", B);
	ctor_char("2556", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", A);
	ctor_char("1000150", B);
	ctor_char("1000150", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("191502086816040508058769501485429142358480752283393809010901812903019017421636531501658722091387723965207369835613458680419152", A);
	ctor_char("32429895406264297993771527300008845774187146823839192918821268800000000000000000000000000000000000000000000000000000000000000", B);
	ctor_char("223931982222304806052541028785437988132667899107233001929723081703019017421636531501658722091387723965207369835613458680419152", T);
	big_int_sum(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

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

void test_should_substract()
{
	BIG_INT *A = base_ctor();
	BIG_INT *B = base_ctor();
	BIG_INT *R = base_ctor();
	BIG_INT *T = base_ctor();

	ctor_char("20003", A);
	ctor_char("2456", B);
	ctor_char("17547", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("1", A);
	ctor_char("1", B);
	ctor_char("0", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", A);
	ctor_char("1", B);
	ctor_char("-1", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("2", A);
	ctor_char("1", B);
	ctor_char("1", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("96643", A);
	ctor_char("75754", B);
	ctor_char("20889", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("99900", A);
	ctor_char("6006", B);
	ctor_char("93894", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("9984", A);
	ctor_char("2556222", B);
	ctor_char("-2546238", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", A);
	ctor_char("0", B);
	ctor_char("0", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-998444", A);
	ctor_char("2556", B);
	ctor_char("-1001000", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-9984", A);
	ctor_char("255622", B);
	ctor_char("-265606", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-9984", A);
	ctor_char("-255622", B);
	ctor_char("-245638", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", A);
	ctor_char("157624825433230490762246168127797657567916321816555529634539929", B);
	ctor_char("3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3481923779495873470699961441127886115309787790054947458822752617", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("-3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3481923779495873470699961441127886115309787790054947458822752617", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-157624825433230490762246168127797657567916321816555529634539929", A);
	ctor_char("-3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("-3166674128629412489175469104872290800173955146421836399553672759", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("-9984", A);
	ctor_char("2556", B);
	ctor_char("-12540", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("993399393090909099393090", A);
	ctor_char("964046696678166464181933", B);
	ctor_char("29352696412742635211157", T);
	big_int_substract(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	free(A);
	free(B);
	free(T);
	free(R);

	printf("==> test_should_substract[passed]\n");
}
void test_should_multiply()
{
	BIG_INT *A = base_ctor();
	BIG_INT *B = base_ctor();
	BIG_INT *R = base_ctor();
	BIG_INT *T = base_ctor();

	ctor_char("0", R);
	ctor_char("2456", A);
	ctor_char("20003", B);
	ctor_char("49127368", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("2456", A);
	ctor_char("0", B);
	ctor_char("0", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("1111111111111111111111", A);
	ctor_char("1111111111111111111111", B);
	ctor_char("1234567901234567901234320987654320987654321", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("99339939309090909939309036434567534789534566322555599965352468877", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("330235656341857344427306467991636173969355735344993753690588034171903458530046727041675524180340518694179474155432188767776511376", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", A);
	ctor_char("157624825433230490762246168127797657567916321816555529634539929", B);
	ctor_char("523992042321994806059141329145437988132698862137233062019813141703019017421636531501658722091387723965207369835613458680419152", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", A);
	ctor_char("1", B);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("1", A);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", B);
	ctor_char("3324298954062642979937715273000088457741871468238391929188212688", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("1", A);
	ctor_char("33242989540626429799377", B);
	ctor_char("33242989540626429799377", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("33242989540626429799377", A);
	ctor_char("1", B);
	ctor_char("33242989540626429799377", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("33242989540626429799377", A);
	ctor_char("10", B);
	ctor_char("332429895406264297993770", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("33242989540626429799377", A);
	ctor_char("100", B);
	ctor_char("3324298954062642979937700", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("0", R);
	ctor_char("33242989540626429799377", A);
	ctor_char("0", B);
	ctor_char("0", T);
	big_int_multiply(A, B, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(R);

	free(A);
	free(B);
	free(T);
	free(R);
	printf("==> test_should_multiply[passed]\n");
}

void test_should_pow()
{
	BIG_INT *A = base_ctor();
	BIG_INT *X = base_ctor();
	BIG_INT *R = base_ctor();
	BIG_INT *T = base_ctor();
	// case #1:  x is zero, then r is 1.
	ctor_char("10", A);
	ctor_char("0", X);
	ctor_char("1", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(X);
	big_int_reset(T);
	big_int_reset(R);

	// case #2:  x is 1, then r is a.
	ctor_char("123", A);
	ctor_char("1", X);
	ctor_char("123", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(X);
	big_int_reset(T);
	big_int_reset(R);

	// case #3:  a is zero, then r is zero.
	ctor_char("0", A);
	ctor_char("2", X);
	ctor_char("0", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(X);
	big_int_reset(T);
	// big_int_reset(R);

	// //case #
	ctor_char("10", A);
	ctor_char("2", X);
	ctor_char("100", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(X);
	big_int_reset(T);
	big_int_reset(R);

	// case #
	ctor_char("2", A);
	ctor_char("5", X);
	ctor_char("32", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(X);
	big_int_reset(T);
	big_int_reset(R);

	ctor_char("33242989540626429799377", A);
	ctor_char("3", X);
	ctor_char("36736706524049309749503140261766410950369518374281734279955290795633", T);
	big_int_power(A, X, R);
	assert(strcmp(R->digits, T->digits) == 0);
	big_int_reset(A);
	big_int_reset(X);
	big_int_reset(T);
	big_int_reset(R);

	free(A);
	free(X);
	free(T);
	free(R);
	printf("==> test_should_pow[passed]\n");
}

void test_should_divide()
{
	
	BIG_INT *A = base_ctor();
	BIG_INT *B = base_ctor();
	BIG_INT *T = base_ctor();

	///Test #1:
	ctor_char("99339939309090909939309036434567534789534566322555599965352468877", A);
	ctor_char("33242989540626429799377", B);
	ctor_char("2988297402906169292640812071435105739322839", T);
	
	division_result_t *division_result = (division_result_t *)malloc(sizeof(division_result_t));
	division_result->quotient = base_ctor();
	ctor_char("0", division_result->quotient);

	division_result->remaining = base_ctor();
	ctor_char("0", division_result->remaining);

	big_int_divide(A, B, division_result);

	PRINT_BIG_INT(division_result->quotient);
	assert(strncmp(division_result->quotient->digits, T->digits, T->length)==0);

	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(division_result->quotient);
	big_int_reset(division_result->remaining);


	///Test #2:
	ctor_char("2989540626429799377152730000884577418714682383919291882126", A);
	ctor_char("5774187146823839192918821268", B);
	ctor_char("517742246728915256822471410944", T);
	
	
	ctor_char("0", division_result->quotient);

	division_result->remaining = base_ctor();
	ctor_char("0", division_result->remaining);

	big_int_divide(A, B, division_result);

	PRINT_BIG_INT(division_result->quotient);
	assert(strncmp(division_result->quotient->digits, T->digits, T->length)==0);

	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(T);
	big_int_reset(division_result->quotient);
	big_int_reset(division_result->remaining);
	printf("==> test_should_divide[passed]\n"); // 993399393090909099393090
}



void test_should_divide_by_2()
{
	BIG_INT *A = base_ctor();

	division_result_t *division_result = (division_result_t *)malloc(sizeof(division_result_t));
	division_result->quotient = base_ctor();
	// ctor_char("0", division_result->quotient);

	division_result->remaining = base_ctor();
	ctor_char("0", division_result->remaining);

	ctor_char("107", A);

	big_int_divide_by_2(A, division_result);

	PRINT_BIG_INT(division_result->quotient);
	PRINT_BIG_INT(division_result->remaining);
	assert(division_result->quotient->length == 2);
	uint8_t cc[] = {'5', '3'};
	assert(strncmp(division_result->quotient->digits, cc, 2) == 0);

	big_int_free(A);
	big_int_free(division_result->quotient);
	big_int_free(division_result->remaining);

	printf("==>  test_should_divide_by_2[passed]\n");
}

void test_should_factor_between_m_and_n()
{
	BIG_INT *A = base_ctor();
	BIG_INT *B = base_ctor();
	BIG_INT *R = base_ctor();
	BIG_INT *ZERO = base_ctor();
	BIG_INT *high = base_ctor();
	BIG_INT *factor = base_ctor();

	ctor_char("121", A);
	ctor_char("14", B);
	ctor_char("0", ZERO);

	BIG_INT_COPY_FROM_TO(A, high);
	big_int_factor_between_m_and_n(A, B, high, ZERO, factor);

	PRINT_BIG_INT(factor);
	uint8_t cc1[] = {'8'};
	assert(strncmp(factor->digits, cc1, 1) == 0);

	big_int_reset(factor);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(high);
	big_int_reset(ZERO);

	// Test 2
	ctor_char("34", A);
	ctor_char("5", B);
	ctor_char("0", ZERO);

	BIG_INT_COPY_FROM_TO(A, high);
	big_int_factor_between_m_and_n(A, B, high, ZERO, factor);
	PRINT_BIG_INT(factor);
	uint8_t cc2[] = {'6'};
	assert(strncmp(factor->digits, cc2, 1) == 0);

	big_int_reset(factor);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(high);
	big_int_reset(ZERO);

	// Test #3
	ctor_char("99339939309090909939309036434567534789534566322555599965352468877", A);
	ctor_char("33242989540626429799377", B);
	ctor_char("2988297402906169292640812071435105739322839", R);
	ctor_char("0", ZERO);

	BIG_INT_COPY_FROM_TO(A, high);
	big_int_factor_between_m_and_n(A, B, high, ZERO, factor);
	PRINT_BIG_INT(factor);
	uint8_t cc3[] = {'6'};
	assert(strncmp(factor->digits, R->digits, R->length) == 0);

	big_int_reset(factor);
	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(high);
	big_int_reset(ZERO);

	free(A);
	free(B);
	free(high);
	free(ZERO);
	free(factor);
	printf("==>  test_should_factor_between_m_and_n[passed]\n");
};

void test_should_mod()
{
	BIG_INT *A = base_ctor();
	BIG_INT *B = base_ctor();
	BIG_INT *R = base_ctor();

	ctor_char("2935269641274263521115736434567534789534566322555599965352468877", A);
	ctor_char("33242989540626429799377", B);

	big_int_mod(A, B, R);

	PRINT_BIG_INT(R);

	big_int_reset(A);
	big_int_reset(B);
	big_int_reset(R);

	ctor_char("110", A);
	ctor_char("33", B);

	big_int_mod(A, B, R);

	PRINT_BIG_INT(R);

	free(R);
	free(A);
	free(B);
}

int main()
{
// "332429895406264297993770000000000000000000000000000000000000000"
// "2935269641274263521115736434567534789534566322555599965352468877"

// greater_than();
// test_should_ctor_int();
// test_should_ctor_char();
// test_should_ctor_hex();
// test_should_sum();
// test_should_substract();
#ifdef MAX_COMMON_DIVISION_ONLY
	test_should_max_divisor();
#endif
#ifdef MULTIPLY_ONLY
	test_should_multiply();
#endif
#ifdef DIVISION_ONLY
	test_should_divide();
#endif
#ifdef DIVISION_BY_2
	test_should_divide_by_2();
#endif

#ifdef FACTOR
	test_should_factor_between_m_and_n();
#endif

#ifdef MOD
	test_should_mod();
#endif
	//  test_should_pow();
	// test_should_max_divisor();
	return 0;
}