// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"

#pragma rodata-name("DMC")

#include "hello_dmc.c"

#pragma rodata-name("RODATA")

int main(void){
unsigned int i=0x0;	

//DMCチャネル

//設定1(ループ,サンプリングE)
 

//DMCをon
	APU_CHANNEL = 0x00;
	while(1) {
		for(i=0; i< 60; i++) while(!PPU_VBLANK);

		*(APU_MOD)=0x4A;
		*(APU_MOD+1)=0x40;
		*(APU_MOD+2)=(char)((int)hello_dmc>>6); 
		*(APU_MOD+3)=0x83; /* sample length = 2097 */
		APU_CHANNEL=0x10; /* DMC start */

		for(i=0; i< 60*10; i++) while(!PPU_VBLANK);
		APU_CHANNEL = 0x00;
	}
	
	return 0;
}

