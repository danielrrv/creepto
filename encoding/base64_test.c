
#include "base64.h"
#include "assert.h"

enum
{
	BUFFERSIZE = 1024
};
// echo -n "danielrodrig" | ./base64_test.o 
int main()
{

	uint8_t message[BUFFERSIZE], output[BUFFERSIZE];
	memset(message, 0, BUFFERSIZE);
	uint64_t bytesRead = read(0, message, BUFFERSIZE);
	uint8_t * encoded = encode_base64(message, bytesRead);
	#ifdef DEBUG
		printf("%s\n", encoded);
	#endif
	char text[] = {'Z','G','F','u','a','W','V','s','c','m','9','k','c','m','l','n'};
 	assert(strcmp(text, encoded)!=0);

	uint8_t * decode = decode_base64(text, sizeof(text) - 1);
	assert(strcmp(message, decode)!=0);
	free(encoded);
	free(decode);
	return 0;
}