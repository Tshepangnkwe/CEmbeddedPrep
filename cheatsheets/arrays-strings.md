# Arrays and Strings Cheatsheet

## Arrays

### Declaration and Initialization
```c
// Fixed-size arrays
int numbers[5];                    // Uninitialized
int primes[] = {2, 3, 5, 7, 11};  // Size inferred
int zeros[10] = {0};               // First element 0, rest 0
int partial[5] = {1, 2};           // {1, 2, 0, 0, 0}

// Multidimensional
int matrix[3][4];                  // 3 rows, 4 columns
int cube[2][3][4];                 // 3D array
```

### Accessing Elements
```c
int arr[5] = {10, 20, 30, 40, 50};

printf("%d\n", arr[0]);    // 10
printf("%d\n", arr[4]);    // 50

arr[2] = 35;               // Modify element
```

### Array Size
```c
int arr[5] = {1, 2, 3, 4, 5};
size_t size = sizeof(arr) / sizeof(arr[0]);  // 5

// For function parameters, this doesn't work
void func(int arr[]) {
    // sizeof(arr) is sizeof(int*) - not useful
}
```

## Dynamic Arrays

### Using malloc/free
```c
#include <stdlib.h>

int *dynamic_arr = (int *)malloc(10 * sizeof(int));
if (dynamic_arr == NULL) {
    // Handle allocation failure
}

// Use like regular array
for (int i = 0; i < 10; i++) {
    dynamic_arr[i] = i * 2;
}

free(dynamic_arr);  // Always free allocated memory
```

### Resizing Arrays
```c
int *arr = (int *)malloc(5 * sizeof(int));
int current_size = 5;

// Need more space
int new_size = 10;
int *temp = (int *)realloc(arr, new_size * sizeof(int));
if (temp != NULL) {
    arr = temp;
    current_size = new_size;
} else {
    // Handle reallocation failure
    free(arr);
}
```

## Strings

### C String Basics
```c
// String literals (read-only)
char *str1 = "Hello";

// Character arrays (modifiable)
char str2[] = "Hello";
char str3[6] = "Hello";  // Explicit size
char str4[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  // Manual null termination
```

### String Length
```c
#include <string.h>

char str[] = "Hello";
size_t len = strlen(str);  // 5 (excludes null terminator)
size_t size = sizeof(str); // 6 (includes null terminator)
```

## String Functions

### Copying Strings
```c
#include <string.h>

char dest[20];
char src[] = "Hello World";

// Safe copy (prevents buffer overflow)
strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';  // Ensure null termination

// Or use safer alternatives
strlcpy(dest, src, sizeof(dest));  // If available
```

### Concatenation
```c
char str[20] = "Hello";
strcat(str, " World");  // "Hello World"

// Safe version
strncat(str, " Universe", sizeof(str) - strlen(str) - 1);
```

### Comparison
```c
char str1[] = "apple";
char str2[] = "banana";

if (strcmp(str1, str2) < 0) {
    printf("str1 comes before str2\n");
}

if (strncmp(str1, str2, 3) == 0) {
    printf("First 3 chars are equal\n");
}
```

### Searching
```c
char str[] = "Hello World";
char *pos = strchr(str, 'W');      // Find first 'W'
char *last = strrchr(str, 'l');    // Find last 'l'

char substr[] = "Wor";
char *found = strstr(str, substr); // Find substring
```

## String Conversion

### Numbers to Strings
```c
#include <stdio.h>

char buffer[20];
int num = 42;

// Integer to string
sprintf(buffer, "%d", num);

// Float to string
double pi = 3.14159;
sprintf(buffer, "%.2f", pi);
```

### Strings to Numbers
```c
#include <stdlib.h>

char str[] = "123";
int num = atoi(str);           // 123

char float_str[] = "3.14";
double val = atof(float_str);  // 3.14

// Safer versions
char *endptr;
long lval = strtol(str, &endptr, 10);
if (*endptr != '\0') {
    // Conversion failed
}
```

## Multidimensional Arrays

### Declaration and Access
```c
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

printf("%d\n", matrix[1][2]);  // 7

// Pointer notation
printf("%d\n", *(*(matrix + 1) + 2));  // Same as above
```

### Dynamic 2D Arrays
```c
int **matrix = (int **)malloc(3 * sizeof(int *));
for (int i = 0; i < 3; i++) {
    matrix[i] = (int *)malloc(4 * sizeof(int));
}

// Use matrix[i][j]

// Cleanup
for (int i = 0; i < 3; i++) {
    free(matrix[i]);
}
free(matrix);
```

## Array Algorithms

### Linear Search
```c
int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Found
        }
    }
    return -1;  // Not found
}
```

### Binary Search (sorted array)
```c
int binary_search(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
```

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
```

## String Algorithms

### Reverse String
```c
void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}
```

### Check Palindrome
```c
bool is_palindrome(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}
```

### String Tokenization
```c
#include <string.h>

char str[] = "apple,banana,cherry";
char *token = strtok(str, ",");

while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
}
```

## Embedded-Specific Patterns

### Ring Buffers
```c
#define BUFFER_SIZE 256

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} ring_buffer_t;

void ring_buffer_init(ring_buffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

bool ring_buffer_put(ring_buffer_t *rb, uint8_t data) {
    if (rb->count >= BUFFER_SIZE) {
        return false;  // Buffer full
    }
    
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    rb->count++;
    return true;
}

bool ring_buffer_get(ring_buffer_t *rb, uint8_t *data) {
    if (rb->count == 0) {
        return false;  // Buffer empty
    }
    
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    rb->count--;
    return true;
}
```

### Lookup Tables
```c
// Sine lookup table (pre-computed values)
const uint16_t sine_table[256] = {
    0x8000, 0x8324, 0x8648, 0x896C, /* ... */
};

// Fast sine approximation
uint16_t fast_sin(uint8_t angle) {
    return sine_table[angle];
}
```

### Configuration Arrays
```c
typedef struct {
    uint8_t pin;
    uint8_t mode;
    uint8_t pull;
} gpio_config_t;

const gpio_config_t gpio_configs[] = {
    {0, GPIO_MODE_OUTPUT, GPIO_PULL_NONE},
    {1, GPIO_MODE_INPUT, GPIO_PULL_UP},
    {2, GPIO_MODE_OUTPUT, GPIO_PULL_NONE},
};

void init_gpio(void) {
    for (size_t i = 0; i < sizeof(gpio_configs)/sizeof(gpio_config_t); i++) {
        configure_pin(gpio_configs[i].pin, 
                     gpio_configs[i].mode, 
                     gpio_configs[i].pull);
    }
}
```

## Best Practices

- Always null-terminate strings
- Check array bounds
- Use sizeof for array size calculations
- Prefer strn* functions for safety
- Initialize arrays when declared
- Free dynamic memory when done
- Consider buffer overflow vulnerabilities
- Use const for string literals
- Document array sizes in function parameters
- Validate string inputs before processing