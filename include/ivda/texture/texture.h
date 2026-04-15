/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_TEXTURE_TEXTURE_H
#define IVDA_TEXTURE_TEXTURE_H


#include "../point.h"
#include "../spectrum/spectrum.h"


typedef struct ivda_texture ivda_texture;


typedef struct ivda_texture_vtable {

    ivda_basic_spectrum
    (*const data)(
        const ivda_texture *,
        const ivda_point_3 *,
        ivda_fp,
        ivda_fp
    );

} ivda_texture_vtable;


struct ivda_texture {
    const ivda_texture_vtable *vp;
};


ivda_basic_spectrum
ivda_texture_data(
    const ivda_texture *self,
    const ivda_point_3 *pos,
    ivda_fp u,
    ivda_fp v
);


#endif
