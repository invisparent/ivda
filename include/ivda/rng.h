/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_RNG_H
#define IVDA_RNG_H


#include "./core.h"


ivda_fp
ivda_rng_gen(
    void
);

ivda_fp
ivda_rng_uniform(
    ivda_fp lb,
    ivda_fp ub
);


#endif
