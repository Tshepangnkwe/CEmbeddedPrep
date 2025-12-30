# Loops Cheatsheet

## For Loop

### Basic Syntax
```c
for (initialization; condition; increment) {
    // code
}
```

### Common Patterns
```c
// Count from 0 to 9
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}

// Count from 10 to 1
for (int i = 10; i > 0; i--) {
    printf("%d ", i);
}

// Array iteration
int arr[] = {1, 2, 3, 4, 5};
for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
    printf("%d ", arr[i]);
}
```

## While Loop

### Basic Syntax
```c
while (condition) {
    // code
}
```

### Common Patterns
```c
// Read until EOF
int c;
while ((c = getchar()) != EOF) {
    putchar(c);
}

// Input validation
int value;
printf("Enter positive number: ");
while (scanf("%d", &value) != 1 || value <= 0) {
    printf("Invalid input. Try again: ");
    // Clear input buffer
    while (getchar() != '\n');
}
```

## Do-While Loop

### Basic Syntax
```c
do {
    // code
} while (condition);
```

### Common Patterns
```c
// Menu system
int choice;
do {
    printf("1. Option 1\n");
    printf("2. Option 2\n");
    printf("3. Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);
} while (choice < 1 || choice > 3);
```

## Loop Control

### Break
```c
// Exit loop early
for (int i = 0; i < 100; i++) {
    if (some_condition) {
        break;  // Exit loop
    }
}
```

### Continue
```c
// Skip current iteration
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        continue;  // Skip even numbers
    }
    printf("%d ", i);
}
```

### Nested Loops
```c
// Multiplication table
for (int i = 1; i <= 10; i++) {
    for (int j = 1; j <= 10; j++) {
        printf("%3d ", i * j);
    }
    printf("\n");
}
```

## Common Patterns

### Sum Array
```c
int sum = 0;
int arr[] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++) {
    sum += arr[i];
}
```

### Find Maximum
```c
int max = INT_MIN;
int arr[] = {3, 1, 4, 1, 5};
for (int i = 0; i < 5; i++) {
    if (arr[i] > max) {
        max = arr[i];
    }
}
```

### String Processing
```c
char str[] = "Hello";
for (int i = 0; str[i] != '\0'; i++) {
    printf("%c\n", str[i]);
}
```

### Infinite Loop (with break)
```c
while (1) {
    // Do something
    if (should_exit) {
        break;
    }
}
```

## Embedded-Specific Patterns

### Polling Loop
```c
// Wait for hardware flag
while (!(STATUS_REG & FLAG_MASK)) {
    // Busy wait
}
```

### Timeout Loop
```c
#define TIMEOUT_MS 1000
uint32_t start = get_tick_count();
while (!(STATUS_REG & FLAG_MASK)) {
    if (get_tick_count() - start > TIMEOUT_MS) {
        // Timeout occurred
        break;
    }
}
```

### State Machine Loop
```c
typedef enum { IDLE, RUNNING, ERROR } state_t;
state_t state = IDLE;

while (1) {
    switch (state) {
        case IDLE:
            if (start_condition) {
                state = RUNNING;
            }
            break;
        case RUNNING:
            // Running logic
            if (error_condition) {
                state = ERROR;
            }
            break;
        case ERROR:
            // Error handling
            break;
    }
}
```

## Best Practices

- Use `size_t` for array indices
- Prefer `for` loops for known iterations
- Use `while` for unknown iterations
- Avoid infinite loops without exit conditions
- Consider loop unrolling for performance-critical code
- Use meaningful variable names (i, j, k are OK for simple loops)