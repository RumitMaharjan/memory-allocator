# Memory Allocator in C

A custom implementation of malloc and free built from scratch in C, demonstrating how dynamic memory allocation works under the hood.

## How It Works

Every allocated block has a hidden header storing metadata:
[size | free | next | ← user data starts here →]

When memory is requested, the allocator first searches the free list for a reusable block. If none is found, it requests raw memory from the OS using sbrk(). When memory is freed, the block is marked as available and returned to the free list for future reuse.

## Features
- Custom malloc using sbrk() to request memory from the OS
- Free list to reuse freed blocks instead of always calling sbrk()
- Block headers storing size, free status, and next pointer
- Zero dependencies on standard malloc/free

## Build
gcc memory_management.c -o memory_allocator

## Run
./memory_allocator

## Concepts Demonstrated
- sbrk() — raw memory from the OS
- Linked list of free blocks
- Pointer arithmetic to navigate block headers
- Heap memory management internals

## Author
Rumit Maharjan

program output: 
<img width="824" height="428" alt="Screenshot 2026-05-15 032309" src="https://github.com/user-attachments/assets/34980ae2-f6b0-4ffb-bf2b-b5a3e0a9fc8c" />
