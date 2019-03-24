# assertion in case ARCH is not set or is not in the list
ifndef ARCH
$(error ARCH not set)
endif

ALLOWED_ARCHS := $(shell ls platform)

# assertion in case ARCH is not in the list
ifeq ($(filter $(ARCH), $(ALLOWED_ARCHS)), )
$(error Set proper ARCH variable. Variants: $(ALLOWED_ARCHS))
endif

PREFIX := arm-none-eabi-
GCC    := $(PREFIX)gcc
LD     := $(PREFIX)ld
OCPY   := $(PREFIX)objcopy
QEMU   := qemu-system-arm

CPPFLAGS  := -mcpu=cortex-a7 -fpic -ffreestanding -fno-exceptions -g

IMGDIR    := out/image
PLATDIR   := platform/$(ARCH)
GENDIR    := generic

INCLUDE   := -I$(PLATDIR)/include -I$(GENDIR)/include

CPPFLAGS += $(INCLUDE)

# platform dependent object list
OBJDIR_P := out/obj_p
OBJS_P   := startup.o
OBJS_P	 := $(addprefix $(OBJDIR_P)/, $(OBJS_P))

# generic files objects
OBJDIR_G := out/obj_g
OBJS_G   := entry.o debugger.o
OBJS_G	 := $(addprefix $(OBJDIR_G)/, $(OBJS_G))

.PHONY: clean raspi raspi2 prepare qemu-run qemu-run-gdb

all: $(ARCH)

prepare:
	mkdir -p $(IMGDIR) $(OBJDIR_P) $(OBJDIR_G)

$(ARCH): prepare        \
	$(OBJS_G)           \
	$(OBJS_P)           \
	$(IMGDIR)/image.elf \
	$(IMGDIR)/image.bin

$(OBJDIR_P)/startup.o:
	$(GCC) -c $(CPPFLAGS) $(PLATDIR)/startup.s -o $@

$(OBJDIR_G)/entry.o:
	$(GCC) -c $(CPPFLAGS) entry.cpp -o $@

$(OBJDIR_P)/%.o: $(PLATDIR)/%.cpp
	$(GCC) -c $(CPPFLAGS) $< -o $@

$(OBJDIR_G)/%.o: $(GENDIR)/%.cpp
	$(GCC) -c $(CPPFLAGS) $< -o $@

$(IMGDIR)/image.elf:
	$(LD) -T $(PLATDIR)/entry.ld $(OBJDIR_G)/*.o $(OBJDIR_P)/*.o -o $@

$(IMGDIR)/image.bin:
	$(OCPY) -O binary $(IMGDIR)/image.elf $@

qemu-run: raspi2
	$(QEMU) -m 256 -M raspi2 -nographic -kernel $(IMGDIR)/image.elf

qemu-run-gdb: raspi2
	$(QEMU) -m 256 -M raspi2 -nographic -s -S -kernel $(IMGDIR)/image.elf

clean:
	git clean -xdf
