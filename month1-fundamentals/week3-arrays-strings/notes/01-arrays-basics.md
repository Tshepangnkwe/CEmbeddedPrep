# 01: Arrays Basics

## What is an Array?
An array is a collection of elements of the same type stored in contiguous memory locations.

## Declaration and Initialization
### Declaration
```c
// Syntax: type array_name[size];
int numbers[5];        // Array of 5 integers
char letters[10];      // Array of 10 characters
double values[100];    // Array of 100 doubles
```

### Initialization
```c
// Method 1: Initialize all elements
int arr1[5] = {1, 2, 3, 4, 5};

// Method 2: Partial initialization (rest become 0)
int arr2[5] = {1, 2};  // arr2 = {1, 2, 0, 0, 0}

// Method 3: Size determined by initializer
int arr3[] = {1, 2, 3, 4, 5};  // Size is 5

// Method 4: Initialize all to zero
int arr4[5] = {0};

// Method 5: Designated initializers (C99)
int arr5[5] = {[2] = 10, [4] = 20};  // {0, 0, 10, 0, 20}
```

## Accessing Array Elements
```c
int numbers[5] = {10, 20, 30, 40, 50};

printf("%d\n", numbers[0]);  // First element: 10
printf("%d\n", numbers[4]);  // Last element: 50

// Modify elements
numbers[2] = 35;  // Change third element to 35
```

## Array Size and Bounds
```c
int arr[5] = {1, 2, 3, 4, 5};

// Valid indices: 0, 1, 2, 3, 4
// Size: 5 elements

// Getting array size
int size = sizeof(arr) / sizeof(arr[0]);  // 5

// Bounds checking (manual - C doesn't do this automatically)
if (index >= 0 && index < size) {
    // Safe access
    arr[index] = value;
}
```

## Common Operations
### Traversing Arrays
```c
int arr[] = {1, 2, 3, 4, 5};
int size = 5;

// Method 1: Using index
for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
}

// Method 2: Using pointers (advanced)
for (int* ptr = arr; ptr < arr + size; ptr++) {
    printf("%d ", *ptr);
}
```

### Finding Elements
```c
int find_element(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index
        }
    }
    return -1;  // Not found
}
```

### Sum and Average
```c
int sum = 0;
int arr[] = {1, 2, 3, 4, 5};
int size = 5;

for (int i = 0; i < size; i++) {
    sum += arr[i];
}

double average = (double)sum / size;
```

## Multidimensional Arrays
### 2D Arrays
```c
// Declaration
int matrix[3][4];  // 3 rows, 4 columns

// Initialization
int matrix2[2][3] = {
    {1, 2, 3},      // Row 0
    {4, 5, 6}       // Row 1
};

// Access elements
matrix2[0][1] = 10;  // Row 0, Column 1
```

### 3D Arrays
```c
int cube[2][3][4];  // 2 layers, 3 rows, 4 columns
cube[1][2][3] = 42;  // Access element
```

## Arrays as Function Parameters
### Passing Arrays to Functions
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
int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    print_array(numbers, 5);
    return 0;
}
```

### Returning Arrays from Functions
```c
// Return pointer to array (be careful with lifetime!)
int* create_array(int size) {
    int* arr = malloc(size * sizeof(int));
    // Initialize array...
    return arr;
}

// Better: pass array as parameter
void fill_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * 2;
    }
}
```

## Array Limitations in C
- Fixed size (cannot resize after declaration)
- No bounds checking
- Arrays decay to pointers when passed to functions
- No built-in operations (copy, compare, etc.)

## Best Practices
- Always keep track of array size
- Use const for arrays that shouldn't be modified
- Initialize arrays when declared
- Use meaningful names for array sizes
- Check bounds before accessing elements

## Common Mistakes
- Accessing elements outside bounds (undefined behavior)
- Forgetting arrays are zero-indexed
- Confusing array size with last valid index
- Not passing array size to functions
- Trying to assign arrays directly (use memcpy instead)
- Returning local arrays from functions