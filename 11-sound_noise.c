// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"


#define NOI_VOL  (*(APU_NOISE+0))
#define NOI_LO   (*(APU_NOISE+2))
#define NOI_HI   (*(APU_NOISE+3))

int main(void)
{
   int i;

    while(!PPU_VBLANK) ;
    while(!PPU_VBLANK) ;
    
    APU_CHANNEL = 0x08;    /* Noise enable */

    NOI_VOL = 0x3F;    /* Length halt */

    NOI_LO = 0x88;     /* Noise mode, period */
    NOI_HI = 0x00;     /* Length counter */
    while(1);
}
