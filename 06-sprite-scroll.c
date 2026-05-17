// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"

struct sprite *spdata = (void*)0x200;
unsigned char scroll_x;  
static void ppu_puts(unsigned int addr, const char *s)
{
    SetPPUAdr(addr);
    while (*s) {
        PPUDAT = *s++;
    }
}

static void init_oam(void)
{
    unsigned char i;

    for (i = 1; i < 64; i++) {
        spdata[i].v_pos = 0xEF;
        spdata[i].chr   = 0x00;
        spdata[i].attr  = SP_PALETTE(0);
        spdata[i].h_pos = 0xFF;
    }
    spdata[0].v_pos = 15;           /* Y-1 = 23 -> scanline 24 */
    spdata[0].chr   = 0x01;         /* solid sprite tile        */
    spdata[0].attr  = SP_PALETTE(0) | SP_PRIO; /* behind bg so invisible */
    spdata[0].h_pos = 0;            /* X = 0                    */
}

static void init_nametable(void)
{
    unsigned int addr;
    unsigned char i;

    /* Row 0: "SCORE 000  LIVES 03" */
    ppu_puts(0x2020, "SCORE 000  LIVES 03");

    /* Row 1: decorative separator line (tile 0x01 = solid block) */
    addr = 0x2040;  /* row 1 start */
    for (i = 0; i < 32; i++) {
        SetPPUAdr(addr + i);
        PPUDAT = 0x19;  /* solid line tile - REQUIRED for sprite-0 hit */
    }
    /* Row 2: blank row */
    addr = 0x2060;
    for (i = 0; i < 32; i++) {
        SetPPUAdr(addr + i);
        PPUDAT = 0x00;
    }

    /* --- Game area (rows 3-29) ------------------------------------- */
    /* Fill with a simple repeating pattern so scrolling is visible   */
    SetPPUAdr(0x2100);
    for (i = 0; i < 32; i++) {
        PPUDAT = '0' + i;
    }

    SetPPUAdr(0x2500);
    for (i = 0; i < 32; i++) {
        PPUDAT = '@' + i;
    }

    addr = 0x2440;  /* row 1 start */
    for (i = 0; i < 32; i++) {
        SetPPUAdr(addr + i);
        PPUDAT = 0x19;  /* solid line tile - REQUIRED for sprite-0 hit */
    }
    SetPPUAdr( 0x23C0 );  /* Attribute memory for top 4 rows */
    for (i = 0; i < 8; i++) {
	PPUDAT = 0x55;
    }
    SetPPUAdr( 0x27C0 );  /* Attribute memory for top 4 rows */
    for (i = 0; i < 8; i++) {
	PPUDAT = 0x55;
    }
}

void init_pallet(void) {
        SetPPUAdr(0x3F00);
	PPUDAT = 0x0F;
	PPUDAT = 0x11;
	PPUDAT = 0x14;
	PPUDAT = 0x19;
        SetPPUAdr(0x3F07);
	PPUDAT = 0x15;
        SetPPUAdr(0x3F13);
	PPUDAT = 0x0F;

}

void main(void)
{
    unsigned char demo_frames;

    /* disable rendering during init */
    PPUMASK = PPU_OFF;
    PPUCTRL = 0x00;

    /* wait 2 vblanks for PPU to warm up */
    PPUSTATUS;
    while (!PPU_VBLANK);
    PPUSTATUS;
    while (!PPU_VBLANK);

    /* initialise OAM and nametable */
    init_oam();
    init_nametable();
    init_pallet();

    /* push OAM to PPU */
    PPUSTATUS;
    while (!PPU_VBLANK);
    OAMDMA = 0x02;

    /* enable rendering */
    PPUCTRL =  CTRL_BASE;
    PPUMASK = PPU_ON;

    scroll_x    = 0;
    demo_frames = 0;

    /* ================================================================
     * Main loop
     * ================================================================ */
    while (1) {
	while (PPU_VBLANK == 0);
        scroll_x++;
        OAMDMA = 0x02;
        PPUSTATUS;                  /* reset address latch            */
        PPUCTRL = CTRL_BASE;
        PPUSCR  = 0x00;             /* X scroll = 0  (status bar)     */
        PPUSCR  = 0x00;             /* Y scroll = 0                   */
        PPUSTATUS;
	while (PPU_SPHIT);   /* 前フレームの終わりを待つ */
        while (!PPU_SPHIT);         /* spin until hit detected        */
        PPUSTATUS;                  /* reset latch again              */
        PPUSCR = scroll_x;          /* X scroll for game area         */
        PPUSCR = 0x00;              /* Y scroll = 0                   */
        PPUCTRL =  CTRL_BASE | ((scroll_x >= 128) ? 0x01 : 0x00);
    }
}
