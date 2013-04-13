#include <stdio.h>

#include "keygen.h"
#include "prime.h"
#include "modinvert.h"

// RSA key gen algorithm:
// ++++++++++++++++++++++
// p, q - Two distinct primes
// n = p * q
// phi = (p-1) * (q-1)
// e < n such that gcd(e, phi) = 1
// d = e^-1 mod phi

int
keygen(mpz_t p, mpz_t q, mpz_t n, mpz_t e, mpz_t d,
       int mod_bits, gmp_randstate_t randstate)
{
    mpz_t p_, q_, phi, r;
    mpz_inits(p_, q_, phi, r, NULL);

    mpz_set_ui(e, 3L);

    do {
        gen_prime(p, mod_bits-(mod_bits/2), PRIME_DEFAULT_RELIABILITY, randstate);
    } while (mpz_fdiv_r(r, p, e), mpz_cmp_ui(r, 1) == 0);

    do {
        gen_prime(q, mod_bits/2, PRIME_DEFAULT_RELIABILITY, randstate);
    } while (mpz_cmp(q, p) == 0 || (mpz_fdiv_r(r, q, e), mpz_cmp_ui(r, 1) == 0));

    mpz_sub_ui(p_, p, 1L);
    mpz_sub_ui(q_, q, 1L);
    mpz_mul(phi, p_, q_);

    mpz_mul(n, p, q);
    modinv(d, e, phi);

    mpz_clears(p_, q_, phi, r, NULL);
    return 0;
}
