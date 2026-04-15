/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_POINT_H
#define IVDA_POINT_H

#ifdef IVDA_DIM_EXT
#define IVS_MMP_MCSTK_EXT
#endif

#include "ivs/mmp.h"

#include "./core.h"
#include "./matrix.h"
#include "./vector.h"


#ifndef IVDA_DIM_EXT
#define IVDA_POINT_ARGLIST 1, 2, 3, 4
#else
#define IVDA_POINT_ARGLIST 1, 2, 3, 4, 5, 6, 7, 8
#endif


#define IVDA_POINT_STRUCT(dim) \
    \
    typedef struct ivda_point_ ## dim { \
        ivda_matrix_ ## dim ## _1 dat; \
    } ivda_point_ ## dim ;

IVS_MMP_1(IVDA_POINT_STRUCT, IVDA_POINT_ARGLIST)


#define IVDA_POINT_MAKE_DECL(dim) \
    \
    ivda_point_ ## dim \
    ivda_point_ ## dim ## _make ( \
        IVS_MMP_EXCAT(IVS_MMP_LOWER_ARGMAKE_, dim) (const ivda_fp) \
    );

IVS_MMP_1(IVDA_POINT_MAKE_DECL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_SET_DECL(dim) \
    \
    void \
    ivda_point_ ## dim ## _set ( \
        ivda_point_ ## dim *self, \
        const ivda_fp val \
    );

IVS_MMP_1(IVDA_POINT_SET_DECL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_AT_DECL(dim) \
    \
    ivda_fp \
    ivda_point_ ## dim ## _at ( \
        const ivda_point_ ## dim *self, \
        const unsigned i \
    );

IVS_MMP_1(IVDA_POINT_AT_DECL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_AT_SET_DECL(dim) \
    \
    void \
    ivda_point_ ## dim ## _at_set ( \
        ivda_point_ ## dim *self, \
        const unsigned i, \
        const ivda_fp val \
    );

IVS_MMP_1(IVDA_POINT_AT_SET_DECL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_ADD_EQUAL_DECL(dim) \
    \
    void \
    ivda_point_ ## dim ## _add_equal ( \
        ivda_point_ ## dim *self, \
        const ivda_vector_ ## dim *rhs \
    );

IVS_MMP_1(IVDA_POINT_ADD_EQUAL_DECL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_SUB_EQUAL_DECL(dim) \
    \
    void \
    ivda_point_ ## dim ## _sub_equal ( \
        ivda_point_ ## dim *self, \
        const ivda_vector_ ## dim *rhs \
    );

IVS_MMP_1(IVDA_POINT_SUB_EQUAL_DECL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_ADD_DECL(dim) \
    \
    ivda_point_ ## dim \
    ivda_point_ ## dim ## _add ( \
        const ivda_point_ ## dim *point, \
        const ivda_vector_ ## dim *vector \
    );

IVS_MMP_1(IVDA_POINT_ADD_DECL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_SUB_DECL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_point_ ## dim ## _sub ( \
        const ivda_point_ ## dim *a, \
        const ivda_point_ ## dim *b \
    );

IVS_MMP_1(IVDA_POINT_SUB_DECL, IVDA_POINT_ARGLIST)


#endif
