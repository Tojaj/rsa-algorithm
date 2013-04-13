#include <stdio.h>

#include "encrypt.h"
#include "powm.h"

// RSA encrypt: c = m^e mod n (Note: 1 < m < n)

int
encrypt(mpz_t c, const char *e_str, const char *n_str, const char *m_str)
{
    int rc = 0;
    mpz_t e, n, m;
    mpz_inits(e, n, m, NULL);

    rc += mpz_set_str(e, e_str, 0);
    rc += mpz_set_str(n, n_str, 0);
    rc += mpz_set_str(m, m_str, 0);
    if (rc != 0) {
        fprintf(stderr, "Invalid number argument\n");
        mpz_clears(e, n, m, NULL);
        return 1;
    }

    powm(c, m, e, n);
    mpz_clears(e, n, m, NULL);
    return rc;
}
