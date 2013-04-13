#ifndef KRY2_FACTORIZATION_H_
#define KRY2_FACTORIZATION_H_

#include <gmp.h>

/** Try to factorize factors of n.
 * @param p             Output - First prime number.
 * @param q             Output - Seond prime number.
 * @param n_str         Public modulus
 * @return              0 - OK, 1 - Error
 */
int factorization(mpz_t p, mpz_t q, const char *n_str);

#endif
