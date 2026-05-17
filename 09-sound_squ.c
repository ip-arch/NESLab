// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"


#define SQ1_VOL  (*(APU_SQU1+0))
#define SQ1_LO   (*(APU_SQU1+2))
#define SQ1_HI   (*(APU_SQU1+3))

int main(void)
{
   int i;

    while(!PPU_VBLANK) ;
    while(!PPU_VBLANK) ;
    
    APU_CHANNEL = 0x01;    /* Pulse1 enable */

    SQ1_VOL = 0xBF;    /* volume */

    SQ1_LO = 0xFD;     /* frequency */
    SQ1_HI = 0x00;     /* start note */
    while(1);
}
