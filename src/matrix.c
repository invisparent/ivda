/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include "ivs/core.h"

#include "ivda/matrix.h"


#define IVDA_MATRIX_SET_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _set ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] = val; \
    }

IVS_MMP_2(IVDA_MATRIX_SET_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_AT_IMPL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _at ( \
        const ivda_matrix_ ## row ## _ ## col *const self, \
        const unsigned i, \
        const unsigned j \
    ) { \
        ivs_assert(self); \
        ivs_assert(i < row); \
        ivs_assert(j < col); \
        return self->dat[i][j]; \
    }

IVS_MMP_2(IVDA_MATRIX_AT_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_AT_SET_IMPL(row, col) \
\
    void \
    ivda_matrix_ ## row ## _ ## col ## _at_set ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const unsigned i, \
        const unsigned j, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        ivs_assert(i < row); \
        ivs_assert(j < col); \
        self->dat[i][j] = val; \
    }

IVS_MMP_2(IVDA_MATRIX_AT_SET_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_ADD_EQUAL_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _add_equal ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const ivda_matrix_ ## row ## _ ## col *const rhs \
    ) { \
        ivs_assert(self && rhs); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] += rhs->dat[i][j]; \
    }

IVS_MMP_2(IVDA_MATRIX_ADD_EQUAL_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_SUB_EQUAL_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _sub_equal ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const ivda_matrix_ ## row ## _ ## col *const rhs \
    ) { \
        ivs_assert(self && rhs); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] -= rhs->dat[i][j]; \
    }

IVS_MMP_2(IVDA_MATRIX_SUB_EQUAL_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_NEG_EQUAL_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _neg_equal ( \
        ivda_matrix_ ## row ## _ ## col *const self \
    ) { \
        ivs_assert(self); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] = -self->dat[i][j]; \
    }

IVS_MMP_2(IVDA_MATRIX_NEG_EQUAL_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_HADAMARD_EQUAL_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _hadamard_equal ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const ivda_matrix_ ## row ## _ ## col *const rhs \
    ) { \
        ivs_assert(self && rhs); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] *= rhs->dat[i][j]; \
    }

IVS_MMP_2(IVDA_MATRIX_HADAMARD_EQUAL_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_ADD_SCALAR_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _add_scalar ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] += val; \
    }

IVS_MMP_2(IVDA_MATRIX_ADD_SCALAR_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_SUB_SCALAR_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _sub_scalar ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] -= val; \
    }

IVS_MMP_2(IVDA_MATRIX_SUB_SCALAR_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_MUL_SCALAR_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _mul_scalar ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] *= val; \
    }

IVS_MMP_2(IVDA_MATRIX_MUL_SCALAR_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_DIV_SCALAR_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _div_scalar ( \
        ivda_matrix_ ## row ## _ ## col *const self, \
        const ivda_fp val \
    ) { \
        ivs_assert(self); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                self->dat[i][j] /= val; \
    }

IVS_MMP_2(IVDA_MATRIX_DIV_SCALAR_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_ADD_IMPL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _add ( \
        const ivda_matrix_ ## row ## _ ## col *const a, \
        const ivda_matrix_ ## row ## _ ## col *const b \
    ) { \
        ivs_assert(a && b); \
        ivda_matrix_ ## row ## _ ## col ret; \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                ivda_matrix_ ## row ## _ ## col ## _at_set (&ret, i, j, \
                    ivda_matrix_ ## row ## _ ## col ## _at (a, i, j) + ivda_matrix_ ## row ## _ ## col ## _at (b, i, j)); \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_ADD_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_SUB_IMPL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _sub ( \
        const ivda_matrix_ ## row ## _ ## col *const a, \
        const ivda_matrix_ ## row ## _ ## col *const b \
    ) { \
        ivs_assert(a && b); \
        ivda_matrix_ ## row ## _ ## col ret; \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                ivda_matrix_ ## row ## _ ## col ## _at_set (&ret, i, j, \
                    ivda_matrix_ ## row ## _ ## col ## _at (a, i, j) - ivda_matrix_ ## row ## _ ## col ## _at (b, i, j)); \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_SUB_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_NEG_IMPL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _neg ( \
        const ivda_matrix_ ## row ## _ ## col *const self \
    ) { \
        ivs_assert(self); \
        ivda_matrix_ ## row ## _ ## col ret; \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                ivda_matrix_ ## row ## _ ## col ## _at_set (&ret, i, j, \
                    - ivda_matrix_ ## row ## _ ## col ## _at (self, i, j) ); \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_NEG_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_HADAMARD_IMPL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _hadamard ( \
        const ivda_matrix_ ## row ## _ ## col *const a, \
        const ivda_matrix_ ## row ## _ ## col *const b \
    ) { \
        ivs_assert(a && b); \
        ivda_matrix_ ## row ## _ ## col ret; \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
            ivda_matrix_ ## row ## _ ## col ## _at_set (&ret, i, j, \
                ivda_matrix_ ## row ## _ ## col ## _at (a, i, j) * ivda_matrix_ ## row ## _ ## col ## _at (b, i, j)); \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_HADAMARD_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_MUL_IMPL(row, com, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## com ## _ ## col ## _mul ( \
        const ivda_matrix_ ## row ## _ ## com *const a, \
        const ivda_matrix_ ## com ## _ ## col *const b \
    ) { \
        ivs_assert(a && b); \
        ivda_matrix_ ## row ## _ ## col ret; \
        ivda_matrix_ ## row ## _ ## col ## _set (&ret, ivda_fp_make(0)); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                for (unsigned k = 0; k < com; ++k) \
                    ivda_matrix_ ## row ## _ ## col ## _at_set (&ret, i, j, \
                        ivda_matrix_ ## row ## _ ## col ## _at (&ret, i, j) + \
                            ivda_matrix_ ## row ## _ ## com ## _at (a, i, k) * ivda_matrix_ ## com ## _ ## col ## _at (b, k, j)); \
        return ret; \
    }

IVS_MMP_3(IVDA_MATRIX_MUL_IMPL, IVDA_MATRIX_ARGLIST_TRIPLE)


#define IVDA_MATRIX_TRANSPOSE_IMPL(row, col) \
    \
    ivda_matrix_ ## col ## _ ## row \
    ivda_matrix_ ## row ## _ ## col ## _transpose ( \
        const ivda_matrix_ ## row ## _ ## col *const self \
    ) { \
        ivs_assert(self); \
        ivda_matrix_ ## col ## _ ## row ret; \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                ivda_matrix_ ## col ## _ ## row ## _at_set (&ret, j, i, ivda_matrix_ ## row ## _ ## col ## _at (self, i, j)); \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_TRANSPOSE_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_PRINT_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _print ( \
        const ivda_matrix_ ## row ## _ ## col *const self, \
        FILE *const os \
    ) { \
        ivs_assert(self && os); \
        for (unsigned i = 0; i < row; ++i) { \
            fputc('[', os); \
            for (unsigned j = 0; j < col; ++j) { \
                fprintf(os, "%f", ivda_matrix_ ## row ## _ ## col ## _at (self, i, j)); \
                if (j != col - 1) \
                    fprintf(os, ", "); \
            } \
            if (i != row - 1) \
                fprintf(os, "]\n"); \
        } \
    }

IVS_MMP_2(IVDA_MATRIX_PRINT_IMPL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_DOT_IMPL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _dot ( \
        const ivda_matrix_ ## row ## _ ## col *const a, \
        const ivda_matrix_ ## row ## _ ## col *const b \
    ) { \
        ivs_static_assert(row == 1 || col == 1); \
        ivs_assert(a && b); \
        ivda_fp ret = ivda_fp_make(0); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                ret += ivda_matrix_ ## row ## _ ## col ## _at (a, i, j) * ivda_matrix_ ## row ## _ ## col ## _at (b, i, j); \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_DOT_IMPL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_L1NORM_IMPL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _l1norm ( \
        const ivda_matrix_ ## row ## _ ## col *const self \
    ) { \
        ivs_static_assert(row == 1 || col == 1); \
        ivs_assert(self); \
        ivda_fp ret = ivda_fp_make(0); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                ret += ivda_matrix_ ## row ## _ ## col ## _at (self, i, j); \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_L1NORM_IMPL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_L2SQ_IMPL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _l2sq ( \
        const ivda_matrix_ ## row ## _ ## col *const self \
    ) { \
        ivs_static_assert(row == 1 || col == 1); \
        ivs_assert(self); \
        ivda_fp ret = ivda_fp_make(0); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) { \
                const ivda_fp x = ivda_matrix_ ## row ## _ ## col ## _at (self, i, j); \
                ret += x * x; \
            } \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_L2SQ_IMPL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_L2NORM_IMPL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _l2norm ( \
        const ivda_matrix_ ## row ## _ ## col *const self \
    ) { \
        ivs_static_assert(row == 1 || col == 1); \
        ivs_assert(self); \
        return ivda_sqrt ( ivda_matrix_ ## row ## _ ## col ## _l2sq (self) ); \
    }

IVS_MMP_2(IVDA_MATRIX_L2NORM_IMPL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_CROSS_IMPL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _cross ( \
        const ivda_matrix_ ## row ## _ ## col *const a, \
        const ivda_matrix_ ## row ## _ ## col *const b \
    ) { \
        ivs_static_assert((row == 1 && col == 3) || (row == 3 && col == 1)); \
        ivs_assert(a && b); \
        ivda_matrix_ ## row ## _ ## col ret; \
        for (unsigned t = 0; t < 3; ++t) { \
            const unsigned u = (t + 1) % 3; \
            const unsigned v = (t + 2) % 3; \
            if (row == 3) \
                ivda_matrix_ ## row ## _ ## col ## _at_set (&ret, t, 0, \
                    ivda_matrix_ ## row ## _ ## col ## _at (a, u, 0) * ivda_matrix_ ## row ## _ ## col ## _at (b, v, 0) - \
                    ivda_matrix_ ## row ## _ ## col ## _at (b, u, 0) * ivda_matrix_ ## row ## _ ## col ## _at (a, v, 0)); \
            else \
                ivda_matrix_ ## row ## _ ## col ## _at_set (&ret, 0, t, \
                    ivda_matrix_ ## row ## _ ## col ## _at (a, 0, u) * ivda_matrix_ ## row ## _ ## col ## _at (b, 0, v) - \
                    ivda_matrix_ ## row ## _ ## col ## _at (b, 0, u) * ivda_matrix_ ## row ## _ ## col ## _at (a, 0, v)); \
        } \
        return ret; \
    }

IVS_MMP_2(IVDA_MATRIX_CROSS_IMPL, 1, 3, 3, 1)


#define IVDA_MATRIX_COS_IMPL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _cos ( \
        const ivda_matrix_ ## row ## _ ## col *const a, \
        const ivda_matrix_ ## row ## _ ## col *const b \
    ) { \
        ivs_static_assert(row == 1 || col == 1); \
        ivs_assert(a && b); \
        return ivda_matrix_ ## row ## _ ## col ## _dot (a, b) / \
            ( ivda_matrix_ ## row ## _ ## col ## _l2norm (a) * ivda_matrix_ ## row ## _ ## col ## _l2norm (b) ); \
    }

IVS_MMP_2(IVDA_MATRIX_COS_IMPL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_NORMALIZE_IMPL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _normalize ( \
        ivda_matrix_ ## row ## _ ## col *const self \
    ) { \
        ivs_static_assert(row == 1 || col == 1); \
        ivs_assert(self); \
        const ivda_fp norm = ivda_matrix_ ## row ## _ ## col ## _l2norm (self); \
        ivs_assert(!ivda_fp_approx(0, norm)); \
        for (unsigned i = 0; i < row; ++i) \
            for (unsigned j = 0; j < col; ++j) \
                ivda_matrix_ ## row ## _ ## col ## _at_set (self, i, j, \
                    ivda_matrix_ ## row ## _ ## col ## _at (self, i, j) * norm); \
    }

IVS_MMP_2(IVDA_MATRIX_NORMALIZE_IMPL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_IS_NORMALIZED_IMPL(row, col) \
    \
    _Bool \
    ivda_matrix_ ## row ## _ ## col ## _is_normalized ( \
        const ivda_matrix_ ## row ## _ ## col *const self \
    ) { \
        ivs_static_assert(row == 1 || col == 1); \
        ivs_assert(self); \
        return ivda_fp_approx( 1, ivda_matrix_ ## row ## _ ## col ## _l2norm (self) ); \
    }

IVS_MMP_2(IVDA_MATRIX_IS_NORMALIZED_IMPL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)
