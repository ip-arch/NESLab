// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"

void main(void) {
	int i;
	unsigned char d;
	PPUCTRL = CTRL_VALUE;
	PPUMASK = PPU_OFF;

	SetPPUAdr(0x3F00); /* set background pallete table */
	PPUDAT = 0x38;
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x20;

	SetPPUAdr(0x3F11); /* set sprite pallete table (pallete 0 is common to BG */
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x31;

	SetPPUAdr(0x2000);
	for(i=0;i<960;i++)  /* clear name table */
		PPUDAT = 0;

	SetPPUAdr(0x23C0);
	for(i=0;i<64;i++)  /* clear attribute */
		PPUDAT = 0;

	OAMADR = 0x00;
	OAMDAT =   69;     /* y pos */
	OAMDAT =  '@';
	OAMDAT = 0x00;     /* sprite attribute */
	OAMDAT =   20;     /* x pos */

	OAMADR = 0x04;
	OAMDAT =   72;     /* y pos */
	OAMDAT =  'M';
	OAMDAT = 0x00;     /* sprite attribute */
	OAMDAT =   28;     /* x pos */

	OAMADR = 0x08;
	OAMDAT =   75;     /* y pos */
	OAMDAT =  'e';
	OAMDAT = 0x00;     /* sprite attribute */
	OAMDAT =   36;     /* x pos */

	OAMADR = 0x0C;
	OAMDAT =   78;     /* y pos */
	OAMDAT =  'i';
	OAMDAT = 0x00;     /* sprite attribute */
	OAMDAT =   44;     /* x pos */

	OAMADR = 0x10;
	OAMDAT =   81;     /* y pos */
	OAMDAT =  'j';
	OAMDAT = 0x00;     /* sprite attribute */
	OAMDAT =   52;     /* x pos */

	OAMADR = 0x14;
	OAMDAT =   84;     /* y pos */
	OAMDAT =  'i';
	OAMDAT = 0x00;     /* sprite attribute */
	OAMDAT =   60;     /* x pos */

	PPUSTATUS;
        PPUSCR = 0x00; /* scroll x = 0 */
        PPUSCR = 0x00; /* scroll y = 0 */

	PPUCTRL = 0x00;
	PPUMASK = PPU_ON;
	while(1);
}
