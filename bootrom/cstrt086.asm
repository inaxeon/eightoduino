;
;   8OD - Arduino form factor i8086 based SBC
;   Matthew Millman (tech.mattmillman.com)
;
;   Bootrom Master Reset Handler
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

include "defs.inc"

	extrn   _appentry_load_and_boot_ : far

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

		mov		ax,		seg DGROUP
		mov		es,		ax
		mov		ds,		ax

		; Set the PCF8584 into Intel bus mode
		; This must be done before any other memory writes due to a quirky
		; mechanism, detailed in the datasheet.
		mov		al,		0x80
		out		PCF8584_S1,	al
		
		; Zero the BSS
		mov		ax,		seg DGROUP
		mov		ds,		ax
		mov		cx,		offset DGROUP : _end
		mov		di,		offset DGROUP : _edata
		sub		cx,		di
		mov		al,		0
		rep		stosb

		df		0

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
		mov		ax,		seg DGROUP
		mov		ss,		ax
		mov		es,		ax
		mov		ds,		ax
		mov		ax,		STACKTOP
		mov		sp,		ax

		jmp		__CMain

		; Won't ever be reached. This is here just so the symbol is referenced,
		; and therefore won't be stripped by the optimiser.
		jmp		_appentry_load_and_boot_

_startup endp

; Non functional Watcom specific clutter

		public  _small_code_
_small_code_ label near

        public  CodeModelMismatch
CodeModelMismatch label near

_TEXT	ends

		end _cstart_
