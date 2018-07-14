/*
 * Copyright (c) 2012-2016 Israel Jacquez
 * See LICENSE for details.
 *
 * Israel Jacquez <mrkotfw@gmail.com>
 */

#ifndef _SMPC_RTC_H_
#define _SMPC_RTC_H_

#include <stdint.h>

struct smpc_time {
        uint16_t year;
        uint8_t day;
        uint8_t month;
        uint8_t days;
        uint8_t hours;
        uint8_t minutes;
        uint8_t seconds;
};

#endif /* !_SMPC_RTC_H_ */
