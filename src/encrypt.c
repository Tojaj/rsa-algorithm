#include <stdio.h>
#include <assert.h>

#include "encrypt.h"
#include "powm.h"

int
encrypt(const char *e_str, const char *n_str, const char *m_str)
{
    int rc = 0;
    mpz_t e, n, m, c;
    mpz_inits(e, n, m, c, NULL);

    rc += mpz_set_str(e, e_str, 0);
    rc += mpz_set_str(n, n_str, 0);
    rc += mpz_set_str(m, m_str, 0);
    if (rc != 0) {
        fprintf(stderr, "Invalid number argument\n");
        mpz_clears(e, n, m, c, NULL);
        return 1;
    }

    powm(c, m, e, n);
    gmp_printf("0x%Zx\n", c);
    //gmp_printf("%Zd\n", c);
    mpz_clears(e, n, m, c, NULL);
    return rc;
}
