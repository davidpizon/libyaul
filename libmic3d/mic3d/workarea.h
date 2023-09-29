/*
 * Copyright (c) 2022-2023 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef _MIC3D_WORKAREA_H_
#define _MIC3D_WORKAREA_H_

#include <stdint.h>

#include <mic3d/config.h>
#include <mic3d/sizes.h>

#define POOL_MIC3D_SORT_SINGLES_COUNT    CONFIG_MIC3D_CMDT_COUNT
#define POOL_MIC3D_CMDTS_COUNT           CONFIG_MIC3D_CMDT_COUNT
#define POOL_MIC3D_DEPTH_VALUES_COUNT    CONFIG_MIC3D_POINTS_COUNT
#define POOL_MIC3D_Z_VALUES_COUNT        CONFIG_MIC3D_POINTS_COUNT
#define POOL_MIC3D_SCREEN_POINTS_COUNT   CONFIG_MIC3D_POINTS_COUNT
#define POOL_MIC3D_RENDER_MATRICES_COUNT 2
#define POOL_MIC3D_LIGHT_MATRICES_COUNT  5
#define POOL_MIC3D_COLORS_COUNT          CONFIG_MIC3D_POINTS_COUNT

#define WORKAREA_MIC3D_SORT_SINGLES_BYTE_SIZE    (STRUCT_MIC3D_SORT_SINGLES_BYTE_SIZE * POOL_MIC3D_SORT_SINGLES_COUNT)
#define WORKAREA_MIC3D_CMDTS_BYTE_SIZE           (STRUCT_MIC3D_CMDTS_BYTE_SIZE * POOL_MIC3D_CMDTS_COUNT)
#define WORKAREA_MIC3D_DEPTH_VALUES_BYTE_SIZE    (STRUCT_MIC3D_DEPTH_VALUES_BYTE_SIZE * POOL_MIC3D_DEPTH_VALUES_COUNT)
#define WORKAREA_MIC3D_Z_VALUES_BYTE_SIZE        (STRUCT_MIC3D_Z_VALUES_BYTE_SIZE * POOL_MIC3D_Z_VALUES_COUNT)
#define WORKAREA_MIC3D_SCREEN_POINTS_BYTE_SIZE   (STRUCT_MIC3D_SCREEN_POINTS_BYTE_SIZE * POOL_MIC3D_SCREEN_POINTS_COUNT)
#define WORKAREA_MIC3D_RENDER_MATRICES_BYTE_SIZE (STRUCT_MIC3D_RENDER_MATRICES_BYTE_SIZE * POOL_MIC3D_RENDER_MATRICES_COUNT)
#define WORKAREA_MIC3D_LIGHT_MATRICES_BYTE_SIZE  (STRUCT_MIC3D_LIGHT_MATRICES_BYTE_SIZE * POOL_MIC3D_LIGHT_MATRICES_COUNT)
#define WORKAREA_MIC3D_COLORS_BYTE_SIZE          (STRUCT_MIC3D_COLORS_BYTE_SIZE * POOL_MIC3D_COLORS_COUNT)
#define WORKAREA_MIC3D_WORK_BYTE_SIZE            (STRUCT_MIC3D_WORK_BYTE_SIZE)

#define WORKAREA_MIC3D_SORT_SINGLES_ALIGNMENT    16
#define WORKAREA_MIC3D_CMDTS_ALIGNMENT           16
#define WORKAREA_MIC3D_DEPTH_VALUES_ALIGNMENT    16
#define WORKAREA_MIC3D_Z_VALUES_ALIGNMENT        16
#define WORKAREA_MIC3D_SCREEN_POINTS_ALIGNMENT   16
#define WORKAREA_MIC3D_RENDER_MATRICES_ALIGNMENT 16
#define WORKAREA_MIC3D_LIGHT_MATRICES_ALIGNMENT  16
#define WORKAREA_MIC3D_COLORS_ALIGNMENT          16
#define WORKAREA_MIC3D_WORK_ALIGNMENT            16

#define __WORKAREA_MIC3D_DECLARE_STRUCT(lname, uname)                          \
    typedef struct workarea_mic3d_##lname {                                    \
        uint8_t pool[WORKAREA_MIC3D_##uname##_BYTE_SIZE];                      \
    } __aligned(WORKAREA_MIC3D_##uname##_ALIGNMENT) workarea_mic3d_##lname##_t

__WORKAREA_MIC3D_DECLARE_STRUCT(sort_singles, SORT_SINGLES);
__WORKAREA_MIC3D_DECLARE_STRUCT(cmdts, CMDTS);
__WORKAREA_MIC3D_DECLARE_STRUCT(depth_values, DEPTH_VALUES);
__WORKAREA_MIC3D_DECLARE_STRUCT(z_values, Z_VALUES);
__WORKAREA_MIC3D_DECLARE_STRUCT(screen_points, SCREEN_POINTS);
__WORKAREA_MIC3D_DECLARE_STRUCT(render_matrices, RENDER_MATRICES);
__WORKAREA_MIC3D_DECLARE_STRUCT(light_matrices, LIGHT_MATRICES);
__WORKAREA_MIC3D_DECLARE_STRUCT(colors, COLORS);
__WORKAREA_MIC3D_DECLARE_STRUCT(work, WORK);

#undef __WORKAREA_MIC3D_DECLARE_STRUCT

typedef struct workarea_mic3d {
    workarea_mic3d_depth_values_t *depth_values;
    workarea_mic3d_z_values_t *z_values;
    workarea_mic3d_screen_points_t *screen_points;
    workarea_mic3d_sort_singles_t *sort_singles;
    workarea_mic3d_cmdts_t *cmdts;
    workarea_mic3d_render_matrices_t *render_matrices;
    workarea_mic3d_light_matrices_t *light_matrices;
    workarea_mic3d_colors_t *colors;
    workarea_mic3d_work_t *work;
} workarea_mic3d_t;

#endif /* !_MIC3D_WORKAREA_H_ */