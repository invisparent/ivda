/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_MATERIAL_MATERIAL_H
#define IVDA_MATERIAL_MATERIAL_H


#include <stdint.h>

#include "../ray.h"
#include "../shape/shape.h"
#include "../spectrum/spectrum.h"


typedef uint32_t ivda_material_property_t;

extern const ivda_material_property_t ivda_material_property_clean;
extern const ivda_material_property_t ivda_material_property_never_generate;
extern const ivda_material_property_t ivda_material_property_helmholtz_reciprocity_violation;
extern const ivda_material_property_t ivda_material_property_pdf_dirac_delta;


typedef struct ivda_material_generate_result {
    ivda_ray ray;
    ivda_fp pdf;
} ivda_material_generate_result;


typedef struct ivda_material ivda_material;


typedef struct ivda_material_vtable {

    ivda_material_property_t
    (*const property)(
        const ivda_material *
    );

    ivda_material_generate_result
    (*const generate)(
        const ivda_material *,
        const ivda_ray *,
        const ivda_shape_intersect_result *
    );

    ivda_basic_spectrum
    (*const interact)(
        const ivda_material *,
        const ivda_ray *,
        const ivda_shape_intersect_result *,
        const ivda_ray *,
        const ivda_basic_spectrum *
    );

} ivda_material_vtable;


struct ivda_material {
    const ivda_material_vtable *vp;
};


ivda_material_property_t
ivda_material_property(
    const ivda_material *material
);

ivda_material_generate_result
ivda_material_generate(
    const ivda_material *material,
    const ivda_ray *in,
    const ivda_shape_intersect_result *intersect
);

ivda_basic_spectrum
ivda_material_interact(
    const ivda_material *material,
    const ivda_ray *in,
    const ivda_shape_intersect_result *intersect,
    const ivda_ray *out,
    const ivda_basic_spectrum *input
);


#endif
