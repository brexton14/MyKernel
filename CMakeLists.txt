cmake_minimum_required(VERSION 3.28)

# Tell CMake this is bare-metal and avoid platform checks
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i686)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Define your project AFTER system setup
project(MyKernel C ASM_NASM)

# Compiler paths
set(CMAKE_C_COMPILER "C:/Kernel Enviroment/bin/i686-elf-gcc.exe")
set(CMAKE_ASM_NASM_COMPILER "C:/KernelASM/nasm.exe")

# Use C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set kernel-specific flags
set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra -nostdlib")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -nostdlib -static")

# Enable ASM for NASM
enable_language(ASM_NASM)

# Output raw binary instead of .exe
add_executable(kernel.bin
        boot/boot.asm
        src/kernel.c
        src/keyboard.c
        lib/print.c
        lib/kstdio.c
        lib/stdlib.c
)

# Prevent outputting a .exe suffix
set_target_properties(kernel.bin PROPERTIES SUFFIX "")
