/*
 * Copyright (c) 2012-2016
 * See LICENSE for details.
 *
 * Anders Montonen
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#include <assert.h>

#include <cpu/cache.h>
#include <cpu/divu.h>
#include <cpu/dmac.h>
#include <cpu/frt.h>

#include <cons.h>

#include <usb-cart.h>

#include "usb-cart-internal.h"

void
usb_cart_init(void)
{
        /* Disabling A-bus refresh adds ~20 KiB/s */
        MEMORY_WRITE(32, SCU(AREF), 0x00000000);

        /* Removing wait states doubles speed */
        MEMORY_WRITE(32, SCU(ASR0), 0x00000000);
}

void
usb_cart_long_send(uint32_t w)
{
        usb_cart_byte_send(w >> 24);
        usb_cart_byte_send(w >> 16);
        usb_cart_byte_send(w >> 8);
        usb_cart_byte_send(w & 0xFF);
}

uint32_t
usb_cart_long_read(void)
{
        uint32_t b;
        b = 0;

        b |= (usb_cart_byte_read()) << 24;
        b |= (usb_cart_byte_read()) << 16;
        b |= (usb_cart_byte_read()) << 8;
        b |= (usb_cart_byte_read());

        return b;
}

uint8_t
usb_cart_byte_xchg(uint8_t c)
{
        uint8_t b;
        b = usb_cart_byte_read();

        usb_cart_byte_send(c);

        return b;
}

void
usb_cart_dma_read(void *buffer, uint32_t len)
{
        assert(buffer != NULL);

        assert(len > 0);

        const struct dmac_ch_cfg dmac_cfg = {
                .dcc_ch = 0,
                .dcc_src_mode = DMAC_SOURCE_FIXED,
                .dcc_dst_mode = DMAC_DESTINATION_INCREMENT,
                .dcc_stride = DMAC_STRIDE_1_BYTE,
                .dcc_bus_mode = DMAC_BUS_MODE_CYCLE_STEAL,
                .dcc_src = USB_CART(FIFO),
                .dcc_dst = (uint32_t)buffer,
                .dcc_len = USB_CART_OUT_EP_SIZE,
                .dcc_ihr = NULL
        };

        uint32_t aref_bits;
        aref_bits = MEMORY_READ(32, SCU(AREF));

        uint32_t asr0_bits;
        asr0_bits = MEMORY_READ(32, SCU(ASR0));

        cpu_dmac_channel_wait(0);
        cpu_dmac_channel_config_set(&dmac_cfg);

        /* Disabling A-bus refresh adds ~20 KiB/s */
        MEMORY_WRITE(32, SCU(AREF), 0x00000000);
        MEMORY_WRITE(32, SCU(ASR0), 0x00000000);

        while (len > 0) {
                uint32_t len_mod;
                len_mod = len & (USB_CART_OUT_EP_SIZE - 1);

                uint32_t offset;
                offset = (len_mod == 0) ? USB_CART_OUT_EP_SIZE : len_mod;

                usb_cart_rxf_wait();
                cpu_dmac_channel_transfer_set(0, offset);
                cpu_dmac_channel_start(0);

                len -= offset;

                cpu_dmac_channel_wait(0);
        }

        MEMORY_WRITE(32, SCU(AREF), aref_bits);
        MEMORY_WRITE(32, SCU(ASR0), asr0_bits);
}

void
usb_cart_dma_send(const void *buffer, uint32_t len)
{
        assert(buffer != NULL);

        assert(len > 0);

        const struct dmac_ch_cfg dmac_cfg = {
                .dcc_ch = 0,
                .dcc_src_mode = DMAC_SOURCE_INCREMENT,
                .dcc_dst_mode = DMAC_DESTINATION_FIXED,
                .dcc_stride = DMAC_STRIDE_1_BYTE,
                .dcc_bus_mode = DMAC_BUS_MODE_CYCLE_STEAL,
                .dcc_src = (uint32_t)buffer,
                .dcc_dst = USB_CART(FIFO),
                .dcc_len = USB_CART_OUT_EP_SIZE,
                .dcc_ihr = NULL
        };

        uint32_t aref_bits;
        aref_bits = MEMORY_READ(32, SCU(AREF));

        uint32_t asr0_bits;
        asr0_bits = MEMORY_READ(32, SCU(ASR0));

        cpu_dmac_channel_wait(0);
        cpu_dmac_channel_config_set(&dmac_cfg);

        /* Disabling A-bus refresh adds ~20 KiB/s */
        MEMORY_WRITE(32, SCU(AREF), 0x00000000);
        /* Set 9-cycle wait was tested manually, and found to be the
         * bare minimum */
        MEMORY_WRITE(32, SCU(ASR0), 0x00900000);

        int32_t len_left;
        len_left = len;

        while (len_left > 0) {
                usb_cart_txe_wait();

                cpu_dmac_channel_start(0);
                cpu_dmac_channel_wait(0);

                /* Reset CPU-DMAC transfer */
                cpu_dmac_channel_transfer_set(0, USB_CART_OUT_EP_SIZE);

                len_left -= USB_CART_OUT_EP_SIZE;
        }

        if (len_left < 0) {
                uint32_t count;
                count = (len_left + USB_CART_OUT_EP_SIZE);

                uint32_t i;
                for (i = 0; i < count; i++) {
                        uint8_t *p;
                        p = (uint8_t *)((uint32_t)buffer + len - count + i);

                        usb_cart_txe_wait();
                        usb_cart_byte_send(*p);
                }
        }

        MEMORY_WRITE(32, SCU(AREF), aref_bits);
        MEMORY_WRITE(32, SCU(ASR0), asr0_bits);
}
