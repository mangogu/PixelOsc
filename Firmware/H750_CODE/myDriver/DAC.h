#ifndef __DAC_H
#define __DAC_H

#include "CONF.h"

#define MCP4725_ADDR		0x60<<1

#define CHA_VGA_CTR_EN	0x00
#define CHA_TRIG_VOL_EN 0x01
#define CHA_OFST_F_EN		0x02
#define CHB_VGA_CTR_EN  0x03
#define CHB_TRIG_VOL_EN 0x04
#define CHB_OFST_F_EN   0x05

void DAC_Init(void);
void DAC_SelectChip(uint8_t id);
void I2C_Init(void);

#endif

