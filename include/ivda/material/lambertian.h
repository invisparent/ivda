/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */
 
 
#ifndef IVDA_MATERIAL_LAMBERTIAN_H
#define IVDA_MATERIAL_LAMBERTIAN_H


#include "./material.h"
#include "../spectrum/spectrum.h"
#include "../texture/texture.h"


typedef struct ivda_lambertian {
    ivda_material base;
    const ivda_texture* tex;
} ivda_lambertian;


void
ivda_lambertian_init(
    ivda_lambertian *self,
    const ivda_texture *texture
);

ivda_material_property_t
ivda_lambertian_property(
    const ivda_lambertian *self
);

ivda_material_generate_result
ivda_lambertian_generate(
    const ivda_lambertian *self,
    const ivda_ray *ray,
    const ivda_shape_intersect_result *intersect
);

ivda_basic_spectrum
ivda_lambertian_interact(
    const ivda_lambertian *self,
    const ivda_ray *in,
    const ivda_shape_intersect_result *intersect,
    const ivda_ray *out,
    const ivda_basic_spectrum *input
);


#endif
