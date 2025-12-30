# Functions Cheatsheet

## Function Declaration

### Basic Syntax
```c
return_type function_name(parameter_type parameter_name, ...) {
    // function body
    return value;  // if not void
}
```

### Examples
```c
// Function that returns int
int add(int a, int b) {
    return a + b;
}

// Function that returns void
void print_message(char *message) {
    printf("%s\n", message);
}

// Function with no parameters
void greet(void) {
    printf("Hello!\n");
}
```

## Function Prototypes

### Declaration vs Definition
```c
// Prototype (declaration) - usually in header files
int add(int a, int b);

// Definition (implementation) - in source files
int add(int a, int b) {
    return a + b;
}
```

### Header File Example
```c
// math.h
#ifndef MATH_H
#define MATH_H

int add(int a, int b);
double divide(double a, double b);
void print_result(int result);

#endif
```

## Parameters

### Pass by Value
```c
void increment(int x) {
    x++;  // Only local copy is modified
}

int main() {
    int num = 5;
    increment(num);
    printf("%d\n", num);  // Still 5
}
```

### Pass by Reference (using pointers)
```c
void increment(int *x) {
    (*x)++;  // Original value is modified
}

int main() {
    int num = 5;
    increment(&num);
    printf("%d\n", num);  // Now 6
}
```

### Array Parameters
```c
// Array decays to pointer
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

// Or explicitly as pointer
void print_array(int *arr, int size) {
    // Same as above
}
```

## Return Values

### Single Value
```c
int get_max(int a, int b) {
    return (a > b) ? a : b;
}
```

### Multiple Values (using pointers)
```c
void get_min_max(int arr[], int size, int *min, int *max) {
    *min = *max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

int main() {
    int arr[] = {3, 1, 4, 1, 5};
    int min, max;
    get_min_max(arr, 5, &min, &max);
    printf("Min: %d, Max: %d\n", min, max);
}
```

## Recursion

### Basic Example
```c
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

### Tail Recursion
```c
int factorial_tail(int n, int acc) {
    if (n <= 1) {
        return acc;
    }
    return factorial_tail(n - 1, n * acc);
}

int factorial(int n) {
    return factorial_tail(n, 1);
}
```

## Function Pointers

### Declaration
```c
// Function pointer type
typedef int (*operation_t)(int, int);

// Or directly
int (*operation)(int, int);
```

### Usage
```c
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {
    int (*op)(int, int) = add;
    printf("%d\n", op(5, 3));  // 8

    op = subtract;
    printf("%d\n", op(5, 3));  // 2
}
```

### Function Pointers in Structs
```c
typedef struct {
    char *name;
    int (*operation)(int, int);
} calculator_t;

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int main() {
    calculator_t calc = {"add", add};
    printf("%d\n", calc.operation(3, 4));
}
```

## Variable Arguments

### Using stdarg.h
```c
#include <stdarg.h>

int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    return total;
}

int main() {
    printf("%d\n", sum(3, 1, 2, 3));  // 6
}
```

## Inline Functions

### For Performance
```c
inline int max(int a, int b) {
    return (a > b) ? a : b;
}
```

## Static Functions

### File Scope
```c
// Only accessible in this file
static int helper_function(int x) {
    return x * 2;
}
```

## Embedded-Specific Patterns

### Hardware Abstraction
```c
// GPIO functions
void gpio_set_pin(uint8_t pin) {
    GPIO_PORT |= (1 << pin);
}

void gpio_clear_pin(uint8_t pin) {
    GPIO_PORT &= ~(1 << pin);
}

// Timer functions
void timer_delay_ms(uint32_t ms) {
    // Implementation depends on hardware
}
```

### State Machine Functions
```c
typedef enum { IDLE, RUNNING, ERROR } state_t;

void enter_idle_state(void) {
    // Initialize idle state
}

void enter_running_state(void) {
    // Initialize running state
}

state_t process_idle_state(void) {
    if (start_condition) {
        enter_running_state();
        return RUNNING;
    }
    return IDLE;
}
```

## Best Practices

- Use meaningful function names
- Keep functions focused on single responsibility
- Use prototypes in header files
- Document parameters and return values
- Prefer pass-by-value for small types
- Use const for pointer parameters that shouldn't be modified
- Avoid global variables in functions
- Consider function complexity and splitting large functions