#ifndef KRY2_DECRYPT_H_
#define KRY2_DECRYPT_H_

#include <stdio.h>
#include <gmp.h>

/** Decipher cipher text. Cipher text must be a number.
 * @param d_str         Private exponent.
 * @param n_str         Public modulus.
 * @param c_str         Cipher text.
 */
int decrypt(const char *d_str, const char *n_str, const char *c_str);

#endif
