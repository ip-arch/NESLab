// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"

unsigned char read_pad(unsigned char *pad)
{
    unsigned char i;
    unsigned char data;

    *pad = 1;
    *pad = 0;

    for(i = 8; i != 0; i--) {
        data >>= 1;
        if(*pad & 1)
            data |= 0x80;
    }

    return data;
}

void main(void) {
	int i;
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
	while(1) {
		d = read_pad(PAD1);
		while(!(PPUSTATUS & 0x80));
		SetPPUAdr(0x2200); /* Name Table */
		if(d&1) PPUDAT = 'A';
		else    PPUDAT = 0;
		if(d&2) PPUDAT = 'B';
		else    PPUDAT = 0;
		if(d&4) PPUDAT = 'e';
		else    PPUDAT = 0;
		if(d&8) PPUDAT = 't';
		else    PPUDAT = 0;
		if(d&16) PPUDAT = 'U';
		else    PPUDAT = 0;
		if(d&32) PPUDAT = 'D';
		else    PPUDAT = 0;
		if(d&64) PPUDAT = 'L';
		else    PPUDAT = 0;
		if(d&128) PPUDAT = 'R';
		else    PPUDAT = 0;
		PPUSTATUS;
		PPUSCR = 0x00; /* scroll x = 0 */
		PPUSCR = 0x00; /* scroll y = 0 */
   }
}
