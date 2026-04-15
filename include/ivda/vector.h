/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_VECTOR_H
#define IVDA_VECTOR_H


#ifdef IVDA_DIM_EXT
#define IVS_MMP_MCSTK_EXT
#endif

#include "ivs/mmp.h"

#include "./core.h"
#include "./matrix.h"


#ifndef IVDA_DIM_EXT
#define IVDA_VECTOR_ARGLIST 1, 2, 3, 4
#else
#define IVDA_VECTOR_ARGLIST 1, 2, 3, 4, 5, 6, 7, 8
#endif


#define IVDA_VECTOR_STRUCT(dim) \
    \
    typedef struct ivda_vector_ ## dim { \
        ivda_matrix_ ## dim ## _1 dat; \
    } ivda_vector_ ## dim ;

IVS_MMP_1(IVDA_VECTOR_STRUCT, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_MAKE_DECL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _make ( \
        IVS_MMP_EXCAT(IVS_MMP_LOWER_ARGMAKE_, dim) (const ivda_fp) \
    );

IVS_MMP_1(IVDA_VECTOR_MAKE_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_SET_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _set ( \
        ivda_vector_ ## dim *self, \
        const ivda_fp val \
    );

IVS_MMP_1(IVDA_VECTOR_SET_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_AT_DECL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _at ( \
        const ivda_vector_ ## dim *self, \
        const unsigned i \
    );

IVS_MMP_1(IVDA_VECTOR_AT_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_AT_SET_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _at_set ( \
        ivda_vector_ ## dim *self, \
        const unsigned i, \
        const ivda_fp val \
    );

IVS_MMP_1(IVDA_VECTOR_AT_SET_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_ADD_EQUAL_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _add_equal ( \
        ivda_vector_ ## dim *self, \
        const ivda_vector_ ## dim *rhs \
    );

IVS_MMP_1(IVDA_VECTOR_ADD_EQUAL_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_SUB_EQUAL_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _sub_equal ( \
        ivda_vector_ ## dim *self, \
        const ivda_vector_ ## dim *rhs \
    );

IVS_MMP_1(IVDA_VECTOR_SUB_EQUAL_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_NEG_EQUAL_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _neg_equal ( \
        ivda_vector_ ## dim *self \
    );

IVS_MMP_1(IVDA_VECTOR_NEG_EQUAL_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_HADAMARD_EQUAL_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _hadamard_equal ( \
        ivda_vector_ ## dim *self, \
        const ivda_vector_ ## dim *rhs \
    );

IVS_MMP_1(IVDA_VECTOR_HADAMARD_EQUAL_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_ADD_SCALAR_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _add_scalar ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    );

IVS_MMP_1(IVDA_VECTOR_ADD_SCALAR_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_SUB_SCALAR_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _sub_scalar ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    );

IVS_MMP_1(IVDA_VECTOR_SUB_SCALAR_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_MUL_SCALAR_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _mul_scalar ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    );

IVS_MMP_1(IVDA_VECTOR_MUL_SCALAR_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_DIV_SCALAR_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _div_scalar ( \
        ivda_vector_ ## dim *const self, \
        const ivda_fp val \
    );

IVS_MMP_1(IVDA_VECTOR_DIV_SCALAR_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_DATA_DECL(dim) \
    \
    ivda_matrix_ ## dim ## _1 * \
    ivda_vector_ ## dim ## _data ( \
        ivda_vector_ ## dim *self \
    );

IVS_MMP_1(IVDA_VECTOR_DATA_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_ADD_DECL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _add ( \
        const ivda_vector_ ## dim *a, \
        const ivda_vector_ ## dim *b \
    );

IVS_MMP_1(IVDA_VECTOR_ADD_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_SUB_DECL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _sub ( \
        const ivda_vector_ ## dim *a, \
        const ivda_vector_ ## dim *b \
    );

IVS_MMP_1(IVDA_VECTOR_SUB_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_NEG_DECL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _neg ( \
        const ivda_vector_ ## dim *self \
    );

IVS_MMP_1(IVDA_VECTOR_NEG_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_HADAMARD_DECL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_vector_ ## dim ## _hadamard ( \
        const ivda_vector_ ## dim *a, \
        const ivda_vector_ ## dim *b \
    );

IVS_MMP_1(IVDA_VECTOR_HADAMARD_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_DOT_DECL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _dot ( \
        const ivda_vector_ ## dim *a, \
        const ivda_vector_ ## dim *b \
    );

IVS_MMP_1(IVDA_VECTOR_DOT_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_L1NORM_DECL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _l1norm ( \
        const ivda_vector_ ## dim *self \
    );

IVS_MMP_1(IVDA_VECTOR_L1NORM_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_L2SQ_DECL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _l2sq ( \
        const ivda_vector_ ## dim *self \
    );

IVS_MMP_1(IVDA_VECTOR_L2SQ_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_L2NORM_DECL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _l2norm ( \
        const ivda_vector_ ## dim *self \
    );

IVS_MMP_1(IVDA_VECTOR_L2NORM_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_COS_DECL(dim) \
    \
    ivda_fp \
    ivda_vector_ ## dim ## _cos ( \
        const ivda_vector_ ## dim *a, \
        const ivda_vector_ ## dim *b \
    );

IVS_MMP_1(IVDA_VECTOR_COS_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_NORMALIZE_DECL(dim) \
    \
    void \
    ivda_vector_ ## dim ## _normalize ( \
        ivda_vector_ ## dim *self \
    );

IVS_MMP_1(IVDA_VECTOR_NORMALIZE_DECL, IVDA_VECTOR_ARGLIST)


#define IVDA_VECTOR_IS_NORMALIZED_DECL(dim) \
    \
    _Bool \
    ivda_vector_ ## dim ## _is_normalized ( \
        const ivda_vector_ ## dim *self \
    );

IVS_MMP_1(IVDA_VECTOR_IS_NORMALIZED_DECL, IVDA_VECTOR_ARGLIST)


ivda_vector_3
ivda_vector_cross (
    const ivda_vector_3 *a,
    const ivda_vector_3 *b
);


ivda_vector_3
ivda_vector_3_to_polar(
    const ivda_vector_3 *self
);

ivda_vector_3
ivda_vector_3_to_cartesian(
    const ivda_vector_3 *self
);


#endif
