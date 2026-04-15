/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include <math.h>

#include "ivs/core.h"
#include "ivs/mmp.h"

#include "ivda/ray.h"


void
ivda_ray_set(
    ivda_ray *const self,
    const ivda_point_3 *const o,
    const ivda_vector_3 *const d
) {
    ivs_assert(self);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_point_3_at(o, 0),,
                                     ivda_point_3_at(o, 1),,
                                     ivda_point_3_at(o, 2),
                                     ivs));
    ivs_assert(ivda_vector_3_is_normalized(d));
    ivda_ray_set_o(self, o);
    ivda_ray_set_d(self, d);
}

void
ivda_ray_set_o(
    ivda_ray *const self,
    const ivda_point_3 *const o
) {
    ivs_assert(self && o);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_point_3_at(o, 0),,
                                     ivda_point_3_at(o, 1),,
                                     ivda_point_3_at(o, 2),
                                     ivs));
    self->o = *o;
}

void
ivda_ray_set_d(
    ivda_ray *const self,
    const ivda_vector_3 *const d
) {
    ivs_assert(self && d);
    ivs_assert(ivda_vector_3_is_normalized(d));
    self->d = *d;
}

const ivda_point_3 *
ivda_ray_o(
    const ivda_ray *const self
) {
    ivs_assert(self);
    return &self->o;
}

const ivda_vector_3 *
ivda_ray_d(
    const ivda_ray *const self
) {
    ivs_assert(self);
    return &self->d;
}

void
ivda_ray_offset(
    ivda_ray *const self,
    const ivda_vector_3 *const direction,
    const ivda_fp val
) {
    ivs_assert(self && direction);
    ivs_assert(val > ivda_fp_make(0) && isfinite(val));
    ivda_vector_3 offset = *direction;
    ivda_vector_3_mul_scalar(&offset, val);
    ivda_point_3_add_equal(&self->o, &offset);
}

ivda_point_3
ivda_ray_target(
    const ivda_ray *const self,
    const ivda_fp val
) {
    ivs_assert(self);
    ivs_assert(isfinite(val));
    ivs_hint(val >= ivda_fp_make(0));
    ivda_vector_3 v = self->d;
    ivda_vector_3_mul_scalar(&v, val);
    return ivda_point_3_add(&self->o, &v);
}
