# 01: Pointer Basics

## What is a Pointer?
A pointer is a variable that stores the memory address of another variable.

## Pointer Declaration
```c
// Syntax: type* pointer_name;
int* ptr;       // Pointer to int
char* str_ptr;  // Pointer to char
double* dbl_ptr; // Pointer to double

// Multiple pointers
int* p1, p2;    // p1 is pointer, p2 is int
int *p1, *p2;   // Both are pointers
```

## Address-of Operator (&)
```c
int x = 42;
int* ptr = &x;  // ptr stores address of x

printf("Value of x: %d\n", x);
printf("Address of x: %p\n", &x);
printf("Value of ptr: %p\n", ptr);
printf("Value pointed to by ptr: %d\n", *ptr);
```

## Dereference Operator (*)
```c
int x = 10;
int* ptr = &x;

// Read value through pointer
int value = *ptr;  // value = 10

// Modify value through pointer
*ptr = 20;  // x is now 20

printf("x = %d\n", x);  // 20
```

## NULL Pointers
```c
int* ptr = NULL;  // Points to nothing

// Always check before dereferencing
if (ptr != NULL) {
    *ptr = 42;
}

// NULL is defined in stddef.h (included via stdio.h)
```

## Pointer Types and Sizes
```c
int x = 5;
char c = 'A';
double d = 3.14;

int* int_ptr = &x;
char* char_ptr = &c;
double* double_ptr = &d;

printf("Size of int*: %zu bytes\n", sizeof(int_ptr));
printf("Size of char*: %zu bytes\n", sizeof(char_ptr));
printf("Size of double*: %zu bytes\n", sizeof(double_ptr));

// On most systems, all pointers are same size (4 or 8 bytes)
```

## Pointer to Pointer
```c
int x = 10;
int* ptr = &x;
int** ptr_to_ptr = &ptr;

printf("x = %d\n", x);
printf("*ptr = %d\n", *ptr);
printf("**ptr_to_ptr = %d\n", **ptr_to_ptr);

// All three access the same value
```

## Void Pointers
```c
void* generic_ptr;

// Can point to any type
int x = 42;
generic_ptr = &x;

// Must cast to dereference
int* int_ptr = (int*)generic_ptr;
printf("%d\n", *int_ptr);

// Common use: malloc returns void*
int* arr = (int*)malloc(5 * sizeof(int));
```

## Pointer Constants
### Constant Pointer
```c
int x = 10, y = 20;
int* const ptr = &x;  // Constant pointer

*ptr = 30;    // OK: can change value
// ptr = &y;  // Error: cannot change address
```

### Pointer to Constant
```c
int x = 10, y = 20;
const int* ptr = &x;  // Pointer to constant

// *ptr = 30;  // Error: cannot change value
ptr = &y;     // OK: can change address
```

### Constant Pointer to Constant
```c
int x = 10, y = 20;
const int* const ptr = &x;  // Constant pointer to constant

// *ptr = 30;  // Error: cannot change value
// ptr = &y;   // Error: cannot change address
```

## Pointer Initialization
### Good Practices
```c
// Initialize to NULL
int* ptr = NULL;

// Initialize to valid address
int x = 42;
int* ptr2 = &x;

// Never leave uninitialized
int* bad_ptr;  // Points to random memory!
// *bad_ptr = 10;  // Dangerous!
```

## Memory Addresses
```c
int x = 42;
printf("Address of x: %p\n", (void*)&x);

// Addresses are typically shown in hexadecimal
// Example output: 0x7ffd2c9a8b4c
```

## Pointer Casting
```c
int x = 42;
void* void_ptr = &x;

// Cast back to int*
int* int_ptr = (int*)void_ptr;
printf("%d\n", *int_ptr);

// Be careful with incompatible casts
char c = 'A';
int* bad_cast = (int*)&c;  // Dangerous!
// *bad_cast = 12345;       // May corrupt memory
```

## Best Practices
- Always initialize pointers
- Check for NULL before dereferencing
- Use const when appropriate
- Be careful with pointer arithmetic
- Free dynamically allocated memory
- Use meaningful names for pointers

## Common Mistakes
- Dereferencing NULL pointers (segmentation fault)
- Uninitialized pointers
- Memory leaks (not freeing allocated memory)
- Dangling pointers (pointing to freed memory)
- Wrong pointer types
- Off-by-one errors in pointer arithmetic