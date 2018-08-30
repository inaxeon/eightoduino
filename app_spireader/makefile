SYS = ..\sys
OBJ = .\obj
CFLAGS = -q -0 -fpc -s -d0 -od -ms -zm -i=$(SYS)
ASMFLAGS = -q -0 -fpc -s -d0
SYSCOBJS = stubs.obj uart.obj mid.obj i2c.obj spiflash.obj adc.obj eod_io.obj cmain086.obj
SYSASMOBJS = cstrt086.obj util.obj

.c.obj: *.h
    wcc $(CFLAGS) $<

.asm.obj:
    wasm $(ASMFLAGS) $<

app.hex: main.obj $(SYSCOBJS) $(SYSASMOBJS)
    wlink name app.hex file { $< }

$(SYSCOBJS): $(SYS)\*.c $(SYS)\*.h
    wcc $(CFLAGS) $(SYS)\$*.c

$(SYSASMOBJS): $(SYS)\*.asm
    wasm $(ASMFLAGS) $(SYS)\$*.asm

clean: .symbolic
    rm -f *.obj *.hex *.err *.map *.bin
