// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"

void main(void) {
	int i,j,addr;
	unsigned char d;
	PPUCTRL = 0x00;
	PPUMASK = PPU_OFF;

	SetPPUAdr(0x3F00); /* Palette */
	PPUDAT = 0x0f;     /* 0 */
	PPUDAT = 0x01;     /* 1 */
	PPUDAT = 0x10;     /* 2 */
	PPUDAT = 0x20;     /* 3 */

        PPUSCR = 0x00; /* scroll x = 0 */
        PPUSCR = 0x00; /* scroll y = 0 */

	PPUCTRL = 0x00;
	PPUMASK = PPU_ON;
	while(1)
	  for(i=0;i<29;i++) {
#ifdef VBLANK
		while(!(PPUSTATUS & 0x80));
#endif
		addr = 0x2200+(i<<5)+i;
		SetPPUAdr(addr); /* Name Table */
		PPUDAT = 'A';
		PPUDAT = 'B';
		PPUDAT = 'C';
		PPUDAT = 'D';
		PPUSTATUS;
		PPUSCR = 0x00; /* scroll x = 0 */
		PPUSCR = 0x00; /* scroll y = 0 */
		for(j=0;j<10;j++);
	}

}
