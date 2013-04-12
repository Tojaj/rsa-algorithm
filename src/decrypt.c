#include <stdio.h>
#include <assert.h>

#include "decrypt.h"
#include "powm.h"

int
decrypt(const char *d_str, const char *n_str, const char *c_str)
{
    int rc = 0;
    mpz_t d, n, c, m;
    mpz_inits(d, n, c, m, NULL);

    rc += mpz_set_str(d, d_str, 0);
    rc += mpz_set_str(n, n_str, 0);
    rc += mpz_set_str(c, c_str, 0);
    if (rc != 0) {
        fprintf(stderr, "Invalid number argument\n");
        mpz_clears(d, n, c, m, NULL);
        return 1;
    }

    powm(m, c, d, n);
    gmp_printf("0x%Zx\n", m);
    //gmp_printf("%Zd\n", m);
    mpz_clears(d, n, c, m, NULL);
    return rc;
}
