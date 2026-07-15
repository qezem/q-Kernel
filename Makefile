# COMPILERS
ASM 		= nasm
CC 			= i386-elf-gcc
LD 			= i386-elf-ld
OBJCOPY = i386-elf-objcopy
QEMU 		= qemu-system-x86_64

#BUILD DIRECTORIES
BUILD_DIR = ./build
BIN_DIR 	= $(BUILD_DIR)/bin
ELF_DIR 	= $(BUILD_DIR)/elf
OBJ_DIR 	= $(BUILD_DIR)/obj

#FLAGS
CC_FLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -nostdlib -I ./qKernel/ -c

C_SOURCES = $(shell find ./qKernel -name "*.c")
C_OBJECTS = $(patsubst ./qKernel/%,$(OBJ_DIR)/%,$(C_SOURCES:.c=.o))

OBJS = $(OBJ_DIR)/entry.o $(C_OBJECTS)

all: qKernel.img

$(BIN_DIR)/boot.bin: ./qKernel/boot.asm
	mkdir -p $(BIN_DIR)
	$(ASM) -f bin $< -o $@

$(OBJ_DIR)/entry.o: ./qKernel/entry.asm
	mkdir -p $(OBJ_DIR)
	$(ASM) -f elf32 -i ./qKernel/ $< -o $@

$(OBJ_DIR)/%.o: ./qKernel/%.c
	mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $< -o $@

$(BIN_DIR)/kernel.bin: $(ELF_DIR)/kernel.elf
	$(OBJCOPY) -O binary $< $@

$(ELF_DIR)/kernel.elf: $(OBJS) ./qKernel/linker.ld
	mkdir -p $(ELF_DIR)
	$(LD) -T ./qKernel/linker.ld -o $@ $(OBJS)

qKernel.img: $(BIN_DIR)/boot.bin $(BIN_DIR)/kernel.bin
	cat $(BIN_DIR)/boot.bin $(BIN_DIR)/kernel.bin >qKernel.img

clean:
	rm -rf $(BUILD_DIR) qKernel.img

run: all
	$(QEMU) -drive format=raw,file=qKernel.img -serial stdio

.PHONY: all run clean

