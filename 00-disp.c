// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"

void main(void) {
	int i;
	PPUCTRL = CTRL_VALUE;
	PPUMASK = PPU_OFF;

	SetPPUAdr(0x3F00); /* set pallete table */
	PPUDAT = 0x38;
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x20;

	SetPPUAdr(0x2000);
	for(i=0;i<960;i++)  /* clear name table */
		PPUDAT = 0;

	SetPPUAdr(0x23C0);
	for(i=0;i<64;i++)  /* clear attribute */
		PPUDAT = 0;

	PPUSTATUS;
        PPUSCR = 0x00; /* scroll x = 0 */
        PPUSCR = 0x00; /* scroll y = 0 */

	PPUCTRL = 0x00;
	PPUMASK = PPU_ON;
	while(1);
}
