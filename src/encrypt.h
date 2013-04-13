#ifndef KRY2_ENCRYPT_H_
#define KRY2_ENCRYPT_H_

#include <stdio.h>
#include <gmp.h>

/** Encrypt message. Message is a number < public modulus.
 * @param e_str     Public exponent.
 * @param n_str     Public modulus.
 * @param m_str     Message.
 */
int encrypt(const char *e_str, const char *n_str, const char *m_str);

#endif
