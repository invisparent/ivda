/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include "ivs/core.h"

#include "ivda/mis.h"
#include "ivda/material/lambertian.h"


const ivda_material_vtable ivda_lambertian_vtable = {

    .property = (ivda_material_property_t(*const)(
        const ivda_material *
    )) ivda_lambertian_property,

    .generate = (ivda_material_generate_result(*const)(
        const ivda_material *,
        const ivda_ray *,
        const ivda_shape_intersect_result *
    )) ivda_lambertian_generate,

    .interact = (ivda_basic_spectrum(*const)(
        const ivda_material *,
        const ivda_ray *,
        const ivda_shape_intersect_result *,
        const ivda_ray *,
        const ivda_basic_spectrum *
    )) ivda_lambertian_interact

};


void
ivda_lambertian_init(
    ivda_lambertian *const self,
    const ivda_texture *const texture
) {
    ivs_assert(self && texture);
    self->base.vp = &ivda_lambertian_vtable;
    self->tex = texture;
}

ivda_material_property_t
ivda_lambertian_property(
    const ivda_lambertian *const self
) {
    (void) self;
    ivs_assert(self);
    return ivda_material_property_clean;
}

ivda_material_generate_result
ivda_lambertian_generate(
    const ivda_lambertian *const self,
    const ivda_ray *const ray,
    const ivda_shape_intersect_result *const intersect
) {
    (void) self;
    (void) ray;
    ivs_assert(self && ray && intersect);
    const ivda_mis_result mis = ivda_mis_hemisphere_cos_weighted(&intersect->n);
    ivda_material_generate_result ret;
    ret.pdf = mis.pdf;
    ivda_ray_set(&ret.ray, &intersect->p, &mis.vec);
    ivda_ray_offset(&ret.ray, ivda_ray_d(&ret.ray), ivda_fp_tolerance);
    return ret;
}

ivda_basic_spectrum
ivda_lambertian_interact(
    const ivda_lambertian *const self,
    const ivda_ray *const in,
    const ivda_shape_intersect_result *const intersect,
    const ivda_ray *const out,
    const ivda_basic_spectrum *const input
) {
    (void) out;
    ivs_assert(self && in && intersect && out && input);
    const ivda_fp cos = -ivda_vector_3_dot(&intersect->n, ivda_ray_d(in));
    ivda_basic_spectrum ret = *input;
    const ivda_basic_spectrum albedo = ivda_texture_data(self->tex, &intersect->p, intersect->u, intersect->v);
    ivda_basic_spectrum_hadamard_equal(&ret, (const ivda_spectrum *) &albedo, ivda_spectrum_sampling_res_balanced, 1);
    ivda_basic_spectrum_mul(&ret, cos);
    return ret;
}
