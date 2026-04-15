/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include "ivs/core.h"

#include "ivda/texture/texture.h"


ivda_basic_spectrum
ivda_texture_data(
    const ivda_texture *const self,
    const ivda_point_3 *const pos,
    const ivda_fp u,
    const ivda_fp v
) {
    ivs_assert(self && pos);
    return self->vp->data(self, pos, u, v);
}
