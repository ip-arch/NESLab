// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
#include "ppusample.h"

enum pitch {
A1,As1,B1,
C2,Cs2,D2,Ds2,E2,F2,Fs2,G2,Gs2,A2,As2,B2,
C3,Cs3,D3,Ds3,E3,F3,Fs3,G3,Gs3,A3,As3,B3,
C4,Cs4,D4,Ds4,E4,F4,Fs4,G4,Gs4,A4,As4,B4,
C5,Cs5,D5,Ds5,E5,F5,Fs5,G5,Gs5,A5,As5,B5,
SP,FIN
};

struct note {
  enum pitch pt;
  char len;
};


struct nestimer {
  char TH, TL;
};


static const struct nestimer pulsetimer[] = {
//A1,As1,B1,
{3,248}, {3,191}, {3,137},
//C2,Cs2,D2,Ds2,E2,F2,Fs2,G2,Gs2,A2,As2,B2,
{3,86},
{3,38},
{2,249},
{2,206},
{2,166},
{2,128},
{2,92},
{2,58},
{2,26},
{1,251},
{1,223},
{1,196},
//C3,Cs3,D3,Ds3,E3,F3,Fs3,G3,Gs3,A3,As3,B3,
{1,171},
{1,147},
{1,124},
{1,103},
{1,82},
{1,63},
{1,45},
{1,28},
{1,12},
{0,253},
{0,239},
{0,225},
//C4,Cs4,D4,Ds4,E4,F4,Fs4,G4,Gs4,A4,As4,B4,
{0,213},
{0,201},
{0,189},
{0,179},
{0,169},
{0,159},
{0,150},
{0,142},
{0,134},
{0,126},
{0,119},
{0,112},
//C5,Cs5,D5,Ds5,E5,F5,Fs5,G5,Gs5,A5,As5,B5,
{0,106},
{0,100},
{0,94},
{0,89},
{0,84},
{0,79},
{0,75},
{0,70},
{0,66},
{0,63},
{0,59},
{0,56},
//SP,FIN
{0,0},
{0,0}
};

static const struct note atrain1[] =
{
{C3,8}, {SP,1}, {E4,3}, {G3,2}, {C4,2}, 
{E4,1}, {Gs3,15},
{A3,8}, {A3,1}, {As3,1}, {B3,1}, {E4,1}, {G3,1}, {Fs3,1}, {F3,1}, {Cs4,1},
{C4,1}, {E3,15},
{G3,8}, {SP,1}, {E4,3}, {G3,2}, {C4,2},
{E4,1}, {Gs3,15},
{A3,8}, {A3,1}, {As3,1}, {B3,1}, {E4,1}, {G3,1}, {Fs3,1}, {F3,1}, {Cs4,1},
{C4,1}, {E3,15},
{A3,1}, {C4,7}, {E4,1}, {F3,3}, {A3,2}, {C4,2},
{E4,1}, {A3,14}, {SP,1},
{A3,1}, {C4,7}, {E4,1}, {Fs3,3}, {A3,2}, {C4,2},
{E4,1}, {A3,11}, {Gs3,4},
{G3,8}, {SP,1}, {E4,3}, {G3,2}, {C4,2},
{E4,1}, {Gs3,15},
{A3,7}, {SP,1}, {A3,1}, {As3,1}, {B3,1}, {E4,1}, {G3,1}, {Fs3,1}, {F3,1}, {Cs4,1}, {C4,1}, {E3,3}, {F3,2}, {Fs3,2}, {G3,1}, {A3,1}, {B3,1}, {C4,1}, {SP,2}, {C2,2}, {SP,2},
{FIN,0}
};



static const struct note atrain2[] =
{
{SP,4}, {G3,4}, {SP,2},{C4,2},{SP,4}, {SP,2}, {E4,4},{SP,2}, {E4,2},{SP,4}, {E4,2},
{SP,4}, {F3,3},  {SP,5}, {F3,4}, {SP,2}, {E4,4},{SP,2}, {E4,2},{SP,4}, {E4,2},
{SP,4}, {G3,4}, {SP,2},{C4,2},{SP,4}, {SP,2}, {E4,4},{SP,2}, {E4,2},{SP,4}, {E4,2},
{SP,4}, {F3,3},  {SP,5}, {F3,4}, {SP,2}, {E4,4},{SP,2}, {E4,2},{SP,4}, {E4,2},
{SP,4}, {F3,3},  {SP,5}, {F3,4}, {SP,2}, {E4,4},{SP,2}, {E4,2},{SP,4}, {E4,2},
{SP,4}, {F3,3},  {SP,5}, {F3,4}, {SP,2}, {E4,4},{SP,2}, {E4,2},{SP,4}, {E4,2},
{SP,4}, {G3,4}, {SP,2},{C4,2},{SP,4}, {SP,2}, {E4,4},{SP,2}, {E4,2},{SP,4}, {E4,2},
{SP,4}, {F3,3},  {SP,5}, {F3,4}, {SP,2}, {E4,4},{SP,2}, {E4,2},{SP,4}, {E4,2},
{FIN,0}
};


static const struct note base[] =
{
/*A*/
{C3,1}, {SP,1}, {D3,1}, {SP,1}, {E3,1}, {SP,1}, {F3,1}, {SP,1},
{G3,1}, {SP,1}, {E3,1}, {SP,1}, {C3,1}, {SP,1}, {E3,1}, {SP,1},

{D3,1}, {SP,1}, {E3,1}, {SP,1}, {Gs3,1}, {SP,1}, {D3,1}, {SP,1},
{Gs3,1}, {SP,1}, {D3,1}, {SP,1}, {Gs3,1}, {SP,1}, {D3,1}, {SP,1},

{F3,1}, {SP,1}, {A3,1}, {SP,1}, {Fs3,1}, {SP,1}, {G3,1}, {SP,1},
{F3,1}, {SP,1}, {Cs3,1}, {SP,1}, {Fs3,1}, {SP,1}, {C4,1}, {SP,1},

{A3,1}, {SP,1}, {G3,1}, {SP,1}, {E3,1}, {SP,1}, {C3,1}, {SP,1},
{E3,1}, {SP,1}, {C3,1}, {SP,1}, {D3,1}, {SP,1}, {C3,1}, {SP,1},

{C3,1}, {SP,1}, {D3,1}, {SP,1}, {E3,1}, {SP,1}, {F3,1}, {SP,1},
{G3,1}, {SP,1}, {E3,1}, {SP,1}, {C3,1}, {SP,1}, {E3,1}, {SP,1},

{D3,1}, {SP,1}, {E3,1}, {SP,1}, {Gs3,1}, {SP,1}, {D3,1}, {SP,1},
{Gs3,1}, {SP,1}, {D3,1}, {SP,1}, {Gs3,1}, {SP,1}, {D3,1}, {SP,1},

{F3,1}, {SP,1}, {A3,1}, {SP,1}, {Fs3,1}, {SP,1}, {G3,1}, {SP,1},
{F3,1}, {SP,1}, {Cs3,1}, {SP,1}, {Fs3,1}, {SP,1}, {C4,1}, {SP,1},

{A3,1}, {SP,1}, {G3,1}, {SP,1}, {E3,1}, {SP,1}, {C3,1}, {SP,1},
{E3,1}, {SP,1}, {C3,1}, {SP,1}, {D3,1}, {SP,1}, {C3,1}, {SP,1},

/*B*/
{D3,1}, {SP,1}, {E3,1}, {SP,1}, {D3,1}, {SP,1}, {F3,1}, {SP,1},
{A3,1}, {SP,1}, {F3,1}, {SP,1}, {E3,1}, {SP,1}, {F3,1}, {SP,1},

{D3,1}, {SP,1}, {E3,1}, {SP,1}, {D3,1}, {SP,1}, {F3,1}, {SP,1},
{A3,1}, {SP,1}, {F3,1}, {SP,1}, {E3,1}, {SP,1}, {F3,1}, {SP,1},

{D3,1}, {SP,1}, {Fs3,1}, {SP,1}, {D3,1}, {SP,1}, {Gs3,1}, {SP,1},
{D3,1}, {SP,1}, {Fs3,1}, {SP,1}, {D3,1}, {SP,1}, {Gs3,1}, {SP,1},

{D3,1}, {SP,1}, {F3,1}, {SP,1}, {Gs3,1}, {SP,1}, {Fs3,1}, {SP,1},
{G3,1}, {SP,1}, {B3,1}, {SP,1}, {G3,1}, {SP,1}, {F3,1}, {SP,1},
/*A*/

{C3,1}, {SP,1}, {D3,1}, {SP,1}, {E3,1}, {SP,1}, {F3,1}, {SP,1},
{G3,1}, {SP,1}, {E3,1}, {SP,1}, {C3,1}, {SP,1}, {E3,1}, {SP,1},

{D3,1}, {SP,1}, {E3,1}, {SP,1}, {Gs3,1}, {SP,1}, {D3,1}, {SP,1},
{Gs3,1}, {SP,1}, {D3,1}, {SP,1}, {Gs3,1}, {SP,1}, {D3,1}, {SP,1},

{F3,1}, {SP,1}, {A3,1}, {SP,1}, {Fs3,1}, {SP,1}, {G3,1}, {SP,1},
{F3,1}, {SP,1}, {Cs3,1}, {SP,1}, {Fs3,1}, {SP,1}, {C4,1}, {SP,1},

{A3,1}, {SP,1}, {G3,1}, {SP,1}, {E3,1}, {SP,1}, {C3,1}, {SP,1},
{E3,1}, {SP,1}, {C3,1}, {SP,1}, {D3,1}, {SP,1}, {C3,1}, {SP,1},

{FIN,0}
};

static const struct note drum[] =
{
/*A*/
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, 
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, 

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, 
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, 

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

/*B*/
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, 
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, 

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

/*A*/

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, 
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, 

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},

{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},
{C3,1},{SP,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1}, {SP,1}, {A1,1},


{FIN,0}
};


static const int metro=10;

int sound1up(const struct note *nt) {
static int timecount=0;
	if(timecount==0) {
		timecount = nt->len*metro-1;
		*(APU_SQU1+2)=pulsetimer[nt->pt].TL;
		*(APU_SQU1+3)=pulsetimer[nt->pt].TH;
	}
	else
	   timecount--;
	return timecount;
}


int sound2up(const struct note *nt) {
static int timecount=0;
	if(timecount==0) {
		timecount = nt->len*metro-1;
		*(APU_SQU2+2)=pulsetimer[nt->pt].TL;
		*(APU_SQU2+3)=pulsetimer[nt->pt].TH;
	}
	else
	   timecount--;
   return timecount;
}

int soundTup(const struct note *nt) {
static int timecount=0;
	if(timecount==0) {
		timecount = nt->len*metro-1;
		*(APU_TRI+2)=pulsetimer[nt->pt].TL;
		*(APU_TRI+3)=pulsetimer[nt->pt].TH;
	}
	else
	   timecount--;
   return timecount;
}

int noiseup(const struct note *nt) {
static int timecount=0;
	if(timecount==0) {
		timecount = nt->len*metro-1;
		if(nt->pt==SP) APU_CHANNEL &=0xF7;
		else  APU_CHANNEL |=0x08;
		*(APU_NOISE+2)=0;
		*(APU_NOISE+3)=nt->pt<<3;
	}
	else
	   timecount--;
   return timecount;
}
int sheet1 = 0, sheet2 = 0, sheet3 = 0, sheet4 = 0;
char sound1=1, sound2=1, sound3=1, sound4 = 1;

void nmi_routine() {
	//設定3(チャンネル周期261hz,長さカウンタindex'00')
	//チャンネル周期=1789000/(出力周波数*32)-1
	if(atrain1[sheet1].pt==FIN) {
		sound1=0;
		APU_CHANNEL&=0xFE;
	}
	if(atrain2[sheet2].pt==FIN) {
		sound2=0;
		APU_CHANNEL&=0xFD;
	}
	if(base[sheet3].pt==FIN) {
		sound3=0;
		APU_CHANNEL&=0xFB;
	}
	if(drum[sheet4].pt==FIN) {
		sound4=0;
		APU_CHANNEL&=0xF7;
	}
	if(sound1) {
	  if(sound1up(&atrain1[sheet1])==0)
		  sheet1++;
	}
	if(sound2) {
	  if(sound2up(&atrain2[sheet2])==0)
		  sheet2++;
	}
	if(sound3) {
	  if(soundTup(&base[sheet3])==0)
		  sheet3++;
	}
	if(sound4) {
	  if(noiseup(&drum[sheet4])==0)
		  sheet4++;
	}
}

int main(){
    	
	//方形波
	
	//方形波ch1,2, Triangle, noiseをon
	APU_CHANNEL=0x0F;

	//設定1(デューティー比50%,長さカウンタ無効,エンベロープ(ノコギリ波)無効,ボリュームF)
	*(APU_SQU1)=0xB3;
	*(APU_SQU2)=0xB3;
	*(APU_TRI)=0xC0;
	APU_FRAME=0x00;
	*(APU_NOISE)=0x03;

	//設定2(スイープ無効)
	*(APU_SQU1+1)=0x00;
	*(APU_SQU2+1)=0x00;

	nmivec=(void*)nmi_routine;

	*PPU = 0x80;  // Enable NMI on Blanking

	while(sound1 || sound2 || sound3 || sound4);

	APU_CHANNEL=0x00;
	*PPU = 0x00;  // Disable NMI on Blanking
	while(1);
	return 0;
}

