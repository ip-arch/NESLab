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

	SetPPUAdr(0x3F11); /* set sprite pallete table (pallete 0 is common to BG) */
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x3C;
	SetPPUAdr(0x3F17); /* set sprite pallete table (pallete 7) */
	PPUDAT = 0x15;

	for(i=1;i<64;i++) spdata[i].v_pos=255;

	SetPPUAdr(0x2000);
	for(i=0;i<960;i++)  /* clear name table */
		PPUDAT = 0;

	SetPPUAdr(0x2020);
	for(i=0; i<32;i++) PPUDAT = 0x01;

	SetPPUAdr(0x23C0);
	for(i=0;i<64;i++)  /* clear attribute */
		PPUDAT = 0;

	PPUSTATUS;
	PPUCTRL = 0x00;
	PPUMASK = PPU_ON;
	i=0;
	do {
		while(PPU_VBLANK == 0);
		PPUSCR = 0x00; 
		PPUSCR = 0x00; 

		spdata[0].v_pos =   239-i;     /* y pos */
		spdata[0].chr  =  0x02;
		spdata[0].attr =  SP_PALETTE(0);
		spdata[0].h_pos =   128;     /* x pos */
		i++;
		OAMDMA = 0x02;
	} while (PPU_SPHIT == 0);
	while(PPU_VBLANK == 0);
	PPUSCR = 0x00; 
	PPUSCR = 0x00; 
	spdata[0].attr =  SP_PALETTE(1);     /* sprite attribute */
	OAMDMA = 0x02;

	while(PPU_VBLANK == 0);
	SetPPUAdr(0x3F00); /* set background pallete table */
	PPUDAT = 0x22;
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x38;

	SetPPUAdr(0x2000);
	PPUSCR = 0x00; 
	PPUSCR = 0x00; 


	while(1);
}
