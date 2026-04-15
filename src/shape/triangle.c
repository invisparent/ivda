/**
 * Copyright (c) 2026 Chenyi Wang.
 *   (a.k.a. Invisparent, an Art, Computer Science and Mathematics Noob.)
 * SPDX-License-Identifier: LGPL-3.0-only
 */


#include "ivda/shape/triangle.h"


const ivda_shape_vtable ivda_triangle_vtable = {

    .intersect = (ivda_shape_intersect_result(*const)(
        const ivda_shape *,
        const ivda_ray *
    )) ivda_triangle_intersect,

    // .surface_area = (ivda_fp(*const)(
    //     const ivda_shape *
    // )) ivda_triangle_surface_area,

    .bound = (ivda_aabb_3(*const)(
        const ivda_shape *
    )) ivda_triangle_bound

};


void
ivda_triangle_init(
    ivda_triangle *const self
) {
    ivs_assert(self);
    const ivda_point_3 p = ivda_point_3_make(ivda_fp_make(0), ivda_fp_make(0), ivda_fp_make(0));
    ivda_triangle_init_set(self, &p, &p, &p, NULL);
}

void
ivda_triangle_init_set(
    ivda_triangle *const self,
    const ivda_point_3 *const a,
    const ivda_point_3 *const b,
    const ivda_point_3 *const c,
    const ivda_material *const m
) {
    ivs_assert(self && a && b && c);
    self->base.vp = &ivda_triangle_vtable;
    ivda_triangle_set_vert(self, a, b, c);
    ivda_triangle_set_material(self, m);
}

void
ivda_triangle_set_vert(
    ivda_triangle *const self,
    const ivda_point_3 *const a,
    const ivda_point_3 *const b,
    const ivda_point_3 *const c
) {
    ivs_assert(self && a && b && c);
    self->o = *a;
    self->va = ivda_point_3_sub(b, a); // NOLINT
    self->vb = ivda_point_3_sub(c, a);
}

void
ivda_triangle_set_material(
    ivda_triangle *const self,
    const ivda_material *const m
) {
    ivs_assert(self && m);
    self->m = m;
}

ivda_shape_intersect_result
ivda_triangle_intersect(
    const ivda_triangle *const self,
    const ivda_ray *const ray
) {
    ivs_assert(self && ray);
    ivda_shape_intersect_result ret = {
        .intersected = 0
    };
    const ivda_vector_3 sub = ivda_point_3_sub(ivda_ray_o(ray), &self->o);
    const ivda_vector_3 *const ea = &self->va;
    const ivda_vector_3 *const eb = &self->vb;
    const ivda_vector_3 sa = ivda_vector_cross(ivda_ray_d(ray), eb);
    const ivda_vector_3 sb = ivda_vector_cross(&sub, ea);
    const ivda_fp se = ivda_vector_3_dot(&sa, ea);
    const ivda_fp t = ivda_vector_3_dot(&sb, eb) / se;
    const ivda_fp u = ivda_vector_3_dot(&sa, &sub) / se;
    const ivda_fp v = ivda_vector_3_dot(&sb, ivda_ray_d(ray)) / se;
    if (t >= ivda_fp_make(0) && u >= ivda_fp_make(0) && v >= ivda_fp_make(0) && u + v <= ivda_fp_make(1)) {
        ret.p = ivda_ray_target(ray, t);
        ivda_vector_3 n = ivda_vector_cross(ea, eb);
        ivda_vector_3_normalize(&n);
        ret.n = n;
        ret.u = u;
        ret.v = v;
        ret.t = t;
        ret.m = self->m;
        ret.raw = (const ivda_shape *) self;
        ret.intersected = 1;
        const ivda_fp dot = ivda_vector_3_dot(&n, ivda_ray_d(ray));
        if (dot > ivda_fp_make(0)) {
            ivda_vector_3_neg(&ret.n);
            ret.front = 0;
        } else
            ret.front = 1;
    }
    return ret;
}

ivda_fp
ivda_triangle_surface_area(
    const ivda_triangle *const self
) {
    ivs_assert(self);
    const ivda_vector_3 x = ivda_vector_cross(&self->va, &self->vb);
    return ivda_vector_3_l2norm(&x) / ivda_fp_make(2);
}

ivda_aabb_3
ivda_triangle_bound(
    const ivda_triangle *const self
) {
    ivs_assert(self);
    ivda_aabb_3 ret;
    ivda_aabb_3_init(&ret);
    const ivda_point_3 a = ivda_point_3_add(&self->o, &self->va);
    const ivda_point_3 b = ivda_point_3_add(&self->o, &self->vb);
    ivda_aabb_3_include(&ret, &self->o);
    ivda_aabb_3_include(&ret, &a);
    ivda_aabb_3_include(&ret, &b);
    return ret;
}
