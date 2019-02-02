/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <assert.h>

#include <vdp1/env.h>
#include <vdp1/map.h>
#include <vdp1/cmdt.h>
#include <vdp1/vram.h>

#include "vdp-internal.h"

void
vdp1_vram_partitions_set(uint32_t cmdt_count, uint32_t texture_size,
    uint32_t gouraud_count, uint32_t clut_count)
{
        /* We have to have at least one command */
        assert(cmdt_count > 0);

        /* One command table is allocated to us */
        uint32_t vram_size;
        vram_size = VDP1_VRAM_SIZE - sizeof(struct vdp1_cmdt);

        uint32_t cmdt_size;
        cmdt_size = cmdt_count * sizeof(struct vdp1_cmdt);

        uint32_t gouraud_size;
        gouraud_size = gouraud_count * sizeof(struct vdp1_gouraud_table);

        uint32_t clut_size;
        clut_size = clut_count * sizeof(struct vdp1_clut);

        uint32_t total_size;
        total_size = cmdt_size + texture_size + gouraud_size + clut_size;

        assert(total_size <= vram_size);

        uint32_t vram_base;
        vram_base = VDP1_VRAM(sizeof(struct vdp1_cmdt));

        _state_vdp1()->vram.cmdt_base = vram_base;
        vram_base += cmdt_size;

        _state_vdp1()->vram.texture_base = vram_base;
        vram_base += texture_size;

        _state_vdp1()->vram.gouraud_base = vram_base;
        vram_base += gouraud_size;

        _state_vdp1()->vram.clut_base = vram_base;
        vram_base += clut_size;

        /* Get the remaining amount left over */
        _state_vdp1()->vram.remaining_base =
            (((VDP1_VRAM(VDP1_VRAM_SIZE) - vram_base) == 0)
                ? 0x00000000
                : vram_base);
}

void *
vdp1_vram_texture_base_get(void)
{
        return (void *)_state_vdp1()->vram.texture_base;
}

struct vdp1_gouraud_table *
vdp1_vram_gouraud_base_get(void)
{
        return (struct vdp1_gouraud_table *)_state_vdp1()->vram.gouraud_base;
}

struct vdp1_clut *
vdp1_vram_clut_base_get(void)
{
        return (struct vdp1_clut *)_state_vdp1()->vram.clut_base;
}

void *
vdp1_vram_remaining_get(void)
{
        return (void *)_state_vdp1()->vram.remaining_base;
}
