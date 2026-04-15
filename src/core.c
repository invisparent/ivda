/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


/**
 * Clang has some problems on tgmath.
 * So...
 */
// #include <tgmath.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "ivs/core.h"
#include "ivs/mmp.h"

#include "ivda/core.h"


_Bool
ivda_spectrum_lambda_valid(
    const ivda_fp lambda
) {
    return ivs_inline_between_cc(IVDA_SPECTRUM_LOWER, IVDA_SPECTRUM_UPPER, lambda);
}


const ivs_allocator *ivda_palloc;


#define IVDA_CORE_MATH_UNARY_IMPL(op) \
    \
    ivda_fp \
    ivda_ ## op ( \
        const ivda_fp x \
    ) { \
        return _Generic ((x), float: op ## f, double: op ) (x); \
    }

IVS_MMP_1(IVDA_CORE_MATH_UNARY_IMPL,
          sin, cos, tan,
          asin, acos, atan,
          sinh, cosh, tanh,
          exp, exp2, expm1,
          log, log2, log10, log1p,
          sqrt, cbrt,
          ceil, floor, round
)


#define IVDA_CORE_MATH_BINARY_IMPL(op) \
    \
    ivda_fp \
    ivda_ ## op ( \
        const ivda_fp a, \
        const ivda_fp b \
    ) { \
        return _Generic ((a), float: op ## f, double: op ) (a, b); \
    }

IVS_MMP_1(IVDA_CORE_MATH_BINARY_IMPL,
          atan2,
          pow,
          fmod, remainder
)


#define IVDA_CORE_FP_RELATION_IMPL(syn) \
    \
    _Bool \
    ivda_fp_ ## syn ( \
        const ivda_fp target, \
        const ivda_fp x \
    ) { \
        return ivs_inline_ ## syn (target, ivda_fp_tolerance, x); \
    }

IVS_MMP_1(IVDA_CORE_FP_RELATION_IMPL,
          approx,
          approx_less,
          approx_greater,
          strict_less,
          strict_greater
)


_Bool
ivda_fp_strict_between(
    const ivda_fp lb,
    const ivda_fp ub,
    const ivda_fp x
) {
    return ivda_fp_strict_less(ub, x) && ivda_fp_strict_greater(lb, x);
}


void
ivda_init(
    void
) {
    ivda_palloc = ivs_palloc;
}


void
ivda_hint_handler(
    const char *const expr,
    const char *const file,
    const unsigned line,
    const char *const func,
    const char *const extra,
    ...
) {
    fprintf(stderr, "ivda::hint: expr: %s, file: %s:%u in %s\n", expr, file, line, func);
    if (extra) {
        va_list args;
        va_start(args, extra);
        fputs("extra info:\n", stderr);
        vfprintf(stderr, extra, args);
        va_end(args);
        fputc('\n', stderr);
    }
}
