#ifndef KRY2_KEYGEN_H_
#define KRY2_KEYGEN_H_

#include <stdio.h>
#include <gmp.h>

/** RSA key generation.
 * @param mod_bits      Required length of public modulus in bits.
 * @param randstate     Random number generator state.
 * @return              0 - OK, 1 - Error
 */
int keygen(int mod_bits, gmp_randstate_t randstate);

#endif
