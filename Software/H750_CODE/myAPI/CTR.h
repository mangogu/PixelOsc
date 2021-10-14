#ifndef __CTR_H
#define __CTR_H

#include "GPIO.h"

#define CH_COUPLE_DC 0x00
#define CH_COUPLE_AC 0x01

#define CH_CALI_GND 0x00
#define CH_CALI_NORMAL 0x01

void CHA_couple(uint8_t mode);
void CHA_calibrate(uint8_t mode);
void analog_init(void);

#endif
