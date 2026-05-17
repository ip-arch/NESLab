// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"


void main(void) {
	int i;
	unsigned char d;
	struct sprite *spdata = (void*)0x0200;
	PPUCTRL = CTRL_VALUE;
	PPUMASK = PPU_OFF;

	SetPPUAdr(0x3F00); /* set background pallete table */
	PPUDAT = 0x00;
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x20;

	SetPPUAdr(0x3F11); /* set sprite pallete table (pallete 0 is common to BG */
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x38;

	for(i=1;i<64;i++) spdata[i].v_pos=255;

	SetPPUAdr(0x2000);
	for(i=0;i<960;i++)  /* clear name table */
		PPUDAT = 0;

	SetPPUAdr(0x23C0);
	for(i=0;i<64;i++)  /* clear attribute */
		PPUDAT = 0;

	for(i=0;i<8;i++) {
		spdata[i].v_pos =   119+i*2;     /* y pos */
		spdata[i].chr  =  'P';
		spdata[i].attr =  SP_PALETTE(0) | SP_VFLIP;     /* sprite attribute */
		spdata[i].h_pos =   128+i*4;     /* x pos */
	}

	OAMDMA = 0x02;

	PPUSTATUS;
        PPUSCR = 0x00; /* scroll x = 0 */
        PPUSCR = 0x00; /* scroll y = 0 */

	PPUCTRL = 0x00;
	PPUMASK = PPU_ON;
	while(1);
}
