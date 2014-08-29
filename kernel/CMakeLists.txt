CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (kernel)

SET (CMAKE_C_LINK_FLAGS "-m elf_i386 -T${PROJECT_SOURCE_DIR}/link.ld")
SET (CMAKE_C_FLAGS "-m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Werror -lgcc -g -gdwarf-2")
SET (CMAKE_C_LINK_EXECUTABLE "/usr/bin/ld <CMAKE_C_LINK_FLAGS> <OBJECTS> -o <TARGET>")
SET (CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")

ENABLE_LANGUAGE (ASM_NASM)

INCLUDE_DIRECTORIES ("include")

FILE (GLOB_RECURSE C_SOURCES "*.c")
FILE (GLOB_RECURSE ASM_SOURCES "*.asm")

ADD_EXECUTABLE (kernel.bin ${C_SOURCES} ${ASM_SOURCES})

ADD_CUSTOM_COMMAND (
  TARGET kernel.bin POST_BUILD
  COMMENT "Building debug symbols"
  COMMAND objcopy --only-keep-debug kernel.bin kernel.bin.sym
  COMMAND objcopy --strip-debug kernel.bin
)
