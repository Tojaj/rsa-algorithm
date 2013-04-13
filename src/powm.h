#ifndef KRY2_POWM_H_
#define KRY2_POWM_H_

#include <stdio.h>
#include <gmp.h>

/** Modular exponentiation. (base^exponent = num mod modulus)
 * @param num       Result will be stored here.
 * @param base      Base.
 * @param exp       Exponent.
 * @param mod       Modulus.
 */
void powm(mpz_t num, mpz_t base, mpz_t exp, mpz_t mod);
void powm_ui(mpz_t res, mpz_t base, unsigned long exp, mpz_t mod);

#endif
