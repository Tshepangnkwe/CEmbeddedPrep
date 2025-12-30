# C Embedded Programming Prep

A structured 2-month learning path for mastering C fundamentals before embedded systems development.

## Overview

This repository contains exercises, notes, and resources for learning C programming with an embedded focus.

## Repository Structure

```
CEmbeddedPrep/
├── README.md
├── .gitignore
├── cheatsheets/
│   ├── loops.md
│   ├── functions.md
│   ├── pointers.md
│   ├── arrays-strings.md
│   ├── structs-enums.md
│   ├── bitwise.md
│   ├── preprocessor.md
│   └── state-machines.md
├── month1-fundamentals/
│   ├── week1-basics-loops/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-variables-datatypes.md
│   │   │   ├── 02-operators.md
│   │   │   ├── 03-conditionals.md
│   │   │   ├── 04-for-loops.md
│   │   │   ├── 05-while-loops.md
│   │   │   └── 06-nested-loops.md
│   │   ├── exercises/
│   │   │   ├── 01-hello-world/
│   │   │   ├── 02-pattern-printer/
│   │   │   ├── 03-number-analyzer/
│   │   │   ├── 04-calculator/
│   │   │   └── 05-fibonacci-factorial/
│   │   └── drills/
│   │       ├── loop-patterns.c
│   │       └── loop-challenges.c
│   ├── week2-functions/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-function-basics.md
│   │   │   ├── 02-prototypes-scope.md
│   │   │   ├── 03-recursion.md
│   │   │   └── 04-multiple-files.md
│   │   ├── exercises/
│   │   │   ├── 06-math-library/
│   │   │   ├── 07-password-validator/
│   │   │   ├── 08-menu-system/
│   │   │   └── 09-modular-calculator/
│   │   └── drills/
│   │       ├── function-writing.c
│   │       └── recursion-practice.c
│   ├── week3-arrays-strings/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-arrays-basics.md
│   │   │   ├── 02-multidimensional-arrays.md
│   │   │   ├── 03-strings.md
│   │   │   └── 04-string-functions.md
│   │   ├── exercises/
│   │   │   ├── 10-string-library/
│   │   │   ├── 11-array-sorter/
│   │   │   ├── 12-text-analyzer/
│   │   │   ├── 13-matrix-operations/
│   │   │   └── 14-word-counter/
│   │   └── drills/
│   │       ├── array-manipulation.c
│   │       └── string-manipulation.c
│   └── week4-pointers/
│       ├── README.md
│       ├── notes/
│       │   ├── 01-pointer-basics.md
│       │   ├── 02-pointer-arithmetic.md
│       │   ├── 03-pointers-arrays.md
│       │   ├── 04-pointers-functions.md
│       │   └── 05-common-mistakes.md
│       ├── exercises/
│       │   ├── 15-pointer-basics/
│       │   ├── 16-swap-functions/
│       │   ├── 17-dynamic-arrays/
│       │   ├── 18-string-reverser/
│       │   └── 19-caesar-cipher/
│       └── drills/
│           ├── pointer-arithmetic.c
│           └── pointer-functions.c
├── month2-advanced/
│   ├── week5-structs-typedef-enums/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-structs.md
│   │   │   ├── 02-typedef.md
│   │   │   ├── 03-enums.md
│   │   │   ├── 04-unions.md
│   │   │   └── 05-structs-pointers.md
│   │   ├── exercises/
│   │   │   ├── 20-student-database/
│   │   │   ├── 21-inventory-system/
│   │   │   ├── 22-contact-manager/
│   │   │   └── 23-register-simulator/
│   │   └── drills/
│   │       └── struct-practice.c
│   ├── week6-bitwise-memory/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-bitwise-operators.md
│   │   │   ├── 02-bit-manipulation.md
│   │   │   ├── 03-bit-flags.md
│   │   │   ├── 04-memory-layout.md
│   │   │   └── 05-volatile-const.md
│   │   ├── exercises/
│   │   │   ├── 24-binary-calculator/
│   │   │   ├── 25-bit-flag-manager/
│   │   │   ├── 26-register-simulator/
│   │   │   └── 27-bit-packing/
│   │   └── drills/
│   │       ├── bitwise-operations.c
│   │       └── bit-manipulation.c
│   ├── week7-advanced-functions-preprocessor/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-function-pointers.md
│   │   │   ├── 02-callbacks.md
│   │   │   ├── 03-preprocessor-macros.md
│   │   │   ├── 04-conditional-compilation.md
│   │   │   └── 05-modular-design.md
│   │   ├── exercises/
│   │   │   ├── 28-callback-menu/
│   │   │   ├── 29-generic-sorting/
│   │   │   ├── 30-macro-utilities/
│   │   │   └── 31-modular-library/
│   │   └── drills/
│   │       └── function-pointers.c
│   └── week8-state-machines-integration/
│       ├── README.md
│       ├── notes/
│       │   ├── 01-state-machines.md
│       │   ├── 02-fsm-patterns.md
│       │   ├── 03-file-io.md
│       │   └── 04-error-handling.md
│       ├── exercises/
│       │   ├── 32-text-game/
│       │   ├── 33-protocol-parser/
│       │   ├── 34-data-logger/
│       │   └── 35-vending-machine/
│       └── capstone/
│           ├── requirements.md
│           └── sensor-processor/
└── progress/
    ├── weekly-reflections.md
    └── skills-checklist.md
```

## Getting Started

1. Follow the weeks in order
2. Complete exercises and drills
3. Track progress in progress/weekly-reflections.md
4. Use cheatsheets for quick reference

## Prerequisites

- C compiler (GCC recommended)
- Basic programming knowledge
- Text editor or IDE

### Development Environment Setup

This guide covers setting up MSYS2, LLVM (Clang), and GCC on Windows for C development.

#### MSYS2 Installation and Setup

MSYS2 is a software distribution and building platform for Windows that provides a Unix-like environment with package management.

**Step 1: Download MSYS2**
1. Visit [msys2.org](https://www.msys2.org/)
2. Download the latest `msys2-x86_64-*.exe` installer
3. Run the installer with default settings (installs to `C:\msys64`)

**Step 2: Initial Setup**
1. Open "MSYS2 MSYS" from Start menu
2. Update the package database and core system:
   ```bash
   pacman -Syu
   ```
3. Close the terminal when prompted, then reopen and run:
   ```bash
   pacman -Syu
   ```

**Step 3: Install Development Tools**
```bash
# Install GCC
pacman -S mingw-w64-x86_64-gcc

# Install Clang/LLVM
pacman -S mingw-w64-x86_64-clang

# Install additional tools
pacman -S mingw-w64-x86_64-gdb      # Debugger
pacman -S mingw-w64-x86_64-make     # Build system
pacman -S mingw-w64-x86_64-cmake    # Build system
```

**Step 4: Add to PATH (Optional)**
To use MSYS2 tools from any command prompt:
1. Add `C:\msys64\mingw64\bin` to your Windows PATH
2. Restart terminals/command prompts

#### LLVM (Clang) Setup

Clang is a compiler front-end for LLVM that can compile C, C++, and Objective-C.

**Installation via MSYS2:**
```bash
pacman -S mingw-w64-x86_64-clang
```

**Key Features:**
- Faster compilation than GCC in many cases
- Better error messages and diagnostics
- Extensive static analysis tools
- Memory sanitizer and other debugging tools

**Basic Usage:**
```bash
# Compile C file
clang source.c -o output.exe

# With debugging symbols
clang -g source.c -o output.exe

# Enable warnings
clang -Wall -Wextra source.c -o output.exe
```

#### GCC Setup

GCC (GNU Compiler Collection) is the most widely used C compiler.

**Installation via MSYS2:**
```bash
pacman -S mingw-w64-x86_64-gcc
```

**Key Features:**
- Industry standard for embedded development
- Extensive optimization options
- Strong support for embedded targets
- Comprehensive documentation

**Basic Usage:**
```bash
# Compile C file
gcc source.c -o output.exe

# With debugging symbols
gcc -g source.c -o output.exe

# Enable all warnings
gcc -Wall -Wextra source.c -o output.exe

# Optimize for size (good for embedded)
gcc -Os source.c -o output.exe
```

#### Using Both Compilers

**From MSYS2 Terminal:**
Both compilers are available in the MSYS2 environment.

**From Windows Command Prompt/PowerShell:**
If added to PATH, use `gcc` or `clang` directly.

**In VS Code:**
Create `.vscode/tasks.json`:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build with GCC",
            "type": "shell",
            "command": "gcc",
            "args": ["-Wall", "-Wextra", "-g", "${file}", "-o", "${fileDirname}/${fileBasenameNoExtension}.exe"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "Build with Clang",
            "type": "shell",
            "command": "clang",
            "args": ["-Wall", "-Wextra", "-g", "${file}", "-o", "${fileDirname}/${fileBasenameNoExtension}.exe"],
            "group": "build"
        }
    ]
}
```

**In Makefiles:**
```makefile
# Choose compiler
CC = gcc
# CC = clang

# Compilation flags
CFLAGS = -Wall -Wextra -g

# Build target
target: source.c
	$(CC) $(CFLAGS) source.c -o target.exe
```

#### Testing Your Setup

Create `hello.c`:
```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

**Test GCC:**
```bash
gcc hello.c -o hello_gcc.exe
./hello_gcc.exe
```

**Test Clang:**
```bash
clang hello.c -o hello_clang.exe
./hello_clang.exe
```

#### Troubleshooting

**PATH Issues:**
- Ensure `C:\msys64\mingw64\bin` is in PATH
- Restart terminals after PATH changes

**Missing Libraries:**
```bash
# Update packages
pacman -Syu

# Search for packages
pacman -Ss package_name
```

**Permission Errors:**
- Run MSYS2 as administrator for system-wide installs
- Check antivirus exclusions for MSYS2 directory

#### Recommended Workflow

1. **Development:** Use MSYS2 terminal for most work
2. **Default Compiler:** GCC for embedded-focused learning
3. **Alternative:** Clang for faster compilation or better diagnostics
4. **Debugging:** Use GDB from MSYS2
5. **Building:** Makefiles or direct compilation

For embedded development, GCC is more commonly used, but Clang is excellent for learning and general C programming.

## Resources

- Embedded C books and tutorials
- Online documentation
- Practice problems and challenges
