/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#ifndef IVDA_CORE_H
#define IVDA_CORE_H


#include "ivs/memory.h"
#include "ivs/mmp.h"


/**
 * Versions
 */

#define IVDA_VERSION_MAJOR_ESSENTIAL_A "Astrid"
#define IVDA_VERSION_MAJOR_FULL_A      "\"Astrid\" Hofferson-Haddock"

#define IVDA_VERSION_MAJOR_ESSENTIAL_B "Batman"
#define IVDA_VERSION_MAJOR_FULL_B      "\"Batman\""

#define IVDA_VERSION_MAJOR_ESSENTIAL_C "Coco"
#define IVDA_VERSION_MAJOR_FULL_C      "\"Coco\""

#define IVDA_VERSION_MAJOR_ESSENTIAL_D "Darth Vader"
#define IVDA_VERSION_MAJOR_FULL_D      "\"Darth Vader\""

#define IVDA_VERSION_MAJOR_ESSENTIAL_E "Elsa"
#define IVDA_VERSION_MAJOR_FULL_E      "\"Elsa\""

#define IVDA_VERSION_MAJOR_ESSENTIAL_F "Furina"
#define IVDA_VERSION_MAJOR_FULL_F      "\"Furina\" de Fontaine"

#define IVDA_VERSION_MAJOR_ESSENTIAL_G "Gris"
#define IVDA_VERSION_MAJOR_FULL_G      "\"Gris\""

#define IVDA_VERSION_MAJOR_ESSENTIAL_H "Hyposelenia"
#define IVDA_VERSION_MAJOR_FULL_H      "Columbina \"Hyposelenia\""

#define IVDA_VERSION_MAJOR "H"
#define IVDA_VERSION_MAJOR_ESSENTIAL IVDA_VERSION_MAJOR_ESSENTIAL_H
#define IVDA_VERSION_MAJOR_FULL      IVDA_VERSION_MAJOR_FULL_H
#define IVDA_VERSION_MINOR 0
#define IVDA_VERSION_PATCH 0


/**
 * Fp def
 */

#ifndef IVDA_XPREC

typedef float ivda_fp;
#define IVDA_FP_LITERAL "float"
#define ivda_fp_make(expr) ((float) (expr))
#define ivda_fp_tolerance (0x1p-10f)

#else

typedef double ivda_fp;
#define IVDA_FP_LITERAL "double"
#define ivda_fp_make(expr) ((double) (expr))
#define ivda_fp_tolerance (0x1p-20)

#endif


#define ivda_fp_pi ivda_fp_make(3.14159265358979323846264338328)

#define ivda_fp_inf_pos ivda_fp_make(ivda_fp_make(1) / ivda_fp_make(0))
#define ivda_fp_inf_neg ivda_fp_make(ivda_fp_make(-1) / ivda_fp_make(0))

#define ivda_inline_is_normalized(expr) (ivda_fp_make(0) >= (expr) && (expr) <= ivda_fp_make(1))


/**
 * Spectrums
 */


#define IVDA_VISIBLE_WAVELENGTH_LOWER 360
#define IVDA_VISIBLE_WAVELENGTH_UPPER 830

#define IVDA_SPECTRUM_LOWER ivda_fp_make(IVDA_VISIBLE_WAVELENGTH_LOWER)
#define IVDA_SPECTRUM_UPPER ivda_fp_make(IVDA_VISIBLE_WAVELENGTH_UPPER)
#define IVDA_SPECTRUM_BASIC_ARRAY_LEN 47
#define IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT ivda_fp_make((IVDA_SPECTRUM_UPPER - IVDA_SPECTRUM_LOWER) / IVDA_SPECTRUM_BASIC_ARRAY_LEN)


_Bool
ivda_spectrum_lambda_valid(
    ivda_fp lambda
);


/**
 * Alloc
 */

extern const ivs_allocator *ivda_palloc;


/**
 * Basic maths
 */

#define ivda_abs(expr) ((expr) >= ivda_fp_make(0) ? (expr) : -(expr))


#define IVDA_CORE_MATH_UNARY_DECL(op) \
    \
    ivda_fp \
    ivda_ ## op ( \
        ivda_fp x \
    );

IVS_MMP_1(IVDA_CORE_MATH_UNARY_DECL,
          sin, cos, tan,
          asin, acos, atan,
          sinh, cosh, tanh,
          exp, exp2, expm1,
          log, log2, log10, log1p,
          sqrt, cbrt,
          ceil, floor, round
)


#define IVDA_CORE_MATH_BINARY_DECL(op) \
    \
    ivda_fp \
    ivda_ ## op ( \
        ivda_fp a, \
        ivda_fp b \
    );

IVS_MMP_1(IVDA_CORE_MATH_BINARY_DECL,
          atan2,
          pow,
          fmod, remainder
)


#define IVDA_CORE_FP_RELATION_DECL(syn) \
    \
    _Bool \
    ivda_fp_ ## syn ( \
        ivda_fp target, \
        ivda_fp x \
    );

IVS_MMP_1(IVDA_CORE_FP_RELATION_DECL,
          approx,
          approx_less,
          approx_greater,
          strict_less,
          strict_greater
)


_Bool
ivda_fp_strict_between(
    ivda_fp lb,
    ivda_fp ub,
    ivda_fp x
);


/**
 * Init
 */

void
ivda_init(
    void
);


#endif
