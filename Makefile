###############################################################################
# (GNU make is required)
# Usage:
# 		To comple .c to .s	: make x.s
# 		To comple to .nes	: make x.nes
# 		To run emulator		: make x.run
#
# 		cha-rom -> neschar.inc (ascii code)
# 		memory map -> map.h
###############################################################################
# 2014-12-19 : Initial vertion by T.Furukawa	based on AISoC's Makefile
###############################################################################
ifndef SRCDIR
SRCDIR = .
endif
NESDIR		= $(SRCDIR)/../nes
NESEXE		= $(NESDIR)/debug/obj_dir/VNES

M65CDIR		?= /opt/cc65
M65C		= $(M65CDIR)/bin/cc65
#M65ASM		= $(M65CDIR)/bin/ca65 --include-dir $(M65CDIR)/asminc
M65ASM		= $(M65CDIR)/bin/ca65 
M65LD		= $(M65CDIR)/bin/ld65
M65CFG		= $(SRCDIR)/lib/nes.cfg
M65LIB		= $(M65CDIR)/share/cc65/lib/nes.lib
EMULATOR	= ./emulators/fceux-2.6.6-win64/fceux64.exe
READNES		= ./emulators/ReadNES3.exe
INPUTS		= $(wildcard *.c)
OUTPUTS		= $(INPUTS:.c=.nes)
FILE		= lib/ppu.h lib/apu.h lib/pad.h lib/map.h
VPATH		= $(SRCDIR):$(SRCDIR)/lib
ifndef EDITOR
EDITOR		= $(SRCDIR)/Terapad/TeraPad.exe
endif
MIRROR		= 1

all: $(M65C) $(OUTPUTS)

$(M65C):
	cd $(M65CDIR); make
$(NESEXE):
	cd $(NESDIR); make sim

$(FILE):

clean:
	rm -f *.s *.o *.nes *.hex *~ *.cha *.prg *.txt *.bin
	
dist-clean:clean
	cd $(M65CDIR); make clean;


################################
# suffix rules
################################
.SUFFIXES:  .c .hex .s .nes .run

%.s:$(M65C) %.c $(FILE)
	$(M65C) $(CFLAGS) -Or -I./lib $*.c

%.o:$(M65C) %.s
	$(M65ASM) $*.s

%.nes:%.s crt0.o
	$(M65ASM) $*.s
	$(M65LD) -o $*.nes -C $(M65CFG) $*.o crt0.o $(M65LIB)

crt0.o:$(M65C) crt0.s neschar.inc
	$(M65ASM) -D__NES_MIRRORING__=$(MIRROR) -I$(SRCDIR) -I$(SRCDIR)/lib $(SRCDIR)/lib/crt0.s -o $@

%.rom:%.nes
	$(READNES) $<

%.run:%.nes
	$(EMULATOR) $<

game:game.nes
	$(EMULATOR) $<

repair:
	cp .game.c.bak game.c
	cp .game.h.bak game.h
	
edit:game.c
	$(EDITOR) $< &


%.cha:%.nes
	( PRG_N=`od -v -An -t x1 $< |awk 'NR==1 {print strtonum("0x" $$5)*0x4000/0x10}'`; \
	  CHA_N=`od -v -An -t x1 $< |awk 'NR==1 {print strtonum("0x" $$6)*0x2000/0x10}'`; \
	  od -v -An -t x1 $< |awk "NR>$$PRG_N+1&&NR<=($$CHA_N+$$PRG_N+1)" > $@ ; )
	  
%.prg:%.nes
	( PRG_N=`od -v -An -t x1 $< |awk 'NR==1 {print strtonum("0x" $$5)*0x4000/0x10}'`; \
	  CHA_N=`od -v -An -t x1 $< |awk 'NR==1 {print strtonum("0x" $$6)*0x2000/0x10}'`; \
	  od -v -An -t x1 $< |awk "NR>1&&NR<=$$PRG_N+1" > $@ ; )

%.sim:%.prg %.cha %.nes $(NESEXE)
	(cd $(NESDIR); make sim)
	cp $*.prg prg.txt
	cp $*.cha cha.txt
	$(NESEXE) $*.nes


