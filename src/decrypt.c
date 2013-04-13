#include <stdio.h>
#include <assert.h>

#include "decrypt.h"
#include "powm.h"

int
decrypt_mpz_d(mpz_t m, mpz_t d, const char *n_str, const char *c_str)
{
    int rc = 0;
    mpz_t n, c;
    mpz_inits(n, c, NULL);

    rc += mpz_set_str(n, n_str, 0);
    rc += mpz_set_str(c, c_str, 0);
    if (rc != 0) {
        fprintf(stderr, "Invalid number argument\n");
        mpz_clears(n, c, NULL);
        return 1;
    }

    powm(m, c, d, n);
    //gmp_printf("0x%Zx\n", m);
    //gmp_printf("%Zd\n", m);
    mpz_clears(n, c, NULL);
    return rc;
}

int
decrypt(mpz_t m, const char *d_str, const char *n_str, const char *c_str)
{
    int rc;
    mpz_t d;
    mpz_init_set_str(d, d_str, 0);
    rc = decrypt_mpz_d(m, d, n_str, c_str);
    mpz_clear(d);
    return rc;
}
