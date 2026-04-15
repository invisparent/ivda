/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include "ivda/shape/shape.h"


ivda_shape_intersect_result
ivda_shape_intersect(
    const ivda_shape *const self,
    const ivda_ray *const ray
) {
    ivs_assert(ray && self);
    return self->vp->intersect(self, ray);
}

// ivda_fp
// ivda_shape_surface_area(
//     const ivda_shape *const self
// ) {
//     ivs_assert(self);
//     return self->vp->surface_area(self);
// }

ivda_aabb_3
ivda_shape_bound(
    const ivda_shape *self
) {
    ivs_assert(self);
    return self->vp->bound(self);
}
