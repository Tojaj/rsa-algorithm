#include <assert.h>

#include "keygen.h"

#include "prime.h"
#include "gcd.h"
#include "modinvert.h"

int
keygen(int mod_bits, gmp_randstate_t randstate)
{
    mpz_t p, q, p_, q_, n, phi, d, e, gcd;
    mpz_inits(p, q, p_, q_, n, phi, d, e, gcd, NULL);

    mpz_set_ui(e, 3L);

    do {
        gen_prime(p, mod_bits-(mod_bits/2), PRIME_DEFAULT_RELIABILITY, randstate);
    } while (mpz_fdiv_r(gcd, p, e), mpz_cmp_ui(gcd, 1) == 0);

    do {
        gen_prime(q, mod_bits/2, PRIME_DEFAULT_RELIABILITY, randstate);
    } while (mpz_cmp(q, p) == 0 || (mpz_fdiv_r(gcd, q, e), mpz_cmp_ui(gcd, 1) == 0));

    mpz_sub_ui(p_, p, 1L);
    mpz_sub_ui(q_, q, 1L);
    mpz_mul(phi, p_, q_);

    mpz_mul(n, p, q);
    modinv(d, e, phi);

    /*gmp_printf("p:   0x%Zx (%Zd)\n", p, p);*/
    /*gmp_printf("q:   0x%Zx (%Zd)\n", q, q);*/
    /*gmp_printf("e:   0x%Zx (%Zd)\n", e, e);*/
    /*gmp_printf("phi: 0x%Zx (%Zd)\n", phi, phi);*/
    /*gmp_printf("gcd: 0x%Zx (%Zd)\n", gcd, gcd);*/
    /*gmp_printf("n:   %Zx\n", n);*/
    /*gmp_printf("d:   %Zx\n", d);*/

    gmp_printf("0x%Zx 0x%Zx 0x%Zx 0x%Zx 0x%Zx\n", p, q, n, e, d);
    //gmp_printf("p: %Zd q: %Zd n: %Zd e: %Zd d: %Zd\n", p, q, n, e, d);

    mpz_clears(p, q, p_, q_, n, phi, d, e, gcd, NULL);
    return 0;
}
