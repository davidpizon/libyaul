/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef _DBGIO_H_
#define _DBGIO_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DBGIO_DEV_NULL  0
#define DBGIO_DEV_VDP1  1
#define DBGIO_DEV_VDP2  2

typedef struct {
        const uint32_t *font_cpd;
        const uint16_t *font_pal;
        uint8_t font_fg;
        uint8_t font_bg;

        uint8_t scrn;

        uint8_t cpd_bank;
        uint32_t cpd_offset;

        uint8_t pnd_bank;
        uint8_t pnd_offset;

        uint32_t cpd_cycp_mask;
        uint32_t pnd_cycp_mask;

        uint8_t cram_index;
} dbgio_vdp2_t;

extern void dbgio_init(void);
extern void dbgio_dev_init(uint8_t, const void *);
extern void dbgio_dev_default_init(uint8_t);
extern void dbgio_dev_set(uint8_t);
extern void dbgio_buffer(const char *);
extern void dbgio_flush(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !_DBGIO_H_ */
