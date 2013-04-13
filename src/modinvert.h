#ifndef KRY2_MODINVERT_H_
#define KRY2_MODINVERT_H_

#include <stdio.h>
#include <gmp.h>

/** Modular multiplicative inverse. (x^-1 = r (mod m))
 * (Extended Euclidean algorithm from Knuth)
 * @param r         Result will be stored here.
 * @param x         Base.
 * @param m         Modulus.
 */
void modinv(mpz_t r, mpz_t x, mpz_t m);

#endif
