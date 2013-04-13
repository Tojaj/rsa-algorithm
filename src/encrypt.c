#include <stdio.h>

#include "encrypt.h"
#include "powm.h"

// RSA encrypt: c = m^e mod n (Note: 1 < m < n)

int
encrypt(mpz_t c, const char *e_str, const char *n_str, const char *m_str)
{
    int rc = 0;
    mpz_t e, n, m;

    rc += mpz_init_set_str(e, e_str, 0);
    rc += mpz_init_set_str(n, n_str, 0);
    rc += mpz_init_set_str(m, m_str, 0);
    if (rc != 0) {
        fprintf(stderr, "Invalid number argument\n");
        rc = 1;
        goto cleanup;
    }

    powm(c, m, e, n);
cleanup:
    mpz_clear(e);
    mpz_clear(n);
    mpz_clear(m);
    return rc;
}
