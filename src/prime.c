#include <assert.h>

#include "powm.h"
#include "prime.h"

int
is_probably_prime(mpz_t n, int reliability, gmp_randstate_t randstate)
{
    // Miller-Rabin test
    assert(reliability > 0);

    int ret = 1;
    long long s = 0;
    mpz_t n_, d, a, x;

    if (mpz_even_p(n))
        return 0;  // Even number is definitely not a prime

    if (mpz_cmp_si(n, 3L) <= 0)
        return -1;  // Do not bother with too small or negative numbers!

    mpz_inits(n_, d, a, x, NULL);       // n_ = s = d = a = x = 0
    mpz_sub_ui(n_, n, 1L);              // n_ = n - 1
    mpz_set(d, n_);                     // d = n_
    do {
        mpz_fdiv_q_2exp(d, d, 1);       // d = d >> 1 ~ d = d / 2
        //mpz_add_ui(s, s, 1L);           // s++
        ++s;
    } while (mpz_even_p(d));
    --s;

    for (int i=0; i < reliability; i++) {
        int continue_for = 0;

        do {  // Get random number in <2; num-2>
            mpz_urandomm(a, randstate, n_);
        } while (mpz_cmp_si(a, 2) == -1);
        powm(x, a, d, n);
        if (mpz_cmp_ui(x, 1L) == 0 || mpz_cmp(x, n_) == 0)
            continue;  // This number is probably a prime

        for (long long r = 0; r < s; r++) {
            powm_ui(x, x, 2L, n);
            if (mpz_cmp_ui(x, 1L) == 0) {
                // Not a prime
                ret = 0;
                goto final;
            }
            if (mpz_cmp(x, n_) == 0) {
                continue_for = 1;
                break; // This number is probably a prime
            }
        }

        if (continue_for)
            continue;

        ret = 0;  // Not a prime
    }

final:
    mpz_clears(n_, d, a, x, NULL);
    return ret; // This number is probably a prime
}

void
gen_prime(mpz_t prime, int len, int reliability, gmp_randstate_t randstate)
{
    mpz_t max_val;
    mpz_init(max_val);
    mpz_ui_pow_ui(max_val, 2L, len);

    // Get next by random
    do {
        mpz_urandomm(prime, randstate, max_val);
        mpz_setbit(prime, 0);       // Guarantee the number is odd
        mpz_setbit(prime, len-1);   // Guarantee the number minimal len
        mpz_setbit(prime, len-2);   // Guarantee the number minimal len
        //gmp_printf("candidate: 0x%Zx (%Zd)\n", prime, prime);
    } while(is_probably_prime(prime, reliability, randstate) != 1);

    // Gen next by incrementing by 2
    /*
    mpz_urandomm(prime, randstate, max_val);
    mpz_setbit(prime, 0);       // Guarantee the number is odd
    mpz_setbit(prime, len-1);   // Guarantee the number minimal len
    mpz_setbit(prime, len-2);   // Guarantee the number minimal len
    while(is_probably_prime(prime, reliability, randstate) != 1)
        mpz_add_ui(prime, prime, 2);
    */
}
