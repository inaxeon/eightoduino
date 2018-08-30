;
;   8OD - Arduino form factor i8086 based SBC
;   Matthew Millman (tech.mattmillman.com)
;
;   Entry point allowing RAM based apps to call the load_and_boot routine
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

APPENTRY	segment word public 'APPENTRY'

		public  _appentry_load_and_boot_
_appentry_load_and_boot_ proc near

		; Preserve the parameter
		mov		bx,	ax

		; Set the segment registers back to the correct values
		; for execution of bootrom code
		mov		ax, seg DGROUP
		mov		ss, ax
		mov		es, ax
		mov		ds, ax
		mov		ax, STACKTOP
		mov		sp, ax

		mov		ax,	bx
		jmp		__LoadAndBoot

_appentry_load_and_boot_ endp

APPENTRY  ends

end