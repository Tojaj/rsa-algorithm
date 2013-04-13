#ifndef KRY2_GCD_H_
#define KRY2_GCD_H_

#include <stdio.h>
#include <gmp.h>

/** Greatest Common Divisor. (Implementation of binary GCD algorithm)
 * @param r         Result will be stored here.
 * @param u         First number.
 * @param v         Second number.
 */
void binary_gcd(mpz_t r, mpz_t u, mpz_t v);

#endif
