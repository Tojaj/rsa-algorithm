#ifndef KRY2_ENCRYPT_H_
#define KRY2_ENCRYPT_H_

#include <gmp.h>

/** Encrypt message. Message is a number < public modulus.
 * @param c         Output - Cipher text.
 * @param e_str     Public exponent.
 * @param n_str     Public modulus.
 * @param m_str     Message.
 * @return          0 - OK, 1 - Error
 */
int encrypt(mpz_t c, const char *e_str, const char *n_str, const char *m_str);

#endif
