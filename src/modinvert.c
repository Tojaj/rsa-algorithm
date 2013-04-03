#include <assert.h>

#include "modinvert.h"

void
modinv(mpz_t r, mpz_t x, mpz_t m)
{
    int iter = 1;
    mpz_t x1, x3, m1, m3, t1, t3, q;

    mpz_inits(x1, x3, m1, m3, t1, t3, q, NULL);
    mpz_set_ui(x1, 1L);
    mpz_set(x3, x);
    mpz_set(m3, m);

    // Loop while m3 != 0
    int kk = 0;

    /*
     *gmp_printf("x1:   %Zd\n", x1);
     *gmp_printf("x3:   %Zd\n", x3);
     *gmp_printf("m1:   %Zd\n", m1);
     *gmp_printf("m3:   %Zd\n", m3);
     */

    while (mpz_sgn(m3) != 0) {
        // Divide and "Subtract"
        mpz_fdiv_qr(q, t3, x3, m3);
        mpz_mul(t1, q, m1);
        mpz_add(t1, t1, x1);
        // Swap
        mpz_swap(x1, m1);
        mpz_swap(m1, t1);
        mpz_swap(x3, m3);
        mpz_swap(m3, t3);
        iter = -iter;
        ++kk;
    }

    // Make sure x3 = gcd(x,m) == 1
    if (mpz_cmp_ui(x3, 1L) != 0) {
        // Error: No inverse exists
        mpz_set_ui(r, 0L);
        goto end;
    }

    // Ensure a positive result
    if (iter < 0)
        mpz_sub(r, m, x1);
    else
        mpz_set(r, x1);

end:
    mpz_clears(x1 ,x3, m1, m3, t1, t3, q, NULL);
}
