# 05: Array Functions

## Basic Array Operations
Common operations performed on arrays in C.

## Copying Arrays
### Method 1: Manual Loop
```c
void copy_array(int dest[], int src[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

// Usage
int source[] = {1, 2, 3, 4, 5};
int destination[5];
copy_array(destination, source, 5);
```

### Method 2: memcpy (from string.h)
```c
#include <string.h>

int source[] = {1, 2, 3, 4, 5};
int destination[5];
memcpy(destination, source, sizeof(source));  // Copy entire array
```

## Comparing Arrays
### Manual Comparison
```c
int arrays_equal(int arr1[], int arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;  // Not equal
        }
    }
    return 1;  // Equal
}

// Usage
int a[] = {1, 2, 3};
int b[] = {1, 2, 3};
int c[] = {1, 2, 4};

printf("a == b: %d\n", arrays_equal(a, b, 3));  // 1 (true)
printf("a == c: %d\n", arrays_equal(a, c, 3));  // 0 (false)
```

### memcmp (from string.h)
```c
#include <string.h>

int result = memcmp(arr1, arr2, sizeof(arr1));
if (result == 0) {
    // Arrays are equal
} else if (result < 0) {
    // arr1 < arr2
} else {
    // arr1 > arr2
}
```

## Finding Elements
### Linear Search
```c
int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index
        }
    }
    return -1;  // Not found
}

// Usage
int numbers[] = {10, 20, 30, 40, 50};
int index = linear_search(numbers, 5, 30);
if (index != -1) {
    printf("Found at index %d\n", index);
}
```

### Find Maximum/Minimum
```c
int find_max(int arr[], int size) {
    if (size == 0) return -1;  // Error case

    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int find_min(int arr[], int size) {
    if (size == 0) return -1;

    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}
```

## Sorting Arrays
### Bubble Sort
```c
void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Usage
int numbers[] = {64, 34, 25, 12, 22, 11, 90};
bubble_sort(numbers, 7);
```

### Selection Sort
```c
void selection_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}
```

## Reversing Arrays
```c
void reverse_array(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

// Usage
int arr[] = {1, 2, 3, 4, 5};
reverse_array(arr, 5);  // {5, 4, 3, 2, 1}
```

## Array Rotation
### Left Rotation
```c
void rotate_left(int arr[], int size, int positions) {
    positions = positions % size;  // Handle large rotations
    for (int i = 0; i < positions; i++) {
        int temp = arr[0];
        for (int j = 0; j < size - 1; j++) {
            arr[j] = arr[j + 1];
        }
        arr[size - 1] = temp;
    }
}

// Usage
int arr[] = {1, 2, 3, 4, 5};
rotate_left(arr, 5, 2);  // {3, 4, 5, 1, 2}
```

### Right Rotation
```c
void rotate_right(int arr[], int size, int positions) {
    positions = positions % size;
    for (int i = 0; i < positions; i++) {
        int temp = arr[size - 1];
        for (int j = size - 1; j > 0; j--) {
            arr[j] = arr[j - 1];
        }
        arr[0] = temp;
    }
}
```

## Removing Duplicates
```c
int remove_duplicates(int arr[], int size) {
    if (size == 0 || size == 1) return size;

    int j = 0;  // Index for unique elements
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            arr[j++] = arr[i];
        }
    }
    arr[j++] = arr[size - 1];  // Last element
    return j;  // New size
}

// Usage (assumes sorted array)
int sorted_arr[] = {1, 1, 2, 2, 3, 4, 4, 5};
int new_size = remove_duplicates(sorted_arr, 8);
// sorted_arr now contains {1, 2, 3, 4, 5}
```

## Frequency Count
```c
void count_frequency(int arr[], int size) {
    int visited[size];
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < size; i++) {
        if (visited[i] == 1) continue;

        int count = 1;
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }
        printf("%d appears %d times\n", arr[i], count);
    }
}
```

## Best Practices
- Use library functions when available (memcpy, memcmp)
- Consider time complexity for large arrays
- Handle edge cases (empty arrays, single elements)
- Document array size requirements
- Use const for read-only array parameters

## Common Mistakes
- Off-by-one errors in loops
- Not handling empty arrays
- Modifying arrays when they should be const
- Forgetting to update size after operations
- Using wrong comparison operators in sorts