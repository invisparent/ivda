/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_AABB_H
#define IVDA_AABB_H


#include "./core.h"
#include "./point.h"
#include "./ray.h"


typedef struct ivda_aabb_3 {
    ivda_point_3 lower;
    ivda_point_3 upper;
} ivda_aabb_3;


typedef struct ivda_aabb_3_intersect_result {
    ivda_fp t_min;
    ivda_fp t_max;
    _Bool intersected;
} ivda_aabb_3_intersect_result;


void
ivda_aabb_3_init(
    ivda_aabb_3 *self
);

void
ivda_aabb_3_include(
    ivda_aabb_3 *self,
    const ivda_point_3 *point
);

ivda_aabb_3_intersect_result
ivda_aabb_3_intersect(
    const ivda_aabb_3 *self,
    const ivda_ray *ray
);

ivda_fp
ivda_aabb_3_surface_area(
    const ivda_aabb_3 *self
);

ivda_fp
ivda_aabb_3_volume(
    const ivda_aabb_3 *self
);

ivda_point_3
ivda_aabb_3_center(
    const ivda_aabb_3 *self
);

ivda_aabb_3
ivda_aabb_3_add(
    const ivda_aabb_3 *a,
    const ivda_aabb_3 *b
);


#endif
