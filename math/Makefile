CC = gcc

utils=-I ../utils
substract:  big_int_test.c
	$(CC) big_int_test.c $(utils) -o big_int_test.o -DSUBSTRACT  && ./big_int_test.o	
ctor_binary: big_int_test.c
	$(CC) big_int_test.c $(utils) -o big_int_test.o -DCTOR_BINARY -DDEBUG_CTOR_BINARY  && ./big_int_test.o
division: big_int_test.c
	$(CC) big_int_test.c -o big_int_test.o -D DIVISION_ONLY && ./big_int_test.o
division_debug: big_int_test.c
	$(CC) big_int_test.c -o big_int_test.o -D DIVISION_ONLY -D DEBUGDIVIDE && ./big_int_test.o

max_divisor: big_int_test.c
	$(CC) big_int_test.c -o big_int_test.o -DMAX_COMMON_DIVISION_ONLY -DDEBUG_MAX_DIVISOR -DEBUGDIVIDE && ./big_int_test.o
division_by_2: big_int_test.c
	$(CC) big_int_test.c -o big_int_test.o -DDIVISION_BY_2 -DDEBUG_DIVIDE_BY_2 && ./big_int_test.o

factor: big_int_test.c
	$(CC) big_int_test.c -o big_int_test.o -DFACTOR && ./big_int_test.o
mod: big_int_test.c
	$(CC) big_int_test.c -o big_int_test.o -DMOD && ./big_int_test.o
gcd: big_int_test.c
	$(CC) big_int_test.c -o big_int_test.o -DGCD && ./big_int_test.o
random:big_int_test.c
	$(CC) big_int_test.c -DRAND -I ../utils -o big_int_test.o && ./big_int_test.o  
clean:
	rm big_int_test.o
