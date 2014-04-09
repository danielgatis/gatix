SET (CMAKE_C_LINK_FLAGS "-m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/link.ld")
SET (CMAKE_C_FLAGS "-m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=c99")
SET (CMAKE_C_LINK_EXECUTABLE "/usr/bin/ld <CMAKE_C_LINK_FLAGS> <OBJECTS> -o <TARGET>")
SET (CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

ENABLE_LANGUAGE (ASM_NASM)

INCLUDE_DIRECTORIES ("include")

FILE (GLOB_RECURSE myos_C_SOURCES "*.c")
FILE (GLOB_RECURSE myos_ASM_SOURCES "*.asm")

ADD_EXECUTABLE (myos.bin ${myos_C_SOURCES} ${myos_ASM_SOURCES})

ADD_CUSTOM_COMMAND (
  TARGET myos.bin POST_BUILD
  COMMENT "Building bootable ISO img"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMAND rm -fr build/iso
  COMMAND mkdir -p build/iso/boot/grub
  COMMAND cp build/src/myos.bin build/iso/boot/myos.bin
  COMMAND cp -R iso/* build/iso
  COMMAND grub-mkrescue -o build/iso/myos.iso build/iso >/dev/null 2>&1
)
