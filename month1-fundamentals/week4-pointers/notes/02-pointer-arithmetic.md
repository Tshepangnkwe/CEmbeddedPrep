# 02: Pointer Arithmetic

## What is Pointer Arithmetic?
Pointer arithmetic involves performing mathematical operations on pointers to navigate memory.

## Basic Pointer Arithmetic
### Increment/Decrement
```c
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;  // Points to arr[0]

printf("%d\n", *ptr);    // 10
ptr++;                   // Points to arr[1]
printf("%d\n", *ptr);    // 20
ptr--;                   // Back to arr[0]
printf("%d\n", *ptr);    // 10
```

### Addition/Subtraction
```c
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;

ptr = ptr + 2;           // Points to arr[2] (30)
printf("%d\n", *ptr);

ptr = ptr - 1;           // Points to arr[1] (20)
printf("%d\n", *ptr);
```

## Pointer Scaling
Pointers automatically scale by the size of the pointed-to type:
```c
int arr[] = {10, 20, 30, 40, 50};
char str[] = "Hello";

int* int_ptr = arr;
char* char_ptr = str;

printf("int_ptr: %p\n", (void*)int_ptr);
int_ptr++;  // Adds sizeof(int) (usually 4 bytes)
printf("int_ptr after ++: %p\n", (void*)int_ptr);

printf("char_ptr: %p\n", (void*)char_ptr);
char_ptr++;  // Adds sizeof(char) (1 byte)
printf("char_ptr after ++: %p\n", (void*)char_ptr);
```

## Pointer Subtraction
```c
int arr[] = {10, 20, 30, 40, 50};
int* ptr1 = &arr[0];
int* ptr2 = &arr[3];

int difference = ptr2 - ptr1;  // 3 (elements between them)
printf("Difference: %d\n", difference);

// Can also subtract pointers of same type
```

## Pointer Comparison
```c
int arr[] = {10, 20, 30, 40, 50};
int* ptr1 = &arr[1];  // Points to 20
int* ptr2 = &arr[3];  // Points to 40

if (ptr1 < ptr2) {
    printf("ptr1 points to earlier element\n");
}

if (ptr1 == &arr[1]) {
    printf("ptr1 points to arr[1]\n");
}

// Only compare pointers pointing to same array
```

## Arrays and Pointers Relationship
```c
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;  // ptr points to arr[0]

// These are equivalent:
printf("%d\n", arr[2]);     // 30
printf("%d\n", *(arr + 2)); // 30
printf("%d\n", *(ptr + 2)); // 30
printf("%d\n", ptr[2]);     // 30
```

## Traversing Arrays with Pointers
### Method 1: Array indexing
```c
int arr[] = {10, 20, 30, 40, 50};
for (int i = 0; i < 5; i++) {
    printf("%d ", arr[i]);
}
```

### Method 2: Pointer arithmetic
```c
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;
for (int i = 0; i < 5; i++) {
    printf("%d ", *ptr);
    ptr++;
}
```

### Method 3: Pointer comparison
```c
int arr[] = {10, 20, 30, 40, 50};
for (int* ptr = arr; ptr < arr + 5; ptr++) {
    printf("%d ", *ptr);
}
```

## String Traversal with Pointers
```c
char str[] = "Hello";
char* ptr = str;

// Method 1: Using pointer arithmetic
while (*ptr != '\0') {
    printf("%c", *ptr);
    ptr++;
}

// Method 2: Using array notation
for (int i = 0; str[i] != '\0'; i++) {
    printf("%c", str[i]);
}
```

## Pointer to Pointer Arithmetic
```c
int arr[] = {10, 20, 30};
int* ptr_array[] = {&arr[0], &arr[1], &arr[2]};
int** ptr_ptr = ptr_array;

printf("%d\n", **ptr_ptr);        // 10
ptr_ptr++;                        // Points to &arr[1]
printf("%d\n", **ptr_ptr);        // 20
```

## Function Pointer Arithmetic
Function pointers cannot do arithmetic:
```c
int add(int a, int b) { return a + b; }
int (*func_ptr)(int, int) = add;

// func_ptr++;  // Error: cannot increment function pointer
```

## Void Pointer Arithmetic
Void pointers cannot do arithmetic directly:
```c
int arr[] = {10, 20, 30};
void* void_ptr = arr;

// void_ptr++;  // Error: invalid use of void pointer

// Must cast first
int* int_ptr = (int*)void_ptr;
int_ptr++;  // OK
```

## Common Patterns
### Finding Array Length
```c
int arr[] = {1, 2, 3, 4, 5};
int* start = arr;
int* end = arr + 5;  // Points past last element

size_t length = end - start;  // 5
```

### Reversing Array with Pointers
```c
void reverse_array(int* start, int* end) {
    end--;  // Point to last element
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Usage
int arr[] = {1, 2, 3, 4, 5};
reverse_array(arr, arr + 5);
```

### Copying Memory with Pointers
```c
void copy_array(int* dest, int* src, size_t size) {
    for (size_t i = 0; i < size; i++) {
        *dest = *src;
        dest++;
        src++;
    }
}

// Usage
int source[] = {1, 2, 3, 4, 5};
int dest[5];
copy_array(dest, source, 5);
```

## Best Practices
- Only do arithmetic on pointers to array elements
- Stay within array bounds
- Use pointer comparison instead of array indexing when possible
- Be careful with pointer scaling
- Document pointer arithmetic operations

## Common Mistakes
- Arithmetic on uninitialized pointers
- Going beyond array bounds
- Wrong pointer types in arithmetic
- Comparing pointers from different arrays
- Forgetting pointer scaling
- Invalid pointer arithmetic with void pointers