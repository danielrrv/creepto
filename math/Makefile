CC = gcc

libraries=-I ../utils -I ./random
substract:  bint/big_int_test.c
	$(CC) $^ $(libraries) -o bint/big_int_test.o -DSUBSTRACT  && ./bint/big_int_test.o	
ctor_binary: bint/big_int_test.c
	$(CC) $^   $(libraries) -o bint/big_int_test.o -DCTOR_BINARY -DDEBUG_CTOR_BINARY  && ./bint/big_int_test.o
division: bint/big_int_test.c
	$(CC) $^ $(libraries) -o bint/big_int_test.o -D DIVISION_ONLY && ./bint/big_int_test.o
division_debug: bint/big_int_test.c
	$(CC) $^ $(libraries) -o bint/big_int_test.o -D DIVISION_ONLY -D DEBUGDIVIDE && ./bint/big_int_test.o

max_divisor: bint/big_int_test.c
	$(CC) $^ $(libraries) -o bint/big_int_test.o -DMAX_COMMON_DIVISION_ONLY -DDEBUG_MAX_DIVISOR -DEBUGDIVIDE && ./bint/big_int_test.o
division_by_2: bint/big_int_test.c
	$(CC) $^ $(libraries) -o bint/big_int_test.o -DDIVISION_BY_2 -DDEBUG_DIVIDE_BY_2 && ./bint/big_int_test.o

factor: bint/big_int_test.c
	$(CC) $^  $(libraries) -o bint/big_int_test.o -DFACTOR && ./bint/big_int_test.o
mod: bint/big_int_test.c
	$(CC) $^ $(libraries) -o bint/big_int_test.o -DMOD && ./bint/big_int_test.o
gcd: bint/big_int_test.c
	$(CC) $^ $(libraries) -o bint/big_int_test.o -DGCD && ./bint/big_int_test.o
random_big_int:bint/big_int_test.c
	$(CC) $^ -DRAND $(libraries) -o bint/big_int_test.o && ./bint/big_int_test.o  
big_int_to_bits:bint/big_int_test.c
	$(CC) $^ -DBIG_INT_TO_BITS   $(libraries) -o bint/big_int_test.o && ./bint/big_int_test.o 
entropy: random/random_test.c
	$(CC) $^ $(libraries) -o random/random_test.o && ./random/random_test.o
clean:
	rm bint/big_int_test.o random/random_test.o
