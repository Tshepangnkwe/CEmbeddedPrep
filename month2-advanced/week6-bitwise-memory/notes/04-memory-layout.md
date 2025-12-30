# 04: Memory Layout

## Memory Organization
Understanding how data is organized in memory is crucial for efficient programming and debugging.

## Memory Segments
### Code Segment (Text)
Contains executable instructions:
```c
// Functions are stored in code segment
void function() {
    printf("This code is in the text segment\n");
}

int main() {
    function();  // Code executed from text segment
    return 0;
}
```

### Data Segment
Contains global and static variables:
```c
int global_var = 10;              // Initialized data
static int static_var = 20;       // Initialized data
int uninitialized_global;         // BSS segment (zero-initialized)

void func() {
    static int static_local = 30; // Initialized data
    // Local variables go on stack
}
```

### Stack Segment
Contains local variables and function call information:
```c
void func1() {
    int local1 = 10;  // Stack
    func2();
}

void func2() {
    int local2 = 20;  // Stack (different frame)
}

int main() {
    int main_local = 5;  // Stack
    func1();
    return 0;
}
```

### Heap Segment
Dynamically allocated memory:
```c
int main() {
    int* heap_ptr = (int*)malloc(sizeof(int));  // Heap
    *heap_ptr = 42;

    free(heap_ptr);  // Return to heap
    return 0;
}
```

## Variable Storage Classes
### Automatic Variables (Stack)
```c
void func() {
    int auto_var = 10;        // Stack, lifetime = function duration
    auto int another = 20;    // Explicit auto (same as above)

    // auto_var goes out of scope when function returns
}
```

### Static Variables
```c
void func() {
    static int count = 0;     // Data segment, lifetime = program duration
    count++;
    printf("Called %d times\n", count);
}

int main() {
    func();  // "Called 1 times"
    func();  // "Called 2 times"
    return 0;
}
```

### Register Variables
```c
void func() {
    register int fast_var = 10;  // Hint to store in CPU register
    // May be ignored by compiler
    // Cannot take address: &fast_var is invalid
}
```

## Struct Memory Layout
### Padding and Alignment
```c
struct Example {
    char c;      // 1 byte
    int i;       // 4 bytes (aligned to 4-byte boundary)
    char c2;     // 1 byte, but padded to 4-byte boundary
}; // Total: 12 bytes (not 6!)

printf("Size: %zu bytes\n", sizeof(struct Example));

struct Packed {
    char c;
    char c2;
    int i;
}; // Total: 8 bytes (better packing)
```

### Controlling Alignment
```c
// Force alignment
struct Aligned {
    char c;
    int i __attribute__((aligned(8)));  // Align to 8-byte boundary
};

// Pack struct (no padding)
struct Packed {
    char c;
    int i;
} __attribute__((packed));
```

## Array Memory Layout
### Contiguous Memory
```c
int arr[5] = {1, 2, 3, 4, 5};
// Memory: |1|2|3|4|5| (contiguous)

printf("Address of arr[0]: %p\n", (void*)&arr[0]);
printf("Address of arr[1]: %p\n", (void*)&arr[1]);
printf("Difference: %ld bytes\n", (char*)&arr[1] - (char*)&arr[0]);
```

### Multidimensional Arrays
```c
int matrix[2][3] = {
    {1, 2, 3},  // Row 0
    {4, 5, 6}   // Row 1
};
// Memory: |1|2|3|4|5|6| (row-major order)

printf("matrix[0][0]: %p\n", (void*)&matrix[0][0]);
printf("matrix[0][1]: %p\n", (void*)&matrix[0][1]);
printf("matrix[1][0]: %p\n", (void*)&matrix[1][0]);
```

## Pointer Memory Layout
### Pointer Size
```c
int* int_ptr;
char* char_ptr;
void* void_ptr;

printf("int* size: %zu bytes\n", sizeof(int_ptr));
printf("char* size: %zu bytes\n", sizeof(char_ptr));
printf("void* size: %zu bytes\n", sizeof(void_ptr));
// Usually 4 or 8 bytes on modern systems
```

### Pointer Arithmetic
```c
int arr[5] = {10, 20, 30, 40, 50};
int* ptr = arr;

printf("ptr: %p, *ptr: %d\n", (void*)ptr, *ptr);
ptr++;  // Adds sizeof(int) to pointer
printf("ptr after ++: %p, *ptr: %d\n", (void*)ptr, *ptr);
```

## Memory Alignment
### Why Alignment Matters
```c
struct Misaligned {
    char c;    // Offset 0
    int i;     // Offset 1 (misaligned!)
};

struct Aligned {
    char c;    // Offset 0
    char pad;  // Offset 1 (padding)
    int i;     // Offset 2 (still misaligned on some systems)
};

struct Better {
    int i;     // Offset 0 (aligned)
    char c;    // Offset 4
}; // Total: 8 bytes with padding
```

### Alignment Requirements
- char: 1-byte aligned
- short: 2-byte aligned
- int: 4-byte aligned
- double: 8-byte aligned
- pointers: 4 or 8-byte aligned

## Endianness
### Little-Endian vs Big-Endian
```c
#include <stdio.h>

void show_bytes(void* ptr, size_t size) {
    unsigned char* bytes = (unsigned char*)ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}

int main() {
    int x = 0x12345678;
    printf("Value: 0x%X\n", x);
    printf("Bytes: ");
    show_bytes(&x, sizeof(x));

    // Little-endian: 78 56 34 12
    // Big-endian:    12 34 56 78
    return 0;
}
```

## Memory Layout Visualization
```c
// High addresses
// +----------------+
// | Command line   |
// | arguments      |
// | Environment    |
// +----------------+ <- Stack grows downward
// | Local variables|
// | Function calls |
// +----------------+
// |      Heap      | <- Heap grows upward
// |  (malloc)      |
// +----------------+
// | Uninitialized  |
// | data (BSS)     |
// +----------------+
// | Initialized    |
// | global data    |
// +----------------+
// |   Code/Text    |
// |  (program)     |
// +----------------+
// Low addresses
```

## Best Practices
- Be aware of struct padding and alignment
- Use sizeof() instead of hardcoded sizes
- Consider endianness in network/serialization code
- Pack structs only when necessary (performance vs space)
- Document memory layout assumptions
- Use alignment attributes when interfacing with hardware

## Common Mistakes
- Assuming struct size equals sum of members
- Ignoring padding in memory calculations
- Misunderstanding pointer arithmetic scaling
- Assuming little-endian byte order
- Not accounting for alignment requirements
- Using unaligned pointers (undefined behavior)