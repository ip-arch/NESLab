// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"

void main(void) {
	int i;
	unsigned char d;
	PPUCTRL = CTRL_VALUE;
	PPUMASK = PPU_OFF;

	SetPPUAdr(0x3F00);
	PPUDAT = 0x0f;
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x20;

	SetPPUAdr(0x2200);
	PPUDAT = 'A';
	PPUDAT = 'B';
	PPUDAT = 'C';
	PPUDAT = 'D';

	PPUSTATUS;
        PPUSCR = 0x00; /* scroll x = 0 */
        PPUSCR = 0x00; /* scroll y = 0 */

	PPUCTRL = 0x00;
	PPUMASK = PPU_ON;
	while(1);
}
