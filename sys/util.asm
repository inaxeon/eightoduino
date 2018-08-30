;
;   8OD - Arduino form factor i8086 based SBC
;   Matthew Millman (tech.mattmillman.com)
;
;   Misc routines implemented as ASM
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

CONFIG_REG		equ	2h			;	CONFIG register
CONFIG_RESET	equ	8000h		;	Suicide bit

extrn   _cstart_			: far

_TEXT   segment word public 'CODE'

public  hard_reset_

hard_reset_ proc near
		mov		ax,		CONFIG_RESET
		out		CONFIG_REG,		ax
		jmp		_cstart_
hard_reset_ endp

_TEXT	ends

end