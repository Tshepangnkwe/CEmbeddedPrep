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

## Resources

- Embedded C books and tutorials
- Online documentation
- Practice problems and challenges
