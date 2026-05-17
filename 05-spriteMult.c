// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"


void main(void) {
	int i,count;
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

	PPUSTATUS;
	PPUCTRL = 0x00;
	PPUMASK = PPU_ON;
	count=0;
	for(i=0;i<10;i++) {
		do {
		  while(PPU_VBLANK == 0);
		} while(count++<60);
		count=0;
		PPUSCR = 0x00; 
		PPUSCR = 0x00; 
		spdata[i].v_pos =   119;     /* y pos */
		spdata[i].chr  =  '0'+i;
		spdata[i].attr =  SP_PALETTE(0) ;     /* sprite attribute */
		spdata[i].h_pos =   32+i*10;     /* x pos */
		OAMDMA = 0x02;
	}

	while(1);
}
