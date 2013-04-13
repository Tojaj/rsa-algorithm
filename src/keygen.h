#ifndef KRY2_KEYGEN_H_
#define KRY2_KEYGEN_H_

#include <gmp.h>

/** RSA key generation.
 * @param p             Output - First prime number.
 * @param q             Output - Second prime number.
 * @param n             Output - Public modulus.
 * @param e             Output - Public exponent.
 * @param d             Output - Private exponent.
 * @param mod_bits      Required length of public modulus in bits.
 * @param randstate     Random number generator state.
 * @return              0 - OK, 1 - Error
 */
int keygen(mpz_t p, mpz_t q, mpz_t n, mpz_t e, mpz_t d,
           int mod_bits, gmp_randstate_t randstate);

#endif
