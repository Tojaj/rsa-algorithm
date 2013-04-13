#ifndef KRY2_FACTORIZATION_H_
#define KRY2_FACTORIZATION_H_

#include <stdio.h>
#include <gmp.h>

/** Try to factorize factors of n.
 * @param e         Public exponent - Not used
 * @param n         Public modulus
 * @param c         Ciphertext - Not used
 */
void factorization(mpz_t e, mpz_t n, mpz_t c);

#endif
