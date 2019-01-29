/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <vdp2/cram.h>

#include "vdp-internal.h"

void
vdp2_cram_mode_set(uint8_t mode)
{
#ifdef DEBUG
        assert((mode >= 0) && (mode <= 2));
#endif /* DEBUG */

        _state_vdp2()->regs.ramctl &= 0xCFFF;
        _state_vdp2()->regs.ramctl |= mode << 12;

        MEMORY_WRITE(16, VDP2(RAMCTL), _state_vdp2()->regs.ramctl);
}

void
vdp2_cram_offset_set(uint8_t scrn, uint32_t cram_addr)
{
#ifdef DEBUG
        assert((scrn == SCRN_NBG0) ||
               (scrn == SCRN_NBG1) ||
               (scrn == SCRN_NBG2) ||
               (scrn == SCRN_NBG3) ||
               (scrn == SCRN_RBG0) ||
               (scrn == SCRN_RBG1) ||
               (scrn == SCRN_SPRITE));

        assert((cram_addr >= CRAM_ADDR(0x000)) &&
               (cram_addr < CRAM_ADDR(CRAM_SIZE >> 1)));
#endif /* DEBUG */

        /* Fetch CRAM mode */
        uint8_t mode;
        mode = (_state_vdp2()->regs.ramctl >> 12) & 0x03;

        cram_addr = ((mode == 1) ? (cram_addr >> 10) : (cram_addr >> 9)) & 0x07;

        switch (scrn) {
        case SCRN_RBG1:
        case SCRN_NBG0:
                _state_vdp2()->regs.craofa &= 0xFFF8;
                _state_vdp2()->regs.craofa |= cram_addr;
                break;
        case SCRN_NBG1:
                _state_vdp2()->regs.craofa &= 0xFF8F;
                _state_vdp2()->regs.craofa |= cram_addr << 4;
                break;
        case SCRN_NBG2:
                _state_vdp2()->regs.craofa &= 0xF8FF;
                _state_vdp2()->regs.craofa |= cram_addr << 8;
                break;
        case SCRN_NBG3:
                _state_vdp2()->regs.craofa &= 0x8FFF;
                _state_vdp2()->regs.craofa |= cram_addr << 12;
                break;
        case SCRN_RBG0:
                _state_vdp2()->regs.craofb &= 0xFFF8;
                _state_vdp2()->regs.craofb |= cram_addr;
                break;
        case SCRN_SPRITE:
                _state_vdp2()->regs.craofb &= 0xFF8F;
                _state_vdp2()->regs.craofb |= cram_addr << 4;
                break;
        default:
                return;
        }
}
