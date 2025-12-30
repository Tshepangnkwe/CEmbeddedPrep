# 04: For Loops

## Basic for Loop
```c
for (initialization; condition; increment) {
    // Loop body
}

// Example: Print numbers 1 to 5
for (int i = 1; i <= 5; i++) {
    printf("%d ", i);
}
// Output: 1 2 3 4 5
```

## Components
- **Initialization**: Executed once at start
- **Condition**: Checked before each iteration
- **Increment**: Executed after each iteration

## Common Patterns

### Counting Up
```c
for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
}
```

### Counting Down
```c
for (int i = 10; i > 0; i--) {
    printf("%d\n", i);
}
```

### Stepping by 2
```c
for (int i = 0; i < 10; i += 2) {
    printf("%d\n", i);
}
// Output: 0 2 4 6 8
```

## Nested for Loops
```c
// Multiplication table
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        printf("%d ", i * j);
    }
    printf("\n");
}
```

## Loop Control

### break Statement
```c
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        break;  // Exit loop when i == 5
    }
    printf("%d ", i);
}
// Output: 0 1 2 3 4
```

### continue Statement
```c
for (int i = 0; i < 5; i++) {
    if (i == 2) {
        continue;  // Skip iteration when i == 2
    }
    printf("%d ", i);
}
// Output: 0 1 3 4
```

## Infinite Loops
```c
// Intentional infinite loop
for (;;) {
    printf("This runs forever\n");
}

// With break condition
for (;;) {
    char input = getchar();
    if (input == 'q') {
        break;
    }
}
```

## Variable Scope
```c
for (int i = 0; i < 5; i++) {
    printf("%d ", i);
}
// i is not accessible here (in C99+)

int j;
for (j = 0; j < 5; j++) {
    printf("%d ", j);
}
// j is accessible here
```

## Best Practices
- Use meaningful loop variable names
- Keep loop bodies simple
- Avoid deep nesting
- Use break/continue sparingly
- Prefer for loops for known iterations

## Common Mistakes
- Off-by-one errors (fencepost problem)
- Infinite loops
- Modifying loop variable inside loop
- Using wrong comparison operator