#include "rsa.h"

//gcc rsa_test.c -I ../bint/ -I ../hex/ -I ../random/  -o rsa_test.o && ./rsa_test.o
int main(){
    RSA_PUBLIC_KEY pub;
    RSA_PRIVATE_KEY priv;

    // Small key size for a fast smoke test.
    generate_pair_keys(1024, &pub, &priv);

    // Show that a usable key pair was produced.
    PRINT_BIG_INT(pub.n);
    PRINT_BIG_INT(pub.e);
    PRINT_BIG_INT(priv.n);
    PRINT_BIG_INT(priv.d);

    free_public_key(&pub);
    free_private_key(&priv);
    return 0;
}