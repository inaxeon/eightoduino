;
;   8OD - Arduino form factor i8086 based SBC
;   Matthew Millman (tech.mattmillman.com)
;
;   EPROM App Master Reset Handler
;
;   This is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 2 of the License, or
;   (at your option) any later version.
;
;   This software is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with this software.  If not, see <http://www.gnu.org/licenses/>.
;

STACKSIZE	equ	6000h		;	0x72000 - 0x77FFF
STACKTOP	equ	8000h		;	0x7FFFF

HEAPSTART	equ	STACKTOP	;	0x78000
HEAPSIZE	equ 8000h		;	0x78000 - 0x7FFFF

DGROUP group

	extrn   __CMain			: far
	extrn   _edata          : byte          ; end of DATA (start of BSS)
    extrn   _end            : byte          ; end of BSS (start of STACK)

STACK   segment para stack 'STACK'
		db	(STACKSIZE) dup(?)
STACK	ends

_DATA	segment word public 'DATA'
__curbrk		dw	0FFFFh
	public	__curbrk
_DATA	ends

_BSS	segment word public 'BSS'
_BSS	ends

ROMDATA	segment word public 'ROMDATA'
ROMDATA	ends

ROMDATAE	segment word public 'ROMDATAE'
ROMDATAE	ends

START	segment word public 'START'

		public  _cstart_
_cstart_ proc near
		jmp		_startup

_cstart_ endp

START  ends

_TEXT   segment word public 'CODE'

__heap_start		dw	HEAPSTART
__heap_size			dw	HEAPSIZE

		public	__heap_start
		public	__heap_size

		public  _startup
_startup proc far

		mov		ax, seg DGROUP
		mov		es, ax
		mov		ds, ax
		
		; Zero the BSS
		mov		ax, seg DGROUP
		mov		ds, ax
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

		; Calculate length of ROMDATA section, round up to nearest word
		; Assumes first 4 bits of ROMDATA start/end address match.
		mov		ax,		seg ROMDATAE
		mov		cl,		4
		shl		ax,		cl
		mov		dx,		offset ROMDATAE
		add		ax,		dx
		mov		dx,		seg ROMDATA
		shl		dx,		cl
		sub		ax,		dx
		mov		dx,		ax
		and		dx,		1
		shr		ax,		1
		add		ax,		dx
		; Copy it to RAM
		mov		cx,		ax
		xor		di,		di
		mov		ax,		seg ROMDATA
		mov		si,		offset ROMDATA
		mov		ds,		ax
		rep		movsw

		; Setup for C code operation
		mov		ax, seg DGROUP
		mov		ss, ax
		mov		es, ax
		mov		ds, ax
		mov		ax, STACKTOP
		mov		sp, ax

		jmp		__CMain

_startup endp

	public  boot_fail_

boot_fail_ proc near
	nop
	jmp		boot_fail_

boot_fail_ endp

; Non functional Watcom specific clutter

		public  _small_code_
_small_code_    label   near

        public  CodeModelMismatch
CodeModelMismatch label near

_TEXT	ends

		end _cstart_
