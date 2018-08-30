;
;   8OD - Arduino form factor i8086 based SBC
;   Matthew Millman (tech.mattmillman.com)
;
;   Entry point for "boot from flash" applications
;
;   This is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 2 of the License, or
;   (at your option) any later version.
;
;   this software is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with this software.  If not, see <http://www.gnu.org/licenses/>.
;

STACKTOP		equ	8000h		;	0x27FFF

HEAPSTART		equ	STACKTOP	;	0x28000
HEAPSIZE		equ 8000h		;	0x28000 - 0x2FFFF

CONFIG_REG		equ	2h			;	CONFIG register
CONFIG_GINT		equ	1h			;	GINT bit


DGROUP group

	extrn	hard_reset_				: near
	extrn	__g_shadowRegisters		: near
	extrn   interrupt_handler_		: near
	extrn   __CMain					: far
	extrn   _edata					: byte          ; end of DATA (start of BSS)
    extrn   _end					: byte          ; end of BSS (start of STACK)

STACK   segment para stack 'STACK'
		db	(4) dup(?)
STACK	ends

_DATA	segment word public 'DATA'
__curbrk		dw	0FFFFh
	public	__curbrk
_DATA	ends

_BSS	segment word public 'BSS'
_BSS	ends

BEGDATA	segment word public 'BEGDATA'
BEGDATA	ends

VECTORS	segment word public 'VECTORS'
		
		org		0h
		
		; Divide by 0
		dw		offset	hard_reset_
		dw		seg		hard_reset_
		; Single step
		dw		offset	hard_reset_
		dw		seg		hard_reset_
		; NMI
		dw		offset	nm_interrupt
		dw		seg		nm_interrupt
		; Breakpoint
		dw		offset	hard_reset_
		dw		seg		hard_reset_
		; Overflow
		dw		offset	hard_reset_
		dw		seg		hard_reset_

VECTORS	ends

START	segment word public 'START'

		public  _cstart_
		; This is where the bootrom jumps to when it's done loading
_cstart_ proc near

		mov		ax, seg DGROUP
		mov		ds, ax
		mov		es, ax
		
		; Zero the BSS
		mov     cx, offset DGROUP : _end
        mov     di, offset DGROUP : _edata
        sub     cx, di
        mov     al, 0
        rep     stosb

		df		0

		; And zero the heap head otherwise there's some f***ing stupid
		; problem where it occasionally gets stuck in an infinte loop
		; on the first call to malloc() despite __HeapInit() being called.
		mov		di,		HEAPSTART
		mov		cx,		0x80
		mov		ax,		0
		rep		stosw

		; Setup for C code operation
		mov		ax, seg DGROUP
		mov		ss, ax
		mov		ds, ax
		mov		es, ax
		mov		ax, STACKTOP
		mov		sp, ax

		jmp		__CMain

_cstart_ endp

START  ends

_TEXT   segment word public 'CODE'

nm_interrupt proc near
		
		; Save the AX register which gets modified in this routine.
		; The rest will be saved to the stack by interrupt_handler().
		; 
		; *** CAVEAT EMPTOR ***
		; This interrupt mechanism does not save SS, DS or ES, because
		; it's using the 'small' model, and these *shouldn't* be modified
		; in interrupt_handler(), unless some insolent code specifically
		; does, likely by using 'far' pointers. In this case these registers
		; need to be saved to the stack too.
		push	ax

		; Disable interrupts globally
		and		word ptr __g_shadowRegisters + CONFIG_REG,	not CONFIG_GINT
		mov		ax,		word ptr __g_shadowRegisters + CONFIG_REG
		out		CONFIG_REG,	ax

		; Call C interrupt handler
		; This will push/pop BX, CX, DX, SI, DI and BP registers to the stack.
		call	interrupt_handler_

		; Re-enable interrupts globally
		; Makes sure that anything which happened while we were
		; in interrupt_handler() re-triggers NMI interrupt
		or		word ptr __g_shadowRegisters + CONFIG_REG,	CONFIG_GINT
		mov		ax,		word ptr __g_shadowRegisters + CONFIG_REG
		out		CONFIG_REG,	ax

		pop		ax

		iret

nm_interrupt endp

__heap_start		dw	HEAPSTART
__heap_size			dw	HEAPSIZE

		public	__heap_start
		public	__heap_size

; Non functional Watcom specific clutter

		public  _small_code_
_small_code_    label   near

        public  CodeModelMismatch
CodeModelMismatch label near

        public  "C",_HShift
_HShift    db 12

_TEXT	ends

		end _cstart_
