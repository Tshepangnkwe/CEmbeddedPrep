# 04: Conditional Compilation

## Conditional Compilation
The preprocessor can include or exclude code based on conditions, enabling platform-specific code and feature toggles.

## Basic Conditional Directives
```c
#include <stdio.h>

// Define a feature flag
#define DEBUG_MODE

int main() {
    printf("Program started\n");

    #ifdef DEBUG_MODE
        printf("Debug mode is enabled\n");
        printf("This code only appears in debug builds\n");
    #endif

    printf("Program continues\n");

    #ifndef RELEASE_MODE
        printf("Not in release mode\n");
    #endif

    return 0;
}
```

## #ifdef, #ifndef, #endif
```c
#define FEATURE_A
//#define FEATURE_B
#define FEATURE_C 1

int main() {
    #ifdef FEATURE_A
        printf("Feature A is defined\n");
    #endif

    #ifdef FEATURE_B
        printf("Feature B is defined\n");
    #else
        printf("Feature B is not defined\n");
    #endif

    #ifndef FEATURE_C
        printf("Feature C is not defined\n");
    #else
        printf("Feature C is defined and equals %d\n", FEATURE_C);
    #endif

    return 0;
}
```

## #if, #elif, #else, #endif
```c
#define VERSION 2
#define PLATFORM_WINDOWS 1
#define PLATFORM_LINUX 2
#define PLATFORM_MAC 3

#define TARGET_PLATFORM PLATFORM_WINDOWS

int main() {
    #if VERSION >= 2
        printf("Version 2 or higher\n");
    #elif VERSION >= 1
        printf("Version 1\n");
    #else
        printf("Version 0 or lower\n");
    #endif

    #if TARGET_PLATFORM == PLATFORM_WINDOWS
        printf("Running on Windows\n");
    #elif TARGET_PLATFORM == PLATFORM_LINUX
        printf("Running on Linux\n");
    #elif TARGET_PLATFORM == PLATFORM_MAC
        printf("Running on Mac\n");
    #else
        printf("Unknown platform\n");
    #endif

    return 0;
}
```

## defined() Operator
```c
// Alternative syntax using defined()
#define FEATURE_X
//#define FEATURE_Y

int main() {
    #if defined(FEATURE_X) && defined(FEATURE_Y)
        printf("Both features enabled\n");
    #elif defined(FEATURE_X) || defined(FEATURE_Y)
        printf("At least one feature enabled\n");
    #else
        printf("No features enabled\n");
    #endif

    // Can also use !defined()
    #if !defined(FEATURE_Z)
        printf("Feature Z is not enabled\n");
    #endif

    return 0;
}
```

## Nested Conditionals
```c
#define DEBUG 1
#define VERBOSE 1
#define TARGET_EMBEDDED

int main() {
    #ifdef DEBUG
        printf("Debug build\n");

        #ifdef VERBOSE
            printf("Verbose debug output enabled\n");
        #endif

        #ifndef TARGET_EMBEDDED
            printf("Running on desktop\n");
        #else
            printf("Running on embedded system\n");
        #endif

    #else
        printf("Release build\n");
    #endif

    return 0;
}
```

## Platform-Specific Code
```c
// Simulate different platforms
#define _WIN32
//#define __linux__
//#define __APPLE__

int main() {
    #ifdef _WIN32
        printf("Windows-specific code\n");
        // Windows API calls would go here
    #elif defined(__linux__)
        printf("Linux-specific code\n");
        // Linux system calls would go here
    #elif defined(__APPLE__)
        printf("macOS-specific code\n");
        // macOS specific code would go here
    #else
        printf("Generic/unknown platform\n");
    #endif

    return 0;
}
```

## Compiler-Specific Code
```c
// Different compilers
//#define __GNUC__
//#define _MSC_VER
//#define __clang__

#ifdef __GNUC__
    #define COMPILER_NAME "GCC"
    #define COMPILER_VERSION __GNUC__
#elif defined(_MSC_VER)
    #define COMPILER_NAME "MSVC"
    #define COMPILER_VERSION _MSC_VER
#elif defined(__clang__)
    #define COMPILER_NAME "Clang"
    #define COMPILER_VERSION __clang_major__
#else
    #define COMPILER_NAME "Unknown"
    #define COMPILER_VERSION 0
#endif

int main() {
    printf("Compiler: %s\n", COMPILER_NAME);
    printf("Version: %d\n", COMPILER_VERSION);
    return 0;
}
```

## Feature Toggles
```c
// Feature flags
#define ENABLE_LOGGING
#define ENABLE_NETWORKING
//#define ENABLE_ENCRYPTION
#define MAX_CONNECTIONS 10

void log_message(const char* msg) {
    #ifdef ENABLE_LOGGING
        printf("[LOG] %s\n", msg);
    #endif
}

int connect_to_server() {
    #ifdef ENABLE_NETWORKING
        printf("Connecting to server...\n");
        return 1;
    #else
        printf("Networking disabled\n");
        return 0;
    #endif
}

void encrypt_data(char* data) {
    #ifdef ENABLE_ENCRYPTION
        printf("Encrypting data: %s\n", data);
    #else
        printf("Encryption disabled, data: %s\n", data);
    #endif
}

int main() {
    log_message("Application started");

    if (connect_to_server()) {
        encrypt_data("secret message");
    }

    printf("Max connections: %d\n", MAX_CONNECTIONS);

    return 0;
}
```

## Build Configuration
```c
// Build types
//#define BUILD_DEBUG
#define BUILD_RELEASE
//#define BUILD_TEST

#if defined(BUILD_DEBUG)
    #define LOG_LEVEL 3  // All logs
    #define ENABLE_ASSERTS
    #define SLOW_OPERATIONS
#elif defined(BUILD_RELEASE)
    #define LOG_LEVEL 1  // Only errors
    #define OPTIMIZE_FOR_SPEED
#elif defined(BUILD_TEST)
    #define LOG_LEVEL 2  // Warnings and errors
    #define ENABLE_MOCKS
    #define RUN_UNIT_TESTS
#endif

void log_error(const char* msg) {
    #if LOG_LEVEL >= 1
        printf("[ERROR] %s\n", msg);
    #endif
}

void log_warning(const char* msg) {
    #if LOG_LEVEL >= 2
        printf("[WARN] %s\n", msg);
    #endif
}

void log_debug(const char* msg) {
    #if LOG_LEVEL >= 3
        printf("[DEBUG] %s\n", msg);
    #endif
}

int main() {
    log_error("This is an error");
    log_warning("This is a warning");
    log_debug("This is debug info");

    #ifdef ENABLE_ASSERTS
        printf("Assertions enabled\n");
    #endif

    #ifdef OPTIMIZE_FOR_SPEED
        printf("Optimized for speed\n");
    #endif

    return 0;
}
```

## Header Guards
```c
// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H

// Header contents
#define CONSTANT 42

void my_function();

#endif // MYHEADER_H

// Alternative modern syntax
// #pragma once
```

## Error and Warning Directives
```c
#define REQUIRED_FEATURE

#ifndef REQUIRED_FEATURE
    #error "REQUIRED_FEATURE must be defined"
#endif

#if __STDC_VERSION__ < 199901L
    #warning "C99 or later recommended"
#endif

int main() {
    printf("Compilation successful\n");
    return 0;
}
```

## Complex Conditions
```c
#define VERSION_MAJOR 2
#define VERSION_MINOR 1
#define PLATFORM_DESKTOP
#define ARCHITECTURE_64BIT

// Complex conditional
#if (VERSION_MAJOR >= 2 && VERSION_MINOR >= 1) && \
    (defined(PLATFORM_DESKTOP) || defined(PLATFORM_MOBILE)) && \
    defined(ARCHITECTURE_64BIT)

    #define ADVANCED_FEATURES_ENABLED
#endif

int main() {
    #ifdef ADVANCED_FEATURES_ENABLED
        printf("Advanced features enabled\n");
    #else
        printf("Basic features only\n");
    #endif

    return 0;
}
```

## Include Guards with Conditionals
```c
// config.h
#ifndef CONFIG_H
#define CONFIG_H

// Platform detection
#if defined(_WIN32)
    #define PLATFORM "Windows"
    #define PATH_SEPARATOR '\\'
#elif defined(__linux__)
    #define PLATFORM "Linux"
    #define PATH_SEPARATOR '/'
#elif defined(__APPLE__)
    #define PLATFORM "macOS"
    #define PATH_SEPARATOR '/'
#else
    #define PLATFORM "Unknown"
    #define PATH_SEPARATOR '/'
#endif

// Architecture detection
#if defined(__x86_64__) || defined(_M_X64)
    #define ARCHITECTURE "x64"
#elif defined(__i386__) || defined(_M_IX86)
    #define ARCHITECTURE "x86"
#elif defined(__arm__)
    #define ARCHITECTURE "ARM"
#else
    #define ARCHITECTURE "Unknown"
#endif

#endif // CONFIG_H
```

## Best Practices
- Use meaningful macro names for conditions
- Document what each conditional block does
- Keep conditional blocks small and focused
- Use consistent naming conventions
- Avoid deeply nested conditionals
- Test all conditional paths
- Use #error for required features
- Use #warning for deprecated features
- Combine related conditions with logical operators

## Common Mistakes
- Forgetting #endif
- Mismatched #ifdef/#ifndef
- Undefined macros in conditions
- Case sensitivity in macro names
- Missing parentheses in complex conditions
- Side effects in #if conditions
- Inconsistent indentation
- Overusing conditional compilation

## Performance Considerations
```c
// Conditional compilation for performance
#define USE_FAST_ALGORITHM

#ifdef USE_FAST_ALGORITHM
    // Fast but memory-intensive algorithm
    #define SORT_THRESHOLD 1000
#else
    // Slow but memory-efficient algorithm
    #define SORT_THRESHOLD 100
#endif

int main() {
    int data_size = 500;

    if (data_size > SORT_THRESHOLD) {
        printf("Using fast algorithm\n");
    } else {
        printf("Using memory-efficient algorithm\n");
    }

    return 0;
}
```

## Embedded Systems Applications
### Hardware-Specific Code
```c
// Hardware abstraction layer
#define MCU_STM32F4
//#define MCU_ATMEGA328

#ifdef MCU_STM32F4
    #define GPIO_BASE 0x40020000
    #define TIMER_BASE 0x40000000
    typedef uint32_t reg_t;
#elif defined(MCU_ATMEGA328)
    #define GPIO_BASE 0x20
    #define TIMER_BASE 0x44
    typedef uint8_t reg_t;
#endif

// Generic register access
#define REG32(addr) (*(volatile reg_t*)(addr))

void init_hardware() {
    #ifdef MCU_STM32F4
        // STM32 specific initialization
        REG32(0x40023830) |= (1 << 0);  // Enable GPIOA clock
    #elif defined(MCU_ATMEGA328)
        // AVR specific initialization
        REG32(0x24) = 0xFF;  // Set PORTB as output
    #endif
}
```

### Memory-Constrained Systems
```c
// Memory configuration
#define MEMORY_SMALL    // 2KB RAM
//#define MEMORY_MEDIUM  // 8KB RAM
//#define MEMORY_LARGE   // 32KB RAM

#ifdef MEMORY_SMALL
    #define MAX_BUFFER_SIZE 128
    #define ENABLE_COMPRESSION
    #define DISABLE_LOGGING
#elif defined(MEMORY_MEDIUM)
    #define MAX_BUFFER_SIZE 1024
    #define ENABLE_COMPRESSION
    #define ENABLE_LOGGING
#else
    #define MAX_BUFFER_SIZE 4096
    #define DISABLE_COMPRESSION
    #define ENABLE_LOGGING
#endif

char buffer[MAX_BUFFER_SIZE];

int main() {
    printf("Buffer size: %d bytes\n", MAX_BUFFER_SIZE);

    #ifdef ENABLE_COMPRESSION
        printf("Compression enabled\n");
    #endif

    #ifdef ENABLE_LOGGING
        printf("Logging enabled\n");
    #else
        printf("Logging disabled\n");
    #endif

    return 0;
}
```

### Power Management
```c
// Power modes
#define POWER_LOW
//#define POWER_NORMAL
//#define POWER_HIGH

#ifdef POWER_LOW
    #define CPU_FREQUENCY 8000000   // 8MHz
    #define DISABLE_PERIPHERALS
    #define SLEEP_BETWEEN_TASKS
#elif defined(POWER_NORMAL)
    #define CPU_FREQUENCY 48000000  // 48MHz
    #define ENABLE_BASIC_PERIPHERALS
#else
    #define CPU_FREQUENCY 168000000 // 168MHz
    #define ENABLE_ALL_PERIPHERALS
#endif

void configure_power() {
    printf("CPU Frequency: %d Hz\n", CPU_FREQUENCY);

    #ifdef DISABLE_PERIPHERALS
        printf("Peripherals disabled for power saving\n");
    #endif

    #ifdef SLEEP_BETWEEN_TASKS
        printf("Sleep mode enabled between tasks\n");
    #endif
}
```