# 05: Stack vs Heap

## Stack Memory
Fast, automatic memory managed by the compiler. Used for local variables and function calls.

## Stack Characteristics
### Automatic Allocation/Deallocation
```c
void func() {
    int x = 10;        // Allocated on stack
    int arr[100];      // Allocated on stack
    // Memory automatically freed when function returns
}

int main() {
    func();  // Stack frames created and destroyed
    return 0;
}
```

### Limited Size
```c
void deep_recursion(int n) {
    if (n > 0) {
        int large_array[1000];  // Each call uses stack space
        deep_recursion(n - 1);
    }
}

int main() {
    deep_recursion(100);  // May cause stack overflow
    return 0;
}
```

### Fast Access
```c
void stack_example() {
    int a = 1, b = 2, c = 3;  // Fast stack access
    int sum = a + b + c;
    printf("Sum: %d\n", sum);
}
```

## Heap Memory
Dynamically allocated memory that persists until explicitly freed. Managed manually by programmer.

## Heap Characteristics
### Manual Management
```c
#include <stdlib.h>

void heap_example() {
    // Allocate memory
    int* ptr = (int*)malloc(sizeof(int) * 100);
    if (ptr == NULL) {
        printf("Allocation failed\n");
        return;
    }

    // Use memory
    for (int i = 0; i < 100; i++) {
        ptr[i] = i * i;
    }

    // Free memory
    free(ptr);
    ptr = NULL;  // Good practice
}
```

### Flexible Size
```c
int* grow_array(int** arr, int* size, int new_size) {
    int* new_arr = (int*)realloc(*arr, new_size * sizeof(int));
    if (new_arr == NULL) {
        return NULL;  // Allocation failed
    }

    // Initialize new elements
    for (int i = *size; i < new_size; i++) {
        new_arr[i] = 0;
    }

    *arr = new_arr;
    *size = new_size;
    return new_arr;
}
```

### Persistent Across Function Calls
```c
int* create_counter() {
    int* count = (int*)malloc(sizeof(int));
    *count = 0;
    return count;  // Pointer to heap memory
}

void increment_counter(int* counter) {
    (*counter)++;
}

int main() {
    int* counter = create_counter();
    increment_counter(counter);
    increment_counter(counter);
    printf("Count: %d\n", *counter);  // 2

    free(counter);
    return 0;
}
```

## Comparison: Stack vs Heap

| Aspect | Stack | Heap |
|--------|-------|------|
| Speed | Fast | Slower |
| Size | Limited | Large (system dependent) |
| Lifetime | Automatic | Manual |
| Fragmentation | No | Yes |
| Access | Direct | Via pointers |
| Thread safety | Thread-local | Needs synchronization |

## When to Use Stack
### Small, Fixed-Size Data
```c
void process_data() {
    char buffer[1024];        // OK for stack
    int temp_results[100];    // OK for stack
    struct Data data;         // OK if small
    // Process data...
}
```

### Temporary Variables
```c
int calculate_sum(int a, int b) {
    int temp = a + b;         // Stack variable
    return temp * 2;
}
```

### Function Parameters and Locals
```c
void print_coordinates(int x, int y) {
    char message[50];         // Stack buffer
    sprintf(message, "(%d, %d)", x, y);
    printf("%s\n", message);
}
```

## When to Use Heap
### Large Data Structures
```c
typedef struct {
    int data[10000];
    char name[100];
} LargeStruct;

LargeStruct* create_large_struct() {
    return (LargeStruct*)malloc(sizeof(LargeStruct));
}
```

### Dynamic Arrays
```c
int* create_dynamic_array(int size) {
    return (int*)calloc(size, sizeof(int));  // Zero-initialized
}

int main() {
    int* arr = create_dynamic_array(1000);
    // Use array...
    free(arr);
}
```

### Data That Outlives Function Scope
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_list(int size) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < size; i++) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = i;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    return head;  // List persists after function returns
}
```

## Memory Management Best Practices
### Always Check Allocation
```c
int* ptr = (int*)malloc(sizeof(int) * 100);
if (ptr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
}
```

### Free All Allocated Memory
```c
void cleanup_resources() {
    free(ptr1);
    free(ptr2);
    free(ptr3);
    // Set to NULL if still in scope
    ptr1 = ptr2 = ptr3 = NULL;
}
```

### Use Appropriate Functions
```c
// malloc: uninitialized memory
int* arr1 = (int*)malloc(10 * sizeof(int));

// calloc: zero-initialized memory
int* arr2 = (int*)calloc(10, sizeof(int));

// realloc: resize existing allocation
arr1 = (int*)realloc(arr1, 20 * sizeof(int));
```

### Avoid Memory Leaks
```c
void leaky_function() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    // Forgot free(ptr) - memory leak!
}

void good_function() {
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        free(ptr);
    }
}
```

## Stack Overflow Prevention
### Check Stack Usage
```c
// Recursive functions can cause stack overflow
int factorial(int n) {
    if (n <= 1) return 1;

    // Large local variables in recursion multiply stack usage
    char buffer[1000];  // 1000 bytes per call

    return n * factorial(n - 1);
}

// Iterative version uses constant stack space
int factorial_iterative(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
```

## Embedded Considerations
### Limited Stack Size
```c
// In embedded systems, stack is often small (KB range)
void embedded_function() {
    char small_buffer[100];  // OK
    // char large_buffer[10000];  // May cause stack overflow
}
```

### Static Allocation for Critical Code
```c
// Use static for data that must persist
void interrupt_handler() {
    static char buffer[256];  // Not on stack
    // Handle interrupt...
}
```

## Best Practices
- Use stack for small, temporary data
- Use heap for large or persistent data
- Always check malloc/calloc return values
- Free memory as soon as no longer needed
- Set freed pointers to NULL
- Be aware of stack size limitations
- Use tools like Valgrind to detect memory issues

## Common Mistakes
- Memory leaks (not freeing heap memory)
- Dangling pointers (using freed memory)
- Stack overflow (too much stack usage)
- Double free (freeing already freed memory)
- Using uninitialized pointers
- Assuming allocation always succeeds