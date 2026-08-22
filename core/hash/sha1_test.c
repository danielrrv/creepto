
#include "sha1.h"

enum
{
	BUFFERSIZE = 1024
};

int main(int argc, char *argv[])
{
	uint8_t message[BUFFERSIZE], output[BUFFERSIZE];
	memset(message, 0, BUFFERSIZE);
	memset(output, 0, BUFFERSIZE);
	uint64_t bytesRead = read(0, message, BUFFERSIZE);
	if (bytesRead == 0)
		return 1;
	uint8_t sha1_digest[SHA1_HASH_SIZE];
	hash_sha1(message, sha1_digest, bytesRead);
	hex_to_char_buffer(sha1_digest, output);
	write(1, output, SHA1_HASH_SIZE * 2);
	write(1, "\n", 1);
	return 0;
}