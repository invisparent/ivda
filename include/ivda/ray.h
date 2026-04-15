/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_RAY_H
#define IVDA_RAY_H


#include "./point.h"
#include "./vector.h"


typedef struct ivda_ray {
    ivda_point_3 o;
    ivda_vector_3 d;
} ivda_ray;


void
ivda_ray_set(
    ivda_ray *self,
    const ivda_point_3 *o,
    const ivda_vector_3 *d
);

void
ivda_ray_set_o(
    ivda_ray *self,
    const ivda_point_3 *o
);

void
ivda_ray_set_d(
    ivda_ray *self,
    const ivda_vector_3 *d
);

const ivda_point_3 *
ivda_ray_o(
    const ivda_ray *self
);

const ivda_vector_3 *
ivda_ray_d(
    const ivda_ray *self
);

void
ivda_ray_offset(
    ivda_ray *self,
    const ivda_vector_3 *direction,
    ivda_fp val
);

ivda_point_3
ivda_ray_target(
    const ivda_ray *self,
    ivda_fp val
);


#endif
