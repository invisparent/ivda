/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */
 
 
#ifndef IVDA_SHAPE_BVH_H
#define IVDA_SHAPE_BVH_H


#include "ivs/array_list.h"

#include "./shape.h"


extern const ivda_shape_vtable ivda_bvh_vtable;


typedef struct ivda_bvh {
    ivda_shape base;
    /**
     * stat:
     *   0: not build
     *   1: empty
     *   2: only one
     *   3: normal case
     */
    int stat;
    /**
     * Before build:
     *   typeof(dat) == array_list<shape*>
     * After build:
     *   typeof(dat) == array_list<bvh_node>
     * Cache friendly.
     */
    ivs_array_list dat;
} ivda_bvh;


void
ivda_bvh_init(
    ivda_bvh *self
);

void
ivda_bvh_free(
    const ivda_bvh *self
);

void
ivda_bvh_insert(
    ivda_bvh *self,
    const ivda_shape *shape
);

void
ivda_bvh_build(
    ivda_bvh *self
);

ivda_shape_intersect_result
ivda_bvh_intersect(
    const ivda_bvh *self,
    const ivda_ray *ray
);

ivda_aabb_3
ivda_bvh_bound(
    const ivda_bvh *self
);


#endif
