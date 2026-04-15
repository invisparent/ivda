/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_TEXTURE_FIXED_H
#define IVDA_TEXTURE_FIXED_H


#include "./texture.h"


extern const ivda_texture_vtable ivda_fixed_texture_vtable;


typedef struct ivda_fixed_texture {
    ivda_texture base;
    ivda_basic_spectrum dat;
} ivda_fixed_texture;


void
ivda_fixed_texture_init(
    ivda_fixed_texture *self,
    const ivda_spectrum *spectrum,
    unsigned spb,
    unsigned random
);

ivda_basic_spectrum
ivda_fixed_texture_data(
    const ivda_fixed_texture *self,
    const ivda_point_3 *pos,
    ivda_fp u,
    ivda_fp v
);


#endif
