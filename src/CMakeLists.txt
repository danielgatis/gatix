SET (CMAKE_C_LINK_FLAGS "-m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/arch/i386/link.ld")
SET (CMAKE_C_FLAGS "-m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=c99")
SET (CMAKE_C_LINK_EXECUTABLE "/usr/bin/ld <CMAKE_C_LINK_FLAGS> <OBJECTS> -o <TARGET>")
SET (CMAKE_ASM_NASM_OBJECT_FORMAT "elf")

ENABLE_LANGUAGE (ASM_NASM)

INCLUDE_DIRECTORIES ("include")

FILE (GLOB_RECURSE gatix_C_SOURCES "*.c")
FILE (GLOB_RECURSE gatix_ASM_SOURCES "*.asm")

ADD_EXECUTABLE (gatix.bin ${gatix_C_SOURCES} ${gatix_ASM_SOURCES})

ADD_CUSTOM_COMMAND (
  TARGET gatix.bin POST_BUILD
  COMMENT "Building bootable ISO img"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMAND rm -fr build/iso
  COMMAND mkdir -p build/iso/boot/grub
  COMMAND cp build/src/gatix.bin build/iso/boot/gatix.bin
  COMMAND cp -R iso/* build/iso
  COMMAND grub-mkrescue -o build/iso/gatix.iso build/iso >/dev/null 2>&1
)
