/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <vdp2/scrn.h>

#include <assert.h>

#include "vdp2-internal.h"

void
vdp2_scrn_priority_set(uint8_t scrn, uint8_t priority)
{
#ifdef DEBUG
        assert((scrn == SCRN_NBG0) ||
               (scrn == SCRN_NBG1) ||
               (scrn == SCRN_NBG2) ||
               (scrn == SCRN_NBG3) ||
               (scrn == SCRN_RBG0) ||
               (scrn == SCRN_RBG1));
#endif /* DEBUG */

        /* When priority is zero, scroll screen is transparent. */
        priority &= 0x07;

        switch (scrn) {
        case SCRN_RBG1:
        case SCRN_NBG0:
                vdp2_state.buffered_regs.prina &= 0xFFF8;
                vdp2_state.buffered_regs.prina |= priority;
                break;
        case SCRN_NBG1:
                vdp2_state.buffered_regs.prina &= 0xF8FF;
                vdp2_state.buffered_regs.prina |= priority << 8;
                break;
        case SCRN_NBG2:
                vdp2_state.buffered_regs.prinb &= 0xFFF8;
                vdp2_state.buffered_regs.prinb |= priority;
                break;
        case SCRN_NBG3:
                vdp2_state.buffered_regs.prinb &= 0xF8FF;
                vdp2_state.buffered_regs.prinb |= priority << 8;
                break;
        case SCRN_RBG0:
                vdp2_state.buffered_regs.prir &= 0xFFF8;
                vdp2_state.buffered_regs.prir |= priority;
                break;
        default:
                return;
        }
}
