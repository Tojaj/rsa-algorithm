#ifndef KRY2_PRIME_H_
#define KRY2_PRIME_H_

#include <stdio.h>
#include <gmp.h>


#define PRIME_DEFAULT_RELIABILITY   20  /*!< Sufficient number of cycles
                                             for primality test */

/** Test number for primality. (Fermat test + Miller-Rabin test)
 * @param num           Number for testing.
 * @param reliability   Number of cycles for Miller-Rabin primality test.
 * @param randstate     Random number generator state.
 */
int is_probably_prime(mpz_t num, int reliability, gmp_randstate_t randstate);

/** Gen a number which is probably a prime.
 * @param num           Result will be stored in this variable.
 * @param len           Required bit length of the number.
 * @param reliability   Number of cycles for Miller-Rabin primality test.
 * @param randstate     Random number generator state.
 */
void gen_prime(mpz_t prime, int len, int reliability, gmp_randstate_t randstate);

#endif
