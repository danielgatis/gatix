INCLUDE_DIRECTORIES ("include")

FILE (GLOB_RECURSE gatix_test_C_SOURCES "*.c")
FILE (GLOB_RECURSE gatix_test_ASM_SOURCES "*.asm")

ADD_EXECUTABLE (gatix_test.bin ${gatix_test_C_SOURCES} ${gatix_test_ASM_SOURCES})
