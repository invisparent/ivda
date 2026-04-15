/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_MIS_H
#define IVDA_MIS_H


#include "./core.h"
#include "./vector.h"


typedef struct ivda_mis_result {
    ivda_vector_3 vec;
    ivda_fp pdf;
} ivda_mis_result;


ivda_mis_result
ivda_mis_hemisphere_uniform(
    const ivda_vector_3 *norm
);

ivda_mis_result
ivda_mis_hemisphere_cos_weighted(
    const ivda_vector_3 *norm
);

ivda_mis_result
ivda_mis_blinn_phong(
    const ivda_vector_3 *norm,
    ivda_fp exponent
);

ivda_mis_result
ivda_mis_trowbridge_reitz(
    const ivda_vector_3 *norm,
    ivda_fp roughness
);


#endif
