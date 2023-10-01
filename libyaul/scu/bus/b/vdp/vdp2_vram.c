/*
 * Copyright (c) Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <string.h>

#include <cpu/dmac.h>

#include <vdp2/cram.h>
#include <vdp2/vram.h>

#include "vdp-internal.h"

static vdp2_vram_ctl_t _vdp2_vram_ctl = {
    .coeff_table = VDP2_VRAM_CTL_COEFF_TABLE_VRAM,
    .vram_mode   = VDP2_VRAM_CTL_MODE_PART_BANK_BOTH
};

void
__vdp2_vram_init(void)
{
    _state_vdp2()->vram_ctl = &_vdp2_vram_ctl;

    vdp2_vram_control_set(&_vdp2_vram_ctl);
    vdp2_vram_cycp_clear();

    cpu_dmac_memset(0, (void *)VDP2_VRAM(0x0000), 0x00000000, VDP2_VRAM_SIZE);
}

void
vdp2_vram_control_set(const vdp2_vram_ctl_t *vram_ctl)
{
    volatile vdp2_ioregs_t * const vdp2_ioregs = (volatile vdp2_ioregs_t *)VDP2_IOREG_BASE;

    assert(vram_ctl != NULL);

    /* If the coefficient table is set to be stored in CRAM, the color mode
     * must be 1 */
    _state_vdp2()->shadow_regs.ramctl &= 0xEFFF;
    _state_vdp2()->shadow_regs.ramctl |= 1 << vram_ctl->coeff_table;

    /* Coefficient table storage */
    _state_vdp2()->shadow_regs.ramctl &= 0x7FFF;
    _state_vdp2()->shadow_regs.ramctl |= vram_ctl->coeff_table << 15;

    /* VRAM mode */
    _state_vdp2()->shadow_regs.ramctl &= 0xFCFF;
    _state_vdp2()->shadow_regs.ramctl |= vram_ctl->vram_mode << 8;

    vdp2_ioregs->vrsize = 0x0000;
    vdp2_ioregs->ramctl = _state_vdp2()->shadow_regs.ramctl;

    (void)memcpy(_state_vdp2()->vram_ctl, &vram_ctl,
      sizeof(vdp2_vram_ctl_t));
}

void
vdp2_vram_usage_set(const vdp2_vram_usage_t *vram_usage)
{
    _state_vdp2()->shadow_regs.ramctl &= 0xFF00;

    _state_vdp2()->shadow_regs.ramctl |= vram_usage->a0;
    _state_vdp2()->shadow_regs.ramctl |= vram_usage->a1 << 2;
    _state_vdp2()->shadow_regs.ramctl |= vram_usage->b0 << 4;
    _state_vdp2()->shadow_regs.ramctl |= vram_usage->b1 << 6;
}

vdp2_vram_cycp_t *
vdp2_vram_cycp_get(void)
{
    return (vdp2_vram_cycp_t *)&_state_vdp2()->shadow_regs.cyc[0];
}

void
vdp2_vram_cycp_set(const vdp2_vram_cycp_t *vram_cycp)
{
    assert(vram_cycp != NULL);

    vdp2_vram_cycp_bank_set(VDP2_VRAM_BANK_A0, &vram_cycp->pt[0]);
    vdp2_vram_cycp_bank_set(VDP2_VRAM_BANK_A1, &vram_cycp->pt[1]);
    vdp2_vram_cycp_bank_set(VDP2_VRAM_BANK_B0, &vram_cycp->pt[2]);
    vdp2_vram_cycp_bank_set(VDP2_VRAM_BANK_B1, &vram_cycp->pt[3]);
}

void
vdp2_vram_cycp_clear(void)
{
    vdp2_vram_cycp_bank_clear(VDP2_VRAM_BANK_A0);
    vdp2_vram_cycp_bank_clear(VDP2_VRAM_BANK_A1);
    vdp2_vram_cycp_bank_clear(VDP2_VRAM_BANK_B0);
    vdp2_vram_cycp_bank_clear(VDP2_VRAM_BANK_B1);
}

vdp2_vram_cycp_bank_t *
vdp2_vram_cycp_bank_get(vdp2_vram_bank_t bank)
{
    return (vdp2_vram_cycp_bank_t *)&_state_vdp2()->shadow_regs.cyc[bank & 3];
}

void
vdp2_vram_cycp_bank_set(vdp2_vram_bank_t bank,
  const vdp2_vram_cycp_bank_t *cycp_bank)
{
    assert(cycp_bank != NULL);

    _state_vdp2()->shadow_regs.cyc[bank & 3] = cycp_bank->raw;
}

void
vdp2_vram_cycp_bank_clear(vdp2_vram_bank_t bank)
{
    _state_vdp2()->shadow_regs.cyc[bank] = 0xFFFFFFFF;
}
