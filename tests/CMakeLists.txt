INCLUDE_DIRECTORIES ("include")

FILE (GLOB_RECURSE myos_test_C_SOURCES "*.c")
FILE (GLOB_RECURSE myos_test_ASM_SOURCES "*.asm")

ADD_EXECUTABLE (myos_test.bin ${myos_test_C_SOURCES} ${myos_test_ASM_SOURCES})
