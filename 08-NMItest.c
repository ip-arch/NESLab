// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"


void set_scroll(char x, char y) {
	PPUSCR = x;	
	PPUSCR = y;
}

void init_PPU () {
	PPUCTRL = 0x80; // Enable NMI on blanking start
	PPUMASK = 0x00;
}

void init_padIO () {
	*PAD1 = 1;
	*PAD1 = 0;
}

void read_padIO(char *b) {
	char i;

	init_padIO();
	for(i = 0; i < 8; i++)
		b[i] = *PAD1;
}

void set_sprite ( char y, char data, char flag, char x) {
	OAMDAT = y;
	OAMDAT = data;
	OAMDAT = flag;
	OAMDAT = x;
}

char sx = 40;
char sy = 30;
char buttons[8],i;

void nmi_routine() {

	set_scroll(0,0);

	//書き込むスプライトのアドレス指定
	OAMADR = 0x00;

	//スプライトデータ
	set_sprite(sy, 0x41, 0x80, sx);
			


	//パッド読み込み
	read_padIO(buttons);		

	if(buttons[7] & 0x01) {
		sx += 2;
	}
	if(buttons[5] & 0x01) {
		sy += 2;
	}
	return;
}

char main () {

	nmivec=(void*)nmi_routine;

	while(!PPU_VBLANK);

	init_PPU();

	SetPPUAdr(0x3f10); 
	PPUDAT = 0x0f;
	PPUDAT = 0x01;
	PPUDAT = 0x10;
	PPUDAT = 0x20;

	PPUMASK = 0x1e;

	while(1) ;
}
