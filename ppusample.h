// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#define PPU (unsigned char*)0x2000
#define PPUCTRL (*(PPU+0))
#define PPUMASK (*(PPU+1))
#define PPUSTATUS (*(PPU+2))
#define OAMADR (*(PPU+3))
#define OAMDAT (*(PPU+4))
#define PPUSCR (*(PPU+5))
#define PPUADR (*(PPU+6))
#define PPUDAT (*(PPU+7))

#define OAMDMA (*(unsigned char*)0x4014)
#define PAD1 ((unsigned char*)0x4016)
#define PAD2 ((unsigned char*)0x4017)


#define APU				(unsigned char*)0x4000
#define APU_SQU1		(unsigned char*)0x4000
#define APU_SQU2		(unsigned char*)0x4004
#define APU_TRI			(unsigned char*)0x4008
#define APU_NOISE		(unsigned char*)0x400C
#define APU_MOD			(unsigned char*)0x4010
#define APU_CHANNEL		(*(unsigned char*)0x4015)
#define APU_FRAME		(*(unsigned char*)0x4017)

#define PPU_ON  0x1E
#define PPU_OFF 0x00

#define CTRL_VALUE 0x00 /* 0x00 -> horizontal 0x04 -> virtical */

#define SetPPUAdr(addr) do {PPUSTATUS;\
       				PPUADR = (addr >> 8);\
       				PPUADR = addr & 255;}\
      		 	while(0)

#define PPU_VBLANK (PPUSTATUS&0x80)
#define PPU_SPHIT  (PPUSTATUS&0x40)

struct sprite {
	unsigned char v_pos;
	unsigned char chr;
	unsigned char attr;
	unsigned char h_pos;
};

/* Attribute byte masks (NES OAM spec) */
#define SP_PALETTE(n)  ((n) & 0x03)       /* bits 0-1 */
#define SP_PRIO        0x20                /* bit 5    */
#define SP_HFLIP       0x40                /* bit 6    */
#define SP_VFLIP       0x80                /* bit 7    */

#define CTRL_NMI        0x80    /* enable NMI */
#define CTRL_BASE       0x00    /* nametable 0, 8x8 sprites */


void sei();
void cli();
extern int *irqvec;
extern int *nmivec;

