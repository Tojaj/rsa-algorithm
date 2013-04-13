#include <stdio.h>

#include "powm.h"

void
powm(mpz_t res_, mpz_t base_, mpz_t exp_, mpz_t mod)
{
    int doit;
    mpz_t res, base, exp;

    mpz_init_set(base, base_);
    mpz_init_set(exp, exp_);
    mpz_init_set_ui(res, 1L);

    doit = mpz_sgn(exp);
    while (doit > 0) {
        if (mpz_tstbit(exp, 0L)) {  // (exp mod 2 == 1)
            mpz_mul(res, res, base);
            mpz_tdiv_r(res, res, mod);
        }
        mpz_tdiv_q_2exp(exp, exp, 1);
        if (mpz_sgn(exp) <= 0)
            break;
        mpz_mul(base, base, base);
        mpz_tdiv_r(base, base, mod);
    }

    mpz_set(res_, res);
    mpz_clear(res);
    mpz_clear(base);
    mpz_clear(exp);
}

void
powm_ui(mpz_t res, mpz_t base, unsigned long exp, mpz_t mod)
{
    mpz_t mpz_exp;
    mpz_init_set_ui(mpz_exp, exp);
    powm(res, base, mpz_exp, mod);
    mpz_clear(mpz_exp);
}
