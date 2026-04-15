/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include "ivs/core.h"

#include "ivda/texture/fixed.h"


const ivda_texture_vtable ivda_fixed_texture_vtable = {

    .data = (ivda_basic_spectrum(*const)(
        const ivda_texture *,
        const ivda_point_3 *,
        ivda_fp,
        ivda_fp
    )) ivda_fixed_texture_data

};


void
ivda_fixed_texture_init(
    ivda_fixed_texture *const self,
    const ivda_spectrum *const spectrum,
    const unsigned spb,
    const unsigned random
) {
    ivs_assert(self && spectrum);
    self->base.vp = &ivda_fixed_texture_vtable;
    ivda_basic_spectrum_copy(&self->dat, spectrum, spb, random);
}

ivda_basic_spectrum
ivda_fixed_texture_data(
    const ivda_fixed_texture *const self,
    const ivda_point_3 *const pos,
    const ivda_fp u,
    const ivda_fp v
) {
    ivs_assert(self);
    (void) pos;
    (void) u;
    (void) v;
    return self->dat;
}
