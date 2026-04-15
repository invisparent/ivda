/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include "ivs/core.h"

#include "ivda/point.h"


#define IVDA_POINT_MAKE_IMPL(dim) \
    \
    ivda_point_ ## dim \
    ivda_point_ ## dim ## _make ( \
        IVS_MMP_EXCAT(IVS_MMP_LOWER_ARGMAKE_, dim) (const ivda_fp) \
    ) { \
        const ivda_point_ ## dim ret = { IVS_MMP_EXCAT(IVS_MMP_LOWER_, dim) }; \
        return ret; \
    }

IVS_MMP_1(IVDA_POINT_MAKE_IMPL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_SET_IMPL(dim) \
    \
    void \
    ivda_point_ ## dim ## _set ( \
        ivda_point_ ## dim *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivda_matrix_ ## dim ## _1_set (&self->dat, val); \
    }

IVS_MMP_1(IVDA_POINT_SET_IMPL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_AT_IMPL(dim) \
    \
    ivda_fp \
    ivda_point_ ## dim ## _at ( \
        const ivda_point_ ## dim *const self, \
        const unsigned i \
    ) { \
        ivs_assert(self); \
        ivs_assert(i < dim); \
        return ivda_matrix_ ## dim ## _1_at (&self->dat, i, 0); \
    }

IVS_MMP_1(IVDA_POINT_AT_IMPL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_AT_SET_IMPL(dim) \
    \
    void \
    ivda_point_ ## dim ## _at_set ( \
        ivda_point_ ## dim *const self, \
        const unsigned i, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivs_assert(i < dim); \
        ivda_matrix_ ## dim ## _1_at_set (&self->dat, i, 0, val); \
    }

IVS_MMP_1(IVDA_POINT_AT_SET_IMPL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_ADD_EQUAL_IMPL(dim) \
    \
    void \
    ivda_point_ ## dim ## _add_equal ( \
        ivda_point_ ## dim *const self, \
        const ivda_vector_ ## dim *const rhs \
    ) { \
        ivs_assert(self && rhs); \
        ivda_matrix_ ## dim ## _1_add_equal (&self->dat, &rhs->dat); \
    }

IVS_MMP_1(IVDA_POINT_ADD_EQUAL_IMPL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_SUB_EQUAL_IMPL(dim) \
    \
    void \
    ivda_point_ ## dim ## _sub_equal ( \
        ivda_point_ ## dim *const self, \
        const ivda_vector_ ## dim *const rhs \
    ) { \
        ivs_assert(self && rhs); \
        ivda_matrix_ ## dim ## _1_sub_equal (&self->dat, &rhs->dat); \
    }

IVS_MMP_1(IVDA_POINT_SUB_EQUAL_IMPL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_ADD_IMPL(dim) \
    \
    ivda_point_ ## dim \
    ivda_point_ ## dim ## _add ( \
        const ivda_point_ ## dim *const point, \
        const ivda_vector_ ## dim *const vector \
    ) { \
        ivs_assert(point && vector); \
        ivda_point_ ## dim ret = *point; \
        ivda_point_ ## dim ## _add_equal (&ret, vector); \
        return ret; \
    }

IVS_MMP_1(IVDA_POINT_ADD_IMPL, IVDA_POINT_ARGLIST)


#define IVDA_POINT_SUB_IMPL(dim) \
    \
    ivda_vector_ ## dim \
    ivda_point_ ## dim ## _sub ( \
        const ivda_point_ ## dim *const a, \
        const ivda_point_ ## dim *const b \
    ) { \
        ivs_assert(a && b); \
        ivda_vector_ ## dim ret; \
        ret.dat = ivda_matrix_ ## dim ## _1_sub (&a->dat, &b->dat); \
        return ret; \
    }

IVS_MMP_1(IVDA_POINT_SUB_IMPL, IVDA_POINT_ARGLIST)
