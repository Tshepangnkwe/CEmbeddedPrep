# 04: Pointers and Functions

## Function Pointers
Function pointers store the address of a function and can be used to call that function indirectly.

## Declaring Function Pointers
```c
// Function prototype
int add(int a, int b);

// Function pointer declaration
int (*func_ptr)(int, int);

// Alternative syntax (using typedef)
typedef int (*operation)(int, int);
operation func_ptr2;
```

## Assigning Function Pointers
```c
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {
    int (*operation)(int, int) = add;
    printf("%d\n", operation(5, 3));  // 8

    operation = subtract;
    printf("%d\n", operation(5, 3));  // 2
}
```

## Using Function Pointers
```c
void execute_operation(int a, int b, int (*op)(int, int)) {
    int result = op(a, b);
    printf("Result: %d\n", result);
}

int multiply(int a, int b) { return a * b; }

int main() {
    execute_operation(4, 5, multiply);  // Result: 20
    execute_operation(4, 5, add);       // Result: 9
}
```

## Arrays of Function Pointers
```c
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main() {
    int (*operations[4])(int, int) = {add, subtract, multiply, divide};

    char* names[] = {"add", "subtract", "multiply", "divide"};

    for (int i = 0; i < 4; i++) {
        printf("%s(10, 5) = %d\n", names[i], operations[i](10, 5));
    }
}
```

## Function Pointers as Parameters
### Calculator Example
```c
typedef int (*math_op)(int, int);

int calculate(int a, int b, math_op operation) {
    return operation(a, b);
}

int main() {
    printf("Add: %d\n", calculate(10, 5, add));
    printf("Multiply: %d\n", calculate(10, 5, multiply));
}
```

### Callback Functions
```c
void for_each(int arr[], int size, void (*callback)(int)) {
    for (int i = 0; i < size; i++) {
        callback(arr[i]);
    }
}

void print_element(int x) {
    printf("%d ", x);
}

void square_element(int x) {
    printf("%d ", x * x);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    printf("Original: ");
    for_each(arr, 5, print_element);

    printf("\nSquared: ");
    for_each(arr, 5, square_element);
}
```

## Pointers as Function Parameters
### Pass by Reference
```c
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    printf("Before: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After: x=%d, y=%d\n", x, y);
}
```

### Returning Multiple Values
```c
void divide_with_remainder(int dividend, int divisor,
                          int* quotient, int* remainder) {
    *quotient = dividend / divisor;
    *remainder = dividend % divisor;
}

int main() {
    int q, r;
    divide_with_remainder(17, 5, &q, &r);
    printf("17 / 5 = %d remainder %d\n", q, r);
}
```

## Dynamic Memory Allocation
### Single Variables
```c
#include <stdlib.h>

int* create_int(int value) {
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = value;
    }
    return ptr;
}

int main() {
    int* num = create_int(42);
    if (num != NULL) {
        printf("Value: %d\n", *num);
        free(num);
    }
}
```

### Arrays
```c
int* create_array(int size) {
    return (int*)malloc(size * sizeof(int));
}

int main() {
    int size = 5;
    int* arr = create_array(size);
    if (arr != NULL) {
        for (int i = 0; i < size; i++) {
            arr[i] = i * 10;
            printf("%d ", arr[i]);
        }
        free(arr);
    }
}
```

## Function Pointers in Structs
```c
typedef struct {
    char* name;
    int (*calculate)(int, int);
} calculator_t;

int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

int main() {
    calculator_t calc = {"Addition", add};
    printf("%s: %d\n", calc.name, calc.calculate(5, 3));

    calc.calculate = multiply;
    calc.name = "Multiplication";
    printf("%s: %d\n", calc.name, calc.calculate(5, 3));
}
```

## Advanced Patterns
### Generic Swap Function
```c
void generic_swap(void* a, void* b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

int main() {
    int x = 10, y = 20;
    generic_swap(&x, &y, sizeof(int));
    printf("x=%d, y=%d\n", x, y);

    double a = 1.5, b = 2.5;
    generic_swap(&a, &b, sizeof(double));
    printf("a=%.1f, b=%.1f\n", a, b);
}
```

### Function Table
```c
typedef void (*command_func)(void);

void help_command() { printf("Help command\n"); }
void quit_command() { printf("Quit command\n"); }
void save_command() { printf("Save command\n"); }

int main() {
    command_func commands[] = {
        help_command,
        quit_command,
        save_command
    };

    char* command_names[] = {"help", "quit", "save"};

    // Simulate command lookup
    int cmd_index = 0;  // Would be determined by user input
    commands[cmd_index]();
}
```

## Best Practices
- Use typedef for complex function pointer types
- Always check for NULL before calling function pointers
- Document function pointer parameters clearly
- Use function pointers for callbacks and polymorphism
- Be careful with function pointer arithmetic (not allowed)
- Free dynamically allocated memory

## Common Mistakes
- Incorrect function pointer syntax
- Calling NULL function pointers
- Wrong parameter types in function pointers
- Memory leaks from not freeing allocated pointers
- Confusing function pointers with regular pointers
- Forgetting parentheses in function pointer declarations