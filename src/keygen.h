#ifndef KRY2_KEYGEN_H_
#define KRY2_KEYGEN_H_

#include <stdio.h>
#include <gmp.h>

int keygen(int mod_bits, gmp_randstate_t randstate);

#endif
