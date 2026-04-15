/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include <math.h>

#include "ivs/core.h"

#include "ivda/vector.h"


#define IVDA_VECTOR_MAKE_IMPL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _make ( \
        IVS_MMP_EXCAT(IVS_MMP_LOWER_ARGMAKE_, dim) (const ivda_fp) \
    ) { \
        const ivda_vector_ ## dim ret = { IVS_MMP_EXCAT(IVS_MMP_LOWER_, dim) }; \
        return ret; \
    }

IVS_MMP_1(IVDA_VECTOR_MAKE_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_SET_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _set ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivda_matrix_ ## dim ## _1_set (&self->dat, val); \
    }

IVS_MMP_1(IVDA_VECTOR_SET_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_AT_IMPL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _at ( \
        const ivda_vector_ ## dim *const self, \
        const unsigned i \
    ) { \
        ivs_assert(self); \
        ivs_assert(i < dim); \
        return ivda_matrix_ ## dim ## _1_at (&self->dat, i, 1); \
    }

IVS_MMP_1(IVDA_VECTOR_AT_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_AT_SET_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _at_set ( \
        ivda_vector_ ## dim *const self, \
        const unsigned i, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivs_assert(i < dim); \
        ivda_matrix_ ## dim ## _1_at_set (&self->dat, i, 1, val); \
    }

IVS_MMP_1(IVDA_VECTOR_AT_SET_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_ADD_EQUAL_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _add_equal ( \
        ivda_vector_ ## dim *const self, \
        const ivda_vector_ ## dim *const rhs \
    ) { \
        ivs_assert(self && rhs); \
        ivda_matrix_ ## dim ## _1_add_equal (&self->dat, &rhs->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_ADD_EQUAL_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_SUB_EQUAL_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _sub_equal ( \
        ivda_vector_ ## dim *const self, \
        const ivda_vector_ ## dim *const rhs \
    ) { \
        ivs_assert(self && rhs); \
        ivda_matrix_ ## dim ## _1_sub_equal (&self->dat, &rhs->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_SUB_EQUAL_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_NEG_EQUAL_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _neg_equal ( \
    ivda_vector_ ## dim *const self \
    ) { \
        ivs_assert(self); \
        ivda_matrix_ ## dim ## _1_neg_equal (&self->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_NEG_EQUAL_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_HADAMARD_EQUAL_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _hadamard_equal ( \
        ivda_vector_ ## dim *const self, \
        const ivda_vector_ ## dim *const rhs \
    ) { \
        ivs_assert(self && rhs); \
        ivda_matrix_ ## dim ## _1_hadamard_equal (&self->dat, &rhs->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_HADAMARD_EQUAL_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_ADD_SCALAR_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _add_scalar ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivs_assert(isfinite(val)); \
        ivda_matrix_ ## dim ## _1_add_scalar (&self->dat, val); \
    }

IVS_MMP_1(IVDA_VECTOR_ADD_SCALAR_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_SUB_SCALAR_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _sub_scalar ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivs_assert(isfinite(val)); \
        ivda_matrix_ ## dim ## _1_sub_scalar (&self->dat, val); \
    }

IVS_MMP_1(IVDA_VECTOR_SUB_SCALAR_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_MUL_SCALAR_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _mul_scalar ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivs_assert(isfinite(val)); \
        ivda_matrix_ ## dim ## _1_mul_scalar (&self->dat, val); \
    }

IVS_MMP_1(IVDA_VECTOR_MUL_SCALAR_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_DIV_SCALAR_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _div_scalar ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivs_assert(isfinite(val) && !ivda_fp_approx(ivda_fp_make(0), val)); \
        ivda_matrix_ ## dim ## _1_div_scalar (&self->dat, val); \
    }

IVS_MMP_1(IVDA_VECTOR_DIV_SCALAR_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_DATA_IMPL(dim) \
    \
    ivda_matrix_ ## dim ## _1 * \
    ivda_vector_ ## dim ## _data ( \
        ivda_vector_ ## dim *const self \
    ) { \
        ivs_assert(self); \
        return &self->dat; \
    }

IVS_MMP_1(IVDA_VECTOR_DATA_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_ADD_IMPL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _add ( \
        const ivda_vector_ ## dim *const a, \
        const ivda_vector_ ## dim *const b \
    ) { \
        ivs_assert(a && b); \
        ivda_vector_ ## dim ret; \
        ret.dat = ivda_matrix_ ## dim ## _1_add (&a->dat, &b->dat); \
        return ret; \
    }

IVS_MMP_1(IVDA_VECTOR_ADD_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_SUB_IMPL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _sub ( \
        const ivda_vector_ ## dim *const a, \
        const ivda_vector_ ## dim *const b \
    ) { \
        ivs_assert(a && b); \
        ivda_vector_ ## dim ret; \
        ret.dat = ivda_matrix_ ## dim ## _1_sub (&a->dat, &b->dat); \
        return ret; \
    }

IVS_MMP_1(IVDA_VECTOR_SUB_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_NEG_IMPL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _neg ( \
        const ivda_vector_ ## dim *const self \
    ) { \
        ivs_assert(self); \
        ivda_vector_ ## dim ret; \
        ret.dat = ivda_matrix_ ## dim ## _1_neg (&self->dat); \
        return ret; \
    }

IVS_MMP_1(IVDA_VECTOR_NEG_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_HADAMARD_IMPL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _hadamard ( \
        const ivda_vector_ ## dim *const a, \
        const ivda_vector_ ## dim *const b \
    ) { \
        ivs_assert(a && b); \
        ivda_vector_ ## dim ret; \
        ret.dat = ivda_matrix_ ## dim ## _1_hadamard (&a->dat, &b->dat); \
        return ret; \
    }

IVS_MMP_1(IVDA_VECTOR_HADAMARD_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_DOT_IMPL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _dot ( \
        const ivda_vector_ ## dim *const a, \
        const ivda_vector_ ## dim *const b \
    ) { \
        ivs_assert(a && b); \
        return ivda_matrix_ ## dim ## _1_dot (&a->dat, &b->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_DOT_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_L1NORM_IMPL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _l1norm ( \
        const ivda_vector_ ## dim *const self \
    ) { \
        ivs_assert(self); \
        return ivda_matrix_ ## dim ## _1_l1norm (&self->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_L1NORM_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_L2SQ_IMPL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _l2sq ( \
        const ivda_vector_ ## dim *const self \
    ) { \
        ivs_assert(self); \
        return ivda_matrix_ ## dim ## _1_l2sq (&self->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_L2SQ_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_L2NORM_IMPL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _l2norm ( \
        const ivda_vector_ ## dim *const self \
    ) { \
        ivs_assert(self); \
        return ivda_matrix_ ## dim ## _1_l2norm (&self->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_L2NORM_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_COS_IMPL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _cos ( \
        const ivda_vector_ ## dim *const a, \
        const ivda_vector_ ## dim *const b \
    ) { \
        ivs_assert(a && b); \
        return ivda_matrix_ ## dim ## _1_cos (&a->dat, &b->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_COS_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_NORMALIZE_IMPL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _normalize ( \
        ivda_vector_ ## dim *const self \
    ) { \
        ivs_assert(self); \
        ivda_matrix_ ## dim ## _1_normalize (&self->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_NORMALIZE_IMPL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_IS_NORMALIZED_IMPL(dim) \
    \
    _Bool \
    ivda_vector_ ## dim ## _is_normalized ( \
        const ivda_vector_ ## dim *const self \
    ) { \
        ivs_assert(self); \
        return ivda_matrix_ ## dim ## _1_is_normalized (&self->dat); \
    }

IVS_MMP_1(IVDA_VECTOR_IS_NORMALIZED_IMPL, IVDA_VECTOR_ARGLIST)


ivda_vector_3
ivda_vector_cross(
    const ivda_vector_3 *const a,
    const ivda_vector_3 *const b
) {
    ivs_assert(a && b);
    ivda_vector_3 ret;
    ret.dat = ivda_matrix_3_1_cross(&a->dat, &b->dat);
    return ret;
}


ivda_vector_3
ivda_vector_3_to_polar(
    const ivda_vector_3 *const self
) {
    ivs_assert(self);
    const ivda_fp x = ivda_vector_3_at(self, 0);
    const ivda_fp y = ivda_vector_3_at(self, 1);
    const ivda_fp z = ivda_vector_3_at(self, 2);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,, x,, y,, z, ivs));
    const ivda_fp n = ivda_vector_3_l2norm(self);
    if (ivda_fp_approx(ivda_fp_make(0), n))
        return ivda_vector_3_make(ivda_fp_make(0), ivda_fp_make(0), ivda_fp_make(0));
    else
        return ivda_vector_3_make(n, ivda_acos(z / n), ivda_atan(y / x));
}

ivda_vector_3
ivda_vector_3_to_cartesian(
    const ivda_vector_3 *const self
) {
    ivs_assert(self);
    ivda_vector_3 ret;
    const ivda_fp r = ivda_vector_3_at(self, 0);
    const ivda_fp theta = ivda_vector_3_at(self, 1);
    const ivda_fp phi = ivda_vector_3_at(self, 2);
    return ivda_vector_3_make(r * ivda_sin(theta) * ivda_cos(phi),
                              r * ivda_sin(theta) * ivda_sin(phi),
                              r * ivda_cos(theta));
}
