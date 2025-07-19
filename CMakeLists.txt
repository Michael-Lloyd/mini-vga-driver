cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER gcc)
find_program(CMAKE_ASM_NASM_COMPILER nasm)

project(vga_driver ASM_NASM C)

# Force build output to .build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/.build)

set(CMAKE_C_FLAGS "-m32 -ffreestanding -fno-PIE -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra")
set(CMAKE_ASM_NASM_FLAGS "-f elf32")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <FLAGS> -o <OBJECT> <SOURCE>")

enable_language(ASM_NASM)

add_subdirectory(boot)
add_subdirectory(src)

add_custom_target(vga_test.img ALL
    COMMAND dd if=/dev/zero of=${CMAKE_SOURCE_DIR}/.build/vga_test.img bs=512 count=2880
    COMMAND dd if=${CMAKE_SOURCE_DIR}/.build/boot.bin of=${CMAKE_SOURCE_DIR}/.build/vga_test.img bs=512 count=1 conv=notrunc
    COMMAND dd if=${CMAKE_SOURCE_DIR}/.build/kernel.bin of=${CMAKE_SOURCE_DIR}/.build/vga_test.img bs=512 seek=1 conv=notrunc
    DEPENDS boot.bin kernel.bin
    COMMENT "Creating bootable disk image"
)

add_custom_target(run
    COMMAND qemu-system-x86_64 -fda ${CMAKE_SOURCE_DIR}/.build/vga_test.img -m 128 -vga std
    DEPENDS vga_test.img
    COMMENT "Running VGA driver in QEMU"
)