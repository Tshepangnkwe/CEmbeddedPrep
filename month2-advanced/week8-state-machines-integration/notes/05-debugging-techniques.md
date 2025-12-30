# 05: Debugging Techniques

## Debugging Techniques
Effective debugging is essential for finding and fixing bugs in C programs. This covers various techniques and tools for systematic debugging.

## Printf Debugging
```c
#include <stdio.h>
#include <stdlib.h>

// Basic printf debugging
void basic_debugging() {
    printf("DEBUG: Entering basic_debugging()\n");

    int x = 10;
    int y = 20;
    printf("DEBUG: x = %d, y = %d\n", x, y);

    int sum = x + y;
    printf("DEBUG: sum = %d\n", sum);

    if (sum > 15) {
        printf("DEBUG: sum is greater than 15\n");
    } else {
        printf("DEBUG: sum is not greater than 15\n");
    }

    printf("DEBUG: Exiting basic_debugging()\n");
}

// Conditional debugging with macros
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) printf("DEBUG: " fmt "\n", ##__VA_ARGS__)
    #define DEBUG_VAR(var) printf("DEBUG: " #var " = %d\n", var)
#else
    #define DEBUG_PRINT(fmt, ...)
    #define DEBUG_VAR(var)
#endif

void conditional_debugging() {
    DEBUG_PRINT("Starting conditional debugging");

    int value = 42;
    DEBUG_VAR(value);

    for (int i = 0; i < 3; i++) {
        DEBUG_PRINT("Loop iteration %d", i);
        value *= 2;
        DEBUG_VAR(value);
    }

    DEBUG_PRINT("Conditional debugging complete");
}

// Hex dump for debugging binary data
void hex_dump(const void* data, size_t size) {
    const unsigned char* bytes = (const unsigned char*)data;

    printf("DEBUG: Hex dump of %zu bytes:\n", size);
    for (size_t i = 0; i < size; i++) {
        if (i % 16 == 0) printf("DEBUG: %04zx: ", i);
        printf("%02x ", bytes[i]);
        if (i % 16 == 15 || i == size - 1) {
            // Print ASCII representation
            printf(" |");
            for (size_t j = i - (i % 16); j <= i; j++) {
                char c = bytes[j];
                printf("%c", (c >= 32 && c <= 126) ? c : '.');
            }
            printf("|\n");
        }
    }
}

void demonstrate_hex_dump() {
    char text[] = "Hello, World! This is a test.";
    int numbers[] = {1, 2, 3, 4, 5};

    hex_dump(text, sizeof(text));
    hex_dump(numbers, sizeof(numbers));
}

int main() {
    basic_debugging();
    printf("\n");
    conditional_debugging();
    printf("\n");
    demonstrate_hex_dump();

    return 0;
}
```

## Assertions
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

// Basic assertions
void test_assertions() {
    int x = 10;
    int y = 5;

    assert(x > 0);
    assert(y >= 0);
    assert(x > y);

    printf("All basic assertions passed\n");
}

// Custom assertion macro with messages
#define ASSERT_MSG(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: %s\n", message); \
            fprintf(stderr, "File: %s, Line: %d\n", __FILE__, __LINE__); \
            abort(); \
        } \
    } while (0)

void test_custom_assertions() {
    int array[10];
    int index = 5;

    ASSERT_MSG(index >= 0 && index < 10, "Array index out of bounds");
    ASSERT_MSG(array != NULL, "Array is NULL");

    array[index] = 42;
    printf("Custom assertions passed\n");
}

// Function preconditions and postconditions
int divide_assert(int dividend, int divisor) {
    // Preconditions
    assert(divisor != 0 && "Division by zero");
    assert(divisor >= INT_MIN && divisor <= INT_MAX && "Divisor out of range");

    int result = dividend / divisor;

    // Postconditions
    assert(result >= INT_MIN && result <= INT_MAX && "Result out of range");

    return result;
}

// Design by contract
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector* vec, size_t capacity) {
    // Precondition
    assert(vec != NULL);
    assert(capacity > 0);

    vec->data = malloc(capacity * sizeof(int));
    assert(vec->data != NULL);  // Allocation must succeed

    vec->size = 0;
    vec->capacity = capacity;

    // Postcondition
    assert(vec->data != NULL);
    assert(vec->size == 0);
    assert(vec->capacity == capacity);
}

void vector_push_back(Vector* vec, int value) {
    // Preconditions
    assert(vec != NULL);
    assert(vec->data != NULL);
    assert(vec->size <= vec->capacity);

    if (vec->size >= vec->capacity) {
        // Would need to resize in real implementation
        assert(0 && "Vector is full");
    }

    vec->data[vec->size++] = value;

    // Postconditions
    assert(vec->size > 0);
    assert(vec->size <= vec->capacity);
}

void demonstrate_assertions() {
    test_assertions();
    test_custom_assertions();

    int result = divide_assert(10, 2);
    printf("10 / 2 = %d\n", result);

    Vector vec;
    vector_init(&vec, 10);
    vector_push_back(&vec, 42);
    printf("Vector operations completed\n");

    free(vec.data);
}

int main() {
    demonstrate_assertions();
    return 0;
}
```

## GDB Debugging
```c
// Compile with debugging symbols: gcc -g -o program program.c
// Run with GDB: gdb program

#include <stdio.h>
#include <stdlib.h>

// Program with intentional bugs for GDB demonstration
void buggy_function() {
    int* ptr = NULL;
    *ptr = 42;  // Segmentation fault
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);  // Watch this recursive call
}

void memory_leak() {
    int* leak = malloc(sizeof(int) * 100);
    // Forgot to free(leak)
    leak[0] = 123;
    printf("Leaked memory contains: %d\n", leak[0]);
}

void infinite_loop() {
    int counter = 0;
    while (1) {  // Intentional infinite loop
        counter++;
        if (counter % 1000000 == 0) {
            printf("Counter: %d\n", counter);
        }
    }
}

int main(int argc, char* argv[]) {
    printf("Program started\n");

    if (argc > 1) {
        int choice = atoi(argv[1]);

        switch (choice) {
            case 1:
                printf("Testing segmentation fault\n");
                buggy_function();
                break;
            case 2:
                printf("Calculating factorial\n");
                printf("Factorial of 5: %d\n", factorial(5));
                break;
            case 3:
                printf("Testing memory leak\n");
                memory_leak();
                break;
            case 4:
                printf("Testing infinite loop (Ctrl+C to stop)\n");
                infinite_loop();
                break;
            default:
                printf("Usage: %s [1-4]\n", argv[0]);
                printf("1: segmentation fault\n");
                printf("2: factorial\n");
                printf("3: memory leak\n");
                printf("4: infinite loop\n");
                break;
        }
    } else {
        printf("No arguments provided, running basic test\n");
        printf("Factorial of 3: %d\n", factorial(3));
    }

    printf("Program finished\n");
    return 0;
}

/*
GDB Commands:
- break main                    # Set breakpoint at main
- break buggy_function          # Set breakpoint at function
- break 15                      # Set breakpoint at line 15
- run                           # Start program
- next                          # Step to next line
- step                          # Step into function
- continue                      # Continue execution
- print x                       # Print variable x
- print *ptr                    # Print what ptr points to
- backtrace                     # Show call stack
- frame 1                       # Switch to frame 1
- watch counter                 # Watch variable counter
- info locals                   # Show local variables
- info breakpoints              # Show breakpoints
- delete 1                      # Delete breakpoint 1
- quit                          # Exit GDB
*/
```

## Valgrind Memory Debugging
```c
// Compile: gcc -g -o program program.c
// Run with Valgrind: valgrind --leak-check=full ./program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Memory leak example
void memory_leak_example() {
    char* str = malloc(100);
    strcpy(str, "This memory will be leaked");
    printf("String: %s\n", str);
    // Forgot to free(str)
}

// Double free example
void double_free_example() {
    int* ptr = malloc(sizeof(int));
    *ptr = 42;
    printf("Value: %d\n", *ptr);

    free(ptr);
    // free(ptr);  // Double free - ERROR
}

// Invalid read/write
void invalid_access_example() {
    int* array = malloc(5 * sizeof(int));

    // Valid writes
    for (int i = 0; i < 5; i++) {
        array[i] = i * 10;
    }

    // Invalid read - out of bounds
    printf("Invalid read: %d\n", array[10]);

    // Invalid write - out of bounds
    array[10] = 999;

    free(array);
}

// Use after free
void use_after_free_example() {
    int* ptr = malloc(sizeof(int));
    *ptr = 123;
    printf("Before free: %d\n", *ptr);

    free(ptr);

    // Use after free - ERROR
    printf("After free: %d\n", *ptr);
    *ptr = 456;
}

// Uninitialized memory
void uninitialized_memory_example() {
    int* ptr = malloc(sizeof(int));
    // Didn't initialize *ptr

    printf("Uninitialized value: %d\n", *ptr);  // May be garbage

    // Conditional jump on uninitialized value
    if (*ptr > 0) {
        printf("Value is positive\n");
    }

    free(ptr);
}

// Memory leak with linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_leaky_list(int size) {
    Node* head = NULL;
    Node* current = NULL;

    for (int i = 0; i < size; i++) {
        Node* new_node = malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;
    }

    // Forgot to free the list
    return head;
}

int main() {
    printf("Running memory debugging examples...\n");

    memory_leak_example();
    // double_free_example();      // Uncomment to test
    // invalid_access_example();   // Uncomment to test
    // use_after_free_example();   // Uncomment to test
    uninitialized_memory_example();

    Node* list = create_leaky_list(10);
    printf("Created list with %d nodes (leaked)\n", 10);

    // In a real program, you'd free the list here
    // free_list(list);

    printf("Program finished\n");
    return 0;
}

/*
Valgrind output interpretation:
- "Invalid read/write" - Accessing memory out of bounds
- "Use of uninitialised value" - Using uninitialized memory
- "Conditional jump or move depends on uninitialised value" - Branching on uninitialized data
- "Invalid free" - Double free or freeing invalid pointer
- "definitely lost" - Memory allocated but never freed
- "possibly lost" - Memory that may have been leaked
- "still reachable" - Memory that could be freed but program ended
*/
```

## Static Analysis Tools
```c
// Code with common issues that static analysis can catch

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Buffer overflow vulnerability
void buffer_overflow_example() {
    char buffer[10];
    strcpy(buffer, "This string is way too long for the buffer");
    printf("Buffer: %s\n", buffer);
}

// Null pointer dereference
void null_pointer_example() {
    char* str = NULL;
    if (rand() % 2 == 0) {  // Sometimes NULL
        str = "Hello";
    }
    printf("String length: %zu\n", strlen(str));  // May crash
}

// Uninitialized variable
void uninitialized_variable_example() {
    int x;
    int y;

    if (x > 0) {  // x is uninitialized
        y = x * 2;
    } else {
        y = 0;
    }

    printf("y = %d\n", y);
}

// Memory leak
void memory_leak_example() {
    char* ptr = malloc(100);
    if (ptr) {
        strcpy(ptr, "This will be leaked");
        printf("Allocated: %s\n", ptr);
        // No free(ptr)
    }
}

// Division by zero
void division_by_zero_example() {
    int divisor = 0;
    int result = 100 / divisor;  // Division by zero
    printf("Result: %d\n", result);
}

// Array bounds violation
void array_bounds_example() {
    int array[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i <= 5; i++) {  // Off-by-one error
        printf("array[%d] = %d\n", i, array[i]);
    }
}

// Type mismatch
void type_mismatch_example() {
    int x = 10;
    double* ptr = (double*)&x;  // Wrong cast
    printf("Wrong cast result: %f\n", *ptr);
}

// Unused variable
void unused_variable_example() {
    int unused_variable = 42;
    int used_variable = 24;

    printf("Used: %d\n", used_variable);
    // unused_variable is never used
}

// Dead code
void dead_code_example() {
    int x = 10;

    if (x > 5) {
        printf("x is greater than 5\n");
    } else {
        printf("This will never execute\n");  // Dead code
    }
}

// Missing return value
int missing_return_example(int x) {
    if (x > 0) {
        return x * 2;
    }
    // Missing return statement for x <= 0
}

int main() {
    printf("Running static analysis examples...\n");

    // These examples contain bugs that tools like:
    // - GCC with -Wall -Wextra -Werror
    // - Clang Static Analyzer
    // - Cppcheck
    // - Coverity
    // - SonarQube
    // should detect

    buffer_overflow_example();
    null_pointer_example();
    uninitialized_variable_example();
    memory_leak_example();
    // division_by_zero_example();  // May cause runtime crash
    array_bounds_example();
    type_mismatch_example();
    unused_variable_example();
    dead_code_example();

    int result = missing_return_example(-5);
    printf("Missing return result: %d\n", result);

    printf("Examples completed\n");
    return 0;
}
```

## Debugging Best Practices
```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Systematic debugging approach
void systematic_debugging() {
    printf("=== Systematic Debugging ===\n");

    // 1. Reproduce the bug consistently
    printf("1. Reproducing bug...\n");
    int test_value = 0;
    // Simulate bug: division by zero if test_value is 0
    if (test_value != 0) {
        printf("Result: %d\n", 100 / test_value);
    } else {
        printf("Bug reproduced: division by zero avoided\n");
    }

    // 2. Isolate the bug
    printf("2. Isolating bug...\n");
    // Add checkpoints
    printf("   Checkpoint A: Before problematic code\n");

    // 3. Add debugging output
    printf("3. Adding debug output...\n");
    printf("   test_value = %d\n", test_value);

    // 4. Use assertions
    printf("4. Using assertions...\n");
    assert(test_value >= 0 && "test_value should be non-negative");

    // 5. Check boundary conditions
    printf("5. Checking boundaries...\n");
    int array[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        assert(i >= 0 && i < 5 && "Array index out of bounds");
        printf("   array[%d] = %d\n", i, array[i]);
    }

    printf("Systematic debugging completed\n");
}

// Binary search debugging
int binary_search(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Debug output
        printf("DEBUG: left=%d, right=%d, mid=%d, arr[mid]=%d, target=%d\n",
               left, right, mid, arr[mid], target);

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;  // Not found
}

void test_binary_search() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Searching for 7 in array:\n");
    int result = binary_search(arr, size, 7);
    printf("Result: found at index %d\n", result);

    printf("\nSearching for 4 in array:\n");
    result = binary_search(arr, size, 4);
    printf("Result: %s\n", result == -1 ? "not found" : "found");
}

// Rubber duck debugging - explain code to inanimate object
void rubber_duck_debugging() {
    printf("=== Rubber Duck Debugging ===\n");
    printf("Explaining code as if to a rubber duck:\n");
    printf("'Hello rubber duck. I'm trying to find why my program crashes.\n");
    printf(" I have this function that allocates memory, but sometimes it crashes.\n");
    printf(" Let me walk through what happens:\n");
    printf(" 1. I call malloc() to allocate memory\n");
    printf(" 2. I check if malloc returned NULL\n");
    printf(" 3. If not NULL, I use the memory\n");
    printf(" 4. I free the memory at the end\n");
    printf(" Wait, what if malloc fails and I don't check properly?\n");
    printf(" That could cause a crash! Let me check my error handling...'\n");
    printf("Ah! Found the bug through explanation.\n");
}

int main() {
    systematic_debugging();
    printf("\n");

    test_binary_search();
    printf("\n");

    rubber_duck_debugging();

    return 0;
}
```

## Best Practices Summary
- Reproduce bugs consistently before fixing
- Use systematic approach: isolate, add debug output, use assertions
- Learn your debugger (GDB) thoroughly
- Use memory debugging tools (Valgrind)
- Enable compiler warnings (-Wall -Wextra)
- Use static analysis tools
- Keep debug code separate from production code
- Document bug fixes and lessons learned
- Test fixes thoroughly
- Use version control to track changes

## Common Debugging Mistakes
- Not reproducing the bug first
- Making random changes without understanding
- Adding too much debug output at once
- Not checking error return values
- Assuming code works as intended
- Debugging with optimized builds
- Not testing edge cases
- Fixing symptoms instead of root cause
- Not documenting the fix

## Performance Debugging
- Use profiling tools (gprof, perf)
- Identify bottlenecks with timing
- Check for memory leaks under load
- Monitor resource usage
- Use debug vs release builds appropriately
- Consider algorithmic complexity
- Profile I/O operations
- Check for cache misses

## Embedded Debugging Challenges
- Limited debugging tools on target
- Real-time constraints
- Hardware/software interaction bugs
- Limited visibility into hardware state
- JTAG/SWD debugging
- Remote debugging
- Watchdog timer interactions
- Power and thermal debugging