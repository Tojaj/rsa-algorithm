#include <stdio.h>

#include "powm.h"
#include "prime.h"

int
is_probably_prime(mpz_t n, int reliability, gmp_randstate_t randstate)
{
    // Miller-Rabin test

    int ret = 1;
    unsigned long s = 0;
    mpz_t n_, d, a, x;

    if (mpz_even_p(n))
        return 0;  // Even number is definitely not a prime

    if (mpz_cmp_si(n, 3L) <= 0)
        return -1;  // Do not bother with too small or negative numbers!


    mpz_inits(n_, d, a, x, NULL);       // n_ = d = a = x = 0
    mpz_sub_ui(n_, n, 1L);              // n_ = n - 1

    // First try Fermat test
    mpz_set_ui(d, 6L);
    powm(a, d, n_, n);
    if (mpz_cmp_ui(a, 1L) != 0) {
        ret = 0;
        goto final;
    }

    //mpz_set(d, n_);                     // d = n_
    //do {
    //    mpz_fdiv_q_2exp(d, d, 1);       // d = d >> 1 ~ d = d / 2
    //    ++s;
    //} while (mpz_even_p(d));
    //--s;
    // ^^^ This commented code above is equivalent for these two lines:
    s = mpz_scan1(n_, 0L);
    mpz_tdiv_q_2exp(d, n_, s);

    for (int i=0; i < reliability; i++) {
        int probably_prime = 0;

        do {  // Get random number in <2; num-2>
            mpz_urandomm(a, randstate, n_);
        } while (mpz_cmp_ui(a, 2) == -1);
        powm(x, a, d, n);
        if (mpz_cmp_ui(x, 1L) == 0 || mpz_cmp(x, n_) == 0)
            continue;  // This number is probably a prime

        for (unsigned long r = 0; r < s; r++) {
            powm_ui(x, x, 2L, n);
            if (mpz_cmp_ui(x, 1L) == 0) {
                // Not a prime
                ret = 0;
                goto final;
            }
            if (mpz_cmp(x, n_) == 0) {
                probably_prime = 1;
                break; // This number is probably a prime
            }
        }

        if (probably_prime)
            continue;

        ret = 0;  // Not a prime
    }

final:
    mpz_clears(n_, d, a, x, NULL);
    return ret;
}

void
gen_prime(mpz_t prime, int len, int reliability, gmp_randstate_t randstate)
{
    mpz_t max_val;
    mpz_init(max_val);
    mpz_setbit(max_val, len);

    // Get next by random
/*
    do {
        //mpz_urandomb(prime, randstate, len);
        mpz_urandomm(prime, randstate, max_val);
        mpz_setbit(prime, 0);       // Guarantee the number is odd
        mpz_setbit(prime, len-1);   // Guarantee the number minimal len
        mpz_setbit(prime, len-2);   // Guarantee the number minimal len
        //gmp_printf("candidate: 0x%Zx (%Zd)\n", prime, prime);
    } while(is_probably_prime(prime, reliability, randstate) != 1);
*/

    // Gen next by incrementing by 2

    mpz_urandomm(prime, randstate, max_val);
    mpz_setbit(prime, 0);       // Guarantee the number is odd
    mpz_setbit(prime, len-1);   // Guarantee the number minimal len
    mpz_setbit(prime, len-2);   // Guarantee the number minimal len
    while(is_probably_prime(prime, reliability, randstate) != 1)
        mpz_add_ui(prime, prime, 2);


    mpz_clear(max_val);
}
