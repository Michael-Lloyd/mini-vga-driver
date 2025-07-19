#!/bin/bash

# Check if kernel binary exists
if [ ! -f ".build/kernel.bin" ]; then
    echo "Error: kernel.bin not found. Please build the project first."
    exit 1
fi

# Start GDB with the kernel binary and connect to QEMU
echo "Starting GDB and connecting to QEMU debug server..."
echo "Useful commands:"
echo "  - 'c' to continue execution"
echo "  - 'b kernel_main' to set breakpoint at kernel_main"
echo "  - 'si' to step one instruction"
echo "  - 'ni' to step over one instruction"
echo "  - 'info registers' to see register values"
echo "  - 'x/100xb 0xA0000' to examine VGA memory"
echo ""

gdb --tui .build/kernel.bin \
    -ex "target remote localhost:1234" \
    -ex "set disassembly-flavor intel" \
    -ex "layout asm" \
    -ex "layout regs"
