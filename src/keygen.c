#include <assert.h>

#include "keygen.h"

#include "prime.h"
#include "gcd.h"
#include "modinvert.h"

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

    /*gmp_printf("p:   0x%Zx (%Zd)\n", p, p);*/
    /*gmp_printf("q:   0x%Zx (%Zd)\n", q, q);*/
    /*gmp_printf("e:   0x%Zx (%Zd)\n", e, e);*/
    /*gmp_printf("phi: 0x%Zx (%Zd)\n", phi, phi);*/
    /*gmp_printf("n:   %Zx\n", n);*/
    /*gmp_printf("d:   %Zx\n", d);*/

    //gmp_printf("0x%Zx 0x%Zx 0x%Zx 0x%Zx 0x%Zx\n", p, q, n, e, d);
    //gmp_printf("p: %Zd q: %Zd n: %Zd e: %Zd d: %Zd\n", p, q, n, e, d);

    mpz_clears(p_, q_, phi, r, NULL);
    return 0;
}
