# 04: Error Handling

## Error Handling
Robust error handling is crucial for creating reliable programs that can gracefully handle unexpected situations and provide meaningful feedback.

## Return Code Error Handling
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Error codes
typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_ARGUMENT = -1,
    ERROR_OUT_OF_MEMORY = -2,
    ERROR_FILE_NOT_FOUND = -3,
    ERROR_PERMISSION_DENIED = -4,
    ERROR_IO_ERROR = -5
} ErrorCode;

// Function that can fail
ErrorCode divide_numbers(double a, double b, double* result) {
    if (b == 0.0) {
        return ERROR_INVALID_ARGUMENT;
    }

    *result = a / b;
    return SUCCESS;
}

// Function that allocates memory
ErrorCode create_string_array(int count, char*** array) {
    if (count <= 0) {
        return ERROR_INVALID_ARGUMENT;
    }

    *array = malloc(count * sizeof(char*));
    if (*array == NULL) {
        return ERROR_OUT_OF_MEMORY;
    }

    // Initialize all pointers to NULL
    for (int i = 0; i < count; i++) {
        (*array)[i] = NULL;
    }

    return SUCCESS;
}

// Usage with error handling
void demonstrate_return_codes() {
    double result;
    ErrorCode error = divide_numbers(10.0, 0.0, &result);

    if (error == SUCCESS) {
        printf("Result: %.2f\n", result);
    } else {
        printf("Error: %d\n", error);
    }

    // Better error handling with messages
    char** string_array;
    error = create_string_array(5, &string_array);

    switch (error) {
        case SUCCESS:
            printf("String array created successfully\n");
            free(string_array);  // Clean up
            break;
        case ERROR_INVALID_ARGUMENT:
            printf("Invalid argument passed to function\n");
            break;
        case ERROR_OUT_OF_MEMORY:
            printf("Failed to allocate memory\n");
            break;
        default:
            printf("Unknown error occurred\n");
            break;
    }
}

int main() {
    demonstrate_return_codes();
    return 0;
}
```

## errno and perror
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Safe memory allocation with error reporting
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// File operation with errno handling
FILE* safe_fopen(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file '%s': %s\n", filename, strerror(errno));
        return NULL;
    }
    return file;
}

// String to integer conversion with error checking
int safe_atoi(const char* str, int* result) {
    if (str == NULL || *str == '\0') {
        errno = EINVAL;  // Invalid argument
        return -1;
    }

    char* endptr;
    errno = 0;  // Reset errno

    long value = strtol(str, &endptr, 10);

    // Check for conversion errors
    if (errno != 0) {
        perror("strtol failed");
        return -1;
    }

    // Check if any characters were converted
    if (endptr == str) {
        fprintf(stderr, "No digits found in string\n");
        errno = EINVAL;
        return -1;
    }

    // Check for out of range
    if (value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "Value out of range for int\n");
        errno = ERANGE;
        return -1;
    }

    *result = (int)value;
    return 0;
}

void demonstrate_errno() {
    // Test memory allocation
    int* array = safe_malloc(10 * sizeof(int));
    free(array);

    // Test file operations
    FILE* file = safe_fopen("nonexistent.txt", "r");
    if (file == NULL) {
        printf("File operation failed as expected\n");
    }

    // Test string conversion
    int value;
    if (safe_atoi("123", &value) == 0) {
        printf("Converted '123' to %d\n", value);
    }

    if (safe_atoi("abc", &value) != 0) {
        printf("Failed to convert 'abc' as expected\n");
    }

    if (safe_atoi("", &value) != 0) {
        printf("Failed to convert empty string as expected\n");
    }
}

int main() {
    demonstrate_errno();
    return 0;
}
```

## goto for Error Cleanup
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Complex function with multiple resources to clean up
ErrorCode process_data_complex(const char* input_file, const char* output_file) {
    ErrorCode error = SUCCESS;
    FILE* in_file = NULL;
    FILE* out_file = NULL;
    char* buffer = NULL;
    char** string_array = NULL;

    // Allocate buffer
    buffer = malloc(1024);
    if (buffer == NULL) {
        error = ERROR_OUT_OF_MEMORY;
        goto cleanup;
    }

    // Open input file
    in_file = fopen(input_file, "r");
    if (in_file == NULL) {
        error = ERROR_FILE_NOT_FOUND;
        goto cleanup;
    }

    // Open output file
    out_file = fopen(output_file, "w");
    if (out_file == NULL) {
        error = ERROR_IO_ERROR;
        goto cleanup;
    }

    // Allocate string array
    string_array = malloc(10 * sizeof(char*));
    if (string_array == NULL) {
        error = ERROR_OUT_OF_MEMORY;
        goto cleanup;
    }

    // Initialize string array
    for (int i = 0; i < 10; i++) {
        string_array[i] = malloc(50);
        if (string_array[i] == NULL) {
            error = ERROR_OUT_OF_MEMORY;
            goto cleanup;
        }
    }

    // Process data (simplified)
    fprintf(out_file, "Processing complete\n");

cleanup:
    // Clean up all resources in reverse order
    if (string_array) {
        for (int i = 0; i < 10; i++) {
            free(string_array[i]);
        }
        free(string_array);
    }

    if (out_file) {
        fclose(out_file);
    }

    if (in_file) {
        fclose(in_file);
    }

    free(buffer);

    return error;
}

// Alternative: Using do-while(0) for single statement macros
#define CHECK_ERROR(condition, error_code, cleanup_label) \
    do { \
        if (condition) { \
            error = error_code; \
            goto cleanup_label; \
        } \
    } while (0)

ErrorCode process_data_macro(const char* input_file, const char* output_file) {
    ErrorCode error = SUCCESS;
    FILE* in_file = NULL;
    FILE* out_file = NULL;
    char* buffer = NULL;

    buffer = malloc(1024);
    CHECK_ERROR(buffer == NULL, ERROR_OUT_OF_MEMORY, cleanup);

    in_file = fopen(input_file, "r");
    CHECK_ERROR(in_file == NULL, ERROR_FILE_NOT_FOUND, cleanup);

    out_file = fopen(output_file, "w");
    CHECK_ERROR(out_file == NULL, ERROR_IO_ERROR, cleanup);

    // Process data
    fprintf(out_file, "Processing complete\n");

cleanup:
    if (out_file) fclose(out_file);
    if (in_file) fclose(in_file);
    free(buffer);

    return error;
}

int main() {
    ErrorCode error = process_data_complex("input.txt", "output.txt");
    if (error != SUCCESS) {
        printf("Error occurred: %d\n", error);
    }

    return 0;
}
```

## Assertions and Defensive Programming
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Debug vs Release builds
#ifdef DEBUG
    #define ASSERT(condition) assert(condition)
    #define ASSERT_MSG(condition, msg) \
        do { \
            if (!(condition)) { \
                fprintf(stderr, "Assertion failed: %s\n", msg); \
                assert(condition); \
            } \
        } while (0)
#else
    #define ASSERT(condition) ((void)0)
    #define ASSERT_MSG(condition, msg) ((void)0)
#endif

// Function with preconditions and postconditions
int divide_integers(int dividend, int divisor) {
    // Precondition
    ASSERT_MSG(divisor != 0, "Division by zero");
    ASSERT_MSG(divisor > INT_MIN, "Divisor too small");

    int result = dividend / divisor;

    // Postcondition
    ASSERT_MSG(result >= INT_MIN && result <= INT_MAX, "Result out of range");

    return result;
}

// Defensive function that handles errors gracefully
int safe_divide(int dividend, int divisor, int* result) {
    if (result == NULL) {
        return ERROR_INVALID_ARGUMENT;
    }

    if (divisor == 0) {
        return ERROR_INVALID_ARGUMENT;
    }

    // Check for overflow (simplified)
    if (dividend == INT_MIN && divisor == -1) {
        return ERROR_INVALID_ARGUMENT;  // Would cause overflow
    }

    *result = dividend / divisor;
    return SUCCESS;
}

// Bounds checking
int get_array_element(int* array, size_t size, size_t index) {
    ASSERT(array != NULL);
    ASSERT(index < size);

    if (array == NULL || index >= size) {
        // In release build, handle gracefully
        return 0;  // Or some default value
    }

    return array[index];
}

void demonstrate_assertions() {
    // Test assertions (only active in debug builds)
    int result = divide_integers(10, 2);
    printf("10 / 2 = %d\n", result);

    // Test defensive programming
    int safe_result;
    ErrorCode error = safe_divide(10, 0, &safe_result);
    if (error == SUCCESS) {
        printf("Safe divide result: %d\n", safe_result);
    } else {
        printf("Safe divide failed with error: %d\n", error);
    }

    // Test bounds checking
    int array[] = {1, 2, 3, 4, 5};
    int element = get_array_element(array, 5, 2);
    printf("Array element: %d\n", element);
}

int main() {
    demonstrate_assertions();
    return 0;
}
```

## Exception-like Error Handling (setjmp/longjmp)
```c
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

// Exception handling using setjmp/longjmp
jmp_buf exception_buffer;
#define TRY if (setjmp(exception_buffer) == 0)
#define CATCH else
#define THROW_EXCEPTION(code) longjmp(exception_buffer, code)

typedef enum {
    EXCEPTION_NONE = 0,
    EXCEPTION_DIVIDE_BY_ZERO = 1,
    EXCEPTION_OUT_OF_MEMORY = 2,
    EXCEPTION_FILE_ERROR = 3
} ExceptionCode;

// Function that can "throw" exceptions
double divide_with_exceptions(double a, double b) {
    if (b == 0.0) {
        THROW_EXCEPTION(EXCEPTION_DIVIDE_BY_ZERO);
    }
    return a / b;
}

void* allocate_with_exceptions(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        THROW_EXCEPTION(EXCEPTION_OUT_OF_MEMORY);
    }
    return ptr;
}

FILE* fopen_with_exceptions(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        THROW_EXCEPTION(EXCEPTION_FILE_ERROR);
    }
    return file;
}

void demonstrate_exceptions() {
    TRY {
        printf("Starting operations that might fail...\n");

        double result = divide_with_exceptions(10.0, 0.0);
        printf("Result: %.2f\n", result);  // This won't execute

    } CATCH {
        ExceptionCode exception = (ExceptionCode)setjmp(exception_buffer);

        switch (exception) {
            case EXCEPTION_DIVIDE_BY_ZERO:
                printf("Caught divide by zero exception\n");
                break;
            case EXCEPTION_OUT_OF_MEMORY:
                printf("Caught out of memory exception\n");
                break;
            case EXCEPTION_FILE_ERROR:
                printf("Caught file error exception\n");
                break;
            default:
                printf("Caught unknown exception\n");
                break;
        }
    }

    printf("Program continues after exception handling\n");
}

// More complex example with cleanup
void complex_operation() {
    char* buffer1 = NULL;
    char* buffer2 = NULL;
    FILE* file = NULL;

    TRY {
        buffer1 = allocate_with_exceptions(100);
        printf("Allocated buffer1\n");

        buffer2 = allocate_with_exceptions(200);
        printf("Allocated buffer2\n");

        file = fopen_with_exceptions("nonexistent.txt", "r");
        printf("Opened file\n");

        // Do some work
        divide_with_exceptions(1.0, 0.0);  // This will throw

    } CATCH {
        // Cleanup happens here
        free(buffer1);
        free(buffer2);
        if (file) fclose(file);

        printf("Exception caught, cleanup performed\n");
    }
}

int main() {
    demonstrate_exceptions();
    complex_operation();
    return 0;
}
```

## Error Handling Best Practices
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comprehensive error handling example
typedef struct {
    ErrorCode code;
    const char* message;
    const char* file;
    int line;
    const char* function;
} ErrorInfo;

#define CREATE_ERROR(code, msg) \
    ((ErrorInfo){code, msg, __FILE__, __LINE__, __func__})

// Error context for tracking error chains
typedef struct ErrorContext {
    ErrorInfo errors[10];
    int error_count;
    int max_errors;
} ErrorContext;

void error_context_init(ErrorContext* ctx) {
    ctx->error_count = 0;
    ctx->max_errors = 10;
}

void error_context_add(ErrorContext* ctx, ErrorInfo error) {
    if (ctx->error_count < ctx->max_errors) {
        ctx->errors[ctx->error_count++] = error;
    }
}

void error_context_print(const ErrorContext* ctx) {
    printf("Error trace:\n");
    for (int i = 0; i < ctx->error_count; i++) {
        const ErrorInfo* err = &ctx->errors[i];
        printf("  %s:%d in %s(): %s (%d)\n",
               err->file, err->line, err->function, err->message, err->code);
    }
}

// Function with comprehensive error handling
ErrorCode robust_file_operation(const char* filename, ErrorContext* ctx) {
    ErrorCode result = SUCCESS;
    FILE* file = NULL;
    char* buffer = NULL;

    // Attempt to open file
    file = fopen(filename, "r");
    if (file == NULL) {
        error_context_add(ctx, CREATE_ERROR(ERROR_FILE_NOT_FOUND,
                          "Failed to open input file"));
        result = ERROR_FILE_NOT_FOUND;
        goto cleanup;
    }

    // Allocate buffer
    buffer = malloc(1024);
    if (buffer == NULL) {
        error_context_add(ctx, CREATE_ERROR(ERROR_OUT_OF_MEMORY,
                          "Failed to allocate read buffer"));
        result = ERROR_OUT_OF_MEMORY;
        goto cleanup;
    }

    // Read file
    size_t bytes_read = fread(buffer, 1, 1024, file);
    if (bytes_read == 0 && !feof(file)) {
        error_context_add(ctx, CREATE_ERROR(ERROR_IO_ERROR,
                          "Failed to read from file"));
        result = ERROR_IO_ERROR;
        goto cleanup;
    }

    printf("Successfully read %zu bytes from %s\n", bytes_read, filename);

cleanup:
    free(buffer);
    if (file) fclose(file);

    return result;
}

// Recovery strategies
ErrorCode attempt_recovery(ErrorCode error, const char* context) {
    switch (error) {
        case ERROR_FILE_NOT_FOUND:
            printf("Attempting to create missing file: %s\n", context);
            // Try to create the file
            FILE* file = fopen(context, "w");
            if (file) {
                fprintf(file, "Created by error recovery\n");
                fclose(file);
                return SUCCESS;
            }
            break;

        case ERROR_OUT_OF_MEMORY:
            printf("Attempting garbage collection\n");
            // In a real system, trigger garbage collection
            break;

        default:
            printf("No recovery strategy for error %d\n", error);
            break;
    }

    return error;  // Recovery failed
}

int main() {
    ErrorContext ctx;
    error_context_init(&ctx);

    ErrorCode error = robust_file_operation("nonexistent.txt", &ctx);

    if (error != SUCCESS) {
        error_context_print(&ctx);

        // Attempt recovery
        error = attempt_recovery(error, "nonexistent.txt");
        if (error == SUCCESS) {
            printf("Recovery successful!\n");
        } else {
            printf("Recovery failed, exiting\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
```

## Best Practices Summary
- Use appropriate error handling strategy for each situation
- Document error conditions and return values
- Provide meaningful error messages
- Clean up resources properly on errors
- Consider recovery strategies when appropriate
- Log errors for debugging
- Test error paths thoroughly
- Use assertions for debugging
- Avoid silent failures
- Handle errors at the appropriate level

## Common Mistakes
- Ignoring return values
- Not checking for NULL pointers
- Inadequate resource cleanup
- Masking errors with default values
- Using exceptions in C (setjmp/longjmp has limitations)
- Not documenting error conditions
- Inconsistent error codes
- Failing to propagate errors up the call stack
- Not testing error conditions

## Performance Considerations
- Error handling has performance cost
- Use error codes for performance-critical code
- Exceptions (setjmp/longjmp) are expensive
- Consider error frequency vs handling cost
- Profile error paths
- Use different strategies for debug vs release
- Consider async error handling for real-time systems

## Embedded Systems Considerations
- Limited stack space for error context
- Real-time constraints on error handling
- Power failure during error recovery
- Limited debugging capabilities
- Memory constraints for error messages
- Hardware error conditions
- Watchdog timer interactions
- Fail-safe modes and error recovery