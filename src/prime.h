#ifndef KRY2_PRIME_H_
#define KRY2_PRIME_H_

#include <stdio.h>
#include <gmp.h>

#define PRIME_DEFAULT_RELIABILITY   20

int is_probably_prime(mpz_t num, int reliability, gmp_randstate_t randstate);
void gen_prime(mpz_t prime, int len, int reliability, gmp_randstate_t randstate);

#endif
