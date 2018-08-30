;
;   8OD - Arduino form factor i8086 based SBC
;   Matthew Millman (tech.mattmillman.com)
;
;   Boot from SPI flash routine
;
;   This code utilises a few of tricks to load
;   the system from SPI flash as fast as physically possible
;   - much faster than the C based MID driver can.
;
;   It is a realtime process which has been calibrated by
;   logic analyser. Removal of a single 'nop' will likely
;   cause the load to fail. It will work at any CPU clock
;   speed because MIDCLK is synchronous and relative to CPUCLK.
;
;   It also uses no RAM which allows the application it's
;   loading to overwrite the bootrom RAM area if needed -
;   typically 0x70000 - 0x7FFFF.
;
;   It can only load executables built by the C# application
;   'EodPgm' which can assemble simple binaries understood
;   by this code from Watcom generated HEX files.
;
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

_TEXT   segment word public 'CODE'

	public  spi_load_and_boot_

spi_load_and_boot_ proc near

	push	bx
	push	cx
	push	dx
	push	di
	push	es
	
	mov		bx,		ax

	;	Set clock to DIV2
	mov		al,		0x01
	out		SKR,	al

	; All useable chip selects as outputs
	mov		al,		0xF0
	out		PD,		al
	
	; Negative edge clock
	mov		al,		0x00
	out		SKP,	al

	; 8-bit mode for now
	mov		al,		0x00
	out		MWM,	al

	; Select flash
	mov		al,		0xFE
	out		CSEL,	al

	mov		al,		CMD_READ
	out		FMB,	al

	; Wait while the MID completes the transfer
	nop
	nop
	nop

	; Write address
	mov		al,		0x08
	out		FMB,	al

	; Wait while the MID completes the transfer
	nop
	nop
	nop

	mov		al,		0x00
	out		FMB,	al

	; Wait while the MID completes the transfer
	nop
	nop
	nop

	mov		al,		0x00
	out		FMB,	al

	; Wait while the MID completes the transfer
	nop
	nop
	nop

	; Place MID into 16-bit mode
	mov		al,		0x01
	out		MWM,	al

	; Kick off the next read
	mov		al,		0x00
	out		FMBD0,	al

	; Wait while the MID completes the transfer
	nop
	nop
	nop
	nop
	nop
	nop

	; Set string operations to count up, not down
	df	0

next_segment:
	;	Load the segment magic number
	in		al,		SMB
	xchg	al,		ah
	in		al,		FMB

	cmp		ax,		0x6501
	je		start_load

	mov		dx,		ax

	; Done or dusted at this point - de-select flash
	mov		al,		0xFF
	out		CSEL,	al

	cmp		dx,		0x6502
	je		done

	jmp		fail

start_load:
	; Kick off the next read
	out		FMBD0,	al

	; Wait while the MID completes the transfer
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	; Load the segment address word
	in		al,		SMB
	xchg	al,		ah
	in		al,		FMB
	; Kick off the next read
	out		FMBD0,	al
	mov		es,	ax
	
	; Wait while the MID completes the transfer
	nop
	nop
	nop
	nop
	nop
	nop

	; Load the segment offset word
	in		al,		SMB
	xchg	al,		ah
	in		al,		FMB
	; Kick off the next read
	out	FMBD0,		al
	mov		di,		ax

	; Wait while the MID completes the transfer
	nop
	nop
	nop
	nop
	nop
	nop

	; Load the segment length word
	in		al,		SMB
	xchg	al,		ah
	in		al,		FMB
	; Kick off the next read
	out	FMBD0,	al

	shr		ax,		1
	mov		cx,		ax

	; Wait while the MID completes the transfer
	nop
	nop
	nop
	nop
	nop

again:
	; Most of the load time is spent in this loop

	in		al,		SMB
	xchg	al,		ah
	in		al,		FMB
	; Kick off the next read
	out	FMBD0,	al

	stosw
	loop	again

	; Nothing more to load in this segment
	jmp next_segment

done:
	; If '1' was passed into this routine, boot.
	cmp		bx,		1
	je	boot

	; Otherwise return to caller

	pop		es
	pop		di
	pop		dx
	pop		cx
	pop		bx

	mov		ax,		1
	
	ret

fail:

	pop		es
	pop		di
	pop		dx
	pop		cx
	pop		bx

	mov		ax,		0
	
	ret

boot:
	; Jump from the bootrom to the app
	jmpf fword ptr 1000h,0

spi_load_and_boot_ endp

_TEXT	ends

end
