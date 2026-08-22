
#include "sha256.h"
#include "assert.h"

enum
{
	BUFFERSIZE = 1024
};

int main(int argc, char *argv[])
{
	
	uint8_t output[BUFFERSIZE], digest[SHA256_MESSAGE_BLOCK_SIZE / 2];
	
	uint8_t message_test[] = {'c','w','e','r','g','h','j','k','o','i','u','y','t','r','e'};
	uint8_t hash_test_256[] = "5966b357d0ba732302651a75578f058c083269f47a8039fd5b45ee13536816d7";
	
	SHA256_t_ctx context;
	SHA256(&context);
	sha256_update(&context, message_test, sizeof(message_test));
	sha256_digest(&context, digest);
	hex_to_char_buffer(digest, output);
	
	write(1, output, SHA256_MESSAGE_BLOCK_SIZE);
	write(1, "\n", 1);
	assert(strncmp(output, hash_test_256,sizeof(hash_test_256))==0);
	printf("Test passed\n");
	return 0;
}