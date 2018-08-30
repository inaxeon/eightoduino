;
;   8OD - Arduino form factor i8086 based SBC
;   Matthew Millman (tech.mattmillman.com)
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

	extrn   __CMain				     : far
	extrn   _edata					 : byte          ; end of DATA (start of BSS)
    extrn   _end					 : byte          ; end of BSS (start of STACK)
	extrn   __LoadAndBoot			 : far


; TP3465

SMB		equ		0x40
FMB		equ		0x41
FMBD0	equ		0x42
CSEL	equ		0x4A
SKP		equ		0x4B
MWM		equ		0x4C
SKR		equ		0x4D
PD		equ		0x4F

; SPI Flash

BOOT_OFFSET	equ	0x80000
CMD_READ	equ	0x03

; PCF8584

PCF8584_S1		equ		0x51
