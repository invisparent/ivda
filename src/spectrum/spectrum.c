/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include <math.h>

#include "ivs/core.h"

#include "ivda/rng.h"
#include "ivda/spectrum/spectrum.h"


_Bool
ivda_spectrum_sampling_res_legal(
    const unsigned spb
) {
    return spb && spb <= 256;
}


ivda_fp
ivda_spectrum_samp(
    const ivda_spectrum *const self,
    const ivda_fp lambda
) {
    ivs_assert(self);
    return self->vp->samp(self, lambda);
}


const ivda_spectrum_vtable ivda_basic_spectrum_vtable = {

    .samp =
    (ivda_fp(*const)(
        const ivda_spectrum *,
        ivda_fp)
    ) ivda_basic_spectrum_samp

};


void
ivda_basic_spectrum_init(
    ivda_basic_spectrum *const self
) {
    ivs_assert(self);
    self->base.vp = &ivda_basic_spectrum_vtable;
    for (unsigned t = 0; t < IVDA_SPECTRUM_BASIC_ARRAY_LEN; ++t)
        self->dat[t] = ivda_fp_make(0);
}

ivda_fp
ivda_basic_spectrum_samp(
    const ivda_basic_spectrum *const self,
    const ivda_fp lambda
) {
    ivs_assert(self);
    ivs_hint(ivda_spectrum_lambda_valid(lambda));
    if (ivs_inline_between_cc(IVDA_SPECTRUM_LOWER, IVDA_SPECTRUM_UPPER, lambda))
        return self->dat[ivs_inline_restrict(0, IVDA_SPECTRUM_BASIC_ARRAY_LEN - 1,
                                             (int) ((lambda - IVDA_SPECTRUM_LOWER) / IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT))];
    else
        return ivda_fp_make(0);
}

ivda_fp
ivda_basic_spectrum_at(
    const ivda_basic_spectrum *const self,
    const unsigned index
) {
    ivs_assert(self);
    ivs_assert(index < IVDA_SPECTRUM_BASIC_ARRAY_LEN);
    return self->dat[index];
}

void
ivda_basic_spectrum_at_set(
    ivda_basic_spectrum *const self,
    const unsigned index,
    const ivda_fp val
) {
    ivs_assert(self);
    ivs_assert(index < IVDA_SPECTRUM_BASIC_ARRAY_LEN);
    ivs_hint(isfinite(val));
    self->dat[index] = val;
}

void
ivda_basic_spectrum_mul(
    ivda_basic_spectrum *const self,
    const ivda_fp x
) {
    ivs_assert(self);
    ivs_assert(isfinite(x));
    for (unsigned t = 0; t < IVDA_SPECTRUM_BASIC_ARRAY_LEN; ++t)
        ivda_basic_spectrum_at_set(self, t, ivda_basic_spectrum_at(self, t) * x);
}


#define IVDA_SPECTRUM_BASIC_SPECTRUM_OP_IMPL(name, op) \
    \
    void \
    ivda_basic_spectrum_## name ( \
        ivda_basic_spectrum *const self, \
        const ivda_spectrum *const rhs, \
        const unsigned spb, \
        const _Bool random \
    ) { \
        ivs_assert(self && rhs); \
        ivs_assert(ivda_spectrum_sampling_res_legal(spb)); \
        if (rhs->vp == &ivda_basic_spectrum_vtable) { \
            const ivda_basic_spectrum *const p = (const ivda_basic_spectrum *) rhs; \
            for (unsigned t = 0; t < IVDA_SPECTRUM_BASIC_ARRAY_LEN; ++t) \
                self->dat[t] op p->dat[t]; \
        } else { \
            if (random) { \
                const ivda_fp cell = IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT / ivda_fp_make(spb); \
                for (unsigned i = 0; i < IVDA_SPECTRUM_BASIC_ARRAY_LEN; ++i) { \
                    const ivda_fp base = ivda_fp_make(i) * IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT; \
                    ivda_fp r = ivda_fp_make(0); \
                    for (unsigned j = 0; j < spb; ++j) { \
                        const ivda_fp pos = base + ivda_fp_make(j) * cell + ivda_rng_uniform(ivda_fp_make(0), cell); \
                        r += ivda_spectrum_samp(rhs, pos) / ivda_fp_make(spb); \
                    } \
                    self->dat[i] op r; \
                } \
            } else { \
                const ivda_fp cell = IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT / ivda_fp_make(spb); \
                for (unsigned i = 0; i < IVDA_SPECTRUM_BASIC_ARRAY_LEN; ++i) { \
                    const ivda_fp base = ivda_fp_make(i) * IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT + cell / ivda_fp_make(2); \
                    ivda_fp r = ivda_fp_make(0); \
                    for (unsigned j = 0; j < spb; ++j) { \
                        const ivda_fp pos = base + ivda_fp_make(j) * cell; \
                        r += ivda_spectrum_samp(rhs, pos) / ivda_fp_make(spb); \
                    } \
                    self->dat[i] op r; \
                } \
            } \
        } \
    }

IVS_MMP_2(IVDA_SPECTRUM_BASIC_SPECTRUM_OP_IMPL,
          copy, =,
          add_equal, +=,
          hadamard_equal, *=
)


#define IVDA_SPECTRUM_SPECTRUM_OP_IMPL(name, op) \
    \
    ivda_basic_spectrum \
    ivda_spectrum_ ## name ( \
        const ivda_spectrum *const a, \
        const ivda_spectrum *const b, \
        const unsigned spb, \
        const _Bool random \
    ) { \
        ivs_assert(a && b); \
        ivs_assert(ivda_spectrum_sampling_res_legal(spb)); \
        ivda_basic_spectrum ret; \
        ivda_basic_spectrum_init(&ret); \
        if (random) { \
            const ivda_fp cell = IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT / ivda_fp_make(spb); \
            for (unsigned i = 0; i < IVDA_SPECTRUM_BASIC_ARRAY_LEN; ++i) { \
                const ivda_fp base = ivda_fp_make(i) * IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT; \
                for (unsigned j = 0; j < spb; ++j) { \
                    const ivda_fp pos = base + ivda_fp_make(j) * cell + ivda_rng_uniform(ivda_fp_make(0), cell); \
                    ret.dat[i] += (ivda_spectrum_samp(a, pos) op ivda_spectrum_samp(b, pos)) / ivda_fp_make(spb); \
                } \
            } \
        } else { \
            const ivda_fp cell = IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT / ivda_fp_make(spb); \
            for (unsigned i = 0; i < IVDA_SPECTRUM_BASIC_ARRAY_LEN; ++i) { \
                const ivda_fp base = ivda_fp_make(i) * IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT + cell / ivda_fp_make(2); \
                for (unsigned j = 0; j < spb; ++j) { \
                    const ivda_fp pos = base + ivda_fp_make(j) * cell; \
                    ret.dat[i] += (ivda_spectrum_samp(a, pos) op ivda_spectrum_samp(b, pos)) / ivda_fp_make(spb); \
                } \
            } \
        } \
        return ret; \
    }

IVS_MMP_2(IVDA_SPECTRUM_SPECTRUM_OP_IMPL,
          add, +,
          hadamard, *
)
