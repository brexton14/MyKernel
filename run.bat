@echo off
cd cmake-build-debug
qemu-system-i386 -kernel kernel.bin
pause