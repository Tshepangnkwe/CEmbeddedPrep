# Preprocessor Cheatsheet

## Include Directives

### Header Files
```c
#include <stdio.h>     // System headers (angle brackets)
#include "myheader.h"  // User headers (quotes)

// Include guards
#ifndef MYHEADER_H
#define MYHEADER_H

// Header content here

#endif // MYHEADER_H
```

### Include Paths
```c
// Compiler options
// -I/path/to/headers  Add include path
// -isystem /path/to/system/headers  System include path
```

## Macros

### Object-like Macros
```c
#define PI 3.14159
#define BUFFER_SIZE 1024
#define DEBUG 1

// Usage
double area = PI * radius * radius;
char buffer[BUFFER_SIZE];
```

### Function-like Macros
```c
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Usage
int result = SQUARE(5);  // 25
int larger = MAX(x, y);
```

### Multi-line Macros
```c
#define LOG_ERROR(msg) \
    do { \
        fprintf(stderr, "ERROR: %s at %s:%d\n", \
                msg, __FILE__, __LINE__); \
    } while(0)

// Prevents issues when used in if statements without braces
if (error_condition)
    LOG_ERROR("Something went wrong");
```

## Conditional Compilation

### Basic Conditionals
```c
#define DEBUG 1

#if DEBUG
    printf("Debug mode\n");
#endif

#ifdef DEBUG
    // Code only compiled if DEBUG is defined
#endif

#ifndef RELEASE
    // Code excluded in release builds
#endif
```

### Platform-Specific Code
```c
#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR '\\'
#elif defined(__linux__)
    #include <unistd.h>
    #define PATH_SEPARATOR '/'
#else
    #error "Unsupported platform"
#endif
```

### Version Checks
```c
#if __STDC_VERSION__ >= 199901L
    // C99 features available
#endif

#if defined(__GNUC__) && __GNUC__ >= 4
    // GCC 4.0+ specific code
#endif
```

## Predefined Macros

### Standard Macros
```c
__FILE__    // Current source file name
__LINE__    // Current line number
__func__    // Current function name (C99)
__DATE__    // Compilation date
__TIME__    // Compilation time

printf("Error in %s at line %d\n", __FILE__, __LINE__);
```

### Compiler-Specific
```c
// GCC
__GNUC__        // Major version
__GNUC_MINOR__  // Minor version

// Visual Studio
_MSC_VER        // Compiler version

// Architecture
__x86_64__      // x86-64
__arm__         // ARM
__AVR__         // AVR microcontroller
```

## Stringification and Token Pasting

### Stringification (#)
```c
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

#define VERSION 1.2.3
printf("Version: %s\n", TO_STRING(VERSION));  // "Version: 1.2.3"
```

### Token Pasting (##)
```c
#define CONCAT(a, b) a##b
#define MAKE_VAR(name, num) var##name##num

int CONCAT(var, 1) = 10;  // int var1 = 10;
int MAKE_VAR(temp, 2) = 20;  // int vartemp2 = 20;
```

### Generic Macros
```c
#define GENERIC_MAX(type) \
    type max_##type(type a, type b) { \
        return a > b ? a : b; \
    }

GENERIC_MAX(int)    // Creates max_int function
GENERIC_MAX(float)  // Creates max_float function
```

## Variadic Macros

### Basic Variadic
```c
#define LOG(format, ...) \
    printf("[%s:%d] " format "\n", __FILE__, __LINE__, __VA_ARGS__)

LOG("Value: %d", value);
LOG("Multiple: %d %f %s", 42, 3.14, "hello");
```

### Conditional Variadic
```c
#define LOG(...) \
    do { \
        if (DEBUG) { \
            printf(__VA_ARGS__); \
        } \
    } while(0)
```

## Pragma Directives

### Common Pragmas
```c
#pragma once  // Alternative to include guards

#pragma pack(1)  // Disable structure padding
struct packed {
    char c;
    int i;
};
#pragma pack()  // Restore default

#pragma warning(disable: 4996)  // Disable specific warnings (MSVC)
#pragma GCC diagnostic ignored "-Wdeprecated"  // GCC warnings
```

### Optimization Pragmas
```c
#pragma GCC optimize("O3")  // GCC optimization level

// Function-specific optimization
#pragma GCC push_options
#pragma GCC optimize("O0")
void debug_function() {
    // Debug code with no optimization
}
#pragma GCC pop_options
```

## Embedded-Specific Patterns

### Hardware Abstraction
```c
// Register definitions
#define GPIO_BASE 0x40020000
#define GPIO_MODER (*((volatile uint32_t *)(GPIO_BASE + 0x00)))
#define GPIO_ODR   (*((volatile uint32_t *)(GPIO_BASE + 0x14)))

// Bit manipulation macros
#define SET_BIT(reg, bit)   ((reg) |= (1U << (bit)))
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1U << (bit)))
#define TOGGLE_BIT(reg, bit) ((reg) ^= (1U << (bit)))
#define CHECK_BIT(reg, bit) ((reg) & (1U << (bit)))

// Usage
SET_BIT(GPIO_MODER, 0);    // Set pin 0 as output
SET_BIT(GPIO_ODR, 0);      // Set pin 0 high
```

### Peripheral Configuration
```c
// UART configuration
#define UART_BAUD_9600   9600
#define UART_BAUD_115200 115200

#define CONFIGURE_UART(baud) \
    do { \
        UART_CR1 = 0x200C; \
        UART_CR2 = 0x0000; \
        UART_BRR = (SystemCoreClock / baud); \
    } while(0)

// Usage
CONFIGURE_UART(UART_BAUD_9600);
```

### Memory-Mapped I/O
```c
// Memory barrier for volatile access
#define MEMORY_BARRIER() __asm__ __volatile__("" ::: "memory")

// Safe register access
#define READ_REG(reg) ({ \
    MEMORY_BARRIER(); \
    (reg); \
})

#define WRITE_REG(reg, val) do { \
    (reg) = (val); \
    MEMORY_BARRIER(); \
} while(0)
```

### Interrupt Handlers
```c
// Interrupt service routine macros
#define ISR(vector) void vector(void) __attribute__((interrupt))

// Example for AVR
ISR(TIMER0_OVF_vect) {
    // Timer overflow handler
    TCNT0 = 0;  // Reset counter
}

// For ARM Cortex-M
#define INTERRUPT __attribute__((interrupt("IRQ")))
void INTERRUPT SysTick_Handler(void) {
    // Systick handler
}
```

### Conditional Compilation for Features
```c
// Feature flags
#define FEATURE_ADC    1
#define FEATURE_SPI    1
#define FEATURE_I2C    0

// Conditional code inclusion
#if FEATURE_ADC
void adc_init(void) {
    // ADC initialization
}
#endif

#if FEATURE_SPI
#include "spi_driver.h"
#endif

// Configuration validation
#if !defined(FEATURE_SPI) && !defined(FEATURE_I2C)
#error "At least one communication interface must be enabled"
#endif
```

### Build Configuration
```c
// Build types
#define BUILD_DEBUG    1
#define BUILD_RELEASE  2
#define BUILD_TEST     3

#ifndef BUILD_TYPE
#define BUILD_TYPE BUILD_DEBUG
#endif

// Build-specific code
#if BUILD_TYPE == BUILD_DEBUG
    #define ASSERT(expr) \
        if (!(expr)) { \
            printf("Assertion failed: %s at %s:%d\n", \
                   #expr, __FILE__, __LINE__); \
            while(1); \
        }
#else
    #define ASSERT(expr) ((void)0)
#endif

// Usage
ASSERT(x > 0);
```

## Best Practices

- Use include guards or #pragma once
- Parenthesize macro parameters
- Avoid side effects in macro arguments
- Use meaningful macro names
- Document complex macros
- Prefer inline functions over function macros when possible
- Be careful with operator precedence in macros
- Use conditional compilation for platform-specific code
- Avoid deep macro nesting
- Test macros with various inputs
- Consider using static inline functions instead of macros for complex operations