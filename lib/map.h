


#define WRAM			(unsigned char*)0x0000

#define PPU				(unsigned char*)0x2000

#define PPU_CTRL1		(unsigned char*)0x2000
#define PPU_CTRL2		(unsigned char*)0x2001
#define PPU_STATUS		(unsigned char*)0x2002
#define PPU_SPR_ADDR	(unsigned char*)0x2003
#define PPU_SPR_DATA	(unsigned char*)0x2004
#define PPU_SCR			(unsigned char*)0x2005
#define PPU_VRAM_ADDR	(unsigned char*)0x2006
#define PPU_VRAM_DATA	(unsigned char*)0x2007


#define APU				(unsigned char*)0x4000
#define APU_SQU1		(unsigned char*)0x4000
#define APU_SQU2		(unsigned char*)0x4004
#define APU_TRI			(unsigned char*)0x4008
#define APU_NOISE		(unsigned char*)0x400C
#define APU_MOD			(unsigned char*)0x4010
#define APU_CHANNEL		(unsigned char*)0x4015

#define PAD1			(unsigned char*)0x4016
#define PAD2			(unsigned char*)0x4017

#define DMA				(unsigned char*)0x4014

#define SP_ADDR			0x03
#define SP_DATA			((unsigned char*)0x300)

#define BG_FIFO			(unsigned char*)0x400
