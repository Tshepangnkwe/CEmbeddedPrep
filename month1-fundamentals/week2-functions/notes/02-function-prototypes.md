# 02: Function Prototypes

## What is a Function Prototype?
A function prototype declares the function's interface without providing the implementation. It tells the compiler:
- Function name
- Return type
- Parameter types and names (names optional)

## Why Prototypes?
- Allow calling functions before they're defined
- Enable separate compilation
- Help catch type mismatches at compile time
- Improve code organization

## Prototype Syntax
```c
return_type function_name(parameter_types);
```

### Examples
```c
// Basic prototype
int add(int, int);

// With parameter names (recommended for clarity)
int add(int a, int b);

// Void function
void print_message(void);

// Function returning pointer
char* get_name(void);

// Complex parameters
double calculate(int count, double values[]);
```

## Prototype vs Definition
```c
// Prototype (declaration)
int multiply(int a, int b);

// Definition (implementation)
int multiply(int a, int b) {
    return a * b;
}
```

## Placement
### Option 1: Before main
```c
#include <stdio.h>

int add(int, int);  // Prototype

int main() {
    printf("%d\n", add(2, 3));
    return 0;
}

int add(int a, int b) {  // Definition
    return a + b;
}
```

### Option 2: Header Files
```c
// math.h
#ifndef MATH_H
#define MATH_H

int add(int a, int b);
int subtract(int a, int b);

#endif
```

```c
// math.c
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
```

```c
// main.c
#include "math.h"

int main() {
    printf("%d\n", add(5, 3));
    return 0;
}
```

## Parameter Name Rules
- Parameter names in prototypes are optional
- If included, they should match the definition
- They help with documentation

```c
// Valid (names optional)
int divide(int, int);
int divide(int dividend, int divisor);

// But should match definition
int divide(int dividend, int divisor) {
    return dividend / divisor;
}
```

## Default Arguments
C doesn't support default arguments like C++:
```c
// This won't work in C
void func(int x = 5) { }

// Instead, use function overloading simulation
void func(void) { func_with_default(5); }
void func_with_default(int x) { /* implementation */ }
```

## Function Overloading
C doesn't support function overloading:
```c
// This won't work in C
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }

// Instead, use different names
int add_int(int a, int b) { return a + b; }
double add_double(double a, double b) { return a + b; }
```

## Best Practices
- Always provide prototypes for functions
- Use header files for multi-file programs
- Include parameter names in prototypes for clarity
- Group related function prototypes together
- Use include guards in header files

## Common Mistakes
- Missing prototypes (causes implicit int return)
- Parameter type mismatches
- Forgetting to include header files
- Circular dependencies in headers