# 03: Preprocessor Macros

## Preprocessor Macros
The C preprocessor processes source code before compilation, handling macros, includes, and conditional compilation.

## Basic Macros
```c
#include <stdio.h>

// Simple constant macro
#define PI 3.14159
#define MAX_SIZE 100
#define MESSAGE "Hello, World!"

int main() {
    printf("PI = %.5f\n", PI);
    printf("Max size = %d\n", MAX_SIZE);
    printf("%s\n", MESSAGE);
    return 0;
}
```

## Function-like Macros
```c
// Simple function macro
#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    int x = 5, y = 3;

    printf("Square of %d = %d\n", x, SQUARE(x));
    printf("Cube of %d = %d\n", x, CUBE(x));
    printf("Max(%d, %d) = %d\n", x, y, MAX(x, y));
    printf("Min(%d, %d) = %d\n", x, y, MIN(x, y));

    return 0;
}
```

## Why Parentheses Matter
```c
// Wrong - operator precedence issues
#define BAD_SQUARE(x) x * x

// Good - properly parenthesized
#define GOOD_SQUARE(x) ((x) * (x))

int main() {
    int result1 = BAD_SQUARE(3 + 2);   // 3 + 2 * 3 + 2 = 11 (wrong!)
    int result2 = GOOD_SQUARE(3 + 2);  // (3 + 2) * (3 + 2) = 25 (correct!)

    printf("Bad: %d, Good: %d\n", result1, result2);
    return 0;
}
```

## Multi-line Macros
```c
#define PRINT_ARRAY(arr, size) \
    do { \
        printf("["); \
        for (int i = 0; i < (size); i++) { \
            printf("%d", (arr)[i]); \
            if (i < (size) - 1) printf(", "); \
        } \
        printf("]\n"); \
    } while(0)

#define SWAP(a, b) \
    do { \
        typeof(a) temp = (a); \
        (a) = (b); \
        (b) = temp; \
    } while(0)

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    PRINT_ARRAY(arr, 5);

    int x = 10, y = 20;
    printf("Before swap: x=%d, y=%d\n", x, y);
    SWAP(x, y);
    printf("After swap: x=%d, y=%d\n", x, y);

    return 0;
}
```

## Stringification
```c
// Convert argument to string
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

// Variable name and value
#define DEBUG_VAR(var) printf(#var " = %d\n", var)

int main() {
    int value = 42;
    char* name = "test";

    printf("Stringified: %s\n", STRINGIFY(Hello World));
    printf("Variable name: %s\n", TO_STRING(value));

    DEBUG_VAR(value);

    return 0;
}
```

## Token Concatenation
```c
// Concatenate tokens
#define CONCAT(a, b) a##b
#define MAKE_VAR(name, num) var##name##num

// Generate variable names
#define DECLARE_INT(name) int CONCAT(int_, name)
#define CREATE_ARRAY(type, name, size) type CONCAT(arr_, name)[size]

int main() {
    DECLARE_INT(counter);  // Creates: int int_counter
    CREATE_ARRAY(int, numbers, 10);  // Creates: int arr_numbers[10]

    int_counter = 5;
    for (int i = 0; i < 10; i++) {
        arr_numbers[i] = i * 2;
    }

    printf("Counter: %d\n", int_counter);
    printf("Array: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr_numbers[i]);
    }
    printf("\n");

    return 0;
}
```

## Variadic Macros (C99)
```c
#include <stdarg.h>

// Macros with variable arguments
#define DEBUG(fmt, ...) printf("DEBUG: " fmt "\n", __VA_ARGS__)
#define ERROR(fmt, ...) fprintf(stderr, "ERROR: " fmt "\n", __VA_ARGS__)

// Safe variadic macro
#define LOG(level, fmt, ...) \
    do { \
        printf(level ": " fmt "\n", ##__VA_ARGS__); \
    } while(0)

int main() {
    int x = 10, y = 20;

    DEBUG("Simple message");
    DEBUG("Values: x=%d, y=%d", x, y);
    ERROR("Something went wrong: %s", "file not found");

    LOG("INFO", "Starting application");
    LOG("WARN", "Low memory: %d MB", 50);

    return 0;
}
```

## Conditional Macros
```c
// Check if macro is defined
#define FEATURE_A
//#define FEATURE_B

#ifdef FEATURE_A
    #define HAS_FEATURE_A 1
#else
    #define HAS_FEATURE_A 0
#endif

#ifndef FEATURE_B
    #define HAS_FEATURE_B 0
#else
    #define HAS_FEATURE_B 1
#endif

int main() {
    printf("Feature A: %s\n", HAS_FEATURE_A ? "enabled" : "disabled");
    printf("Feature B: %s\n", HAS_FEATURE_B ? "enabled" : "disabled");
    return 0;
}
```

## Undefining Macros
```c
#define DEBUG 1
#define VERSION "1.0"

int main() {
    printf("Debug: %d, Version: %s\n", DEBUG, VERSION);

    #undef DEBUG
    #define DEBUG 0

    printf("Debug: %d, Version: %s\n", DEBUG, VERSION);

    #undef VERSION
    #define VERSION "2.0"

    printf("Debug: %d, Version: %s\n", DEBUG, VERSION);

    return 0;
}
```

## Built-in Macros
```c
int main() {
    printf("__FILE__: %s\n", __FILE__);     // Current file name
    printf("__LINE__: %d\n", __LINE__);     // Current line number
    printf("__DATE__: %s\n", __DATE__);     // Compilation date
    printf("__TIME__: %s\n", __TIME__);     // Compilation time
    printf("__func__: %s\n", __func__);     // Current function name (C99)

    #ifdef __STDC__
        printf("Standard C: %d\n", __STDC__);  // C standard version
    #endif

    #ifdef __STDC_VERSION__
        printf("C Standard Version: %ld\n", __STDC_VERSION__);
    #endif

    return 0;
}
```

## Macro Pitfalls
```c
// Problem 1: Multiple evaluation
#define BAD_MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
    int x = 1;
    int result = BAD_MAX(x++, 5);  // x is incremented twice!
    printf("x = %d, result = %d\n", x, result);  // x=3, not 2!
    return 0;
}

// Problem 2: Semicolon after macro
#define BAD_MACRO printf("Hello\n");

int main() {
    if (1)
        BAD_MACRO  // This creates: if (1) printf("Hello\n"); ;
    else
        printf("World\n");
    return 0;
}
```

## Advanced Macro Techniques
```c
// Generic container macro
#define CONTAINER_OF(ptr, type, member) \
    ((type*)((char*)(ptr) - offsetof(type, member)))

// Foreach macro
#define FOREACH(item, array, size) \
    for (size_t i = 0, item = (array)[0]; i < (size); item = (array)[++i])

// Compile-time assertion
#define COMPILE_TIME_ASSERT(pred) \
    switch(0){case 0:case pred:;}

int main() {
    // Example usage would require more setup
    printf("Macros can be very powerful!\n");
    return 0;
}
```

## Best Practices
- Always parenthesize macro parameters and expressions
- Use do-while(0) for multi-statement macros
- Avoid side effects in macro arguments
- Use inline functions instead of macros when possible
- Document complex macros thoroughly
- Consider using const/static const instead of macros for constants
- Be careful with operator precedence
- Test macros thoroughly with different inputs

## Common Mistakes
- Missing parentheses around parameters
- Missing parentheses around entire expression
- Side effects in macro arguments
- Semicolons after macro definitions
- Multiple evaluation of arguments
- Incorrect token concatenation
- Forgetting to undefine macros when needed
- Using macros when functions would be better

## Performance Considerations
```c
// Macro (no function call overhead)
#define FAST_SQUARE(x) ((x) * (x))

// Inline function (similar performance, type safety)
static inline int fast_square(int x) {
    return x * x;
}

// Regular function (function call overhead)
int slow_square(int x) {
    return x * x;
}

int main() {
    int x = 5;

    // All three are fast, but macro has no type checking
    printf("Macro: %d\n", FAST_SQUARE(x));
    printf("Inline: %d\n", fast_square(x));
    printf("Function: %d\n", slow_square(x));

    return 0;
}
```

## Embedded Systems Applications
### Hardware Register Access
```c
#define REG32(addr) (*(volatile uint32_t*)(addr))

#define GPIO_BASE 0x40020000
#define GPIO_MODER REG32(GPIO_BASE + 0x00)
#define GPIO_OTYPER REG32(GPIO_BASE + 0x04)
#define GPIO_OSPEEDR REG32(GPIO_BASE + 0x08)

#define BIT_SET(reg, bit) ((reg) |= (1U << (bit)))
#define BIT_CLEAR(reg, bit) ((reg) &= ~(1U << (bit)))
#define BIT_TEST(reg, bit) ((reg) & (1U << (bit)))
```

### Configuration Macros
```c
// System configuration
#define SYSTEM_CLOCK 72000000UL
#define UART_BAUD_RATE 115200
#define ADC_RESOLUTION 12

// Feature flags
#define ENABLE_DEBUG
#define USE_DMA
//#define LOW_POWER_MODE

// Conditional compilation based on features
#ifdef ENABLE_DEBUG
    #define DEBUG_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif
```

### Bit Manipulation Macros
```c
#define BIT(n) (1UL << (n))
#define BIT_SET(reg, bit) ((reg) |= BIT(bit))
#define BIT_CLEAR(reg, bit) ((reg) &= ~BIT(bit))
#define BIT_TOGGLE(reg, bit) ((reg) ^= BIT(bit))
#define BIT_TEST(reg, bit) ((reg) & BIT(bit))

#define MASK_SET(reg, mask) ((reg) |= (mask))
#define MASK_CLEAR(reg, mask) ((reg) &= ~(mask))
#define MASK_TEST(reg, mask) ((reg) & (mask))

// Usage
#define LED_PIN 5
#define BUTTON_PIN 3

// Set LED pin as output
BIT_SET(GPIO_MODER, LED_PIN * 2);
// Clear LED pin
BIT_CLEAR(GPIO_ODR, LED_PIN);
// Check if button is pressed
if (BIT_TEST(GPIO_IDR, BUTTON_PIN)) {
    // Button pressed
}
```