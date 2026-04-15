/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include <math.h>

#include "ivs/core.h"

#include "ivda/spectrum/cie.h"


static const ivda_fp ivda_static_cie_1931_xyz_2deg_data[471][3] = {
#include "./cie_1931_xyz_2deg"
};


ivda_fp
ivda_cie_1931_xyz_2deg(
    const ivda_fp lambda,
    const unsigned index
) {
    ivs_assert(index < 3);
    ivs_hint(ivda_spectrum_lambda_valid(lambda));
    if (!ivda_spectrum_lambda_valid(lambda))
        return ivda_fp_make(0);
    if (lambda < ivda_fp_make(IVDA_SPECTRUM_CIE_CIE_1931_LOWER) || lambda > ivda_fp_make(IVDA_SPECTRUM_CIE_CIE_1931_UPPER))
        return ivda_fp_make(0);
    const unsigned base = ivs_inline_restrict(360, 829, (unsigned) lambda);
    const ivda_fp remainder = lambda - (ivda_fp) base;
    return ivs_inline_lerp(ivda_static_cie_1931_xyz_2deg_data[base - 360][index],
                           ivda_static_cie_1931_xyz_2deg_data[base - 360 + 1][index],
                           remainder);
}

ivda_matrix_3_1
ivda_cie_1931_xyz_from_spectrum(
    const ivda_spectrum *const spec,
    const unsigned spb
) {
    ivs_assert(spec);
    ivs_assert(ivda_spectrum_sampling_res_legal(spb));
    const ivda_fp step = IVDA_SPECTRUM_BASIC_WAVELENGTH_PER_SLOT / (ivda_fp) spb;
    const ivda_fp beg = ivda_fp_make(ivs_inline_max(IVDA_SPECTRUM_CIE_CIE_1931_LOWER, IVDA_SPECTRUM_LOWER));
    const ivda_fp end = ivda_fp_make(ivs_inline_min(IVDA_SPECTRUM_CIE_CIE_1931_UPPER, IVDA_SPECTRUM_UPPER));
    const unsigned loop = (unsigned) ((end - beg) / step);
    ivda_fp r[3];
    ivda_matrix_3_1 ret;
    ivda_matrix_3_1_set(&ret, ivda_fp_make(0));
    for (unsigned t = 0; t < loop; ++t) {
        const ivda_fp pos = beg + ivda_fp_make(t) * step;
        const ivda_fp y = ivda_spectrum_samp(spec, pos);
        for (unsigned k = 0; k < 3; ++k)
            r[k] = ivda_cie_1931_xyz_2deg(pos, k) * y;
        for (unsigned k = 0; k < 3; ++k)
            ivda_matrix_3_1_at_set(&ret, k, 0, ivda_matrix_3_1_at(&ret, k, 0) + r[k] / ivda_fp_make(loop));
    }
    return ret;
}


/**
 * Reference:
 * http://brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
 *   by Bruce Justin Lindbloom
 */


/**
 * We may need LTO here, to initialize the matrix.
 * In C, it cannot be constexpr...
 */

ivda_matrix_3_1
ivda_cie_1931_xyz_from_adobe(
    const ivda_matrix_3_1 *const input
) {
    ivs_assert(input);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_matrix_3_1_at(input, 0, 0),,
                                     ivda_matrix_3_1_at(input, 1, 0),,
                                     ivda_matrix_3_1_at(input, 2, 0),
                                     ivs));
    ivs_hint(IVS_MMP_CONJUNCTION_X(ivda_inline_is_normalized, &&,,
                                   ivda_matrix_3_1_at(input, 0, 0),,
                                   ivda_matrix_3_1_at(input, 1, 0),,
                                   ivda_matrix_3_1_at(input, 2, 0),
                                   ivs));
    ivda_matrix_3_3 m;
    ivda_matrix_3_3_at_set(&m, 0, 0, ivda_fp_make(0.5767309));
    ivda_matrix_3_3_at_set(&m, 0, 1, ivda_fp_make(0.1855540));
    ivda_matrix_3_3_at_set(&m, 0, 2, ivda_fp_make(0.1881852));
    ivda_matrix_3_3_at_set(&m, 1, 0, ivda_fp_make(0.2973769));
    ivda_matrix_3_3_at_set(&m, 1, 1, ivda_fp_make(0.6273491));
    ivda_matrix_3_3_at_set(&m, 1, 2, ivda_fp_make(0.0752741));
    ivda_matrix_3_3_at_set(&m, 2, 0, ivda_fp_make(0.0270343));
    ivda_matrix_3_3_at_set(&m, 2, 1, ivda_fp_make(0.0706872));
    ivda_matrix_3_3_at_set(&m, 2, 2, ivda_fp_make(0.9911085));
    return ivda_matrix_3_3_1_mul(&m, input);
}

ivda_matrix_3_1
ivda_cie_1931_xyz_to_adobe(
    const ivda_matrix_3_1 *const input
) {
    ivs_assert(input);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_matrix_3_1_at(input, 0, 0),,
                                     ivda_matrix_3_1_at(input, 1, 0),,
                                     ivda_matrix_3_1_at(input, 2, 0),
                                     ivs));
    ivs_hint(IVS_MMP_CONJUNCTION_X(ivda_inline_is_normalized, &&,,
                                   ivda_matrix_3_1_at(input, 0, 0),,
                                   ivda_matrix_3_1_at(input, 1, 0),,
                                   ivda_matrix_3_1_at(input, 2, 0),
                                   ivs));
    ivda_matrix_3_3 m;
    ivda_matrix_3_3_at_set(&m, 0, 0, ivda_fp_make(2.0413690));
    ivda_matrix_3_3_at_set(&m, 0, 1, ivda_fp_make(-0.5649464));
    ivda_matrix_3_3_at_set(&m, 0, 2, ivda_fp_make(-0.3446944));
    ivda_matrix_3_3_at_set(&m, 1, 0, ivda_fp_make(-0.9692660));
    ivda_matrix_3_3_at_set(&m, 1, 1, ivda_fp_make(1.8760108));
    ivda_matrix_3_3_at_set(&m, 1, 2, ivda_fp_make(0.0415560));
    ivda_matrix_3_3_at_set(&m, 2, 0, ivda_fp_make(0.0134474));
    ivda_matrix_3_3_at_set(&m, 2, 1, ivda_fp_make(-0.1183897));
    ivda_matrix_3_3_at_set(&m, 2, 2, ivda_fp_make(1.0154096));
    return ivda_matrix_3_3_1_mul(&m, input);
}

ivda_matrix_3_1
ivda_cie_1931_xyz_from_srgb(
    const ivda_matrix_3_1 *const input
) {
    ivs_assert(input);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_matrix_3_1_at(input, 0, 0),,
                                     ivda_matrix_3_1_at(input, 1, 0),,
                                     ivda_matrix_3_1_at(input, 2, 0),
                                     ivs));
    ivs_hint(IVS_MMP_CONJUNCTION_X(ivda_inline_is_normalized, &&,,
                                   ivda_matrix_3_1_at(input, 0, 0),,
                                   ivda_matrix_3_1_at(input, 1, 0),,
                                   ivda_matrix_3_1_at(input, 2, 0),
                                   ivs));
    ivda_matrix_3_3 m;
    ivda_matrix_3_3_at_set(&m, 0, 0, ivda_fp_make(0.4124564));
    ivda_matrix_3_3_at_set(&m, 0, 1, ivda_fp_make(0.3575761));
    ivda_matrix_3_3_at_set(&m, 0, 2, ivda_fp_make(0.1804375));
    ivda_matrix_3_3_at_set(&m, 1, 0, ivda_fp_make(0.2126729));
    ivda_matrix_3_3_at_set(&m, 1, 1, ivda_fp_make(0.7151522));
    ivda_matrix_3_3_at_set(&m, 1, 2, ivda_fp_make(0.0721750));
    ivda_matrix_3_3_at_set(&m, 2, 0, ivda_fp_make(0.0193339));
    ivda_matrix_3_3_at_set(&m, 2, 1, ivda_fp_make(0.1191920));
    ivda_matrix_3_3_at_set(&m, 2, 2, ivda_fp_make(0.9503041));
    return ivda_matrix_3_3_1_mul(&m, input);
}

ivda_matrix_3_1
ivda_cie_1931_xyz_to_srgb(
    const ivda_matrix_3_1 *const input
) {
    ivs_assert(input);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_matrix_3_1_at(input, 0, 0),,
                                     ivda_matrix_3_1_at(input, 1, 0),,
                                     ivda_matrix_3_1_at(input, 2, 0),
                                     ivs));
    ivs_hint(IVS_MMP_CONJUNCTION_X(ivda_inline_is_normalized, &&,,
                                   ivda_matrix_3_1_at(input, 0, 0),,
                                   ivda_matrix_3_1_at(input, 1, 0),,
                                   ivda_matrix_3_1_at(input, 2, 0),
                                   ivs));
    ivda_matrix_3_3 m;
    ivda_matrix_3_3_at_set(&m, 0, 0, ivda_fp_make(3.2404542));
    ivda_matrix_3_3_at_set(&m, 0, 1, ivda_fp_make(-1.5371385));
    ivda_matrix_3_3_at_set(&m, 0, 2, ivda_fp_make(-0.4985314));
    ivda_matrix_3_3_at_set(&m, 1, 0, ivda_fp_make(-0.9692660));
    ivda_matrix_3_3_at_set(&m, 1, 1, ivda_fp_make(1.8760108));
    ivda_matrix_3_3_at_set(&m, 1, 2, ivda_fp_make(0.0415560));
    ivda_matrix_3_3_at_set(&m, 2, 0, ivda_fp_make(0.0556434));
    ivda_matrix_3_3_at_set(&m, 2, 1, ivda_fp_make(-0.2040259));
    ivda_matrix_3_3_at_set(&m, 2, 2, ivda_fp_make(1.0572252));
    return ivda_matrix_3_3_1_mul(&m, input);
}

ivda_matrix_3_1
ivda_cie_1931_xyz_from_cie_1931_xyy(
    const ivda_matrix_3_1 *const input
) {
    ivs_assert(input);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_matrix_3_1_at(input, 0, 0),,
                                     ivda_matrix_3_1_at(input, 1, 0),,
                                     ivda_matrix_3_1_at(input, 2, 0),
                                     ivs));
    ivs_hint(IVS_MMP_CONJUNCTION_X(ivda_inline_is_normalized, &&,,
                                   ivda_matrix_3_1_at(input, 0, 0),,
                                   ivda_matrix_3_1_at(input, 1, 0),,
                                   ivda_matrix_3_1_at(input, 2, 0),
                                   ivs));
    const ivda_fp x = ivda_matrix_3_1_at(input, 0, 0);
    const ivda_fp y = ivda_matrix_3_1_at(input, 1, 0);
    const ivda_fp z = ivda_matrix_3_1_at(input, 2, 0);
    ivda_matrix_3_1 ret;
    if (ivda_fp_approx(ivda_fp_make(0), y)) {
        ivda_matrix_3_1_set(&ret, ivda_fp_make(0));
        return ret;
    }
    ivda_matrix_3_1_at_set(&ret, 0, 0, x * z / y);
    ivda_matrix_3_1_at_set(&ret, 1, 0, z);
    ivda_matrix_3_1_at_set(&ret, 2, 0, (ivda_fp_make(1) - x - y) * z / y);
    return ret;
}

ivda_matrix_3_1
ivda_cie_1931_xyz_to_cie_1931_xyy(
    const ivda_matrix_3_1 *const input
) {
    ivs_assert(input);
    ivs_assert(IVS_MMP_CONJUNCTION_X(isfinite, &&,,
                                     ivda_matrix_3_1_at(input, 0, 0),,
                                     ivda_matrix_3_1_at(input, 1, 0),,
                                     ivda_matrix_3_1_at(input, 2, 0),
                                     ivs));
    ivs_hint(IVS_MMP_CONJUNCTION_X(ivda_inline_is_normalized, &&,,
                                   ivda_matrix_3_1_at(input, 0, 0),,
                                   ivda_matrix_3_1_at(input, 1, 0),,
                                   ivda_matrix_3_1_at(input, 2, 0),
                                   ivs));
    const ivda_fp x = ivda_matrix_3_1_at(input, 0, 0);
    const ivda_fp y = ivda_matrix_3_1_at(input, 1, 0);
    const ivda_fp z = ivda_matrix_3_1_at(input, 2, 0);
    const ivda_fp d = x + y + z;
    ivda_matrix_3_1 ret;
    if (ivda_fp_approx(ivda_fp_make(0), d)) {
        // D65 white point
        ivda_matrix_3_1_at_set(&ret, 0, 0, ivda_fp_make(0.31271));
        ivda_matrix_3_1_at_set(&ret, 1, 0, ivda_fp_make(0.32902));
    } else {
        ivda_matrix_3_1_at_set(&ret, 0, 0, x / (x + y + z));
        ivda_matrix_3_1_at_set(&ret, 1, 0, y / (x + y + z));
    }
    ivda_matrix_3_1_at_set(&ret, 2, 0, y);
    return ret;
}
