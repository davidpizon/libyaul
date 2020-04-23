/*
 * Copyright (c) 2012-2019 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef _VDP2_SPRITE_H_
#define _VDP2_SPRITE_H_

#include <sys/cdefs.h>

#include <stdint.h>

__BEGIN_DECLS

typedef struct vdp2_sprite_type_0 {
        unsigned int pr:2; /* Bit 15 */ /* Priority bit(s) */
        unsigned int cc:3; /* Color calculation ratio bit(s) */
        unsigned int dc:11; /* Dot color data bits */
} __packed vdp2_sprite_type_0_t;

typedef struct vdp2_sprite_type_1 {
        unsigned int pr:3; /* Priority bit(s) */
        unsigned int cc:2; /* Color calculation ratio bit(s) */
        unsigned int dc:11; /* Dot color data bits */
} __packed vdp2_sprite_type_1_t;

typedef struct vdp2_sprite_type_2 {
        unsigned int sdw:1; /* Shadow (or sprite window) bit */
        unsigned int pr:1; /* Priority bit(s) */
        unsigned int cc:3; /* Color calculation ratio bit(s) */
        unsigned int dc:11; /* Dot color data bits */
} __packed vdp2_sprite_type_2_t;

typedef struct vdp2_sprite_type_3 {
        unsigned int sdw:1; /* Shadow (or sprite window) bit */
        unsigned int pr:2; /* Priority bit(s) */
        unsigned int cc:2; /* Color calculation ratio bit(s) */
        unsigned int dc:11; /* Dot color data bits */
} __packed vdp2_sprite_type_3_t;

typedef struct vdp2_sprite_type_4 {
        unsigned int sdw:1; /* Shadow (or sprite window) bit */
        unsigned int pr:2; /* Priority bit(s) */
        unsigned int cc:3; /* Color calculation ratio bit(s) */
        unsigned int dc:10; /* Dot color data bits */
} __packed vdp2_sprite_type_4_t;

typedef struct vdp2_sprite_type_5 {
        unsigned int sdw:1; /* Shadow (or sprite window) bit */
        unsigned int pr:3; /* Priority bit(s) */
        unsigned int cc:1; /* Color calculation ratio bit(s) */
        unsigned int dc:11; /* Dot color data bits */
} __packed vdp2_sprite_type_5_t;

typedef struct vdp2_sprite_type_6 {
        unsigned int sdw:1; /* Shadow (or sprite window) bit */
        unsigned int pr:3; /* Priority bit(s) */
        unsigned int cc:2; /* Color calculation ratio bit(s) */
        unsigned int dc:10; /* Dot color data bits */
} __packed vdp2_sprite_type_6_t;

typedef struct vdp2_sprite_type_7 {
        unsigned int sdw:1; /* Shadow (or sprite window) bit */
        unsigned int pr:3; /* Priority bit(s) */
        unsigned int cc:3; /* Color calculation ratio bit(s) */
        unsigned int dc:9; /* Dot color data bits */
} __packed vdp2_sprite_type_7_t;

typedef struct vdp2_sprite_type_8 {
        unsigned int pr:1; /* Priority bit(s) */
        unsigned int dc:7; /* Dot color data bits */
} __packed vdp2_sprite_type_8_t;

typedef struct vdp2_sprite_type_9 {
        unsigned int pr:1; /* Priority bit(s) */
        unsigned int cc:1; /* Color calculation ratio bit(s) */
        unsigned int dc:6; /* Dot color data bits */
} __packed vdp2_sprite_type_9_t;

typedef struct vdp2_sprite_type_a {
        unsigned int pr:2; /* Priority bit(s) */
        unsigned int dc:6; /* Dot color data bits */
} __packed vdp2_sprite_type_a_t;

typedef struct vdp2_sprite_type_b {
        unsigned int cc:2; /* Color calculation ratio bit(s) */
        unsigned int dc:6; /* Dot color data bits */
} __packed vdp2_sprite_type_b_t;

typedef struct vdp2_sprite_type_c {
        unsigned int sp:1; /* Priority, CRAM addr. shared bit(s) */
        unsigned int dc:7; /* Dot color data bits */
} __packed vdp2_sprite_type_c_t;

typedef struct vdp2_sprite_type_d {
        unsigned int sp:1; /* Priority, CRAM addr. shared bit(s) */
        unsigned int sc:1; /* Color calculation ratio, CRAM addr. shared
                            * bit(s) */
        unsigned int dc:6; /* Dot color data bits */
} __packed vdp2_sprite_type_d_t;

typedef struct vdp2_sprite_type_e {
        unsigned int sp:2; /* Priority, CRAM addr. shared bit(s) */
        unsigned int dc:6; /* Dot color data bits */
} __packed vdp2_sprite_type_e_t;

typedef struct vdp2_sprite_type_f {
        unsigned int sc:2; /* Color calculation ratio, CRAM addr. shared
                            * bit(s) */
        unsigned int dc:6; /* Dot color data bits */
} __packed vdp2_sprite_type_f_t;

extern void vdp2_sprite_priority_set(uint8_t, uint8_t);

__END_DECLS

#endif /* !_VDP2_SPRITE_H_ */
