# 01: Function Basics

## What is a Function?
A function is a named block of code that performs a specific task. Functions help organize code into reusable, modular pieces.

## Function Definition
```c
return_type function_name(parameter_list) {
    // Function body
    // Statements
    return value;  // Optional
}
```

### Examples
```c
// Function that returns nothing
void greet() {
    printf("Hello, World!\n");
}

// Function that returns an integer
int add(int a, int b) {
    return a + b;
}

// Function with no parameters
double get_pi() {
    return 3.14159;
}
```

## Function Call
```c
// Calling functions
greet();                    // No arguments, no return value
int sum = add(5, 3);       // Arguments, captures return value
double pi = get_pi();      // No arguments, captures return value

printf("Sum: %d\n", sum);   // Output: Sum: 8
printf("Pi: %f\n", pi);     // Output: Pi: 3.141590
```

## Function Parameters
```c
// Multiple parameters
void print_info(char name[], int age, double height) {
    printf("Name: %s, Age: %d, Height: %.2f\n", name, age, height);
}

// Calling
print_info("Alice", 25, 5.6);
```

## Return Statement
- Causes function to exit immediately
- Returns control to calling function
- Can return a value or nothing (void)

```c
int find_max(int a, int b) {
    if (a > b) {
        return a;  // Exit here if a > b
    }
    return b;      // Otherwise return b
}
```

## void Functions
```c
void display_menu() {
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Exit\n");
}

// No return statement needed for void functions
// (but you can use 'return;' to exit early)
```

## Function Prototypes
```c
// Declaration (prototype) - tells compiler about function
int multiply(int, int);

// Definition - actual implementation
int multiply(int a, int b) {
    return a * b;
}

int main() {
    int result = multiply(4, 5);  // OK to call before definition
    return 0;
}
```

## Best Practices
- Use descriptive function names
- Keep functions focused on single responsibility
- Use meaningful parameter names
- Document function purpose with comments
- Avoid functions that are too long

## Common Mistakes
- Forgetting return type (defaults to int in old C)
- Missing return statement in non-void functions
- Wrong parameter types in calls
- Not handling return values