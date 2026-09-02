#ifndef CREEPTO_RSA_KEY_H
#define CREEPTO_RSA_KEY_H

#include "big_int.h"


//https://github.com/openssl/openssl/blob/master/crypto/rsa/rsa_sp800_56b_gen.c#L381
//

/**
 * RSA key material.
 * Ownership: every BIG_INT* field is independently base_ctor-allocated and MUST
 * be released by the caller with big_int_free (use free_public_key /
 * free_private_key). pub and priv NEVER share buffers.
 */
typedef struct { BIG_INT *n; BIG_INT *e; } RSA_PUBLIC_KEY;
typedef struct { BIG_INT *n; BIG_INT *d; } RSA_PRIVATE_KEY;

// Compute phi = lcm(p-1, q-1) into phi->quotient and surface n = p*q via n_out.
// n_out must be a caller-allocated BIG_INT (base_ctor). p and q are freed here;
// n is NOT freed, it is copied into n_out.

void generate_phi(int size_bits, division_result_t *phi, BIG_INT *n_out){
      /**
     * 
     * Choose two distinct large prime numbers p and q.
     * To make factoring infeasible, p and q must be chosen at random from a large space of possibilities, such as all prime numbers between 21023 and 21024 (corresponding to a 2,048-bit key). 
     * p and q are kept secret.
    */

    BIG_INT *p = base_ctor();
    BIG_INT *q = base_ctor();

    big_int_random_prime(size_bits, p);
    big_int_random_prime(size_bits, q);

    // Ensure p and q are distinct: regenerate q until it differs from p.
    while (BIG_INT_ARE_SAME(p, q))
    {
        big_int_reset(q);
        big_int_random_prime(size_bits, q);
    }

    /**
     * Compute n = pq.
     * n is used as the modulus for both the public and private keys. Its length, usually expressed in bits, is the key length.
     * n is released as part of the public key.
    */
    BIG_INT *n = base_ctor();
    big_int_multiply(p, q, n);
    // Surface n to the caller (n is NOT freed here anymore).
    BIG_INT_COPY_FROM_TO(n, n_out);

    /**
     * Compute λ(n), where λ is Carmichael's totient function. 
     * Since n = pq, λ(n) = lcm(λ(p), λ(q)), and since p and q are prime, λ(p) = φ(p) = p − 1, and likewise λ(q) = q − 1. 
     * Hence λ(n) = lcm(p − 1, q − 1).
    */
    
    BIG_INT *q_minus_one = base_ctor();
    BIG_INT *p_minus_one = base_ctor();
    BIG_INT * gcd_of_p_q = base_ctor();

    big_int_substract(q, (&ONE), q_minus_one);
    big_int_substract(p, (&ONE), p_minus_one);
    
    DIVISION_RESULT_RESET(phi);
    big_int_lcm(p_minus_one, q_minus_one, phi);

    big_int_free(gcd_of_p_q);
    big_int_free(q_minus_one);
    big_int_free(p_minus_one);
    big_int_free(p);
    big_int_free(q);
    big_int_free(n);
}

void generate_pair_keys(int size_bits, RSA_PUBLIC_KEY *pub, RSA_PRIVATE_KEY *priv)
{

    /**
     * 
     * Choose an integer e such that 1 < e < λ(n) and gcd(e, λ(n)) = 1; that is, e and λ(n) are coprime.
     * e having a short bit-length and small Hamming weight results in more efficient encryption – the most commonly chosen value for e is 216 + 1 = 65537. 
     * The smallest (and fastest) possible value for e is 3, but such a small value for e may expose vulnerabilities in insecure padding schemes
     * e is released as part of the public key.
     * 
     * Let's take 65537
    */
    BIG_INT * e = base_ctor();
    ctor_int(65537, e); 


    /**
     * 
     * 
     * Determine d as d ≡ e−1 (mod λ(n)); that is, d is the modular multiplicative inverse of e modulo λ(n).
     * This means: solve for d the equation de ≡ 1 (mod λ(n)); d can be computed efficiently by using the extended Euclidean algorithm, since, thanks to e and λ(n) being coprime, said equation is a form of Bézout's identity, where d is one of the coefficients.
     * d is kept secret as the private key exponent.
    */  

    BIG_INT * d = base_ctor();
    // n = p*q surfaced from generate_phi.
    BIG_INT * n = base_ctor();
    // gcd(e, phi) coprimality check output.
    BIG_INT * gcd_out = base_ctor();

    division_result_t * phi;
    DIVISION_RESULT_FACTORY(phi);

    generate_phi(size_bits, phi, n);

    /**
     * Require e and λ(n) to be coprime: gcd(e, λ(n)) == 1.
     * Combined with the mod_inverse guard (returns non-zero when e is not
     * invertible mod λ(n)). Regenerate p, q (hence n and λ(n)) until both hold.
     */
    big_int_gcd(e, phi->quotient, gcd_out);
    while (!BIG_INT_ARE_SAME(gcd_out, (&ONE)) || big_int_mod_inverse(e, phi->quotient, d) != 0)
    {
        big_int_reset(n);
        generate_phi(size_bits, phi, n);
        big_int_reset(gcd_out);
        big_int_gcd(e, phi->quotient, gcd_out);
    }

    // At this point d holds e^-1 mod λ(n) (set by the loop's mod_inverse call).

    /**
     * Assemble outputs. pub and priv each receive an INDEPENDENT copy of n so
     * the two keys own separate buffers (no shared-pointer aliasing / double-free).
     * pub->e receives e (ownership transferred). priv->d receives d (ownership
     * transferred). Each field must be freed by the caller with big_int_free.
     */
    pub->n = base_ctor();
    BIG_INT_COPY_FROM_TO(n, pub->n);
    pub->e = e; // ownership handed to caller.

    priv->n = base_ctor();
    BIG_INT_COPY_FROM_TO(n, priv->n);
    priv->d = d; // ownership handed to caller.

    // Free only the intermediates we still own (not handed to the caller).
    DIVISION_RESULT_DEINIT(phi); // do NOT big_int_free(phi) afterwards (removed double-free).
    big_int_free(gcd_out);
    big_int_free(n);
}


// Free helpers: release every base_ctor-allocated field of a key.
void free_public_key(RSA_PUBLIC_KEY *k) { big_int_free(k->n); big_int_free(k->e); }
void free_private_key(RSA_PRIVATE_KEY *k) { big_int_free(k->n); big_int_free(k->d); }


#endif