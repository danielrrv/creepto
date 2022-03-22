
#include "hmac.h"
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
	uint64_t bytesRead = read(0, message, BUFFERSIZE);
	if (bytesRead == 0)
		return 1;
	uint8_t key[] = {'s', 'e', 'c', 'r', 'e', 't'};
	uint8_t mac_digest[32];
	sha256_hmac(key, sizeof(key), message, bytesRead, mac_digest);

	// write(1, mac_digest, 64);
	// write(1, "\n", 1);
	return 0;
}