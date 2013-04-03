#include <assert.h>

#include "gcd.h"

void
binary_gcd(mpz_t r, mpz_t u_, mpz_t v_)
{
    unsigned long long shift;

    if (mpz_sgn(u_) == 0) {
        mpz_set(r, u_);
        return;
    }

    if (mpz_sgn(v_) == 0) {
        mpz_set(r, v_);
        return;
    }

    mpz_t u, v;
    mpz_inits(u, v, NULL);
    mpz_set(u, u_);
    mpz_set(v, v_);

    for (shift = 0; (!mpz_tstbit(u, 0) && !mpz_tstbit(v, 0)); ++shift) {
        mpz_fdiv_q_2exp(u, u, 1);
        mpz_fdiv_q_2exp(v, v, 1);
    }

    while (mpz_tstbit(u, 0) == 0)
        mpz_fdiv_q_2exp(u, u, 1);

    do {
        while (mpz_tstbit(v, 0) == 0)
            mpz_fdiv_q_2exp(v, v, 1);

        if (mpz_cmp(u, v) > 0)
            mpz_swap(u, v);

        mpz_sub(v, v, u);
    } while (mpz_sgn(v) > 0);

    mpz_mul_2exp(r, u, shift);

    //gmp_printf("gcd: u: 0x%Zx (%Zd) v: 0x%Zx (%Zd) | 0x%Zx (%Zd)\n", u_, u_, v_, v_, r, r);

    mpz_clears(u, v, NULL);
}
