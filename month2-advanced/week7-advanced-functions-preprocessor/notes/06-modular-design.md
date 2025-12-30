# 06: Modular Design

## Modular Design
Breaking down programs into smaller, independent modules that can be developed, tested, and maintained separately.

## Basic Module Structure
```c
// math_module.h
#ifndef MATH_MODULE_H
#define MATH_MODULE_H

// Public interface
int math_add(int a, int b);
int math_multiply(int a, int b);
double math_power(double base, int exp);
void math_print_version(void);

#endif // MATH_MODULE_H
```

```c
// math_module.c
#include "math_module.h"
#include <stdio.h>
#include <math.h>

// Private constants and functions
static const char* MODULE_VERSION = "1.0.0";

static double internal_calculation(double x) {
    return x * x + 2 * x + 1;
}

// Public function implementations
int math_add(int a, int b) {
    return a + b;
}

int math_multiply(int a, int b) {
    return a * b;
}

double math_power(double base, int exp) {
    return pow(base, exp);
}

void math_print_version(void) {
    printf("Math Module Version: %s\n", MODULE_VERSION);
}
```

```c
// main.c
#include <stdio.h>
#include "math_module.h"

int main() {
    math_print_version();

    printf("5 + 3 = %d\n", math_add(5, 3));
    printf("5 * 3 = %d\n", math_multiply(5, 3));
    printf("2^3 = %.0f\n", math_power(2.0, 3));

    return 0;
}
```

## Module Interface Design
```c
// logger.h - Clean interface design
#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

typedef enum {
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
} LogLevel;

// Opaque pointer to hide implementation
typedef struct Logger Logger;

// Constructor/Destructor
Logger* logger_create(const char* filename);
void logger_destroy(Logger* logger);

// Configuration
void logger_set_level(Logger* logger, LogLevel level);
void logger_enable_timestamps(Logger* logger, int enable);

// Logging functions
void logger_error(Logger* logger, const char* format, ...);
void logger_warning(Logger* logger, const char* format, ...);
void logger_info(Logger* logger, const char* format, ...);
void logger_debug(Logger* logger, const char* format, ...);

// Utility
const char* logger_get_filename(const Logger* logger);

#endif // LOGGER_H
```

```c
// logger.c - Implementation hidden from users
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

struct Logger {
    FILE* file;
    char* filename;
    LogLevel level;
    int timestamps_enabled;
};

Logger* logger_create(const char* filename) {
    Logger* logger = malloc(sizeof(Logger));
    if (!logger) return NULL;

    logger->file = fopen(filename, "a");
    if (!logger->file) {
        free(logger);
        return NULL;
    }

    logger->filename = strdup(filename);
    logger->level = LOG_LEVEL_INFO;
    logger->timestamps_enabled = 1;

    return logger;
}

void logger_destroy(Logger* logger) {
    if (logger) {
        if (logger->file) fclose(logger->file);
        free(logger->filename);
        free(logger);
    }
}

// ... implementation continues
```

## Data Hiding with Opaque Types
```c
// stack.h
#ifndef STACK_H
#define STACK_H

#define STACK_MAX_SIZE 100

// Opaque type - users don't know internal structure
typedef struct Stack Stack;

// Constructor/Destructor
Stack* stack_create(void);
void stack_destroy(Stack* stack);

// Operations
int stack_push(Stack* stack, int value);
int stack_pop(Stack* stack, int* value);
int stack_peek(const Stack* stack, int* value);
int stack_is_empty(const Stack* stack);
int stack_is_full(const Stack* stack);
size_t stack_size(const Stack* stack);

#endif // STACK_H
```

```c
// stack.c
#include "stack.h"
#include <stdlib.h>
#include <string.h>

struct Stack {
    int data[STACK_MAX_SIZE];
    int top;
};

Stack* stack_create(void) {
    Stack* stack = malloc(sizeof(Stack));
    if (stack) {
        stack->top = -1;
    }
    return stack;
}

void stack_destroy(Stack* stack) {
    free(stack);
}

int stack_push(Stack* stack, int value) {
    if (stack->top >= STACK_MAX_SIZE - 1) {
        return 0; // Stack full
    }
    stack->data[++stack->top] = value;
    return 1;
}

int stack_pop(Stack* stack, int* value) {
    if (stack->top < 0) {
        return 0; // Stack empty
    }
    *value = stack->data[stack->top--];
    return 1;
}

// ... other functions
```

## Module Dependencies
```c
// Low-level module
// memory_pool.h
#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

typedef struct MemoryPool MemoryPool;

MemoryPool* memory_pool_create(size_t block_size, size_t num_blocks);
void memory_pool_destroy(MemoryPool* pool);
void* memory_pool_alloc(MemoryPool* pool);
void memory_pool_free(MemoryPool* pool, void* ptr);

#endif // MEMORY_POOL_H

// Mid-level module depends on memory_pool
// network_buffer.h
#ifndef NETWORK_BUFFER_H
#define NETWORK_BUFFER_H

#include "memory_pool.h"

typedef struct NetworkBuffer NetworkBuffer;

NetworkBuffer* network_buffer_create(MemoryPool* pool, size_t size);
void network_buffer_destroy(NetworkBuffer* buffer);
int network_buffer_write(NetworkBuffer* buffer, const void* data, size_t size);
int network_buffer_read(NetworkBuffer* buffer, void* data, size_t size);

#endif // NETWORK_BUFFER_H

// High-level module depends on network_buffer
// tcp_client.h
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "network_buffer.h"

typedef struct TcpClient TcpClient;

TcpClient* tcp_client_create(const char* address, int port);
void tcp_client_destroy(TcpClient* client);
int tcp_client_connect(TcpClient* client);
int tcp_client_send(TcpClient* client, const void* data, size_t size);
int tcp_client_receive(TcpClient* client, void* buffer, size_t size);

#endif // TCP_CLIENT_H
```

## Error Handling in Modules
```c
// error_codes.h
#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum {
    ERROR_SUCCESS = 0,
    ERROR_INVALID_ARGUMENT = -1,
    ERROR_OUT_OF_MEMORY = -2,
    ERROR_IO_ERROR = -3,
    ERROR_TIMEOUT = -4,
    ERROR_NOT_CONNECTED = -5
} ErrorCode;

const char* error_to_string(ErrorCode code);

#endif // ERROR_CODES_H

// file_io.h
#ifndef FILE_IO_H
#define FILE_IO_H

#include "error_codes.h"

typedef struct FileHandle FileHandle;

ErrorCode file_open(const char* filename, FileHandle** handle);
ErrorCode file_close(FileHandle* handle);
ErrorCode file_read(FileHandle* handle, void* buffer, size_t size, size_t* bytes_read);
ErrorCode file_write(FileHandle* handle, const void* buffer, size_t size, size_t* bytes_written);

#endif // FILE_IO_H
```

## Module Initialization and Cleanup
```c
// module_lifecycle.h
#ifndef MODULE_LIFECYCLE_H
#define MODULE_LIFECYCLE_H

#include "error_codes.h"

typedef enum {
    MODULE_STATE_UNINITIALIZED,
    MODULE_STATE_INITIALIZING,
    MODULE_STATE_READY,
    MODULE_STATE_ERROR,
    MODULE_STATE_SHUTTING_DOWN
} ModuleState;

typedef struct {
    const char* name;
    ModuleState state;
    ErrorCode (*init)(void);
    void (*cleanup)(void);
    ErrorCode (*self_test)(void);
} Module;

ErrorCode module_system_init(void);
void module_system_cleanup(void);
ErrorCode module_register(Module* module);
ModuleState module_get_state(const char* name);

#endif // MODULE_LIFECYCLE_H
```

## Testing Modules
```c
// math_module_test.c
#include "math_module.h"
#include <assert.h>
#include <stdio.h>

void test_math_add(void) {
    assert(math_add(2, 3) == 5);
    assert(math_add(-1, 1) == 0);
    assert(math_add(0, 0) == 0);
    printf("test_math_add passed\n");
}

void test_math_multiply(void) {
    assert(math_multiply(2, 3) == 6);
    assert(math_multiply(-2, 3) == -6);
    assert(math_multiply(0, 5) == 0);
    printf("test_math_multiply passed\n");
}

void test_math_power(void) {
    assert(math_power(2.0, 0) == 1.0);
    assert(math_power(2.0, 1) == 2.0);
    assert(math_power(2.0, 3) == 8.0);
    printf("test_math_power passed\n");
}

int main(void) {
    test_math_add();
    test_math_multiply();
    test_math_power();
    printf("All tests passed!\n");
    return 0;
}
```

## Build System Integration
```c
// Makefile for modular project
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.
LDFLAGS =

# Object files
OBJS = main.o math_module.o logger.o

# Executable
TARGET = myprogram

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# Dependencies
main.o: main.c math_module.h logger.h
math_module.o: math_module.c math_module.h
logger.o: logger.c logger.h

.PHONY: clean
```

## Best Practices
- Keep modules focused on single responsibility
- Hide implementation details with opaque types
- Use clear naming conventions
- Document module interfaces thoroughly
- Handle errors consistently across modules
- Minimize module dependencies
- Test modules independently
- Use version numbers for API compatibility
- Provide initialization and cleanup functions

## Common Mistakes
- Global variables in modules
- Tight coupling between modules
- Inconsistent error handling
- Missing module initialization
- Circular dependencies
- Exposing internal implementation
- Inadequate testing
- Poor documentation

## Performance Considerations
```c
// Module with performance considerations
// fast_math.h
#ifndef FAST_MATH_H
#define FAST_MATH_H

// Fast approximations for performance-critical code
float fast_sqrt(float x);
float fast_sin(float x);
float fast_cos(float x);

// High-precision versions for accuracy-critical code
double precise_sqrt(double x);
double precise_sin(double x);
double precise_cos(double x);

#endif // FAST_MATH_H

// Usage in performance-critical code
#include "fast_math.h"

void process_audio_samples(float* samples, size_t count) {
    for (size_t i = 0; i < count; i++) {
        // Use fast approximations for real-time processing
        samples[i] = fast_sin(samples[i]) * fast_cos(samples[i]);
    }
}
```

## Embedded Systems Applications
### Device Driver Module
```c
// uart_driver.h
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include "error_codes.h"

typedef struct UartHandle UartHandle;

typedef struct {
    uint32_t baud_rate;
    uint8_t data_bits;    // 5, 6, 7, 8
    uint8_t stop_bits;    // 1, 2
    char parity;          // 'N', 'E', 'O'
} UartConfig;

ErrorCode uart_init(const UartConfig* config, UartHandle** handle);
ErrorCode uart_deinit(UartHandle* handle);
ErrorCode uart_write(UartHandle* handle, const uint8_t* data, size_t size);
ErrorCode uart_read(UartHandle* handle, uint8_t* buffer, size_t size, uint32_t timeout_ms);
ErrorCode uart_flush(UartHandle* handle);

#endif // UART_DRIVER_H
```

### RTOS Task Module
```c
// task_manager.h
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <stdint.h>
#include "error_codes.h"

typedef void (*TaskFunction)(void* param);

typedef enum {
    TASK_PRIORITY_IDLE,
    TASK_PRIORITY_LOW,
    TASK_PRIORITY_NORMAL,
    TASK_PRIORITY_HIGH,
    TASK_PRIORITY_CRITICAL
} TaskPriority;

typedef struct {
    const char* name;
    TaskFunction function;
    void* parameter;
    uint32_t stack_size;
    TaskPriority priority;
} TaskConfig;

ErrorCode task_create(const TaskConfig* config);
ErrorCode task_delete(const char* task_name);
ErrorCode task_suspend(const char* task_name);
ErrorCode task_resume(const char* task_name);
ErrorCode task_set_priority(const char* task_name, TaskPriority priority);

#endif // TASK_MANAGER_H
```

### Sensor Interface Module
```c
// sensor_interface.h
#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>
#include "error_codes.h"

typedef enum {
    SENSOR_TYPE_TEMPERATURE,
    SENSOR_TYPE_PRESSURE,
    SENSOR_TYPE_HUMIDITY,
    SENSOR_TYPE_ACCELEROMETER
} SensorType;

typedef struct {
    SensorType type;
    uint8_t i2c_address;
    uint32_t sample_rate_hz;
    bool enable_interrupts;
} SensorConfig;

typedef struct SensorHandle SensorHandle;

ErrorCode sensor_init(const SensorConfig* config, SensorHandle** handle);
ErrorCode sensor_deinit(SensorHandle* handle);
ErrorCode sensor_read(SensorHandle* handle, float* value);
ErrorCode sensor_calibrate(SensorHandle* handle);
ErrorCode sensor_get_status(SensorHandle* handle, uint32_t* status);

#endif // SENSOR_INTERFACE_H
```