/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_SHAPE_TRIANGLE_H
#define IVDA_SHAPE_TRIANGLE_H


#include "../core.h"
#include "./shape.h"


typedef struct ivda_triangle {
    ivda_shape base;
    ivda_point_3 o;
    ivda_vector_3 va;
    ivda_vector_3 vb;
    const ivda_material *m;
    /**
     * That's not the performance bottleneck.
     * So...
     */
// #ifdef IVDA_MEMSPEED
//     ivda_vector_3 n;
// #endif
} ivda_triangle;


extern const ivda_shape_vtable ivda_triangle_vtable;


void
ivda_triangle_init(
    ivda_triangle *self
);

void
ivda_triangle_init_set(
    ivda_triangle *self,
    const ivda_point_3 *a,
    const ivda_point_3 *b,
    const ivda_point_3 *c,
    const ivda_material *m
);

void
ivda_triangle_set_vert(
    ivda_triangle *self,
    const ivda_point_3 *a,
    const ivda_point_3 *b,
    const ivda_point_3 *c
);

void
ivda_triangle_set_material(
    ivda_triangle *self,
    const ivda_material *m
);

ivda_shape_intersect_result
ivda_triangle_intersect(
    const ivda_triangle *self,
    const ivda_ray *ray
);

ivda_fp
ivda_triangle_surface_area(
    const ivda_triangle *self
);

ivda_aabb_3
ivda_triangle_bound(
    const ivda_triangle *self
);


#endif
