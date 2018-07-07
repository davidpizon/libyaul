/*
 * Copyright (c) 2012-2016
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com
 */

#include <sys/cdefs.h>

#include <stdio.h>

#include <cpu/intc.h>
#include <cpu/map.h>
#include <cpu/frt.h>

static void _frt_ici_handler(void);
static void _frt_oci_handler(void);
static void _frt_ovi_handler(void);

static void _default_ihr(void);

#define FRT_IHR_INDEX_NONE      0
#define FRT_IHR_INDEX_OCBI      1
#define FRT_IHR_INDEX_OCAI      2

static void (*_frt_oc_ihr_table[])(void) = {
        _default_ihr,
        _default_ihr,
        _default_ihr
};

void
cpu_frt_init(uint8_t clock_div)
{
        MEMORY_WRITE_AND(8, CPU(TIER), ~0x0C);
        MEMORY_WRITE_AND(8, CPU(FTCSR), ~0x0C);

        cpu_frt_priority_set(15);

        /* Set time control register */
        MEMORY_WRITE_AND(8, CPU(TCR), ~0x03);
        MEMORY_WRITE_OR(8, CPU(TCR), clock_div & 0x03);

        cpu_frt_oca_clear();
        cpu_frt_ocb_clear();

        cpu_intc_ihr_set(INTC_INTERRUPT_FRT_ICI, _frt_ici_handler);
        cpu_intc_ihr_set(INTC_INTERRUPT_FRT_OCI, _frt_oci_handler);
        cpu_intc_ihr_set(INTC_INTERRUPT_FRT_OVI, _frt_ovi_handler);

        cpu_frt_count_set(0);
}

void
cpu_frt_oca_set(uint16_t count, void (*ihr)(void))
{
        /* Disable interrupt */
        MEMORY_WRITE_AND(8, CPU(TIER), ~0x08);
        MEMORY_WRITE_AND(8, CPU(FTCSR), ~0x08);

        /* Select OCRA register and select output compare A match */
        MEMORY_WRITE_AND(8, CPU(TOCR), ~0x12);
        MEMORY_WRITE(8, CPU(OCRAH), 0);
        MEMORY_WRITE(8, CPU(OCRAL), 0);

        _frt_oc_ihr_table[FRT_IHR_INDEX_OCAI] = _default_ihr;

        if ((count > 0) && (ihr != NULL)) {
                MEMORY_WRITE_AND(8, CPU(TOCR), ~0x10);
                MEMORY_WRITE(8, CPU(OCRAH), (uint8_t)(count >> 8));
                MEMORY_WRITE(8, CPU(OCRAL), (uint8_t)(count & 0xFF));

                /* Compare on match A */
                MEMORY_WRITE_OR(8, CPU(TOCR), 0x02);
                MEMORY_WRITE_OR(8, CPU(TIER), 0x08);

                _frt_oc_ihr_table[FRT_IHR_INDEX_OCAI] = ihr;
        }
}

void
cpu_frt_ocb_set(uint16_t count, void (*ihr)(void))
{
        /* Disable interrupt */
        MEMORY_WRITE_AND(8, CPU(TIER), ~0x04);
        MEMORY_WRITE_AND(8, CPU(FTCSR), ~0x04);

        /* Select output compare B match */
        MEMORY_WRITE_AND(8, CPU(TOCR), ~0x01);

        /* Select OCRB register */
        MEMORY_WRITE_OR(8, CPU(TOCR), 0x10);
        MEMORY_WRITE(8, CPU(OCRBH), 0);
        MEMORY_WRITE(8, CPU(OCRBL), 0);

        _frt_oc_ihr_table[FRT_IHR_INDEX_OCBI] = _default_ihr;

        if ((count > 0) && (ihr != NULL)) {
                MEMORY_WRITE(8, CPU(OCRBH), (uint8_t)(count >> 8));
                MEMORY_WRITE(8, CPU(OCRBL), (uint8_t)(count & 0xFF));

                MEMORY_WRITE_OR(8, CPU(TOCR), 0x01);
                MEMORY_WRITE_OR(8, CPU(TIER), 0x04);

                _frt_oc_ihr_table[FRT_IHR_INDEX_OCBI] = ihr;
        }
}

static void __attribute__ ((interrupt_handler))
_frt_ici_handler(void)
{
}

static void __attribute__ ((interrupt_handler))
_frt_oci_handler(void)
{
        register uint8_t reg_ftcsr;
        reg_ftcsr = cpu_frt_status_get();

        /* Disable OCA or OCB interrupt (or neither), invoke the
         * callback and enable interrupt again */

        uint32_t ocf_bits;
        ocf_bits = reg_ftcsr & 0x0C;

        MEMORY_WRITE_AND(8, CPU(TIER), ~ocf_bits);
        MEMORY_WRITE_AND(8, CPU(FTCSR), ~ocf_bits);

        _frt_oc_ihr_table[(ocf_bits & 0x08) >> 2]();
        _frt_oc_ihr_table[(ocf_bits & 0x04) >> 2]();

        MEMORY_WRITE_OR(8, CPU(TIER), ocf_bits);
}

static void __attribute__ ((interrupt_handler))
_frt_ovi_handler(void)
{
}

static void
_default_ihr(void)
{
}
