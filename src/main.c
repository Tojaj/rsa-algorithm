#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "keygen.h"
#include "encrypt.h"
#include "decrypt.h"
#include "factorization.h"

typedef enum {
    STATE_BADARG,
    STATE_KEYGEN,
    STATE_ENCRYPTION,
    STATE_DECRYPTION,
    STATE_CRACKING,
} KryState;

void
print_help(const char *prog)
{
    const char *msg =
    "Usage: %s [-g keylen] [-e pub_exp pub_mod message]\n"
    "          [-d exp pub_mod ciphertext] [-b pub_exp pub_mod ciphertext]\n"
    "\n"
    "    -g  Key generation\n"
    "    -e  Encryption\n"
    "    -d  Decryption\n"
    "    -b  RSA cracking\n";

    // Remove path from program
    for (size_t x = strlen(prog); x > 0; x--) {
        if (prog[x] == '/') {
            prog = prog + x + 1;
            break;
        }
    }

    printf(msg, prog);
}

int
main(int argc, char *argv[])
{
    KryState state = STATE_BADARG;
    long mod_bits;

    /////////
    /*mpz_t a, b, c, r;*/
    /*mpz_inits(a, b, c, r, NULL);*/
    /*mpz_set_ui(a, 4);*/
    /*mpz_set_ui(b, 13);*/
    /*mpz_set_ui(c, 497);*/
    /*//binary_gcd(r, a, b);*/
    /*powm(r, a, b, c);*/
    /*gmp_printf("%Zd\n", r);*/
    /*mpz_clears(a, b, c, r, NULL);*/
    /*return 0;*/
    /////////

    if (argc == 3 && !strcmp(argv[1], "-g")) {
        // Key generation
        state = STATE_KEYGEN;
        mod_bits = strtol(argv[2], NULL, 10);
        if (mod_bits < 16) {
            state = STATE_BADARG;
            fprintf(stderr, "Too small key length\n");
        }
    } else if (argc == 5 && !strcmp(argv[1], "-e")) {
        // Encryption
        state = STATE_ENCRYPTION;
    } else if (argc == 5 && !strcmp(argv[1], "-d")) {
        // Decryption
        state = STATE_DECRYPTION;
    } else if (argc == 5 && !strcmp(argv[1], "-b")) {
        // RSA cracking
        state = STATE_CRACKING;
    }

    if (state == STATE_BADARG) {
        // Someting is messed up
        print_help(argv[0]);
        return EXIT_FAILURE;
    }

    // Prepare pseudo number generator stuff
    gmp_randstate_t randstate;
    gmp_randinit_default(randstate);
    //gmp_randseed_ui(randstate, 1);
    gmp_randseed_ui(randstate, time(NULL));

    int rc = EXIT_SUCCESS;
    mpz_t res;
    mpz_init(res);

    switch (state) {
        case STATE_KEYGEN: {
            mpz_t p, q, n, e;  // For d use res var
            mpz_inits(p, q, n, e, NULL);
            rc = keygen(p, q, n, e, res, mod_bits, randstate);
            gmp_printf("0x%Zx 0x%Zx 0x%Zx 0x%Zx 0x%Zx\n", p, q, n, e, res);
            mpz_clears(p, q, n, e, NULL);
            break;
        }
        case STATE_ENCRYPTION:
            rc = encrypt(res, argv[2], argv[3], argv[4]);
            gmp_printf("0x%Zx\n", res);
            break;
        case STATE_DECRYPTION:
            rc = decrypt(res, argv[2], argv[3], argv[4]);
            gmp_printf("0x%Zx\n", res);
            break;
        case STATE_CRACKING:
            rc = factorization(argv[2], argv[3], argv[4]);
            break;
        case STATE_BADARG:
            break;
    }

    mpz_clear(res);
    gmp_randclear(randstate);
    return rc;
}
