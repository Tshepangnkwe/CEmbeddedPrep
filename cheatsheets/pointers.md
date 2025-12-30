# Pointers Cheatsheet

## Basic Pointer Concepts

### Declaration and Initialization
```c
int x = 42;
int *ptr;        // Declaration
ptr = &x;        // Initialization with address of x
int *ptr2 = &x;  // Declaration and initialization
```

### Dereferencing
```c
int value = *ptr;  // Get value at address
*ptr = 100;        // Set value at address
```

## Pointer Arithmetic

### Basic Operations
```c
int arr[] = {10, 20, 30, 40, 50};
int *ptr = arr;  // Points to arr[0]

ptr++;           // Now points to arr[1]
ptr += 2;        // Now points to arr[3]
ptr--;           // Now points to arr[2]

int value = *ptr;  // 30
```

### Pointer Difference
```c
int *start = arr;
int *end = arr + 5;
int length = end - start;  // 5
```

## Pointer Types

### Void Pointers
```c
void *generic_ptr;
int x = 42;
generic_ptr = &x;

// Must cast before dereferencing
int *int_ptr = (int *)generic_ptr;
printf("%d\n", *int_ptr);
```

### Function Pointers
```c
int (*func_ptr)(int, int);
int add(int a, int b) { return a + b; }

func_ptr = add;
int result = func_ptr(3, 4);  // 7
```

### Double Pointers
```c
int x = 42;
int *ptr = &x;
int **double_ptr = &ptr;

printf("%d\n", **double_ptr);  // 42
```

## Arrays and Pointers

### Array Name as Pointer
```c
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;  // Equivalent to &arr[0]

// Both are valid
arr[2] = 10;
*(ptr + 2) = 10;
```

### Dynamic Arrays
```c
int *dynamic_arr = (int *)malloc(5 * sizeof(int));
if (dynamic_arr == NULL) {
    // Handle allocation failure
}

// Use like regular array
for (int i = 0; i < 5; i++) {
    dynamic_arr[i] = i * 2;
}

free(dynamic_arr);  // Don't forget to free!
```

## Strings and Pointers

### String Literals
```c
char *str = "Hello";  // Points to read-only memory
// str[0] = 'h';  // Undefined behavior!

char str_copy[] = "Hello";  // Modifiable copy
str_copy[0] = 'h';  // OK
```

### Dynamic Strings
```c
char *str = (char *)malloc(100 * sizeof(char));
strcpy(str, "Hello World");
printf("%s\n", str);
free(str);
```

## Structures and Pointers

### Accessing Members
```c
typedef struct {
    int x, y;
} point_t;

point_t p = {10, 20};
point_t *ptr = &p;

// Dot operator has higher precedence than *
(*ptr).x = 30;  // Works but ugly
ptr->x = 30;    // Clean syntax
```

### Dynamic Structures
```c
point_t *p = (point_t *)malloc(sizeof(point_t));
p->x = 10;
p->y = 20;
free(p);
```

## Memory Management

### Stack vs Heap
```c
// Stack allocation (automatic)
int stack_var = 42;
int *stack_ptr = &stack_var;

// Heap allocation (manual)
int *heap_ptr = (int *)malloc(sizeof(int));
*heap_ptr = 42;

// Don't forget to free heap memory
free(heap_ptr);
```

### Common Pitfalls
```c
// Dangling pointer
int *ptr;
{
    int x = 42;
    ptr = &x;
}  // x goes out of scope
// *ptr is undefined!

// Memory leak
int *ptr = (int *)malloc(sizeof(int));
ptr = NULL;  // Lost the only reference to allocated memory
```

## Pointer to Pointer (Arrays of Pointers)

### Array of Strings
```c
char *fruits[] = {
    "apple",
    "banana", 
    "cherry"
};

for (int i = 0; i < 3; i++) {
    printf("%s\n", fruits[i]);
}
```

### Dynamic Array of Pointers
```c
int **matrix = (int **)malloc(3 * sizeof(int *));
for (int i = 0; i < 3; i++) {
    matrix[i] = (int *)malloc(4 * sizeof(int));
}

// Use matrix[i][j]
// Don't forget to free in reverse order
for (int i = 0; i < 3; i++) {
    free(matrix[i]);
}
free(matrix);
```

## Function Parameters

### Pass by Reference
```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 1, y = 2;
    swap(&x, &y);
    // x is now 2, y is now 1
}
```

### Returning Pointers
```c
int *get_larger(int *a, int *b) {
    return (*a > *b) ? a : b;
}

// Careful: don't return pointer to local variable!
int *bad_function() {
    int x = 42;
    return &x;  // Dangling pointer!
}
```

## Const Pointers

### Constant Data
```c
const int *ptr;     // Pointer to constant int
int const *ptr;     // Same as above
*ptr = 5;           // Error: can't modify data

ptr = &another_int; // OK: can change pointer
```

### Constant Pointer
```c
int *const ptr = &x;  // Constant pointer to int
*ptr = 5;             // OK: can modify data
ptr = &another_int;   // Error: can't change pointer
```

### Constant Pointer to Constant Data
```c
const int *const ptr = &x;
*ptr = 5;             // Error
ptr = &another_int;   // Error
```

## Embedded-Specific Patterns

### Memory-Mapped Registers
```c
#define GPIO_BASE 0x40020000
#define GPIO_MODER (*((volatile uint32_t *)(GPIO_BASE + 0x00)))
#define GPIO_ODR   (*((volatile uint32_t *)(GPIO_BASE + 0x14)))

// Set pin 0 as output
GPIO_MODER |= (1 << 0);

// Set pin 0 high
GPIO_ODR |= (1 << 0);
```

### Peripheral Control
```c
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
} uart_t;

#define UART1 ((uart_t *)0x40011000)

// Configure UART
UART1->CR1 = 0x200C;
UART1->CR2 = 0x0000;
```

### DMA Buffers
```c
uint8_t *dma_buffer = (uint8_t *)malloc(BUFFER_SIZE);
if (dma_buffer) {
    // Ensure proper alignment for DMA
    uintptr_t addr = (uintptr_t)dma_buffer;
    if (addr % DMA_ALIGNMENT != 0) {
        free(dma_buffer);
        // Handle alignment requirement
    }
}
```

## Best Practices

- Always initialize pointers
- Check for NULL after malloc
- Free allocated memory when done
- Avoid dangling pointers
- Use const for read-only pointers
- Be careful with pointer arithmetic
- Document pointer parameters clearly
- Consider using array notation when possible
- Use sizeof for allocation calculations
- Avoid complex pointer expressions