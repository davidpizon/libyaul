/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <cpu.h>
#include <vdp2/tvmd.h>

#include "vdp2-internal.h"

void
vdp2_tvmd_display_set(void)
{
        vdp2_state.buffered_regs.tvmd |= 0x8000;

        /* Change the DISP bit during VBLANK-IN */
        vdp2_tvmd_vblank_in_wait();

        /* write to memory */
        MEMORY_WRITE(16, VDP2(TVMD), vdp2_state.buffered_regs.tvmd);
}
