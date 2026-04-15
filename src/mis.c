/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include <math.h>

#include "ivs/core.h"
#include "ivs/mmp.h"

#include "ivda/mis.h"
#include "ivda/rng.h"


/**
 * Do not forget it returns p(w),
 *   not p(theta, phi).
 * And remember d(w) = sin(theta) * d(theta) * d(phi).
 */

ivda_mis_result
ivda_mis_hemisphere_uniform(
    const ivda_vector_3 *const norm
) {
    ivs_assert(norm);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_vector_3_at(norm, 0),,
                                     ivda_vector_3_at(norm, 1),,
                                     ivda_vector_3_at(norm, 2),
                                     ivs));
    ivs_hint(ivda_fp_approx(ivda_fp_make(1), ivda_vector_3_l2norm(norm)));
    ivda_mis_result ret;
    ret.vec = ivda_vector_3_to_polar(norm);
    ivda_vector_3_at_set(&ret.vec, 1, ivda_vector_3_at(&ret.vec, 1) - ivda_fp_pi / ivda_fp_make(2));
    const ivda_fp u = ivda_rng_gen();
    const ivda_fp v = ivda_rng_gen();
    const ivda_fp theta = ivda_acos(u);
    const ivda_fp phi = ivda_fp_make(2) * ivda_fp_pi * v;
    ivda_vector_3_at_set(&ret.vec, 1, ivda_vector_3_at(&ret.vec, 1) + theta);
    ivda_vector_3_at_set(&ret.vec, 2, ivda_vector_3_at(&ret.vec, 2) + phi);
    ret.vec = ivda_vector_3_to_cartesian(&ret.vec);
    ret.pdf = ivda_fp_make(.5) / ivda_fp_pi;
    return ret;
}

ivda_mis_result
ivda_mis_hemisphere_cos_weighted(
    const ivda_vector_3 *const norm
) {
    ivs_assert(norm);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_vector_3_at(norm, 0),,
                                     ivda_vector_3_at(norm, 1),,
                                     ivda_vector_3_at(norm, 2),
                                     ivs));
    ivs_hint(ivda_fp_approx(ivda_fp_make(1), ivda_vector_3_l2norm(norm)));
    ivda_mis_result ret;
    ret.vec = ivda_vector_3_to_polar(norm);
    ivda_vector_3_at_set(&ret.vec, 1, ivda_vector_3_at(&ret.vec, 1) - ivda_fp_pi / ivda_fp_make(2));
    const ivda_fp u = ivda_rng_gen();
    const ivda_fp v = ivda_rng_gen();
    const ivda_fp theta = ivda_asin(ivda_sqrt(u));
    const ivda_fp phi = ivda_fp_make(2) * ivda_fp_pi * v;
    ivda_vector_3_at_set(&ret.vec, 1, ivda_vector_3_at(&ret.vec, 1) + theta);
    ivda_vector_3_at_set(&ret.vec, 2, ivda_vector_3_at(&ret.vec, 2) + phi);
    ret.vec = ivda_vector_3_to_cartesian(&ret.vec);
    ret.pdf = ivda_cos(theta) / ivda_fp_pi;
    return ret;
}

ivda_mis_result
ivda_mis_blinn_phong(
    const ivda_vector_3 *const norm,
    const ivda_fp exponent
) {
    ivs_assert(norm);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_vector_3_at(norm, 0),,
                                     ivda_vector_3_at(norm, 1),,
                                     ivda_vector_3_at(norm, 2),
                                     ivs));
    ivs_assert(isfinite(exponent) && ivda_fp_strict_greater(ivda_fp_make(0), exponent));
    ivs_hint(ivda_fp_approx(ivda_fp_make(1), ivda_vector_3_l2norm(norm)));
    ivda_mis_result ret;
    ret.vec = ivda_vector_3_to_polar(norm);
    ivda_vector_3_at_set(&ret.vec, 1, ivda_vector_3_at(&ret.vec, 1) - ivda_fp_pi / ivda_fp_make(2));
    const ivda_fp u = ivda_rng_gen();
    const ivda_fp v = ivda_rng_gen();
    const ivda_fp theta = ivda_acos(ivda_pow(u, ivda_fp_make(1) / (exponent + ivda_fp_make(1))));
    const ivda_fp phi = ivda_fp_make(2) * ivda_fp_pi * v;
    ivda_vector_3_at_set(&ret.vec, 1, ivda_vector_3_at(&ret.vec, 1) + theta);
    ivda_vector_3_at_set(&ret.vec, 2, ivda_vector_3_at(&ret.vec, 2) + phi);
    ret.vec = ivda_vector_3_to_cartesian(&ret.vec);
    ret.pdf = (exponent + ivda_fp_make(1)) / ivda_fp_make(2) / ivda_fp_pi * ivda_pow(ivda_cos(theta), exponent);
    return ret;
}

static
ivda_fp
ivda_static_mis_trowbridge_reitz_d(
    const ivda_fp theta,
    const ivda_fp roughness
) {
    const ivda_fp a2 = roughness * roughness;
    const ivda_fp ct2 = ivda_cos(theta) * ivda_cos(theta);
    const ivda_fp y = ct2 * (a2 - ivda_fp_make(1)) + ivda_fp_make(1);
    const ivda_fp y2 = y * y;
    return a2 / ivda_fp_pi / y2;
}

ivda_mis_result
ivda_mis_trowbridge_reitz(
    const ivda_vector_3 *const norm,
    const ivda_fp roughness
) {
    ivs_assert(norm);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_vector_3_at(norm, 0),,
                                     ivda_vector_3_at(norm, 1),,
                                     ivda_vector_3_at(norm, 2),
                                     ivs));
    ivs_assert(ivda_fp_strict_between(ivda_fp_make(0), ivda_fp_make(1), roughness));
    ivs_hint(ivda_fp_approx(ivda_fp_make(1), ivda_vector_3_l2norm(norm)));
    ivda_mis_result ret;
    ret.vec = ivda_vector_3_to_polar(norm);
    ivda_vector_3_at_set(&ret.vec, 1, ivda_vector_3_at(&ret.vec, 1) - ivda_fp_pi / ivda_fp_make(2));
    const ivda_fp u = ivda_rng_gen();
    const ivda_fp v = ivda_rng_gen();
    const ivda_fp theta = ivda_acos(ivda_sqrt((ivda_fp_make(1) - u) / (u * (roughness * roughness - ivda_fp_make(1)) + ivda_fp_make(1))));
    const ivda_fp phi = ivda_fp_make(2) * ivda_fp_pi * v;
    ivda_vector_3_at_set(&ret.vec, 1, ivda_vector_3_at(&ret.vec, 1) + theta);
    ivda_vector_3_at_set(&ret.vec, 2, ivda_vector_3_at(&ret.vec, 2) + phi);
    ret.vec = ivda_vector_3_to_cartesian(&ret.vec);
    ret.pdf = ivda_cos(theta) * ivda_static_mis_trowbridge_reitz_d(theta, roughness);
    return ret;
}
