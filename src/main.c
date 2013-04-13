#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "keygen.h"
#include "encrypt.h"
#include "decrypt.h"
#include "modinvert.h"
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
            // Argv: [2]=e; [3]=n; [4]=m;
            rc = encrypt(res, argv[2], argv[3], argv[4]);
            gmp_printf("0x%Zx\n", res);
            break;

        case STATE_DECRYPTION:
            // Argv: [2]=d; [3]=n; [4]=c;
            rc = decrypt(res, argv[2], argv[3], argv[4]);
            gmp_printf("0x%Zx\n", res);
            break;

        case STATE_CRACKING: {
            // Argv: [2]=e; [3]=n; [4]=c;
            mpz_t p, q, p_, q_, e, d;
            mpz_inits(p, q, p_, q_, e, d, NULL);

            rc = factorization(p, q, argv[3]);
            if (rc != 0) {
                mpz_clears(p, q, NULL);
                break;
            }

            // phi = (p-1) * (q-1)
            mpz_sub_ui(p_, p, 1L);
            mpz_sub_ui(q_, q, 1L);
            mpz_mul(res, p_, q_);

            // d = e^1 mod phi
            mpz_set_str(e, argv[2], 0);
            modinv(d, e, res);

            rc = decrypt_mpz_d(res, d, argv[3], argv[4]);
            gmp_printf("0x%Zx 0x%Zx 0x%Zx\n", p, q, res);
            mpz_clears(p, q, p_, q_, e, d, NULL);
            break;
        }

        case STATE_BADARG:
            break;
    }

    mpz_clear(res);
    gmp_randclear(randstate);
    return rc;
}
