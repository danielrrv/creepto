#include "random.h"
#include <stdio.h>

int main() {
    uint8_t entropy[32]; 
    memset(entropy, 0, sizeof(entropy));
    get_OS_entropy(entropy, sizeof(entropy));
    
    printf("Entropy: ");
    for (int i = 0; i < sizeof(entropy); i++) {
        printf("%02x", entropy[i]);
    }
    printf("\n");
    return 0;
}
