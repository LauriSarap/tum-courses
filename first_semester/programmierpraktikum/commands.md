# C Compilation & Analysis Commands

## Compilation Pipeline

The C compilation process has 4 stages:

```
Source (.c) → Preprocessor → Compiler → Assembler → Linker → Executable
```

```bash
# 1. Preprocessor - expands macros, includes headers, removes comments
clang -E main.c -o main.i

# 2. Compiler - converts C to assembly
clang -S main.i -o main.s

# 3. Assembler - converts assembly to machine code (object file)
clang -c main.s -o main.o

# 4. Linker - links object files and libraries into executable
clang main.o -o maina
```

### One-step compilation
```bash
clang -Wall -Wextra -g main.c -o main
```
- `-Wall` — enable common warnings
- `-Wextra` — enable extra warnings
- `-g` — include debug symbols

---

## Disassembly & Inspection

```bash
# Disassemble object file (show assembly instructions)
objdump -d main.o

# Disassemble with source code interleaved (requires -g flag during compilation)
objdump -S main.o

# Hex dump - show raw bytes in hexadecimal + ASCII
hexdump -C main.o

# Show all sections and headers
objdump -x main.o

# Show symbol table (functions, variables)
nm main.o
```