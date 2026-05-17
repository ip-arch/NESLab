// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"


#define TRI_VOL  (*(APU_TRI+0))
#define TRI_LO   (*(APU_TRI+2))
#define TRI_HI   (*(APU_TRI+3))

int main(void)
{
   int i;

    while(!PPU_VBLANK) ;
    while(!PPU_VBLANK) ;
    
    APU_CHANNEL = 0x04;    /* Triangle enable */

    TRI_VOL = 0x8F;    /* Length halt */

    TRI_LO = 0xFD;     /* frequency */
    TRI_HI = 0x00;     /* start note */
    while(1);
}
