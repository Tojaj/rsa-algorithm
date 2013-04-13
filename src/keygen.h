#ifndef KRY2_KEYGEN_H_
#define KRY2_KEYGEN_H_

#include <stdio.h>
#include <gmp.h>

/** RSA key generation.
 * @param p             First prime number.
 * @param q             Second prime number.
 * @param n             Public modulus.
 * @param e             Public exponent.
 * @param d             Private exponent.
 * @param mod_bits      Required length of public modulus in bits.
 * @param randstate     Random number generator state.
 * @return              0 - OK, 1 - Error
 */
int keygen(mpz_t p, mpz_t q, mpz_t n, mpz_t e, mpz_t d,
           int mod_bits, gmp_randstate_t randstate);

#endif
