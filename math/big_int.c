
#include "assert.h"
#include "big_int.h"


void test_should_ctor_int(){
	BIG_INT * bg_int = ctor_int(61651);
	uint8_t integer_as_text[] = {'6', '1', '6', '5', '1'};
	assert(strcmp(bg_int->digits,  integer_as_text)==0);
	assert(bg_int->sign=='+');
	BIG_INT * bg_int_2 = ctor_int(10);
	uint8_t second[] = {'1', '0'};
	assert(strncmp(bg_int_2->digits,  second, 2) == 0);

	BIG_INT * bg_int10 = ctor_int(100);
	uint8_t integer10_as_text[] = {'1', '0', '0'};
	assert(strncmp(bg_int10->digits,  integer10_as_text, 2)==0);
	printf("==> test_should_ctor_int[passed]\n");
}

void test_should_ctor_char(){
	BIG_INT * bg_int = ctor_char("-61651");
	BIG_INT * bg_int10 = ctor_char("100");
	uint8_t integer_as_text[] = {'6', '1', '6', '5', '1'};
	uint8_t integer10_as_text[] = {'1', '0', '0'};
	assert(strcmp(bg_int->digits,  integer_as_text)==0);
	assert(bg_int->sign=='-');
	assert(strcmp(bg_int10->digits,  integer10_as_text)==0);
	printf("==> test_should_ctor_char[passed]\n");
	
}
void test_should_sum(){
	assert(strcmp(big_int_sum( ctor_char("20003"),  ctor_char("2456"))->digits, ctor_char("22459")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("96643"),  ctor_char("75754"))->digits,ctor_char("172397")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("99900"),  ctor_char("6006"))->digits, ctor_char("105906")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("9984"),  ctor_char("2556"))->digits, ctor_char("12540")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("8974"),  ctor_char("2554336"))->digits, ctor_char("2563310")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("9984"),  ctor_char("5112556"))->digits, ctor_char("5122540")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("0"),  ctor_char("0"))->digits, ctor_char("0")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("157624825433230490762246168127797657567916321816555529634539929"),  ctor_char("3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("3481923779495873470699961441127886115309787790054947458822752617")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("157624825433230490762246168127797657567916321816555529634539929"),  ctor_char("-3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("-3166674128629412489175469104872290800173955146421836399553672759")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("-157624825433230490762246168127797657567916321816555529634539929"),  ctor_char("3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("3166674128629412489175469104872290800173955146421836399553672759")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("-157624825433230490762246168127797657567916321816555529634539929"),  ctor_char("-3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("-3481923779495873470699961441127886115309787790054947458822752617")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("2556"),  ctor_char("9984"))->digits, ctor_char("12540")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("-9984"),  ctor_char("2556"))->digits, ctor_char("-7428")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("-998422"),  ctor_char("2556"))->digits, ctor_char("-995866")->digits)==0);
	//TODO: returns /9999754362 and should be 245638
	assert(strcmp(big_int_sum( ctor_char("-9984"),  ctor_char("255622"))->digits, ctor_char("-245638")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("-998422"),  ctor_char("-2556"))->digits, ctor_char("-1000978")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("-9984"),  ctor_char("-255622"))->digits, ctor_char("-265606")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("9984"),  ctor_char("0"))->digits, ctor_char("9984")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("0"),  ctor_char("2556"))->digits, ctor_char("2556")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("0"),  ctor_char("1000150"))->digits, ctor_char("1000150")->digits)==0);
	assert(strcmp(big_int_sum( ctor_char("191502086816040508058769501485429142358480752283393809010901812903019017421636531501658722091387723965207369835613458680419152"),  ctor_char("32429895406264297993771527300008845774187146823839192918821268800000000000000000000000000000000000000000000000000000000000000"))->digits, ctor_char("223931982222304806052541028785437988132667899107233001929723081703019017421636531501658722091387723965207369835613458680419152")->digits)==0);

	

	printf("==> test_should_sum[passed]\n");
}
void test_should_get_sign(){
	assert(ctor_int(-100001)->sign =='-');
	assert(ctor_char("-100001")->sign =='-');
}

void test_should_substract(){
	assert(strcmp(big_int_substract( ctor_char("20003"),  ctor_char("2456"))->digits, ctor_char("17547")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("96643"),  ctor_char("75754"))->digits,ctor_char("20889")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("99900"),  ctor_char("6006"))->digits, ctor_char("93894")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("9984"),  ctor_char("2556222"))->digits, ctor_char("-2546238")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("0"),  ctor_char("0"))->digits, ctor_char("0")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("-9984"),  ctor_char("2556"))->digits, ctor_char("-12540")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("-998444"),  ctor_char("2556"))->digits, ctor_char("-1001000")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("-9984"),  ctor_char("255622"))->digits, ctor_char("-265606")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("-9984"),  ctor_char("-255622"))->digits, ctor_char("-245638")->digits)==0);
	assert(strcmp(big_int_substract(ctor_char("3324298954062642979937715273000088457741871468238391929188212688"), ctor_char("157624825433230490762246168127797657567916321816555529634539929"))->digits, ctor_char("3166674128629412489175469104872290800173955146421836399553672759")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("157624825433230490762246168127797657567916321816555529634539929"),  ctor_char("3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("3166674128629412489175469104872290800173955146421836399553672759")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("-157624825433230490762246168127797657567916321816555529634539929"),  ctor_char("3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("3481923779495873470699961441127886115309787790054947458822752617")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("157624825433230490762246168127797657567916321816555529634539929"),  ctor_char("-3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("-3481923779495873470699961441127886115309787790054947458822752617")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("-157624825433230490762246168127797657567916321816555529634539929"),  ctor_char("-3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("-3166674128629412489175469104872290800173955146421836399553672759")->digits)==0);
	assert(strcmp(big_int_substract( ctor_char("-9984"),  ctor_char("2556"))->digits, ctor_char("-12540")->digits) == 0);
	assert(strcmp(big_int_substract( ctor_char("993399393090909099393090"),  ctor_char("964046696678166464181933"))->digits, ctor_char("29352696412742635211157")->digits) == 0);
	printf("==> test_should_substract[passed]\n");
}
void test_should_multiply(){
	assert(strcmp(big_int_multiply( ctor_char("2456"),ctor_char("20003"))->digits, ctor_char("49127368")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("2456"),ctor_char("0"))->digits, ctor_char("0")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("0"),ctor_char("2456"))->digits, ctor_char("0")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("1111111111111111111111"),ctor_char("1111111111111111111111"))->digits, ctor_char("1234567901234567901234320987654320987654321")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("99339939309090909939309036434567534789534566322555599965352468877"), ctor_char("993355599965352468877"))->digits, ctor_char("98679885012903702658339633053923094380397163235416227395597628126096173812919253641129")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("157624825433230490762246168127797657567916321816555529634539929"), ctor_char("3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("523992042321994806059141329145437988132698862137233062019813141703019017421636531501658722091387723965207369835613458680419152")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("3324298954062642979937715273000088457741871468238391929188212688"), ctor_char("157624825433230490762246168127797657567916321816555529634539929"))->digits, ctor_char("523992042321994806059141329145437988132698862137233062019813141703019017421636531501658722091387723965207369835613458680419152")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("3324298954062642979937715273000088457741871468238391929188212688"), ctor_char("1"))->digits, ctor_char("3324298954062642979937715273000088457741871468238391929188212688")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("1"), ctor_char("3324298954062642979937715273000088457741871468238391929188212688"))->digits, ctor_char("3324298954062642979937715273000088457741871468238391929188212688")->digits)==0);
	
	assert(strcmp(big_int_multiply( ctor_char("1"), ctor_char("33242989540626429799377"))->digits, ctor_char("33242989540626429799377")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("33242989540626429799377"), ctor_char("1"))->digits, ctor_char("33242989540626429799377")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("33242989540626429799377"), ctor_char("10"))->digits, ctor_char("332429895406264297993770")->digits)==0);
	assert(strcmp(big_int_multiply( ctor_char("33242989540626429799377"), ctor_char("100"))->digits, ctor_char("3324298954062642979937700")->digits)==0);
	printf("==> test_should_multiply[passed]\n");
}

void test_should_divide(){
	// assert(strcmp(big_int_divide( ctor_char("993"), ctor_char("33"))->quotient->digits, ctor_char("1")->digits)==0);
	// assert(strcmp(big_int_divide( ctor_char("3324298954062642979937715273000088457741871468238391929188212688"), ctor_char("0"))->quotient->digits, ctor_char("523992042321994806059141329145437988132698862137233062019813141703019017421636531501658722091387723965207369835613458680419152")->digits)==0);
		assert(strcmp(big_int_divide( ctor_char("99339939309090909939309036434567534789534566322555599965352468877"), ctor_char("33242989540626429799377"))->quotient->digits, ctor_char("1")->digits)==0);
printf("==> test_should_divide[passed]\n");//993399393090909099393090
}

int main(){

	// test_should_ctor_int();
	// test_should_ctor_char();
	// test_should_sum();
	// test_should_substract();
	// test_should_multiply();
	test_should_divide();
	return 0;
}