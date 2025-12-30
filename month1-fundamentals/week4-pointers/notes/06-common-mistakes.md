# 06: Common Pointer Mistakes

## Uninitialized Pointers
```c
int* ptr;
// ptr contains garbage value - DANGEROUS!

*ptr = 42;  // Segmentation fault or undefined behavior
```

### Safe Version
```c
int* ptr = NULL;  // Initialize to NULL
int x = 42;
ptr = &x;         // Now safe to use
```

## NULL Pointer Dereference
```c
int* ptr = NULL;
*ptr = 42;  // Segmentation fault!
```

### Safe Version
```c
int* ptr = NULL;
if (ptr != NULL) {
    *ptr = 42;
}
```

## Dangling Pointers
```c
int* dangerous_function() {
    int local_var = 42;
    return &local_var;  // DANGEROUS: returns address of local variable
}

int main() {
    int* ptr = dangerous_function();
    *ptr = 100;  // Undefined behavior - local_var no longer exists
}
```

### Safe Version
```c
int* safe_function() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    return ptr;
}

int main() {
    int* ptr = safe_function();
    *ptr = 100;  // OK
    free(ptr);   // Don't forget to free!
}
```

## Memory Leaks
```c
void leaky_function() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    // Forgot to free(ptr) - memory leak!
}

int main() {
    for (int i = 0; i < 1000; i++) {
        leaky_function();  // Leaks 1000 * sizeof(int) bytes
    }
}
```

### Fixed Version
```c
void fixed_function() {
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        free(ptr);
    }
}
```

## Double Free
```c
int* ptr = (int*)malloc(sizeof(int));
free(ptr);
// ptr is now a dangling pointer

free(ptr);  // Double free - undefined behavior!
```

### Safe Version
```c
int* ptr = (int*)malloc(sizeof(int));
free(ptr);
ptr = NULL;  // Set to NULL after free

if (ptr != NULL) {
    free(ptr);  // Won't execute
}
```

## Array Bounds Violation
```c
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

ptr[5] = 100;  // Out of bounds - undefined behavior
*(ptr + 10) = 200;  // Even worse
```

### Safe Version
```c
#define ARRAY_SIZE 5
int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5};
int* ptr = arr;

for (int i = 0; i < ARRAY_SIZE; i++) {
    ptr[i] = i * 10;  // Safe
}
```

## Pointer Type Mismatches
```c
int x = 42;
void* void_ptr = &x;
double* double_ptr = void_ptr;  // Type mismatch

*double_ptr = 3.14;  // Undefined behavior
```

### Safe Version
```c
int x = 42;
void* void_ptr = &x;
int* int_ptr = (int*)void_ptr;  // Proper cast

*int_ptr = 100;  // OK
```

## Returning Local Variable Addresses
```c
int* get_local_address() {
    int local = 42;
    return &local;  // BAD: local goes out of scope
}

int main() {
    int* ptr = get_local_address();
    printf("%d\n", *ptr);  // Undefined behavior
}
```

### Fixed Version
```c
int* get_dynamic_address() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 42;
    return ptr;
}

int main() {
    int* ptr = get_dynamic_address();
    printf("%d\n", *ptr);  // OK
    free(ptr);
}
```

## Incorrect Pointer Arithmetic
```c
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

ptr = ptr + 2;  // OK: points to arr[2]
ptr = ptr * 2;  // ERROR: invalid pointer arithmetic
```

### Valid Pointer Arithmetic
```c
int arr[5] = {1, 2, 3, 4, 5};
int* ptr = arr;

// Valid operations:
ptr++;      // Next element
ptr--;      // Previous element
ptr += 3;   // Skip 3 elements
ptr -= 1;   // Back 1 element

// Comparison
if (ptr < arr + 5) {  // Within bounds
    *ptr = 42;
}
```

## Function Pointer Errors
```c
int add(int a, int b) { return a + b; }

int main() {
    int (*func_ptr)(int, int);  // Uninitialized function pointer
    int result = func_ptr(5, 3);  // Crash!
}
```

### Safe Version
```c
int add(int a, int b) { return a + b; }

int main() {
    int (*func_ptr)(int, int) = NULL;
    func_ptr = add;  // Initialize before use

    if (func_ptr != NULL) {
        int result = func_ptr(5, 3);  // OK
    }
}
```

## String Literal Modification
```c
char* str = "Hello World";
str[0] = 'h';  // UNDEFINED BEHAVIOR!
// String literals are read-only
```

### Safe Version
```c
char str[] = "Hello World";  // Array, not pointer
str[0] = 'h';  // OK

// Or
char* str = (char*)malloc(12);
strcpy(str, "Hello World");
str[0] = 'h';  // OK
free(str);
```

## Malloc Failure Not Checked
```c
int* ptr = (int*)malloc(sizeof(int) * 1000000);
// Assume malloc fails due to insufficient memory

*ptr = 42;  // Segmentation fault!
```

### Safe Version
```c
int* ptr = (int*)malloc(sizeof(int) * 1000000);
if (ptr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return EXIT_FAILURE;
}

*ptr = 42;  // OK
free(ptr);
```

## Pointer to Pointer Confusion
```c
int x = 42;
int* ptr = &x;
int** ptr_ptr = &ptr;

*ptr = 100;     // Changes x to 100
**ptr_ptr = 200; // Also changes x to 200

// But:
*ptr_ptr = NULL;  // Makes ptr point to NULL
// Now *ptr would crash!
```

## Best Practices to Avoid Mistakes
- Always initialize pointers
- Check for NULL before dereferencing
- Free dynamically allocated memory
- Set pointers to NULL after free
- Use const for pointers to constant data
- Be careful with pointer arithmetic
- Use array notation when possible
- Document pointer ownership and lifetime
- Use tools like Valgrind to detect memory errors