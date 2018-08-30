;
;   8OD - Arduino form factor i8086 based SBC
;   Matthew Millman (tech.mattmillman.com)
;
;   Boot from mapped memory loader
;
;   This can only load executables built by the C# application
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

MAXLOAD	equ	0x8000 ; Maximum to load before shifting the segment registers

_TEXT   segment word public 'CODE'

	public  xip_load_and_boot_

xip_load_and_boot_ proc near

	push	bx
	push	cx
	push	di
	push	es
	push	si
	push	ds
	push	bp

	; move first parameter (1 = boot, 0 = return) into BX
	mov		bx,		ax

	; move second parameter (segment addr) into DS
	mov		ds,		dx

	xor		si,		si

next_segment:
	;	Load the segment magic number
	mov		ax,		word ptr[si];
	cmp		ax,		0x6501
	je		start_load

	cmp		ax,		0x6502
	je		done

	jmp		fail

start_load:

	; Load the segment address word
	add		si,		2
	mov		ax,		word ptr[si];
	mov		es,		ax

	; Load the segment offset word
	add		si,		2
	mov		ax,		word ptr[si];
	mov		di,		ax

	; Load the segment length word
	add		si,		2
	mov		ax,		word ptr[si];
	shr		ax,		1
	mov		dx,		ax

	; Copy data to the destination
	add		si,		2

again:
	; Shuffle the DS segment along
	mov		ax,		si
	mov		cl,		4
	shr		ax,		cl
	mov		bp,		ds
	add		bp,		ax
	mov		ds,		bp
	and		si,		0xF

	cmp		dx,		MAXLOAD
	jae		more

	mov		cx,		dx
	jmp		next

more:
	mov		cx,		MAXLOAD

next:
	sub		dx,		cx
	rep		movsw

	cmp		dx,		0
	jne		again

	; Nothing more to load in this segment
	jmp		next_segment

done:
	; If '1' was passed into this routine, boot.
	cmp		bx,		1
	je		boot

	; Otherwise return to caller

	pop		bp
	pop		ds
	pop		si
	pop		es
	pop		di
	pop		cx
	pop		bx
	mov		ax,		1
	ret

fail:
	pop		bp
	pop		ds
	pop		si
	pop		es
	pop		di
	pop		cx
	pop		bx
	mov		ax,		0
	ret

boot:
	; Jump from the bootrom to the app

	jmpf fword ptr 1000h,0

xip_load_and_boot_ endp

_TEXT	ends

end
