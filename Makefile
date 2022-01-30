# This is a Makefile meant for GNU Make. Assert that.
ifneq (,)
This makefile requires GNU Make.
endif
 
# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := kernel.elf
 
# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.
ifeq ($(origin CC), default)
CC := cc
CPP := g++
ASM := nasm
endif
 
# Likewise, "ld" here is just a placeholder and your mileage may vary if using the
# host's "ld".
ifeq ($(origin LD), default)
LD := ld
endif
 
# User controllable CFLAGS.
CFLAGS ?= -Wall -Wextra -O2 -pipe
 
# User controllable linker flags. We set none by default.
LDFLAGS ?=
 
# Internal C flags that should not be changed by the user.
override INTERNALCFLAGS :=   \
	-I.                  \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-pic             \
	-mabi=sysv           \
	-mgeneral-regs-only  \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD				 \
	-Wmissing-field-initializers \
	-Wno-address-of-packed-member
 
override INTERNALLDFLAGS :=    \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static
 
override CFILES := $(shell find ./ -type f -name '*.c')
override CPPFILES := $(shell find ./ -type f -name '*.cpp')
override ASMFILES := $(shell find ./ -type f -name '*.asm')
override COBJ := $(CFILES:.c=.o)
override CHEADER_DEPS := $(CFILES:.c=.d)
override CPPOBJ = $(CPPFILES:.cpp=.o)
override CPPHEADER_DEPS := $(CPPFILES:.cpp=.d)
override ASMOBJ := $(ASMFILES:.asm=.o)
override ASMHEADER_DEPS := $(ASMFILES:.c=.d)

CURRENT_PATH = $(shell pwd)

.PHONY: all
all: clean $(KERNEL) move_all
	mv $(KERNEL) $(CURRENT_PATH)/../build/kernel/
 
$(KERNEL): $(COBJ) $(CPPOBJ) $(ASMOBJ)
	$(LD) $(COBJ) $(CPPOBJ) $(ASMOBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@

-include $(CHEADER_DEPS)
%.o: %.c
	mkdir -p $(CURRENT_PATH)/../build/kernel/$(@D)
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

-include $(CPPHEADER_DEPS)
%.o: %.cpp
	mkdir -p $(CURRENT_PATH)/../build/kernel/$(@D)
	$(CPP) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@
# -include $(ASMHEADER_DEPS)
%.o: %.asm
	mkdir -p $(CURRENT_PATH)/../build/kernel/$(@D)
	$(ASM) $< -f elf64 -o $@

move_all: $(COBJ) $(CPPOBJ) $(ASMOBJ)
	mv $(COBJ) $(CPPOBJ) $(ASMOBJ) $(CHEADER_DEPS) $(CPPHEADER_DEPS) $(CURRENT_PATH)/../build/kernel/
clean:
	rm -Rf $(CURRENT_PATH)/../build/
	mkdir $(CURRENT_PATH)/../build/
	mkdir $(CURRENT_PATH)/../build/kernel