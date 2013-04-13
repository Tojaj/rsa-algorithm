#ifndef KRY2_DECRYPT_H_
#define KRY2_DECRYPT_H_

#include <gmp.h>

/** Decipher cipher text. Cipher text must be a number.
 * @param m             Output - Deciphered message.
 * @param d_str         Private exponent.
 * @param n_str         Public modulus.
 * @param c_str         Cipher text.
 * @return              0 - OK, 1 - Error
 */
int decrypt(mpz_t m, const char *d_str, const char *n_str, const char *c_str);
int decrypt_mpz_d(mpz_t m, mpz_t d, const char *n_str, const char *c_str);

#endif
