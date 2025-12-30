# 01: Function Pointers

## Function Pointers
Functions are stored in memory and can be referenced by pointers, enabling dynamic function calls and callbacks.

## Basic Function Pointers
```c
#include <stdio.h>

// Function to be pointed to
int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // Declare function pointer
    int (*operation)(int, int);

    // Point to add function
    operation = add;
    printf("5 + 3 = %d\n", operation(5, 3));  // 8

    // Point to multiply function
    operation = multiply;
    printf("5 * 3 = %d\n", operation(5, 3));  // 15

    return 0;
}
```

## Function Pointer Syntax
```c
// General syntax:
// return_type (*pointer_name)(parameter_types);

// Examples:
int (*func_ptr)(int, int);           // Pointer to function taking 2 ints, returning int
void (*callback)(void);              // Pointer to function taking no args, returning void
double (*math_func)(double);         // Pointer to function taking double, returning double
char* (*str_func)(const char*, int); // Pointer to function taking string and int, returning string
```

## typedef with Function Pointers
```c
// Make function pointer types more readable
typedef int (*BinaryOperation)(int, int);
typedef void (*CallbackFunction)(void);
typedef double (*MathFunction)(double);

// Usage
BinaryOperation op = add;
CallbackFunction cb = some_callback;
MathFunction math = sin;
```

## Arrays of Function Pointers
```c
typedef int (*Operation)(int, int);

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main() {
    Operation operations[] = {add, subtract, multiply, divide};
    char* names[] = {"add", "subtract", "multiply", "divide"};

    for (int i = 0; i < 4; i++) {
        printf("%s(10, 5) = %d\n", names[i], operations[i](10, 5));
    }

    return 0;
}
```

## Function Pointers as Parameters
```c
// Function that takes a function pointer
int apply_operation(int a, int b, int (*op)(int, int)) {
    return op(a, b);
}

// Usage
int result = apply_operation(10, 5, add);  // 15
int result2 = apply_operation(10, 5, multiply);  // 50
```

## Callback Functions
```c
#include <stdlib.h>

// Generic sorting function with callback
void bubble_sort(int arr[], int n, int (*compare)(int, int)) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (compare(arr[j], arr[j+1]) > 0) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Comparison functions
int ascending(int a, int b) { return a - b; }
int descending(int a, int b) { return b - a; }

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);

    bubble_sort(arr, n, ascending);
    printf("Ascending: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    bubble_sort(arr, n, descending);
    printf("\nDescending: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    return 0;
}
```

## Variable Arguments (varargs)
Functions that accept a variable number of arguments using stdarg.h.

```c
#include <stdarg.h>
#include <stdio.h>

// Function with variable arguments
double average(int count, ...) {
    va_list args;
    double sum = 0.0;

    va_start(args, count);  // Initialize va_list

    for (int i = 0; i < count; i++) {
        sum += va_arg(args, double);  // Get next argument
    }

    va_end(args);  // Clean up

    return sum / count;
}

int main() {
    printf("Average of 1, 2, 3: %.2f\n", average(3, 1.0, 2.0, 3.0));
    printf("Average of 5, 10, 15, 20: %.2f\n", average(4, 5.0, 10.0, 15.0, 20.0));
    return 0;
}
```

## va_list Operations
- va_start(va_list ap, last_fixed_param): Initialize the va_list
- va_arg(va_list ap, type): Get the next argument of specified type
- va_end(va_list ap): Clean up the va_list
- va_copy(va_list dest, va_list src): Copy va_list (C99)

## Recursive Functions
Functions that call themselves, useful for problems with recursive structure.

```c
// Factorial using recursion
unsigned long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Fibonacci using recursion
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Binary search using recursion
int binary_search(int arr[], int left, int right, int target) {
    if (left > right) return -1;

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return binary_search(arr, left, mid - 1, target);
    return binary_search(arr, mid + 1, right, target);
}

int main() {
    printf("5! = %lu\n", factorial(5));
    printf("Fib(8) = %d\n", fibonacci(8));

    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int index = binary_search(arr, 0, 6, 7);
    printf("7 found at index %d\n", index);

    return 0;
}
```

## Tail Recursion
A special case of recursion where the recursive call is the last operation.

```c
// Tail recursive factorial
unsigned long factorial_tail(int n, unsigned long acc) {
    if (n <= 1) return acc;
    return factorial_tail(n - 1, n * acc);
}

unsigned long factorial(int n) {
    return factorial_tail(n, 1);
}

// Tail recursive sum
int sum_tail(int n, int acc) {
    if (n == 0) return acc;
    return sum_tail(n - 1, acc + n);
}

int sum(int n) {
    return sum_tail(n, 0);
}
```

## Inline Functions
Hint to compiler to inline function calls for performance (C99).

```c
// Inline function suggestion
inline int max(int a, int b) {
    return (a > b) ? a : b;
}

inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int x = 10, y = 20;
    printf("Max: %d, Min: %d\n", max(x, y), min(x, y));
    return 0;
}
```

## Function Attributes (GCC specific)
```c
// Function that never returns
void fatal_error(const char* msg) __attribute__((noreturn));

// Pure function (no side effects)
int square(int x) __attribute__((pure));

// Function with format string checking
void log_message(const char* format, ...) __attribute__((format(printf, 1, 2)));
```

## Function Overloading (Not in C)
C doesn't support function overloading like C++. Each function must have a unique name.

```c
// This won't work in C
// int add(int a, int b) { return a + b; }
// double add(double a, double b) { return a + b; }  // Error

// Instead, use different names
int add_int(int a, int b) { return a + b; }
double add_double(double a, double b) { return a + b; }
```

## Default Arguments (Not in C)
C doesn't support default arguments. Use function overloading or separate functions.

```c
// Instead of: void func(int x = 10)
// Use:
void func_default() {
    func(10);
}

void func(int x) {
    // Implementation
}
```

## Lambda Functions (Not in C)
C doesn't have lambda functions. Use function pointers or define separate functions.

```c
// Instead of lambdas, define functions
int is_even(int x) { return x % 2 == 0; }
int is_positive(int x) { return x > 0; }

// Use with generic functions
int count_matching(int arr[], int n, int (*predicate)(int)) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (predicate(arr[i])) count++;
    }
    return count;
}

int main() {
    int arr[] = {-3, -1, 0, 2, 4, 6};
    printf("Even numbers: %d\n", count_matching(arr, 6, is_even));
    printf("Positive numbers: %d\n", count_matching(arr, 6, is_positive));
    return 0;
}
```

## Best Practices
- Use function pointers for callbacks and polymorphism
- Be careful with recursion depth (stack overflow risk)
- Use inline for small, frequently called functions
- Document function pointer parameters clearly
- Consider performance implications of function calls
- Use typedef for complex function pointer types
- Avoid deep recursion when possible
- Use const for function parameters when appropriate

## Common Mistakes
- Incorrect function pointer syntax
- Forgetting to dereference function pointers
- Stack overflow from infinite recursion
- Type mismatches in va_arg calls
- Not cleaning up va_list with va_end
- Assuming inline guarantees inlining
- Using function pointers without null checks
- Recursion on large datasets without optimization

## Performance Considerations
```c
// Function call overhead
int direct_add(int a, int b) {
    return a + b;  // No function call overhead
}

int (*add_ptr)(int, int) = direct_add;

int indirect_add(int a, int b) {
    return add_ptr(a, b);  // Function pointer call overhead
}

// Inline can reduce overhead
inline int inline_add(int a, int b) {
    return a + b;  // Compiler may inline
}
```

## Embedded Systems Applications
### Interrupt Service Routines (ISRs)
```c
typedef void (*ISR_Handler)(void);

ISR_Handler timer_isr = NULL;

void register_timer_isr(ISR_Handler handler) {
    timer_isr = handler;
}

void timer_interrupt() {
    if (timer_isr) {
        timer_isr();  // Call registered handler
    }
}
```

### State Machine Transitions
```c
typedef void (*StateFunction)(void);

typedef struct {
    StateFunction enter;
    StateFunction run;
    StateFunction exit;
} State_t;

State_t current_state;

void transition_to_state(State_t* new_state) {
    if (current_state.exit) current_state.exit();
    current_state = *new_state;
    if (current_state.enter) current_state.enter();
}

void run_state_machine() {
    if (current_state.run) current_state.run();
}
```

### Command Pattern
```c
typedef void (*Command)(void* context);

typedef struct {
    Command execute;
    void* context;
} Command_t;

void execute_command(Command_t* cmd) {
    if (cmd->execute) {
        cmd->execute(cmd->context);
    }
}

// Usage
void turn_on_led(void* context) {
    // Turn on LED
}

void turn_off_led(void* context) {
    // Turn off LED
}

Command_t on_cmd = {turn_on_led, NULL};
Command_t off_cmd = {turn_off_led, NULL};
```