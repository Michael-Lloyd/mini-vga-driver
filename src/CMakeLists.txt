set(CMAKE_ASM_NASM_FLAGS "-f elf32")

# Compile C files
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/.build/kernel.c.o
    COMMAND ${CMAKE_C_COMPILER} -m32 -ffreestanding -fno-PIE -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c ${CMAKE_CURRENT_SOURCE_DIR}/kernel.c -o ${CMAKE_SOURCE_DIR}/.build/kernel.c.o
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/kernel.c
    COMMENT "Building kernel.c"
)

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/.build/vga.c.o
    COMMAND ${CMAKE_C_COMPILER} -m32 -ffreestanding -fno-PIE -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c ${CMAKE_CURRENT_SOURCE_DIR}/vga.c -o ${CMAKE_SOURCE_DIR}/.build/vga.c.o
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/vga.c
    COMMENT "Building vga.c"
)


# Compile assembly entry point
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/.build/kernel_entry.o
    COMMAND ${CMAKE_ASM_NASM_COMPILER} -f elf32 ${CMAKE_SOURCE_DIR}/boot/kernel_entry.asm -o ${CMAKE_SOURCE_DIR}/.build/kernel_entry.o
    DEPENDS ${CMAKE_SOURCE_DIR}/boot/kernel_entry.asm
    COMMENT "Building kernel entry point"
)

# Link everything
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/.build/kernel.bin
    COMMAND ld -m elf_i386 -T ${CMAKE_SOURCE_DIR}/boot/linker.ld -o ${CMAKE_SOURCE_DIR}/.build/kernel.bin 
            ${CMAKE_SOURCE_DIR}/.build/kernel_entry.o 
            ${CMAKE_SOURCE_DIR}/.build/kernel.c.o
            ${CMAKE_SOURCE_DIR}/.build/vga.c.o
            --oformat binary
    DEPENDS ${CMAKE_SOURCE_DIR}/.build/kernel_entry.o ${CMAKE_SOURCE_DIR}/.build/kernel.c.o ${CMAKE_SOURCE_DIR}/.build/vga.c.o
    COMMENT "Linking kernel"
)

add_custom_target(kernel.bin ALL DEPENDS ${CMAKE_SOURCE_DIR}/.build/kernel.bin)