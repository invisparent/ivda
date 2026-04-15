/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include "ivs/core.h"

#include "ivda/material/material.h"


const ivda_material_property_t ivda_material_property_clean = 0;
const ivda_material_property_t ivda_material_property_never_generate = 1u << 0;
const ivda_material_property_t ivda_material_property_helmholtz_reciprocity_violation = 1u << 1;
const ivda_material_property_t ivda_material_property_pdf_dirac_delta = 1u << 2;


ivda_material_property_t
ivda_material_property(
    const ivda_material *const material
) {
    ivs_assert(material);
    return material->vp->property(material);
}

ivda_material_generate_result
ivda_material_generate(
    const ivda_material *const material,
    const ivda_ray *const in,
    const ivda_shape_intersect_result *const intersect
) {
    ivs_assert(!(ivda_material_property(material) & ivda_material_property_never_generate));
    return material->vp->generate(material, in, intersect);
}

ivda_basic_spectrum
ivda_material_interact(
    const ivda_material *const material,
    const ivda_ray *const in,
    const ivda_shape_intersect_result *const intersect,
    const ivda_ray *const out,
    const ivda_basic_spectrum *const input
) {
    ivs_assert(material && in && intersect && out && input);
    return material->vp->interact(material, in, intersect, out, input);
}
