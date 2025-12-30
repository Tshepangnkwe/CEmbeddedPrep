# 06: Nested Loops

## Basic Nested Loops
```c
for (int i = 0; i < 3; i++) {        // Outer loop
    for (int j = 0; j < 3; j++) {    // Inner loop
        printf("(%d,%d) ", i, j);
    }
    printf("\n");
}
// Output:
// (0,0) (0,1) (0,2)
// (1,0) (1,1) (1,2)
// (2,0) (2,1) (2,2)
```

## Different Loop Types
```c
int i = 0;
while (i < 3) {
    int j = 0;
    while (j < 3) {
        printf("%d ", i * 3 + j);
        j++;
    }
    printf("\n");
    i++;
}
```

## Common Patterns

### Multiplication Table
```c
printf("   ");
for (int i = 1; i <= 10; i++) {
    printf("%4d", i);
}
printf("\n");

for (int i = 1; i <= 10; i++) {
    printf("%2d ", i);
    for (int j = 1; j <= 10; j++) {
        printf("%4d", i * j);
    }
    printf("\n");
}
```

### Pattern Printing
```c
// Right triangle
for (int i = 1; i <= 5; i++) {
    for (int j = 1; j <= i; j++) {
        printf("* ");
    }
    printf("\n");
}
/*
*
* *
* * *
* * * *
* * * * *
*/
```

### 2D Array Processing
```c
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        printf("%d ", matrix[i][j]);
    }
    printf("\n");
}
```

## Loop Control in Nested Loops

### break (exits innermost loop)
```c
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (j == 2) break;
        printf("(%d,%d) ", i, j);
    }
    printf("\n");
}
// Output:
// (0,0) (0,1)
// (1,0) (1,1)
// (2,0) (2,1)
```

### continue (skips current iteration)
```c
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (j == 1) continue;
        printf("(%d,%d) ", i, j);
    }
    printf("\n");
}
// Output:
// (0,0) (0,2)
// (1,0) (1,2)
// (2,0) (2,2)
```

### Labeled break (exits specific loop)
```c
outer: for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (i == 1 && j == 1) {
            break outer;  // Exit outer loop
        }
        printf("(%d,%d) ", i, j);
    }
    printf("\n");
}
// Output:
// (0,0) (0,1) (0,2)
// (1,0) (1,1)
```

## Variable Scope
```c
for (int i = 0; i < 2; i++) {
    printf("Outer: %d\n", i);
    for (int j = 0; j < 2; j++) {
        printf("  Inner: %d\n", j);
    }
    // j is not accessible here
}
// i is not accessible here
```

## Time Complexity
- Single loop: O(n)
- Nested loops: O(n²)
- Triple nested: O(n³)

## Best Practices
- Limit nesting to 2-3 levels maximum
- Use meaningful variable names (i, j, k)
- Consider extracting complex nested logic to functions
- Be careful with break/continue in nested loops
- Test with small inputs first

## Common Applications
- Matrix operations
- Pattern printing
- Game boards
- Sorting algorithms
- Image processing
- Graph algorithms