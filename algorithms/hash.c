
#include "sha256.h"

enum {
	BUFFERSIZE=1024
};

int main(int argc, char *argv[])
{	
	uint8_t message[BUFFERSIZE];
	memset(message, 0, BUFFERSIZE);
	uint64_t bytesRead = read(0, message, BUFFERSIZE);
	if(bytesRead==0)return 1;
	uint32_t digest[SHA256_MESSAGE_BLOCK_SIZE / 8];
	hash_256(message, (uint32_t *)&digest, bytesRead);
	return 0;
}