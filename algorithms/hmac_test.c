
#include "hmac.h"
#include "assert.h"
#include "assert.h"


enum
{
	BUFFERSIZE = 1024
};

// echo -n "hello" | ./hmac_test.o 
int main(int argc, char *argv[])
{
	uint8_t message[BUFFERSIZE], output[BUFFERSIZE];
	memset(message, 0, BUFFERSIZE);
	uint8_t message_test[] = {'c','w','e','r','g','h','j','k','o','i','u','y','t','r','e'};
	uint8_t expected_digest[] = "e86dd1420f3b0c35d9838a4e178f52d44663262e302175c414c93ec6d900667a";
	
	uint8_t key[] = {'s', 'e', 'c', 'r', 'e', 't'};
	uint8_t mac_digest[32];
	sha256_hmac(key, sizeof(key), message_test, sizeof(message_test), mac_digest);

	hex_to_char_buffer(mac_digest, output);
	assert(strncmp(output, expected_digest, sizeof(expected_digest))==0);
	write(1, output, 64);
	write(1, "\n", 1);
	printf("Test passed\n");
	return 0;
}