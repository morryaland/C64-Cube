# sdcc C64 Makefile
TARGET = bin/main.prg
OBJECTS = obj/main.rel obj/draw.rel obj/cube.rel obj/cam.rel obj/3d.rel
LIBS = c64.lib

SDKDIR = .

SDCCTARGET = -mmos6502 -D__C64__
SDCCOPT = --max-allocs-per-node 25000 --opt-code-speed --allow-unsafe-read --use-non-free
SDCCDEBUG = --i-code-in-asm
SDKINC = -I $(SDKDIR)/include

CFLAGS = $(SDCCTARGET) $(SDCCOPT) $(SDCCDEBUG) $(SDKINC) --less-pedantic
LDFLAGS = -L $(SDKDIR)/lib -mmos6502 --no-std-crt0

CRTPRG = $(SDKDIR)/lib/c64_prg_crt0.rel
CRTCART =  $(SDKDIR)/lib/c64_cart_crt0.rel


SDCC=sdcc
SDAS=sdas6500
SDAR=sdar
MAKEBIN=makebin

all: $(TARGET)

.PRECIOUS: bin/%.rel bin/%.ihx

bin/%.prg: $(OBJECTS)
	$(SDCC) $(LDFLAGS) --code-loc 0x07ff --data-loc 0x12 --xram-loc 0xc000 $(CRTPRG) -l $(LIBS) $^ -o $@.ihx
	$(MAKEBIN) -o 0x07ff -s 0xd000 -p $@.ihx $@
	size --target=binary $@

obj/%.rel: src/%.c
	$(SDCC) $(CFLAGS) -c -o $@ $<

obj/%.rel: src/%.s
	$(SDAS) -jxlosp $@ $<

run: $(TARGET)
	x64sc $(TARGET)

clean:
	rm bin/* obj/*
