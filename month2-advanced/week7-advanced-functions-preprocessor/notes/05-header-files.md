# 05: Header Files

## Header Files
Header files (.h) contain declarations that can be shared across multiple source files, enabling modular programming.

## Basic Header Structure
```c
// math_utils.h
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Function declarations
int add(int a, int b);
int multiply(int a, int b);
double power(double base, int exp);

// Constant definitions
#define PI 3.14159
#define E 2.71828

// Type definitions
typedef struct {
    double x, y;
} Point;

#endif // MATH_UTILS_H
```

```c
// math_utils.c
#include "math_utils.h"
#include <math.h>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

double power(double base, int exp) {
    return pow(base, exp);
}
```

```c
// main.c
#include <stdio.h>
#include "math_utils.h"

int main() {
    Point p = {3.0, 4.0};

    printf("Add: %d\n", add(5, 3));
    printf("Multiply: %d\n", multiply(5, 3));
    printf("Power: %.2f\n", power(2.0, 3));
    printf("Point: (%.1f, %.1f)\n", p.x, p.y);

    return 0;
}
```

## Include Guards
```c
// myheader.h
#ifndef MYHEADER_H
#define MYHEADER_H

// Header content here

#endif // MYHEADER_H

// Alternative (modern compilers)
// #pragma once
```

## Multiple Inclusion Problem
```c
// Without include guards - PROBLEM
// file1.h
void func1();

// file2.h
#include "file1.h"
void func2();

// main.c
#include "file1.h"
#include "file2.h"  // This includes file1.h again - DUPLICATE!

// With include guards - SOLUTION
// file1.h
#ifndef FILE1_H
#define FILE1_H
void func1();
#endif

// file2.h
#ifndef FILE2_H
#define FILE2_H
#include "file1.h"
void func2();
#endif

// main.c
#include "file1.h"
#include "file2.h"  // Safe - no duplicates
```

## Header File Organization
```c
// device_driver.h - Complete header example
#ifndef DEVICE_DRIVER_H
#define DEVICE_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

// Version information
#define DRIVER_VERSION_MAJOR 1
#define DRIVER_VERSION_MINOR 0

// Hardware constants
#define DEVICE_BASE_ADDRESS 0x40000000
#define DEVICE_BUFFER_SIZE 1024

// Error codes
typedef enum {
    DEVICE_OK = 0,
    DEVICE_ERROR_TIMEOUT = -1,
    DEVICE_ERROR_INVALID_PARAM = -2,
    DEVICE_ERROR_BUSY = -3
} DeviceError;

// Device configuration structure
typedef struct {
    uint32_t baud_rate;
    bool enable_interrupts;
    uint8_t buffer_size;
} DeviceConfig;

// Device handle
typedef struct DeviceHandle DeviceHandle;

// Function declarations
DeviceError device_init(DeviceConfig* config, DeviceHandle** handle);
DeviceError device_write(DeviceHandle* handle, const uint8_t* data, size_t size);
DeviceError device_read(DeviceHandle* handle, uint8_t* buffer, size_t size);
DeviceError device_close(DeviceHandle* handle);

// Utility functions
const char* device_error_string(DeviceError error);
uint32_t device_get_version(void);

#endif // DEVICE_DRIVER_H
```

## Forward Declarations
```c
// When you only need pointers or references to a type
#ifndef MYLIB_H
#define MYLIB_H

// Forward declaration - no need for full definition
struct InternalData;
typedef struct InternalData InternalData;

// Function that uses pointer to incomplete type
void process_data(InternalData* data);

#endif // MYLIB_H

// In the implementation file
// #include "mylib.h"

struct InternalData {
    int value;
    char* name;
};

void process_data(InternalData* data) {
    // Now we can use the full definition
    printf("Value: %d, Name: %s\n", data->value, data->name);
}
```

## Conditional Headers
```c
// config.h
#ifndef CONFIG_H
#define CONFIG_H

// Platform detection
#ifdef _WIN32
    #define PLATFORM_WINDOWS
    #include <windows.h>
#elif defined(__linux__)
    #define PLATFORM_LINUX
    #include <unistd.h>
#elif defined(__APPLE__)
    #define PLATFORM_MACOS
    #include <unistd.h>
#endif

// Feature flags
#define ENABLE_DEBUG
//#define ENABLE_OPTIMIZATION

#endif // CONFIG_H
```

## System vs User Headers
```c
// System headers (angle brackets)
#include <stdio.h>      // Standard library
#include <stdlib.h>
#include <string.h>

// User headers (double quotes)
#include "myheader.h"   // Your custom headers
#include "utils/math.h"
#include "../common/types.h"
```

## Header Dependencies
```c
// Low-level header
// types.h
#ifndef TYPES_H
#define TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#endif // TYPES_H

// Mid-level header
// buffer.h
#ifndef BUFFER_H
#define BUFFER_H

#include "types.h"

typedef struct {
    uint8_t* data;
    uint32_t size;
    uint32_t capacity;
} Buffer;

void buffer_init(Buffer* buf, uint32_t capacity);
void buffer_free(Buffer* buf);

#endif // BUFFER_H

// High-level header
// network.h
#ifndef NETWORK_H
#define NETWORK_H

#include "buffer.h"

typedef struct {
    Buffer send_buffer;
    Buffer recv_buffer;
    uint32_t socket_id;
} NetworkConnection;

int network_connect(NetworkConnection* conn, const char* address);
int network_send(NetworkConnection* conn, const uint8_t* data, uint32_t size);

#endif // NETWORK_H
```

## Inline Functions in Headers
```c
// math_functions.h
#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <math.h>

// Inline functions can be defined in headers
static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

static inline double clamp(double value, double min_val, double max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

// Function declaration (definition in .c file)
double complex_calculation(double x, double y);

#endif // MATH_FUNCTIONS_H
```

## Header-Only Libraries
```c
// vector.h - Header-only vector implementation
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    size_t size;
    size_t capacity;
    int* data;
} Vector;

static inline void vector_init(Vector* vec) {
    vec->size = 0;
    vec->capacity = 0;
    vec->data = NULL;
}

static inline void vector_free(Vector* vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

static inline void vector_push_back(Vector* vec, int value) {
    if (vec->size >= vec->capacity) {
        size_t new_capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
        int* new_data = realloc(vec->data, new_capacity * sizeof(int));
        assert(new_data != NULL);
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size++] = value;
}

static inline int vector_get(const Vector* vec, size_t index) {
    assert(index < vec->size);
    return vec->data[index];
}

#endif // VECTOR_H
```

## Best Practices
- Use include guards or #pragma once
- Include only necessary headers
- Keep headers minimal and focused
- Use forward declarations when possible
- Document all public interfaces
- Avoid global variables in headers
- Use consistent naming conventions
- Separate interface from implementation
- Test header inclusion order

## Common Mistakes
- Missing include guards
- Including headers in wrong order
- Circular dependencies
- Defining variables in headers
- Including unnecessary system headers
- Inconsistent header organization
- Missing function declarations
- Type definition issues

## Performance Considerations
```c
// Minimize header dependencies
// Bad - includes everything
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Good - include only what you need
#include <stdint.h>  // For uint32_t
#include <stdbool.h> // For bool

// Forward declarations instead of includes
struct FileHandle;  // Instead of #include "file.h"
typedef struct FileHandle FileHandle;
```

## Embedded Systems Applications
### Hardware Abstraction Layer (HAL)
```c
// hal_gpio.h
#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOG
} GpioMode;

typedef enum {
    GPIO_PULL_NONE,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} GpioPull;

typedef struct {
    uint8_t pin;
    GpioMode mode;
    GpioPull pull;
    bool initial_state;
} GpioConfig;

void hal_gpio_init(const GpioConfig* config);
void hal_gpio_write(uint8_t pin, bool state);
bool hal_gpio_read(uint8_t pin);
void hal_gpio_toggle(uint8_t pin);

#endif // HAL_GPIO_H
```

### Device Driver Interface
```c
// spi_driver.h
#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>
#include <stddef.h>

typedef struct SpiHandle SpiHandle;

typedef enum {
    SPI_MODE_0,  // CPOL=0, CPHA=0
    SPI_MODE_1,  // CPOL=0, CPHA=1
    SPI_MODE_2,  // CPOL=1, CPHA=0
    SPI_MODE_3   // CPOL=1, CPHA=1
} SpiMode;

typedef struct {
    uint32_t frequency;
    SpiMode mode;
    uint8_t data_size;  // 4-16 bits
    bool lsb_first;
} SpiConfig;

int spi_init(const SpiConfig* config, SpiHandle** handle);
int spi_transfer(SpiHandle* handle, const uint8_t* tx_data,
                 uint8_t* rx_data, size_t size);
int spi_write(SpiHandle* handle, const uint8_t* data, size_t size);
int spi_read(SpiHandle* handle, uint8_t* buffer, size_t size);
void spi_deinit(SpiHandle* handle);

#endif // SPI_DRIVER_H
```

### RTOS Task Interface
```c
// rtos_task.h
#ifndef RTOS_TASK_H
#define RTOS_TASK_H

#include <stdint.h>
#include <stddef.h>

typedef void (*TaskFunction)(void* parameter);

typedef enum {
    TASK_PRIORITY_LOW = 1,
    TASK_PRIORITY_NORMAL = 2,
    TASK_PRIORITY_HIGH = 3,
    TASK_PRIORITY_CRITICAL = 4
} TaskPriority;

typedef struct {
    const char* name;
    TaskFunction function;
    void* parameter;
    uint32_t stack_size;
    TaskPriority priority;
} TaskConfig;

typedef struct TaskHandle TaskHandle;

TaskHandle* rtos_task_create(const TaskConfig* config);
void rtos_task_delete(TaskHandle* task);
void rtos_task_suspend(TaskHandle* task);
void rtos_task_resume(TaskHandle* task);
void rtos_task_delay(uint32_t milliseconds);

#endif // RTOS_TASK_H
```