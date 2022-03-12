
#include "sha256.h"

enum
{
	BUFFERSIZE = 1024
};

int main(int argc, char *argv[])
{
	uint8_t message[BUFFERSIZE], output[BUFFERSIZE];
	memset(message, 0, BUFFERSIZE);
	uint64_t bytesRead = read(0, message, BUFFERSIZE);
	if (bytesRead == 0)
		return 1;
	uint8_t digest[SHA256_MESSAGE_BLOCK_SIZE / 2];
	hash_256(message, digest, bytesRead);
	hex_to_char_buffer(digest, output);
	write(1, output, SHA256_MESSAGE_BLOCK_SIZE);
	write(STDOUT_FILENO, "\n", 1);
	return 0;
}