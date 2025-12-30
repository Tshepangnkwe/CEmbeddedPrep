# 03: Pointers and Arrays

## Arrays as Pointers
In C, arrays and pointers are closely related. An array name is essentially a constant pointer to the first element.

## Array Name is a Pointer
```c
int arr[] = {10, 20, 30, 40, 50};

// arr is equivalent to &arr[0]
printf("arr: %p\n", (void*)arr);
printf("&arr[0]: %p\n", (void*)&arr[0]);

// Both print the same address
```

## Array Decay to Pointers
When passed to functions, arrays decay to pointers:
```c
void func(int arr[]) {
    // arr is actually int*
    printf("Size of arr: %zu\n", sizeof(arr));  // Size of pointer, not array!
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("Size of arr: %zu\n", sizeof(arr));  // Size of array
    func(arr);  // Array decays to pointer
}
```

## Equivalent Notations
```c
int arr[] = {10, 20, 30, 40, 50};
int* ptr = arr;

// These are all equivalent:
arr[2] = 35;      // Array notation
*(arr + 2) = 35;  // Pointer notation
*(ptr + 2) = 35;  // Pointer notation
ptr[2] = 35;      // Array notation on pointer

printf("%d\n", arr[2]);     // 35
printf("%d\n", *(arr + 2)); // 35
printf("%d\n", *(ptr + 2)); // 35
printf("%d\n", ptr[2]);     // 35
```

## Multidimensional Arrays and Pointers
### 2D Arrays
```c
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// matrix is pointer to first row (int (*)[4])
printf("matrix: %p\n", (void*)matrix);
printf("matrix[0]: %p\n", (void*)matrix[0]);
printf("&matrix[0][0]: %p\n", (void*)&matrix[0][0]);
```

### Accessing 2D Array Elements
```c
// All these access matrix[1][2] (value 7):
printf("%d\n", matrix[1][2]);
printf("%d\n", *(*(matrix + 1) + 2));
printf("%d\n", *(matrix[1] + 2));
printf("%d\n", *(&matrix[0][0] + 1*4 + 2));
```

## Array of Pointers
```c
int* arr_of_ptrs[3];

// Initialize
int a = 10, b = 20, c = 30;
arr_of_ptrs[0] = &a;
arr_of_ptrs[1] = &b;
arr_of_ptrs[2] = &c;

// Access
printf("%d\n", *arr_of_ptrs[1]);  // 20
```

## Pointer to Array
```c
int arr[5] = {1, 2, 3, 4, 5};
int (*ptr_to_arr)[5] = &arr;  // Pointer to entire array

// Access elements
printf("%d\n", (*ptr_to_arr)[2]);  // 3
printf("%d\n", *(*ptr_to_arr + 2));  // 3
```

## Dynamic Arrays with Pointers
### Single Dimensional
```c
#include <stdlib.h>

int* dynamic_arr = (int*)malloc(5 * sizeof(int));
if (dynamic_arr == NULL) {
    // Handle allocation failure
    return 1;
}

// Use like regular array
for (int i = 0; i < 5; i++) {
    dynamic_arr[i] = i * 10;
}

// Free memory
free(dynamic_arr);
dynamic_arr = NULL;  // Good practice
```

### Two Dimensional
```c
// Method 1: Array of pointers
int** matrix = (int**)malloc(3 * sizeof(int*));
for (int i = 0; i < 3; i++) {
    matrix[i] = (int*)malloc(4 * sizeof(int));
}

// Use matrix[i][j]

// Free memory
for (int i = 0; i < 3; i++) {
    free(matrix[i]);
}
free(matrix);
```

```c
// Method 2: Single contiguous block
int* matrix = (int*)malloc(3 * 4 * sizeof(int));
// Access as: matrix[i * 4 + j]

// Free memory
free(matrix);
```

## Strings and Pointers
### String Literals
```c
char* str_ptr = "Hello World";
// str_ptr points to read-only string literal

// This is dangerous:
// str_ptr[0] = 'h';  // Undefined behavior!

// Safe way:
char str[] = "Hello World";
str[0] = 'h';  // OK
```

### Array of Strings
```c
char* names[] = {
    "Alice",
    "Bob",
    "Charlie"
};

// Access
printf("%s\n", names[1]);      // "Bob"
printf("%c\n", names[1][0]);   // 'B'
```

## Function Parameters
### Passing Arrays
```c
// Method 1: Array notation (decays to pointer)
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

// Method 2: Pointer notation
void print_array_ptr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
}

// Usage
int arr[] = {1, 2, 3, 4, 5};
print_array(arr, 5);
```

### Modifying Arrays in Functions
```c
void double_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Modifies original array
    }
}

int main() {
    int arr[] = {1, 2, 3};
    double_array(arr, 3);
    // arr is now {2, 4, 6}
}
```

## Common Patterns
### Finding Maximum with Pointers
```c
int* find_max(int* arr, int size) {
    if (size == 0) return NULL;

    int* max_ptr = arr;
    for (int* ptr = arr + 1; ptr < arr + size; ptr++) {
        if (*ptr > *max_ptr) {
            max_ptr = ptr;
        }
    }
    return max_ptr;
}

// Usage
int arr[] = {3, 1, 4, 1, 5};
int* max_ptr = find_max(arr, 5);
printf("Max value: %d at index %ld\n", *max_ptr, max_ptr - arr);
```

### Swapping with Pointers
```c
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    swap(&x, &y);
    // x is 20, y is 10
}
```

## Best Practices
- Remember arrays decay to pointers in function calls
- Use sizeof on arrays before they decay
- Be careful with dynamic memory allocation
- Always free allocated memory
- Check for NULL after malloc
- Use const for pointers to constant data

## Common Mistakes
- Using sizeof on decayed array pointers
- Returning local arrays from functions
- Memory leaks from not freeing dynamic arrays
- Accessing beyond array bounds
- Confusing array names with pointers
- Modifying string literals through pointers