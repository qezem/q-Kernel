mkdir -p ./build/bin/ ./build/elf/ ./build/obj/

nasm -f elf32 -i ./qKernel/ ./qKernel/entry.asm -o ./build/obj/entry.o

i386-elf-gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -nostdlib -c ./qKernel/kernel.c -o ./build/obj/kernel.o
i386-elf-gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -nostdlib -c ./qKernel/drivers/VGA_driver/vga.c -o ./build/obj/vga.o

i386-elf-ld -T ./qKernel/linker.ld -o ./build/elf/kernel.elf ./build/obj/entry.o ./build/obj/kernel.o ./build/obj/vga.o
i386-elf-objcopy -O binary ./build/elf/kernel.elf ./build/bin/kernel.bin

nasm -f bin ./qKernel/boot.asm -o ./build/bin/boot.bin

cat ./build/bin/boot.bin ./build/bin/kernel.bin >qKernel.img

qemu-system-x86_64 -drive format=raw,file=qKernel.img
