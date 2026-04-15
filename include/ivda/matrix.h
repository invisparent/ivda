/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_MATRIX_H
#define IVDA_MATRIX_H


/**
 * While introducing ivs/mmp.h:
 * warning: passing no argument for the '...' parameter of a variadic macro is a C23 extension
 *   [-Wvariadic-macro-arguments-omitted]
 */


#include <stdio.h>

#ifdef IVDA_DIM_EXT
#define IVS_MMP_MCSTK_EXT
#endif

#include "ivs/mmp.h"

#include "./core.h"


#ifndef IVDA_DIM_EXT

#define IVDA_MATRIX_ARGLIST_UNARY 1, 2, 3, 4

#define IVDA_MATRIX_ARGLIST_FULL 1, 1, 1, 2, 1, 3, 1, 4, 2, 1, 2, 2, 2, 3, 2, 4, 3, 1, 3, 2, 3, 3, 3, 4, 4, 1, 4, 2, 4, 3, 4, 4

#define IVDA_MATRIX_ARGLIST_SINGLETON  1, 1
#define IVDA_MATRIX_ARGLIST_VECTOR_ROW 1, 2, 1, 3, 1, 4
#define IVDA_MATRIX_ARGLIST_VECTOR_COL 2, 1, 3, 1, 4, 1

#define IVDA_MATRIX_ARGLIST_SQUARE 1, 1, 2, 2, 3, 3, 4, 4

#define IVDA_MATRIX_ARGLIST_TRIPLE \
    \
    1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 4, 1, 2, 1, 1, 2, 2, 1, 2, 3, 1, 2, 4, \
    1, 3, 1, 1, 3, 2, 1, 3, 3, 1, 3, 4, 1, 4, 1, 1, 4, 2, 1, 4, 3, 1, 4, 4, \
    2, 1, 1, 2, 1, 2, 2, 1, 3, 2, 1, 4, 2, 2, 1, 2, 2, 2, 2, 2, 3, 2, 2, 4, \
    2, 3, 1, 2, 3, 2, 2, 3, 3, 2, 3, 4, 2, 4, 1, 2, 4, 2, 2, 4, 3, 2, 4, 4, \
    3, 1, 1, 3, 1, 2, 3, 1, 3, 3, 1, 4, 3, 2, 1, 3, 2, 2, 3, 2, 3, 3, 2, 4, \
    3, 3, 1, 3, 3, 2, 3, 3, 3, 3, 3, 4, 3, 4, 1, 3, 4, 2, 3, 4, 3, 3, 4, 4, \
    4, 1, 1, 4, 1, 2, 4, 1, 3, 4, 1, 4, 4, 2, 1, 4, 2, 2, 4, 2, 3, 4, 2, 4, \
    4, 3, 1, 4, 3, 2, 4, 3, 3, 4, 3, 4, 4, 4, 1, 4, 4, 2, 4, 4, 3, 4, 4, 4


#else


#define IVDA_MATRIX_ARGLIST_UNARY 1, 2, 3, 4, 5, 6, 7, 8

#define IVDA_MATRIX_ARGLIST_FULL \
    \
    1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, \
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, \
    3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7, 3, 8, \
    4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, 6, 4, 7, 4, 8, \
    5, 1, 5, 2, 5, 3, 5, 4, 5, 5, 5, 6, 5, 7, 5, 8, \
    6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 6, 6, 6, 7, 6, 8, \
    7, 1, 7, 2, 7, 3, 7, 4, 7, 5, 7, 6, 7, 7, 7, 8, \
    8, 1, 8, 2, 8, 3, 8, 4, 8, 5, 8, 6, 8, 7, 8, 8

#define IVDA_MATRIX_ARGLIST_SINGLETON  1, 1
#define IVDA_MATRIX_ARGLIST_VECTOR_ROW 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8
#define IVDA_MATRIX_ARGLIST_VECTOR_COL 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 1

#define IVDA_MATRIX_ARGLIST_SQUARE 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8

#define IVDA_MATRIX_ARGLIST_TRIPLE \
    \
    1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 4, 1, 1, 5, 1, 1, 6, 1, 1, 7, 1, 1, 8, \
    1, 2, 1, 1, 2, 2, 1, 2, 3, 1, 2, 4, 1, 2, 5, 1, 2, 6, 1, 2, 7, 1, 2, 8, \
    1, 3, 1, 1, 3, 2, 1, 3, 3, 1, 3, 4, 1, 3, 5, 1, 3, 6, 1, 3, 7, 1, 3, 8, \
    1, 4, 1, 1, 4, 2, 1, 4, 3, 1, 4, 4, 1, 4, 5, 1, 4, 6, 1, 4, 7, 1, 4, 8, \
    1, 5, 1, 1, 5, 2, 1, 5, 3, 1, 5, 4, 1, 5, 5, 1, 5, 6, 1, 5, 7, 1, 5, 8, \
    1, 6, 1, 1, 6, 2, 1, 6, 3, 1, 6, 4, 1, 6, 5, 1, 6, 6, 1, 6, 7, 1, 6, 8, \
    1, 7, 1, 1, 7, 2, 1, 7, 3, 1, 7, 4, 1, 7, 5, 1, 7, 6, 1, 7, 7, 1, 7, 8, \
    1, 8, 1, 1, 8, 2, 1, 8, 3, 1, 8, 4, 1, 8, 5, 1, 8, 6, 1, 8, 7, 1, 8, 8, \
    2, 1, 1, 2, 1, 2, 2, 1, 3, 2, 1, 4, 2, 1, 5, 2, 1, 6, 2, 1, 7, 2, 1, 8, \
    2, 2, 1, 2, 2, 2, 2, 2, 3, 2, 2, 4, 2, 2, 5, 2, 2, 6, 2, 2, 7, 2, 2, 8, \
    2, 3, 1, 2, 3, 2, 2, 3, 3, 2, 3, 4, 2, 3, 5, 2, 3, 6, 2, 3, 7, 2, 3, 8, \
    2, 4, 1, 2, 4, 2, 2, 4, 3, 2, 4, 4, 2, 4, 5, 2, 4, 6, 2, 4, 7, 2, 4, 8, \
    2, 5, 1, 2, 5, 2, 2, 5, 3, 2, 5, 4, 2, 5, 5, 2, 5, 6, 2, 5, 7, 2, 5, 8, \
    2, 6, 1, 2, 6, 2, 2, 6, 3, 2, 6, 4, 2, 6, 5, 2, 6, 6, 2, 6, 7, 2, 6, 8, \
    2, 7, 1, 2, 7, 2, 2, 7, 3, 2, 7, 4, 2, 7, 5, 2, 7, 6, 2, 7, 7, 2, 7, 8, \
    2, 8, 1, 2, 8, 2, 2, 8, 3, 2, 8, 4, 2, 8, 5, 2, 8, 6, 2, 8, 7, 2, 8, 8, \
    3, 1, 1, 3, 1, 2, 3, 1, 3, 3, 1, 4, 3, 1, 5, 3, 1, 6, 3, 1, 7, 3, 1, 8, \
    3, 2, 1, 3, 2, 2, 3, 2, 3, 3, 2, 4, 3, 2, 5, 3, 2, 6, 3, 2, 7, 3, 2, 8, \
    3, 3, 1, 3, 3, 2, 3, 3, 3, 3, 3, 4, 3, 3, 5, 3, 3, 6, 3, 3, 7, 3, 3, 8, \
    3, 4, 1, 3, 4, 2, 3, 4, 3, 3, 4, 4, 3, 4, 5, 3, 4, 6, 3, 4, 7, 3, 4, 8, \
    3, 5, 1, 3, 5, 2, 3, 5, 3, 3, 5, 4, 3, 5, 5, 3, 5, 6, 3, 5, 7, 3, 5, 8, \
    3, 6, 1, 3, 6, 2, 3, 6, 3, 3, 6, 4, 3, 6, 5, 3, 6, 6, 3, 6, 7, 3, 6, 8, \
    3, 7, 1, 3, 7, 2, 3, 7, 3, 3, 7, 4, 3, 7, 5, 3, 7, 6, 3, 7, 7, 3, 7, 8, \
    3, 8, 1, 3, 8, 2, 3, 8, 3, 3, 8, 4, 3, 8, 5, 3, 8, 6, 3, 8, 7, 3, 8, 8, \
    4, 1, 1, 4, 1, 2, 4, 1, 3, 4, 1, 4, 4, 1, 5, 4, 1, 6, 4, 1, 7, 4, 1, 8, \
    4, 2, 1, 4, 2, 2, 4, 2, 3, 4, 2, 4, 4, 2, 5, 4, 2, 6, 4, 2, 7, 4, 2, 8, \
    4, 3, 1, 4, 3, 2, 4, 3, 3, 4, 3, 4, 4, 3, 5, 4, 3, 6, 4, 3, 7, 4, 3, 8, \
    4, 4, 1, 4, 4, 2, 4, 4, 3, 4, 4, 4, 4, 4, 5, 4, 4, 6, 4, 4, 7, 4, 4, 8, \
    4, 5, 1, 4, 5, 2, 4, 5, 3, 4, 5, 4, 4, 5, 5, 4, 5, 6, 4, 5, 7, 4, 5, 8, \
    4, 6, 1, 4, 6, 2, 4, 6, 3, 4, 6, 4, 4, 6, 5, 4, 6, 6, 4, 6, 7, 4, 6, 8, \
    4, 7, 1, 4, 7, 2, 4, 7, 3, 4, 7, 4, 4, 7, 5, 4, 7, 6, 4, 7, 7, 4, 7, 8, \
    4, 8, 1, 4, 8, 2, 4, 8, 3, 4, 8, 4, 4, 8, 5, 4, 8, 6, 4, 8, 7, 4, 8, 8, \
    5, 1, 1, 5, 1, 2, 5, 1, 3, 5, 1, 4, 5, 1, 5, 5, 1, 6, 5, 1, 7, 5, 1, 8, \
    5, 2, 1, 5, 2, 2, 5, 2, 3, 5, 2, 4, 5, 2, 5, 5, 2, 6, 5, 2, 7, 5, 2, 8, \
    5, 3, 1, 5, 3, 2, 5, 3, 3, 5, 3, 4, 5, 3, 5, 5, 3, 6, 5, 3, 7, 5, 3, 8, \
    5, 4, 1, 5, 4, 2, 5, 4, 3, 5, 4, 4, 5, 4, 5, 5, 4, 6, 5, 4, 7, 5, 4, 8, \
    5, 5, 1, 5, 5, 2, 5, 5, 3, 5, 5, 4, 5, 5, 5, 5, 5, 6, 5, 5, 7, 5, 5, 8, \
    5, 6, 1, 5, 6, 2, 5, 6, 3, 5, 6, 4, 5, 6, 5, 5, 6, 6, 5, 6, 7, 5, 6, 8, \
    5, 7, 1, 5, 7, 2, 5, 7, 3, 5, 7, 4, 5, 7, 5, 5, 7, 6, 5, 7, 7, 5, 7, 8, \
    5, 8, 1, 5, 8, 2, 5, 8, 3, 5, 8, 4, 5, 8, 5, 5, 8, 6, 5, 8, 7, 5, 8, 8, \
    6, 1, 1, 6, 1, 2, 6, 1, 3, 6, 1, 4, 6, 1, 5, 6, 1, 6, 6, 1, 7, 6, 1, 8, \
    6, 2, 1, 6, 2, 2, 6, 2, 3, 6, 2, 4, 6, 2, 5, 6, 2, 6, 6, 2, 7, 6, 2, 8, \
    6, 3, 1, 6, 3, 2, 6, 3, 3, 6, 3, 4, 6, 3, 5, 6, 3, 6, 6, 3, 7, 6, 3, 8, \
    6, 4, 1, 6, 4, 2, 6, 4, 3, 6, 4, 4, 6, 4, 5, 6, 4, 6, 6, 4, 7, 6, 4, 8, \
    6, 5, 1, 6, 5, 2, 6, 5, 3, 6, 5, 4, 6, 5, 5, 6, 5, 6, 6, 5, 7, 6, 5, 8, \
    6, 6, 1, 6, 6, 2, 6, 6, 3, 6, 6, 4, 6, 6, 5, 6, 6, 6, 6, 6, 7, 6, 6, 8, \
    6, 7, 1, 6, 7, 2, 6, 7, 3, 6, 7, 4, 6, 7, 5, 6, 7, 6, 6, 7, 7, 6, 7, 8, \
    6, 8, 1, 6, 8, 2, 6, 8, 3, 6, 8, 4, 6, 8, 5, 6, 8, 6, 6, 8, 7, 6, 8, 8, \
    7, 1, 1, 7, 1, 2, 7, 1, 3, 7, 1, 4, 7, 1, 5, 7, 1, 6, 7, 1, 7, 7, 1, 8, \
    7, 2, 1, 7, 2, 2, 7, 2, 3, 7, 2, 4, 7, 2, 5, 7, 2, 6, 7, 2, 7, 7, 2, 8, \
    7, 3, 1, 7, 3, 2, 7, 3, 3, 7, 3, 4, 7, 3, 5, 7, 3, 6, 7, 3, 7, 7, 3, 8, \
    7, 4, 1, 7, 4, 2, 7, 4, 3, 7, 4, 4, 7, 4, 5, 7, 4, 6, 7, 4, 7, 7, 4, 8, \
    7, 5, 1, 7, 5, 2, 7, 5, 3, 7, 5, 4, 7, 5, 5, 7, 5, 6, 7, 5, 7, 7, 5, 8, \
    7, 6, 1, 7, 6, 2, 7, 6, 3, 7, 6, 4, 7, 6, 5, 7, 6, 6, 7, 6, 7, 7, 6, 8, \
    7, 7, 1, 7, 7, 2, 7, 7, 3, 7, 7, 4, 7, 7, 5, 7, 7, 6, 7, 7, 7, 7, 7, 8, \
    7, 8, 1, 7, 8, 2, 7, 8, 3, 7, 8, 4, 7, 8, 5, 7, 8, 6, 7, 8, 7, 7, 8, 8, \
    8, 1, 1, 8, 1, 2, 8, 1, 3, 8, 1, 4, 8, 1, 5, 8, 1, 6, 8, 1, 7, 8, 1, 8, \
    8, 2, 1, 8, 2, 2, 8, 2, 3, 8, 2, 4, 8, 2, 5, 8, 2, 6, 8, 2, 7, 8, 2, 8, \
    8, 3, 1, 8, 3, 2, 8, 3, 3, 8, 3, 4, 8, 3, 5, 8, 3, 6, 8, 3, 7, 8, 3, 8, \
    8, 4, 1, 8, 4, 2, 8, 4, 3, 8, 4, 4, 8, 4, 5, 8, 4, 6, 8, 4, 7, 8, 4, 8, \
    8, 5, 1, 8, 5, 2, 8, 5, 3, 8, 5, 4, 8, 5, 5, 8, 5, 6, 8, 5, 7, 8, 5, 8, \
    8, 6, 1, 8, 6, 2, 8, 6, 3, 8, 6, 4, 8, 6, 5, 8, 6, 6, 8, 6, 7, 8, 6, 8, \
    8, 7, 1, 8, 7, 2, 8, 7, 3, 8, 7, 4, 8, 7, 5, 8, 7, 6, 8, 7, 7, 8, 7, 8, \
    8, 8, 1, 8, 8, 2, 8, 8, 3, 8, 8, 4, 8, 8, 5, 8, 8, 6, 8, 8, 7, 8, 8, 8

#endif


#define IVDA_MATRIX_STRUCT(row, col) \
    \
    typedef struct ivda_matrix_ ## row ## _ ## col { \
        ivda_fp dat[row][col]; \
    } ivda_matrix_ ## row ## _ ## col ;

IVS_MMP_2(IVDA_MATRIX_STRUCT, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_SET_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _set ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        ivda_fp val \
    );

IVS_MMP_2(IVDA_MATRIX_SET_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_AT_DECL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _at ( \
        const ivda_matrix_ ## row ## _ ## col *self, \
        unsigned i, \
        unsigned j \
    );

IVS_MMP_2(IVDA_MATRIX_AT_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_AT_SET_DECL(row, col) \
\
    void \
    ivda_matrix_ ## row ## _ ## col ## _at_set ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        unsigned i, \
        unsigned j, \
        ivda_fp val \
    );

IVS_MMP_2(IVDA_MATRIX_AT_SET_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_ADD_EQUAL_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _add_equal ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        const ivda_matrix_ ## row ## _ ## col *rhs \
    );

IVS_MMP_2(IVDA_MATRIX_ADD_EQUAL_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_SUB_EQUAL_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _sub_equal ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        const ivda_matrix_ ## row ## _ ## col *rhs \
    );

IVS_MMP_2(IVDA_MATRIX_SUB_EQUAL_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_NEG_EQUAL_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _neg_equal ( \
        ivda_matrix_ ## row ## _ ## col *self \
    );

IVS_MMP_2(IVDA_MATRIX_NEG_EQUAL_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_HADAMARD_EQUAL_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _hadamard_equal ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        const ivda_matrix_ ## row ## _ ## col *rhs \
    );

IVS_MMP_2(IVDA_MATRIX_HADAMARD_EQUAL_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_ADD_SCALAR_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _add_scalar ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        ivda_fp val \
    );

IVS_MMP_2(IVDA_MATRIX_ADD_SCALAR_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_SUB_SCALAR_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _sub_scalar ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        ivda_fp val \
    );

IVS_MMP_2(IVDA_MATRIX_SUB_SCALAR_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_MUL_SCALAR_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _mul_scalar ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        ivda_fp val \
    );

IVS_MMP_2(IVDA_MATRIX_MUL_SCALAR_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_DIV_SCALAR_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _div_scalar ( \
        ivda_matrix_ ## row ## _ ## col *self, \
        ivda_fp val \
    );

IVS_MMP_2(IVDA_MATRIX_DIV_SCALAR_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_ADD_DECL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _add ( \
        const ivda_matrix_ ## row ## _ ## col *a, \
        const ivda_matrix_ ## row ## _ ## col *b \
    );

IVS_MMP_2(IVDA_MATRIX_ADD_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_SUB_DECL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _sub ( \
        const ivda_matrix_ ## row ## _ ## col *a, \
        const ivda_matrix_ ## row ## _ ## col *b \
    );

IVS_MMP_2(IVDA_MATRIX_SUB_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_NEG_DECL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _neg ( \
        const ivda_matrix_ ## row ## _ ## col *self \
    );

IVS_MMP_2(IVDA_MATRIX_NEG_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_HADAMARD_DECL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _hadamard ( \
        const ivda_matrix_ ## row ## _ ## col *a, \
        const ivda_matrix_ ## row ## _ ## col *b \
    );

IVS_MMP_2(IVDA_MATRIX_HADAMARD_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_MUL_DECL(row, com, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## com ## _ ## col ## _mul ( \
        const ivda_matrix_ ## row ## _ ## com *a, \
        const ivda_matrix_ ## com ## _ ## col *b \
    );

IVS_MMP_3(IVDA_MATRIX_MUL_DECL, IVDA_MATRIX_ARGLIST_TRIPLE)


#define IVDA_MATRIX_TRANSPOSE_DECL(row, col) \
    \
    ivda_matrix_ ## col ## _ ## row \
    ivda_matrix_ ## row ## _ ## col ## _transpose ( \
        const ivda_matrix_ ## row ## _ ## col *self \
    );

IVS_MMP_2(IVDA_MATRIX_TRANSPOSE_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_PRINT_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _print ( \
        const ivda_matrix_ ## row ## _ ## col *self, \
        FILE *os \
    );

IVS_MMP_2(IVDA_MATRIX_PRINT_DECL, IVDA_MATRIX_ARGLIST_FULL)


#define IVDA_MATRIX_DOT_DECL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _dot ( \
        const ivda_matrix_ ## row ## _ ## col *a, \
        const ivda_matrix_ ## row ## _ ## col *b \
    );

IVS_MMP_2(IVDA_MATRIX_DOT_DECL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_L1NORM_DECL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _l1norm ( \
        const ivda_matrix_ ## row ## _ ## col *self \
    );

IVS_MMP_2(IVDA_MATRIX_L1NORM_DECL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_L2SQ_DECL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _l2sq ( \
        const ivda_matrix_ ## row ## _ ## col *self \
    );

IVS_MMP_2(IVDA_MATRIX_L2SQ_DECL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_L2NORM_DECL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _l2norm ( \
        const ivda_matrix_ ## row ## _ ## col *self \
    );

IVS_MMP_2(IVDA_MATRIX_L2NORM_DECL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_CROSS_DECL(row, col) \
    \
    ivda_matrix_ ## row ## _ ## col \
    ivda_matrix_ ## row ## _ ## col ## _cross ( \
        const ivda_matrix_ ## row ## _ ## col *a, \
        const ivda_matrix_ ## row ## _ ## col *b \
    );

IVS_MMP_2(IVDA_MATRIX_CROSS_DECL, 1, 3, 3, 1)


#define IVDA_MATRIX_COS_DECL(row, col) \
    \
    ivda_fp \
    ivda_matrix_ ## row ## _ ## col ## _cos ( \
        const ivda_matrix_ ## row ## _ ## col *a, \
        const ivda_matrix_ ## row ## _ ## col *b \
    );

IVS_MMP_2(IVDA_MATRIX_COS_DECL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_NORMALIZE_DECL(row, col) \
    \
    void \
    ivda_matrix_ ## row ## _ ## col ## _normalize ( \
        ivda_matrix_ ## row ## _ ## col *self \
    );

IVS_MMP_2(IVDA_MATRIX_NORMALIZE_DECL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)


#define IVDA_MATRIX_IS_NORMALIZED_DECL(row, col) \
    \
    _Bool \
    ivda_matrix_ ## row ## _ ## col ## _is_normalized ( \
        const ivda_matrix_ ## row ## _ ## col *self \
    );

IVS_MMP_2(IVDA_MATRIX_IS_NORMALIZED_DECL, IVDA_MATRIX_ARGLIST_SINGLETON, IVDA_MATRIX_ARGLIST_VECTOR_ROW, IVDA_MATRIX_ARGLIST_VECTOR_COL)



#endif
