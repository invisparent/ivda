/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include <stdlib.h>

#include "ivs/binary_tree.h"
#include "ivs/core.h"

#include "ivda/shape/bvh.h"


const ivda_shape_vtable ivda_bvh_vtable = {

    .intersect = (ivda_shape_intersect_result(*const)(
    const ivda_shape *,
    const ivda_ray *
    )) ivda_bvh_intersect,

    .bound = (ivda_aabb_3(*const)(
        const ivda_shape *
    )) ivda_bvh_bound

};


void
ivda_bvh_init(
    ivda_bvh *const self
) {
    ivs_assert(self);
    self->base.vp = &ivda_bvh_vtable;
    self->stat = 0;
    ivs_array_list_init(&self->dat);
}

void
ivda_bvh_free(
    const ivda_bvh *const self
) {
    ivs_assert(self);
    ivs_array_list_free(&self->dat, ivda_palloc);
}

void
ivda_bvh_insert(
    ivda_bvh *const self,
    const ivda_shape *const shape
) {
    ivs_assert(self && shape);
    ivs_assert(self->stat == 0);
    ivs_array_list_push_back(&self->dat, sizeof(const ivda_shape *), ivda_palloc, &shape);
}


/**
 * Note:
 *   A bvh node must have two child simultaneously,
 *     or it's ill-formed.
 *   (If there's only one, why not store it in its parent directly?)
 */


typedef struct ivda_static_bvh_node ivda_static_bvh_node;


static
ivda_shape_intersect_result
ivda_static_bvh_node_intersect(
    const ivda_static_bvh_node *self,
    const ivda_ray *ray
);

static
ivda_aabb_3
ivda_static_bvh_node_bound(
    const ivda_static_bvh_node *self
);


static const ivda_shape_vtable ivda_static_bvh_node_vtable = {

    .intersect = (ivda_shape_intersect_result(*const)(
    const ivda_shape *,
    const ivda_ray *
    )) ivda_static_bvh_node_intersect,

    .bound = (ivda_aabb_3(*const)(
        const ivda_shape *
    )) ivda_static_bvh_node_bound

};


struct ivda_static_bvh_node {
    ivda_shape base;
    ivda_aabb_3 bound;
    const ivda_shape *left;
    const ivda_shape *right;
};


static
void
ivda_static_bvh_node_init(
    ivda_static_bvh_node *const self
) {
    self->base.vp = &ivda_static_bvh_node_vtable;
    ivda_aabb_3_init(&self->bound);
    self->left = NULL;
    self->right = NULL;
}

static
ivda_shape_intersect_result
ivda_static_bvh_node_intersect(
    const ivda_static_bvh_node *const self,
    const ivda_ray *const ray
) {
    ivs_assert(self && ray);
    const ivda_aabb_3_intersect_result rb = ivda_aabb_3_intersect(&self->bound, ray);
    if (!rb.intersected) {
        const ivda_shape_intersect_result ret = {
            .intersected = 0
        };
        return ret;
    }
    const ivda_shape_intersect_result ia = ivda_shape_intersect(self->left, ray);
    const ivda_shape_intersect_result ib = ivda_shape_intersect(self->right, ray);
    if (!ia.intersected && !ib.intersected) {
        const ivda_shape_intersect_result ret = {
            .intersected = 0
        };
        return ret;
    } else if (!ia.intersected)
        return ib;
    else if (!ib.intersected)
        return ia;
    else {
        if (ia.t <= ib.t)
            return ia;
        else
            return ib;
    }
}

static
ivda_aabb_3
ivda_static_bvh_node_bound(
    const ivda_static_bvh_node *const self
) {
    ivs_assert(self);
    return self->bound;
}


/**
 * I use SAH method here.
 *
 * The left tree should be taller or equal to the right tree.
 *   (cache-friendly build)
 *
 * Many optimizations can implement here.
 *   But currently, that's not the performance bottleneck.
 *   If you're caring about the time of the construction of the acceleration structure,
 *     why not consider using octree?
 *   So I'd prefer writing code explicitly here.
 */

#define IVDA_SHAPE_BVH_STATIC_BVH_CMP_IMPL(axis, index) \
    \
    static \
    int \
    ivda_static_bvh_cmp_ ## axis ( \
        const void *const a, \
        const void *const b \
    ) { \
        ivs_assert(a && b); \
        const ivda_shape *const pa = *(const ivda_shape *const *) a; \
        const ivda_shape *const pb = *(const ivda_shape *const *) b; \
        const ivda_aabb_3 ba = ivda_shape_bound(pa); \
        const ivda_aabb_3 bb = ivda_shape_bound(pb); \
        const ivda_point_3 ca = ivda_aabb_3_center(&ba); \
        const ivda_point_3 cb = ivda_aabb_3_center(&bb); \
        if (ivda_point_3_at(&ca, index) < ivda_point_3_at(&cb, index)) \
            return -1; \
        else if (ivda_point_3_at(&ca, index) > ivda_point_3_at(&cb, index)) \
            return 1; \
        else \
            return 0; \
    }

IVS_MMP_2(IVDA_SHAPE_BVH_STATIC_BVH_CMP_IMPL,
          x, 0,
          y, 1,
          z, 2)

static
ivda_fp
ivda_static_bvh_sah(
    const ivda_aabb_3 *const ba,
    const size_t na,
    const ivda_aabb_3 *const bb,
    const size_t nb
) {
    ivs_assert(ba && bb);
    ivs_assert(na);
    ivs_assert(nb);
    return ivda_aabb_3_surface_area(ba) * ivda_fp_make(na) + ivda_aabb_3_surface_area(bb) * ivda_fp_make(nb);
}

static
ivs_binary_tree *
ivda_static_bvh_build(
    const ivda_shape **const beg,
    const ivda_shape **const end,
    ivs_binary_tree *const parent
) {
    ivs_assert(beg && end);
    ivs_assert(end - beg >= 1);
    const size_t len = end - beg;
    ivs_binary_tree *const ret = ivs_binary_tree_alloc(sizeof(const ivda_shape *), ivda_palloc);
    const ivda_shape **const p = ivs_binary_tree_data(ret);
    ret->parent = parent;
    if (len == 1) {
        *p = *beg;
        return ret;
    }
    /**
     * Pick up the longest axis to divide.
     */
    ivda_fp axis_len[3][2] = {
        {ivda_fp_inf_pos, ivda_fp_inf_neg},
        {ivda_fp_inf_pos, ivda_fp_inf_neg},
        {ivda_fp_inf_pos, ivda_fp_inf_neg}
    };
    for (const ivda_shape **iter = beg; iter < end; ++iter) {
        const ivda_aabb_3 b = ivda_shape_bound(*iter);
        const ivda_point_3 center = ivda_aabb_3_center(&b);
        for (unsigned t = 0; t < 3; ++t) {
            axis_len[t][0] = ivs_inline_min(axis_len[t][0], ivda_point_3_at(&center, t));
            axis_len[t][1] = ivs_inline_max(axis_len[t][0], ivda_point_3_at(&center, t));
        }
    }
    const ivda_fp axis_diff[3] = {
        axis_len[0][1] - axis_len[0][0],
        axis_len[1][1] - axis_len[1][0],
        axis_len[2][1] - axis_len[2][0]
    };
    if (axis_diff[0] >= axis_diff[1] && axis_diff[0] >= axis_diff[2])
        qsort(beg, len, sizeof(const ivda_shape *), ivda_static_bvh_cmp_x);
    else if (axis_diff[1] >= axis_diff[2])
        qsort(beg, len, sizeof(const ivda_shape *), ivda_static_bvh_cmp_y);
    else
        qsort(beg, len, sizeof(const ivda_shape *), ivda_static_bvh_cmp_z);
    ivda_aabb_3 *const bounds[2] = {
        ivs_allocator_malloc(ivda_palloc, sizeof(ivda_aabb_3) * len),
        ivs_allocator_malloc(ivda_palloc, sizeof(ivda_aabb_3) * len)
    };
    for (size_t t = 0; t < len; ++t) {
        bounds[0][t] = ivda_shape_bound(beg[t]);
        bounds[1][t] = ivda_shape_bound(beg[t]);
    }
    for (size_t t = 0; t < len - 1; ++t)
        bounds[0][t + 1] = ivda_aabb_3_add(&bounds[0][t], &bounds[0][t + 1]);
    for (size_t t = len - 1; t >= 1; --t)
        bounds[1][t - 1] = ivda_aabb_3_add(&bounds[1][t], &bounds[1][t - 1]);
    /**
     * Break before index mpos
     */
    size_t mpos = 1;
    ivda_fp mval = ivda_static_bvh_sah(&bounds[0][0], 1, &bounds[1][1], len - 1);
    for (size_t t = 2; t < len - 1; ++t) {
        const ivda_fp val = ivda_static_bvh_sah(&bounds[0][t - 1], t, &bounds[1][t], len - t);
        if (val < mval) {
            mval = val;
            mpos = t;
        }
    }
    const size_t nl = mpos;
    const size_t nr = len - mpos;
    ivs_assert(nl);
    ivs_assert(nr);
    if (nl >= nr) {
        ret->left = ivda_static_bvh_build(beg, beg + nl, ret);
        ret->right = ivda_static_bvh_build(beg + nl, end, ret);
    } else {
        ret->left = ivda_static_bvh_build(beg + nl, end, ret);
        ret->right = ivda_static_bvh_build(beg, beg + nl, ret);
    }
    return ret;
}

static
size_t
ivda_static_bvh_length(
    const ivs_binary_tree *const self
) {
    ivs_assert(!self || (self->left && self->right));
    if (!self)
        return 0;
    else
        return ivda_static_bvh_length(self->left) + ivda_static_bvh_length(self->right) + 1;
}

static
ivda_shape *
ivda_static_bvh_flat(
    const ivs_binary_tree *const self,
    ivs_array_list *const output,
    size_t *const pos
) {
    ivs_assert(self && output && pos);
    ivda_shape *const p = ivs_binary_tree_data(self);
    if (!self->left) {
        ivs_assert(!self->right);
        ivs_assert(p);
        return p;
    }
    ivs_assert(self->left && self->right);
    ivs_assert(!p);
    const size_t now = (*pos)++;
    ivda_static_bvh_node *const ret = ivs_array_list_at(output, sizeof(ivda_static_bvh_node), now);
    ivda_static_bvh_node_init(ret);
    ret->left = ivda_static_bvh_flat(self->left, output, pos);
    ret->right = ivda_static_bvh_flat(self->right, output, pos);
    const ivda_aabb_3 lb = ivda_shape_bound(ret->left);
    const ivda_aabb_3 rb = ivda_shape_bound(ret->right);
    ret->bound = ivda_aabb_3_add(&lb, &rb);
    return (ivda_shape *) ret;
}

void
ivda_bvh_build(
    ivda_bvh *const self
) {
    ivs_assert(self);
    ivs_assert(self->stat == 0);
    if (ivs_array_list_empty(&self->dat)) {
        self->stat = 1;
        return;
    }
    const size_t flen = ivs_array_list_length(&self->dat, sizeof(const ivda_shape *));
    if (flen == 1) {
        self->stat = 2;
        return;
    }
    const ivda_shape **const base = ivs_array_list_data(&self->dat);
    ivs_binary_tree *const tree = ivda_static_bvh_build(base, base + flen, NULL);
    ivs_array_list_free(&self->dat, ivda_palloc);
    ivs_array_list_init(&self->dat);
    const size_t blen = ivda_static_bvh_length(tree);
    ivs_array_list_resize(&self->dat, sizeof(ivda_static_bvh_node), ivda_palloc, blen);
    size_t pos = 0;
    ivda_static_bvh_flat(tree, &self->dat, &pos);
    ivs_binary_tree_free(tree, ivda_palloc);
    self->stat = 3;
}

ivda_shape_intersect_result
ivda_bvh_intersect(
    const ivda_bvh *const self,
    const ivda_ray *const ray
) {
    ivs_assert(self && ray);
    ivs_assert(self->stat);
    switch (self->stat) {
        case 1:
            const ivda_shape_intersect_result ret = {
                .intersected = 0
            };
            return ret;
        case 2:
            const ivda_shape **const pa = ivs_array_list_front(&self->dat);
            return ivda_shape_intersect(*pa, ray);
        case 3:
            const ivda_static_bvh_node *const p = ivs_array_list_front(&self->dat);
            return ivda_static_bvh_node_intersect(p, ray);
        default:
            ivs_unreachable();
    }
    ivs_unreachable();
}

ivda_aabb_3
ivda_bvh_bound(
    const ivda_bvh *const self
) {
    ivs_assert(self);
    if (ivs_array_list_empty(&self->dat)) {
        ivda_aabb_3 ret;
        ivda_aabb_3_init(&ret);
        return ret;
    } else {
        const ivda_static_bvh_node *const p = ivs_array_list_front(&self->dat);
        return ivda_static_bvh_node_bound(p);
    }
}
