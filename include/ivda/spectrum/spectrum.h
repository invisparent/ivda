/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_SPECTRUM_SPECTRUM_H
#define IVDA_SPECTRUM_SPECTRUM_H


#include "../core.h"


typedef struct ivda_spectrum ivda_spectrum;


typedef struct ivda_spectrum_vtable {

    ivda_fp
    (*const samp)(
        const ivda_spectrum *,
        ivda_fp
    );

} ivda_spectrum_vtable;


struct ivda_spectrum {
    const ivda_spectrum_vtable *vp;
};


typedef enum ivda_spectrum_sampling_res {
    ivda_spectrum_sampling_res_fast = 1,
    ivda_spectrum_sampling_res_balanced = 3,
    ivda_spectrum_sampling_res_accurate = 5,
    ivda_spectrum_sampling_res_placebo = 10
} ivda_spectrum_sampling_res;


_Bool
ivda_spectrum_sampling_res_legal(
    unsigned spb
);


ivda_fp
ivda_spectrum_samp(
    const ivda_spectrum *self,
    ivda_fp lambda
);


extern const ivda_spectrum_vtable ivda_basic_spectrum_vtable;


typedef struct ivda_basic_spectrum {
    ivda_spectrum base;
    ivda_fp dat[IVDA_SPECTRUM_BASIC_ARRAY_LEN];
} ivda_basic_spectrum;


void
ivda_basic_spectrum_init(
    ivda_basic_spectrum *self
);

ivda_fp
ivda_basic_spectrum_samp(
    const ivda_basic_spectrum *self,
    ivda_fp lambda
);

ivda_fp
ivda_basic_spectrum_at(
    const ivda_basic_spectrum *self,
    unsigned index
);

void
ivda_basic_spectrum_at_set(
    ivda_basic_spectrum *self,
    unsigned index,
    ivda_fp val
);

void
ivda_basic_spectrum_mul(
    ivda_basic_spectrum *self,
    ivda_fp x
);


#define IVDA_SPECTRUM_BASIC_SPECTRUM_OP_DECL(name, op) \
    \
    void \
    ivda_basic_spectrum_## name ( \
        ivda_basic_spectrum *self, \
        const ivda_spectrum *rhs, \
        unsigned spb, \
        _Bool random \
    );

IVS_MMP_2(IVDA_SPECTRUM_BASIC_SPECTRUM_OP_DECL,
          copy, =,
          add_equal, +=,
          hadamard_equal, *=
)


#define IVDA_SPECTRUM_SPECTRUM_OP_DECL(name, op) \
    \
    ivda_basic_spectrum \
    ivda_spectrum_ ## name ( \
        const ivda_spectrum *a, \
        const ivda_spectrum *b, \
        unsigned spb, \
        _Bool random \
    );

IVS_MMP_2(IVDA_SPECTRUM_SPECTRUM_OP_DECL,
          add, +,
          hadamard, *
)


#endif
