/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_SHAPE_SHAPE_H
#define IVDA_SHAPE_SHAPE_H


#include "../aabb.h"
#include "../core.h"
#include "../point.h"
#include "../vector.h"


typedef struct ivda_material ivda_material;

typedef struct ivda_shape ivda_shape;


typedef struct ivda_shape_intersect_result {
    ivda_point_3 p;
    ivda_vector_3 n;
    ivda_fp u;
    ivda_fp v;
    ivda_fp t;
    const ivda_material *m;
    const ivda_shape *raw;
    _Bool intersected;
    _Bool front;
} ivda_shape_intersect_result;


typedef struct ivda_shape_vtable {

    ivda_shape_intersect_result
    (*const intersect)(
        const ivda_shape *,
        const ivda_ray *
    );

    // /**
    //  * Return negative abs if it can not be easily calculated.
    //  *   (So that's an estimated value)
    //  * And it only considers single side.
    //  *   (e.g. a 1x1 square's surface area is 1, not 2.)
    //  */
    // ivda_fp
    // (*const surface_area)(
    //     const ivda_shape *
    // );

    ivda_aabb_3
    (*const bound)(
        const ivda_shape *
    );

} ivda_shape_vtable;


struct ivda_shape {
    const ivda_shape_vtable *vp;
};


ivda_shape_intersect_result
ivda_shape_intersect(
    const ivda_shape *self,
    const ivda_ray *ray
);

// ivda_fp
// ivda_shape_surface_area(
//     const ivda_shape *self
// );

ivda_aabb_3
ivda_shape_bound(
    const ivda_shape *self
);


#endif
