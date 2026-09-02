CC = gcc

libraries=-I ./core/random -I ./core/hex
substract:  core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -DSUBSTRACT  && ./core/bint/big_int_test.o	
ctor_binary: core/bint/big_int_test.c
	$(CC) $^   $(libraries) -o ./core/bint/big_int_test.o -DCTOR_BINARY -DDEBUG_CTOR_BINARY  && ./core/bint/big_int_test.o
ctor_hex: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -D HEX_ONLY && ./core/bint/big_int_test.o 
division: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -D DIVISION_ONLY && ./core/bint/big_int_test.o
division_debug: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -D DIVISION_ONLY -D DEBUGDIVIDE && ./core/bint/big_int_test.o

max_divisor: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -DMAX_COMMON_DIVISION_ONLY -DDEBUG_MAX_DIVISOR -DEBUGDIVIDE && ./core/bint/big_int_test.o
division_by_2: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -DDIVISION_BY_2 -DDEBUG_DIVIDE_BY_2 && ./core/bint/big_int_test.o

factor: core/bint/big_int_test.c
	$(CC) $^  $(libraries) -o ./core/bint/big_int_test.o -DFACTOR && ./core/bint/big_int_test.o
mod: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -DMOD && ./core/bint/big_int_test.o
gcd: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -DGCD && ./core/bint/big_int_test.o
random_big_int: core/bint/big_int_test.c
	$(CC) $^ -DRAND $(libraries) -o ./core/bint/big_int_test.o && ./core/bint/big_int_test.o  
big_int_to_bits: core/bint/big_int_test.c
	$(CC) $^ -DBIG_INT_TO_BITS   $(libraries) -o ./core/bint/big_int_test.o && ./core/bint/big_int_test.o 
is_prime: core/bint/big_int_test.c
	$(CC) $^ -DIS_PRIME $(libraries) -o ./core/bint/big_int_test.o && ./core/bint/big_int_test.o
rabin_miller: core/bint/big_int_test.c
	$(CC) $^ -DRABIN_MILLER $(libraries) -o ./core/bint/big_int_test.o && ./core/bint/big_int_test.o
entropy: core/random/random_test.c
	$(CC) $^ $(libraries) -o r./core/random/random_test.o && ./r./core/random/random_test.o
hex: core/hex/hex_test.c
	$(CC) $^ $(libraries) -o hex/hex_test.o && ./hex/hex_test.o
lcm: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -DLCM && ./core/bint/big_int_test.o
modular_inverse_multiplicative: core/bint/big_int_test.c
	$(CC) $^ $(libraries) -o ./core/bint/big_int_test.o -D MODULAR_INVERSE_MULTIPLICATIVE && ./core/bint/big_int_test.o
clean:
	rm ./core/bint/big_int_test.o r./core/random/random_test.o
