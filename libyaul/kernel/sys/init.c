/*
 * Copyright (c) Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 * Joe Fenton <jlfenton65@gmail.com>
 */

#include <sys/cdefs.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <internal.h>
#include <cpu-internal.h>
#include <smpc-internal.h>
#include <vdp-internal.h>

#include <cpu/cache.h>
#include <cpu/intc.h>
#include <stdbool.h>

void user_init(void) __weak;

void user_early_init(void) __weak;

static void _bss_clear(void);

void __noreturn
__sys_init(void)
{
    extern int main(void);

    void __global_ctors(void) __weak;
    void __global_dtors(void) __weak;

    _bss_clear();

    if (user_early_init != NULL) {
        user_early_init();
    }

    __atexit_init();

    __mm_init();

    __cpu_init();
    __scu_init();
    __smpc_init();

    __vdp_init();

    cpu_cache_purge();

    if (__global_ctors != NULL) {
        __global_ctors();
    }

    cpu_intc_mask_set(0);

    if (user_init != NULL) {
        user_init();
    }

    cpu_cache_purge();

    const int ret = main();

    cpu_intc_mask_set(15);

    if (__global_dtors != NULL) {
        __global_dtors();
    }

    exit(ret);
}

static void
_bss_clear(void)
{
    extern uint32_t __bss_start[];
    extern uint32_t __bss_end[];

    for (uint32_t *bss_ptr = __bss_start; bss_ptr < __bss_end; ) {
        *bss_ptr++ = 0x00000000;
        *bss_ptr++ = 0x00000000;
        *bss_ptr++ = 0x00000000;
        *bss_ptr++ = 0x00000000;
    }
}
