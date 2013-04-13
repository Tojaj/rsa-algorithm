#ifndef KRY2_FACTORIZATION_H_
#define KRY2_FACTORIZATION_H_

#include <stdio.h>
#include <gmp.h>

/** Try to factorize factors of n.
 * @param e_str         Public exponent - Not used
 * @param n_str         Public modulus
 * @param c_str         Ciphertext - Not used
 * @return              0 - OK, 1 - Error
 */
int factorization(const char *e_str, const char *n_str, const char *c_str);

#endif
