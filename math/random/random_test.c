#include "random.h"



int main(){
    uint8_t entropy[512]; 
    memset(entropy, '\0', 512);
    get_OS_entropy(entropy, 512);
    printf("%s\n", entropy);
    return 0;
}