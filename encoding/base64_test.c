
#include "base64.h"
#include "assert.h"

enum
{
	BUFFERSIZE = 1024
};

int main()
{

	uint8_t message[BUFFERSIZE], output[BUFFERSIZE];
	memset(message, 0, BUFFERSIZE);
	uint64_t bytesRead = read(0, message, BUFFERSIZE);
	uint8_t * encoded = encode_base64(message, bytesRead);
	printf("%s\n", encoded);

	return 0;
}