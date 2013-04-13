#define _XOPEN_SOURCE

#include <assert.h>
#include <msieve.h>
#include <gmp.h>
#include <signal.h>

#include "factorization.h"
#include "modinvert.h"
#include "decrypt.h"

msieve_obj *g_curr_factorization = NULL;

void signal_handler(int sig) {
    msieve_obj *obj = g_curr_factorization;
    fprintf(stderr, "\nreceived signal %d; shutting down\n", sig);
    if (obj && (obj->flags & MSIEVE_FLAG_SIEVING_IN_PROGRESS))
        obj->flags |= MSIEVE_FLAG_STOP_SIEVING;
    else
        _exit(1);
}

int
factorization(const char *e_str, const char *n_str, const char *c_str)
{
    int rc;

    // Check n if valid integer number
    mpz_t tst;
    rc = mpz_init_set_str(tst, n_str, 0);
    mpz_clear(tst);
    if (rc == -1) {
        fprintf(stderr, "Not a valid integer number: %s\n", n_str);
        return 1;
    }

    // Prepare params for factorization
    uint32 flags = MSIEVE_DEFAULT_FLAGS; // Debug: | MSIEVE_FLAG_LOG_TO_STDOUT
    uint32 seed1 = 1; // XXX: In the real world this two seeds
    uint32 seed2 = 5; // shoud be generated randomly!!
    enum cpu_type cpu = get_cpu_type();
    uint32 cache_size1;
    uint32 cache_size2;
    msieve_factor *factor;

    // Try determine L1 and L2 cache sizes
    get_cache_sizes(&cache_size1, &cache_size2);

    g_curr_factorization = msieve_obj_new(
            (char *) n_str, // Number to be factorized
            flags,      // Factorization config flags
            NULL,       // Savefile name
            NULL,       // Logfile name
            NULL,       // NFS factor base filename
            seed1,      // 1st random seed
            seed2,      // 2nd random seed
            0,          // Stop sieving after finding this number of  relations
            cpu,        // CPU type
            cache_size1,// Size of L1 cache
            cache_size2,// Size of L2 cache
            0,          // How many threads to use at most
            0,          // Which GPU to use
            NULL        // NFS arguments
        );

    if (!g_curr_factorization) {
        fprintf(stderr, "Factoring initialization failed\n");
        return 1;
    }

    struct sigaction sigact, old_sigact_int, old_sigact_term;
    sigact.sa_handler = signal_handler;
    sigaddset(&sigact.sa_mask, SIGINT);
    sigaddset(&sigact.sa_mask, SIGTERM);
    sigact.sa_flags = 0;
    if (sigaction(SIGINT,  &sigact, &old_sigact_int)  == -1 ||
        sigaction(SIGTERM, &sigact, &old_sigact_term) == -1)
    {
        fprintf(stderr, "Cannot install signal handler\n");
        return 1;
    }

    // Factorize
    msieve_run(g_curr_factorization);

    sigaction(SIGINT, &old_sigact_int, NULL);
    sigaction(SIGTERM, &old_sigact_term, NULL);

    // Check the results
    if (!(g_curr_factorization->flags & MSIEVE_FLAG_FACTORIZATION_DONE)) {
        fprintf(stderr, "\nFactorization was interrupted\n");
        return 1;
    }

    factor = g_curr_factorization->factors;
    if (!factor || !factor->next) {
        fprintf(stderr, "No factors fond\n");
        return 1;
    }

    // Read the results (get the factors)
    mpz_t d, p, q, p_, q_, e, phi, m;
    mpz_inits(d, p_, q_, phi, m, NULL);
    mpz_init_set_str(p, factor->number, 0);
    mpz_init_set_str(q, factor->next->number, 0);
    mpz_init_set_str(e, e_str, 0);

    // phi = (p-1) * (q-1)
    mpz_sub_ui(p_, p, 1L);
    mpz_sub_ui(q_, q, 1L);
    mpz_mul(phi, p_, q_);

    // d = e^-1 mod phi
    modinv(d, e, phi);

    // Decrypt the message
    rc = decrypt_mpz_d(m, d, n_str, c_str);

    gmp_printf("0x%Zx 0x%Zx 0x%Zx\n", p, q, m);
    mpz_clears(d, p, q, p_, q_, e, phi, m, NULL);
    return rc;
}
