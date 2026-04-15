/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include <math.h>

#include "ivs/core.h"
#include "ivs/mmp.h"

#include "ivda/aabb.h"


void
ivda_aabb_3_init(
    ivda_aabb_3 *const self
) {
    ivs_assert(self);
    ivda_point_3_set(&self->lower, ivda_fp_inf_pos);
    ivda_point_3_set(&self->upper, ivda_fp_inf_neg);
}

void
ivda_aabb_3_include(
    ivda_aabb_3 *const self,
    const ivda_point_3 *const point
) {
    ivs_assert(self && point);
    for (unsigned t = 0; t < 3; ++t) {
        ivda_point_3_at_set(&self->lower, t, ivs_inline_min(ivda_point_3_at(&self->lower, t), ivda_point_3_at(point, t)));
        ivda_point_3_at_set(&self->upper, t, ivs_inline_max(ivda_point_3_at(&self->upper, t), ivda_point_3_at(point, t)));
    }
}

ivda_aabb_3_intersect_result
ivda_aabb_3_intersect(
    const ivda_aabb_3 *const self,
    const ivda_ray *const ray
) {
    ivs_assert(self && ray);
    ivda_aabb_3_intersect_result ret = {
        .intersected = 0
    };
    ivda_fp tl[3];
    ivda_fp tu[3];
    for (unsigned t = 0; t < 3; ++t) {
        const ivda_fp ro = ivda_point_3_at(ivda_ray_o(ray), t);
        const ivda_fp rd = ivda_vector_3_at(ivda_ray_d(ray), t);
        const ivda_fp lower = ivda_point_3_at(&self->lower, t);
        const ivda_fp upper = ivda_point_3_at(&self->upper, t);
        if (ivda_fp_approx(ivda_fp_make(0), rd))
            if (ro < lower || ro > upper)
                return ret;
            else {
                if (rd > ivda_fp_make(0)) {
                    tl[t] = (lower - ro) / rd;
                    tu[t] = (upper - ro) / rd;
                } else {
                    tl[t] = (upper - ro) / rd;
                    tu[t] = (lower - ro) / rd;
                }
            }
    }
    ret.t_min = ivs_inline_max_3(tl[0], tl[1], tl[2]);
    ret.t_max = ivs_inline_min_3(tu[0], tu[1], tu[2]);
    if (ret.t_max <= ivda_fp_make(0) || ret.t_min >= ret.t_max)
        return ret;
    else {
        ret.intersected = 1;
        ret.t_min = ivs_inline_max(ret.t_min, ivda_fp_make(0));
        return ret;
    }
}

ivda_fp
ivda_aabb_3_surface_area(
    const ivda_aabb_3 *const self
) {
    ivs_assert(self);
    ivda_fp v[3];
    for (unsigned t = 0; t < 3; ++t)
        v[t] = ivs_inline_max(ivda_point_3_at(&self->upper, t) - ivda_point_3_at(&self->lower, t), ivda_fp_make(0));
    const ivda_fp ret = v[0] * v[1] + v[0] * v[2] + v[1] * v[2];
    return ivda_fp_make(2) * ret;
}

ivda_fp
ivda_aabb_3_volume(
    const ivda_aabb_3 *const self
) {
    ivs_assert(self);
    ivda_fp v[3];
    for (unsigned t = 0; t < 3; ++t)
        v[t] = ivs_inline_max(ivda_point_3_at(&self->upper, t) - ivda_point_3_at(&self->lower, t), ivda_fp_make(0));
    return v[0] * v[1] * v[2];
}

ivda_point_3
ivda_aabb_3_center(
    const ivda_aabb_3 *const self
) {
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_point_3_at(&self->lower, 0),,
                                     ivda_point_3_at(&self->lower, 1),,
                                     ivda_point_3_at(&self->lower, 2),,
                                     ivda_point_3_at(&self->upper, 0),,
                                     ivda_point_3_at(&self->upper, 1),,
                                     ivda_point_3_at(&self->upper, 2),
                                     ivs));
    ivda_point_3 ret;
    for (unsigned t = 0; t < 3; ++t)
        ivda_point_3_at_set(&ret, t, ivs_inline_lerp(ivda_point_3_at(&self->lower, t), ivda_point_3_at(&self->upper, t), ivda_fp_make(.5)));
    return ret;
}

ivda_aabb_3
ivda_aabb_3_add(
    const ivda_aabb_3 *const a,
    const ivda_aabb_3 *const b
) {
    ivs_assert(a && b);
    ivda_aabb_3 ret;
    ivda_aabb_3_init(&ret);
    ivda_aabb_3_include(&ret, &a->lower);
    ivda_aabb_3_include(&ret, &a->upper);
    ivda_aabb_3_include(&ret, &b->lower);
    ivda_aabb_3_include(&ret, &b->upper);
    return ret;
}
