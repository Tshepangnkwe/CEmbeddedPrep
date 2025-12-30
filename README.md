# My C Programming Journey for Embedded Systems - 2 Month Challenge

This is my structured learning path for mastering C fundamentals before diving into embedded firmware development. I'm building this repository to track my progress and create a comprehensive resource for anyone else on the same journey.

## Repository Structure

```
c-embedded-prep/
├── README.md
├── .gitignore
├── resources/
│   ├── books.md
│   ├── cheatsheets/
│   │   ├── loops-cheatsheet.md
│   │   ├── functions-cheatsheet.md
│   │   ├── pointers-cheatsheet.md
│   │   ├── bitwise-cheatsheet.md
│   │   ├── preprocessor-cheatsheet.md
│   │   └── debugging-cheatsheet.md
│   └── setup-guide.md
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
│   │   │   │   ├── pattern_printer.c
│   │   │   │   ├── Makefile
│   │   │   │   └── README.md
│   │   │   ├── 03-number-analyzer/
│   │   │   ├── 04-calculator/
│   │   │   └── 05-fibonacci-factorial/
│   │   └── drills/
│   │       ├── loop-patterns-01.c
│   │       ├── loop-patterns-02.c
│   │       └── loop-challenges.c
│   ├── week2-functions/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-function-basics.md
│   │   │   ├── 02-function-prototypes.md
│   │   │   ├── 03-scope-lifetime.md
│   │   │   ├── 04-recursion.md
│   │   │   └── 05-multiple-files.md
│   │   ├── exercises/
│   │   │   ├── 06-math-library/
│   │   │   ├── 07-password-validator/
│   │   │   ├── 08-menu-system-v1/
│   │   │   └── 09-modular-calculator/
│   │   └── drills/
│   │       ├── function-writing-01.c
│   │       ├── function-writing-02.c
│   │       └── recursion-practice.c
│   ├── week3-arrays-strings/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-arrays-basics.md
│   │   │   ├── 02-multidimensional-arrays.md
│   │   │   ├── 03-strings-intro.md
│   │   │   ├── 04-string-functions.md
│   │   │   └── 05-array-functions.md
│   │   ├── exercises/
│   │   │   ├── 10-string-library/
│   │   │   ├── 11-array-sorter/
│   │   │   ├── 12-text-analyzer/
│   │   │   ├── 13-matrix-operations/
│   │   │   └── 14-word-counter/
│   │   └── drills/
│   │       ├── array-manipulation.c
│   │       ├── string-manipulation.c
│   │       └── search-algorithms.c
│   └── week4-pointers/
│       ├── README.md
│       ├── notes/
│       │   ├── 01-pointer-basics.md
│       │   ├── 02-pointer-arithmetic.md
│       │   ├── 03-pointers-arrays.md
│       │   ├── 04-pointers-functions.md
│       │   ├── 05-pointers-strings.md
│       │   └── 06-common-mistakes.md
│       ├── exercises/
│       │   ├── 15-pointer-basics/
│       │   ├── 16-swap-functions/
│       │   ├── 17-dynamic-arrays/
│       │   ├── 18-string-reverser/
│       │   └── 19-caesar-cipher/
│       └── drills/
│           ├── pointer-arithmetic.c
│           ├── pointer-functions.c
│           └── pointer-challenges.c
├── month2-advanced/
│   ├── week5-structs-typedef-enums/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-structs-basics.md
│   │   │   ├── 02-nested-structs.md
│   │   │   ├── 03-typedef.md
│   │   │   ├── 04-enums.md
│   │   │   ├── 05-unions.md
│   │   │   └── 06-structs-pointers.md
│   │   ├── exercises/
│   │   │   ├── 20-student-database/
│   │   │   ├── 21-inventory-system/
│   │   │   ├── 22-contact-manager/
│   │   │   └── 23-embedded-register-simulator/
│   │   └── drills/
│   │       ├── struct-practice.c
│   │       └── enum-state-machines.c
│   ├── week6-bitwise-memory/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-bitwise-operators.md
│   │   │   ├── 02-bit-manipulation.md
│   │   │   ├── 03-bit-flags.md
│   │   │   ├── 04-memory-layout.md
│   │   │   ├── 05-stack-vs-heap.md
│   │   │   └── 06-volatile-const.md
│   │   ├── exercises/
│   │   │   ├── 24-binary-calculator/
│   │   │   ├── 25-bit-flag-manager/
│   │   │   ├── 26-register-simulator/
│   │   │   └── 27-bit-packing/
│   │   └── drills/
│   │       ├── bitwise-operations.c
│   │       ├── bit-manipulation.c
│   │       └── bit-challenges.c
│   ├── week7-advanced-functions-preprocessor/
│   │   ├── README.md
│   │   ├── notes/
│   │   │   ├── 01-function-pointers.md
│   │   │   ├── 02-callback-functions.md
│   │   │   ├── 03-preprocessor-macros.md
│   │   │   ├── 04-conditional-compilation.md
│   │   │   ├── 05-header-files.md
│   │   │   └── 06-modular-design.md
│   │   ├── exercises/
│   │   │   ├── 28-callback-menu-system/
│   │   │   ├── 29-generic-sorting/
│   │   │   ├── 30-macro-utilities/
│   │   │   └── 31-modular-library/
│   │   └── drills/
│   │       ├── function-pointers.c
│   │       └── macro-practice.c
│   └── week8-state-machines-integration/
│       ├── README.md
│       ├── notes/
│       │   ├── 01-state-machines.md
│       │   ├── 02-finite-state-automata.md
│       │   ├── 03-file-io.md
│       │   ├── 04-error-handling.md
│       │   └── 05-debugging-techniques.md
│       ├── exercises/
│       │   ├── 32-text-based-game/
│       │   ├── 33-protocol-parser/
│       │   ├── 34-data-logger/
│       │   └── 35-vending-machine-fsm/
│       └── capstone-project/
│           ├── requirements.md
│           ├── sensor-data-processor/
│           └── command-interpreter/
├── templates/
│   ├── project-template/
│   │   ├── src/
│   │   │   └── main.c
│   │   ├── include/
│   │   │   └── project.h
│   │   ├── Makefile
│   │   └── README.md
│   ├── multi-file-template/
│   │   ├── src/
│   │   │   ├── main.c
│   │   │   └── module.c
│   │   ├── include/
│   │   │   └── module.h
│   │   └── Makefile
│   └── exercise-template.c
├── debugging-practice/
│   ├── README.md
│   ├── buggy-programs/
│   │   ├── bug-01-segfault.c
│   │   ├── bug-02-memory-leak.c
│   │   ├── bug-03-logic-error.c
│   │   └── solutions/
│   └── gdb-tutorial.md
└── progress/
    ├── daily-log.md
    ├── week1-reflection.md
    ├── week2-reflection.md
    ├── loop-mastery-tracker.md
    └── skills-checklist.md
```

## Quick Start

1. Clone my repository:
```bash
git clone https://github.com/yourusername/c-embedded-prep.git
cd c-embedded-prep
```

2. Set up your development environment:
```bash
# Follow instructions in resources/setup-guide.md
```

3. Start with Month 1, Week 1:
```bash
cd month1-fundamentals/week1-basics-loops
cat README.md
```

## My Complete Learning Path

### Month 1: Core C Programming

**Week 1: Basics + Loop Mastery**
- Variables, data types, operators
- Conditionals (if/else, switch)
- For, while, do-while loops
- Nested loops and loop control (break, continue)
- **Focus**: Master all loop patterns

**Week 2: Functions**
- Function basics, prototypes, declarations
- Parameters and return values
- Scope and lifetime (local, global, static)
- Recursion
- Multi-file programs and compilation
- **Focus**: Write modular, reusable code

**Week 3: Arrays & Strings**
- Single and multi-dimensional arrays
- Strings and character arrays
- String manipulation without library functions
- Arrays with functions
- Sorting and searching algorithms
- **Focus**: Data structure manipulation

**Week 4: Pointers**
- Pointer basics and dereferencing
- Pointer arithmetic
- Pointers with arrays and strings
- Pointers with functions (pass by reference)
- Common pointer mistakes
- **Focus**: Master memory addressing

### Month 2: Advanced Concepts

**Week 5: Structs, Typedef, Enums, Unions**
- Structure basics and nested structures
- Typedef for cleaner code
- Enumerations for state machines
- Unions for memory efficiency
- Pointers to structures
- **Focus**: Complex data types (critical for embedded registers)

**Week 6: Bitwise Operations & Memory**
- All bitwise operators (AND, OR, XOR, shifts)
- Bit manipulation techniques
- Bit flags and masks
- Memory layout (stack vs heap)
- Volatile and const keywords
- **Focus**: Low-level hardware control preparation

**Week 7: Advanced Functions & Preprocessor**
- Function pointers
- Callback functions
- Preprocessor directives and macros
- Conditional compilation
- Header file organization
- Modular design patterns
- **Focus**: Professional code structure

**Week 8: State Machines & Integration**
- Finite state machines (FSM)
- State machine implementation patterns
- File I/O operations
- Error handling strategies
- Debugging techniques (GDB)
- **Capstone Project**: Combine everything learned

## Core Topics I'm Covering

✅ **Loops** (my focus area) - practiced in every week  
✅ **Functions** - dedicated week + used throughout  
✅ **Pointers** - full week of practice  
✅ **Bitwise operations** - essential for embedded  
✅ **Structs/Enums** - hardware register modeling  
✅ **State machines** - embedded system design pattern  
✅ **Preprocessor** - conditional compilation, macros  
✅ **Memory management** - stack, heap, volatile  
✅ **Modular design** - multi-file projects  
✅ **Debugging** - GDB and troubleshooting

## My Daily Routine (2 hours)

1. **Read notes** (20 min) - Understand the day's concept
2. **Main exercise** (60 min) - Build the project
3. **Loop/concept drills** (30 min) - Targeted practice
4. **Update progress log** (10 min) - Track learning

## Weekly Milestones

Each week includes:
- 6 days of learning + 1 day for review/catch-up
- 4-5 progressive exercises
- Daily drill problems
- Weekly reflection document
- Skills checklist to track mastery

## Compilation

Each exercise includes a Makefile:
```bash
cd month1-fundamentals/week1-basics-loops/exercises/02-pattern-printer
make
./pattern_printer
```

Or compile manually:
```bash
gcc -Wall -Wextra -std=c11 -g pattern_printer.c -o pattern_printer
```

## Progress Tracking

I use the `progress/` folder to:
- Log daily work in `daily-log.md`
- Write weekly reflections
- Track loop mastery improvements
- Check off skills as I master them

## Debugging Practice

The `debugging-practice/` folder contains:
- Intentionally buggy programs to fix
- GDB tutorial and exercises
- Common mistake patterns
- Solutions with explanations

## Why This Prepares Me for Embedded

- **Loops** → polling peripherals, timing delays, data processing
- **Functions** → driver APIs, peripheral control
- **Pointers** → memory-mapped registers, DMA
- **Bitwise ops** → register manipulation, communication protocols
- **Structs** → peripheral register definitions
- **Enums** → state machines, error codes
- **Preprocessor** → hardware abstraction layers
- **State machines** → embedded system architecture

## Next Steps (Month 3+)

After completing this program:
- ✅ Solid C foundation
- ✅ Comfortable with all language features
- ✅ Ready for bare-metal embedded programming
- → Start with hardware (STM32, Arduino)
- → Learn register-level programming
- → Build real firmware projects

## Resources

See `resources/` folder for:
- Recommended books
- Setup guides (GCC, VS Code, GDB)
- Comprehensive cheatsheets
- Additional practice problems

## License

MIT License - Use freely for your learning journey!

---

**Loop Mastery is My Priority**: Every week includes dedicated loop practice. By month's end, loops will be second nature, and I'll be ready to tackle embedded firmware with confidence.
