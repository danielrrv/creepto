#include "utils.h"
#include "assert.h"
int main(){
    uint8_t bytes[] = {120, 44, 76, 34, 53, 76, 101, 12, 100, 54, 56, 43, 45, 87, 89, 100, 66, 70, 127, 128};
    // printf("sizeof(bytes)=%d\n", sizeof(bytes));
    uint8_t * hex = malloc(sizeof(uint8_t) * sizeof(bytes) * 2);
    memset(hex, '\0', sizeof(bytes) * 2);
    bytes_to_hex(bytes, hex, sizeof(bytes) );
    uint8_t  expected[] = "782C4C22354C650C6436382B2D57596442467F80";
    assert(strncmp(expected, hex, sizeof(bytes) * 2)==0);

    printf("==> bytes_to_hex[passed]\n");

    return 0;
}