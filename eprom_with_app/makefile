SYS = ..\sys
CFLAGS = -q -0 -fpc -s -d0 -od -ms -i=$(SYS)
ASMFLAGS = -q -0 -fpc -s -d0

SYSCOBJS = cmain086.obj stubs.obj uart.obj mid.obj spiflash.obj adc.obj eod_io.obj
SYSASMOBJS = util.obj

.c.obj:
    wcc $(CFLAGS) $<

.asm.obj:
    wasm $(ASMFLAGS) $<

epromapp.hex: cstrt086.obj main.obj $(SYSCOBJS) $(SYSASMOBJS)
    wlink name epromapp.hex file { $< }

$(SYSCOBJS): $(SYS)\*.c $(SYS)\*.h
    wcc $(CFLAGS) $(SYS)\$*.c

$(SYSASMOBJS): $(SYS)\*.asm
    wasm $(ASMFLAGS) $(SYS)\$*.asm

clean: .symbolic
    rm -f *.obj *.hex *.err *.map *.bin
