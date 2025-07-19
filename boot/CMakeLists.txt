set(CMAKE_ASM_NASM_FLAGS "-f bin")

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/.build/boot.bin
    COMMAND ${CMAKE_ASM_NASM_COMPILER} -f bin ${CMAKE_CURRENT_SOURCE_DIR}/boot.asm -o ${CMAKE_SOURCE_DIR}/.build/boot.bin
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/boot.asm
    COMMENT "Building boot sector"
)

add_custom_target(boot.bin ALL DEPENDS ${CMAKE_SOURCE_DIR}/.build/boot.bin)