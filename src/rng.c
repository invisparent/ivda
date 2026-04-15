/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include <stdatomic.h>

#include "ivs/random.h"

#include "ivda/rng.h"


static _Atomic uint64_t ivda_static_rng_seed = IVS_RANDOM_SEED;


ivda_fp
ivda_rng_gen(
    void
) {
    static _Thread_local _Bool tls = 0;
    static _Thread_local ivs_xorshift_64 rng;
    if (ivs_unlikely(!tls)) {
        ivs_xorshift_64_init(&rng, atomic_fetch_add_explicit(&ivda_static_rng_seed, 1, memory_order_relaxed));
        tls = 1;
    }
#ifndef IVDA_XPREC
    return ivs_rng_flt((ivs_rng *) &rng);
#else
    return ivs_rng_dbl((ivs_rng *) &rng);
#endif
}

ivda_fp
ivda_rng_uniform(
    const ivda_fp lb,
    const ivda_fp ub
) {
    return ivs_inline_lerp(lb, ub, ivda_rng_gen());
}
