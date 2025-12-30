# 05: Multiple File Programs

## Why Multiple Files?
- Code organization and modularity
- Easier maintenance and debugging
- Code reuse across projects
- Faster compilation (only changed files recompile)
- Team collaboration

## File Types
### Header Files (.h)
- Function prototypes
- Type definitions
- Constants and macros
- Include guards

### Source Files (.c)
- Function implementations
- Global variables
- Main function (usually in one file)

## Basic Multi-File Structure
```
project/
├── main.c
├── math.h
└── math.c
```

### math.h (Header File)
```c
#ifndef MATH_H
#define MATH_H

// Function prototypes
int add(int a, int b);
int subtract(int a, int b);
double average(int numbers[], int count);

#endif  // MATH_H
```

### math.c (Implementation)
```c
#include "math.h"

// Function implementations
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

double average(int numbers[], int count) {
    if (count == 0) return 0.0;

    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return (double)sum / count;
}
```

### main.c (Main Program)
```c
#include <stdio.h>
#include "math.h"

int main() {
    int a = 10, b = 5;
    int nums[] = {1, 2, 3, 4, 5};

    printf("Add: %d\n", add(a, b));
    printf("Subtract: %d\n", subtract(a, b));
    printf("Average: %.2f\n", average(nums, 5));

    return 0;
}
```

## Include Guards
Prevent multiple inclusion of header files:
```c
#ifndef HEADER_NAME_H
#define HEADER_NAME_H

// Header content here

#endif  // HEADER_NAME_H
```

## Compilation
### Single Command
```bash
gcc main.c math.c -o program
```

### Separate Compilation
```bash
# Compile object files
gcc -c main.c      # Creates main.o
gcc -c math.c      # Creates math.o

# Link object files
gcc main.o math.o -o program
```

## Makefiles for Multi-File Projects
```makefile
# Makefile
CC = gcc
CFLAGS = -Wall -g

# Object files
OBJS = main.o math.o

# Executable
program: $(OBJS)
	$(CC) $(OBJS) -o program

# Compile main.o
main.o: main.c math.h
	$(CC) $(CFLAGS) -c main.c

# Compile math.o
math.o: math.c math.h
	$(CC) $(CFLAGS) -c math.c

# Clean
clean:
	rm -f *.o program
```

## Static Functions
Functions only accessible within their file:
```c
// math.c
static int helper_function(int x) {
    return x * 2;
}

int public_function(int x) {
    return helper_function(x) + 1;
}

// main.c cannot call helper_function()
```

## Global Variables Across Files
### Declaration vs Definition
```c
// globals.h
extern int global_counter;  // Declaration

// globals.c
int global_counter = 0;     // Definition

// main.c
#include "globals.h"
global_counter++;           // Usage
```

## Common Patterns
### Module Pattern
```
utils/
├── utils.h
├── string_utils.c
├── math_utils.c
└── main.c
```

### Library Pattern
```
include/
├── mylib.h
src/
├── mylib.c
├── main.c
```

## Best Practices
- One header file per source file usually
- Use descriptive names for headers
- Include all necessary headers in each file
- Use include guards in all headers
- Declare functions in headers, define in sources
- Minimize global variables
- Use static for file-local functions

## Common Mistakes
- Missing include guards (multiple definition errors)
- Circular includes (header A includes B, B includes A)
- Forgetting to include headers
- Defining functions in headers (causes multiple definition errors)
- Not recompiling all files after header changes
- Using wrong include syntax (#include "file.h" vs <stdio.h>)

## Advanced: Conditional Compilation
```c
// config.h
#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG 1

#endif
```

```c
// main.c
#include "config.h"

int main() {
    #ifdef DEBUG
        printf("Debug mode\n");
    #endif
    return 0;
}
```