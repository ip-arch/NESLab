; SPDX-License-Identifier: GPL-3.0-or-later
; Copyright (C) 2026 Naohiko Shimizu <nshimizu@ip-arch.jp>
;
; Startup code for cc65 (NES version)
;
; by Groepaz/Hitmen <groepaz@gmx.net>
; based on code by Ullrich von Bassewitz <uz@cc65.org>
;

        .export         _exit
	.export   _irqvec, _nmivec
	.export   _sei, _cli
        .export         __STARTUP__ : absolute = 1      ; Mark as startup
        .import         initlib, donelib, callmain
        .import         push0, _main, zerobss, copydata
        .import         ppubuf_flush

        ; Linker generated symbols
        .import         __RAM_START__, __RAM_SIZE__
        .import         __STACK_START__, __STACK_SIZE__
        .import         __ROM0_START__, __ROM0_SIZE__
        .import         __STARTUP_LOAD__,__STARTUP_RUN__, __STARTUP_SIZE__
        .import         __CODE_LOAD__,__CODE_RUN__, __CODE_SIZE__
        .import         __RODATA_LOAD__,__RODATA_RUN__, __RODATA_SIZE__

        .include        "zeropage.inc"
        .include        "nes.inc"

	.ifndef		__NES_MIRRORING__
        		__NES_MIRRORING__ = 1
	.endif

; ------------------------------------------------------------------------
; 16 bytes INES header

.segment        "HEADER"

;    +--------+------+------------------------------------------+
;    | Offset | Size | Content(s)                               |
;    +--------+------+------------------------------------------+
;    |   0    |  3   | 'NES'                                    |
;    |   3    |  1   | $1A                                      |
;    |   4    |  1   | 16K PRG-ROM page count                   |
;    |   5    |  1   | 8K CHR-ROM page count                    |
;    |   6    |  1   | ROM Control Byte #1                      |
;    |        |      |   %####vTsM                              |
;    |        |      |    |  ||||+- 0=Horizontal mirroring      |
;    |        |      |    |  ||||   1=Vertical mirroring        |
;    |        |      |    |  |||+-- 1=SRAM enabled              |
;    |        |      |    |  ||+--- 1=512-byte trainer present  |
;    |        |      |    |  |+---- 1=Four-screen mirroring     |
;    |        |      |    |  |                                  |
;    |        |      |    +--+----- Mapper # (lower 4-bits)     |
;    |   7    |  1   | ROM Control Byte #2                      |
;    |        |      |   %####0000                              |
;    |        |      |    |  |                                  |
;    |        |      |    +--+----- Mapper # (upper 4-bits)     |
;    |  8-15  |  8   | $00                                      |
;    | 16-..  |      | Actual 16K PRG-ROM pages (in linear      |
;    |  ...   |      | order). If a trainer exists, it precedes |
;    |  ...   |      | the first PRG-ROM page.                  |
;    | ..-EOF |      | CHR-ROM pages (in ascending order).      |
;    +--------+------+------------------------------------------+

        .byte   $4e,$45,$53,$1a ; "NES"^Z
        .byte   2               ; ines prg  - Specifies the number of 16k prg banks.
        .byte   1               ; ines chr  - Specifies the number of 8k chr banks.
        .byte   __NES_MIRRORING__   ; ines mir  - Specifies VRAM mirroring of the banks.
        .byte   %00000000       ; ines map  - Specifies the NES mapper used.
        .byte   0,0,0,0,0,0,0,0 ; 8 zeroes


; ------------------------------------------------------------------------
; Place the startup code in a special segment.

.segment        "STARTUP"

start:

; Set up the CPU and System-IRQ.

        sei
        cld
        ldx     #0

        txs

; Clear the BSS data.

        jsr     zerobss

; Initialize the data.
        jsr     copydata

; Set up the stack.

        lda     #<(__STACK_START__ + __STACK_SIZE__)
        sta     sp
        lda     #>(__STACK_START__ + __STACK_SIZE__)
        sta     sp+1            ; Set argument stack ptr

; Call the module constructors.

        jsr     initlib

; Set interrupts vectors
	  LDA     #<(_rts)
          STA     _irqvec  
	  LDA     #>(_rts)
          STA     _irqvec+1
	  LDA     #<(_rts)
          STA     _nmivec  
	  LDA     #>(_rts)
          STA     _nmivec+1
; ---------------------------------------------------------------------------
; Push the command-line arguments; and, call main().

        jsr     callmain

; Call the module destructors. This is also the exit() entry.

_exit:  jsr     donelib         ; Run module destructors

; Reset the NES.

        jmp start

; ------------------------------------------------------------------------
; System V-Blank Interrupt
; Updates PPU Memory (buffered).
; Updates VBLANK_FLAG and tickcount.
; ------------------------------------------------------------------------

nmi:    pha
        tya
        pha
        txa
        pha

	JSR	_nmired

        pla
        tax
        pla
        tay
        pla
	RTI                    ; Return from NMI

; Interrupt exit

irq:
	   CLD
           PHA
           TXA
           PHA
	   TYA
	   PHA
	   JSR _irqred
_irq:      
	   PLA
	   TAY
	   PLA
	   TAX
	   PLA
	   RTI                    ; Return from all IRQ interrupts
irq2:
irq1:
timerirq:
        rti

_nmired:
	JMP	(_nmivec)
_irqred:
           JMP	(_irqvec)

_rts:
	  RTS
_sei:
	  SEI
	  RTS
_cli:
	  CLI
	  RTS

.bss
_irqvec: .word	0
_nmivec: .word	0

; ---------------------------------------------------------------------------
; ------------------------------------------------------------------------
; hardware vectors
; ------------------------------------------------------------------------

.segment "VECTORS"

        .word   nmi         ; $fffa vblank nmi
        .word   start       ; $fffc reset
        .word   irq         ; $fffe irq / brk

; ------------------------------------------------------------------------
; character data
; ------------------------------------------------------------------------

.segment "CHARS"

        .include        "neschar.inc"


