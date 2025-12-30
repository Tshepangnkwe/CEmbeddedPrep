# 05: While Loops

## while Loop
```c
while (condition) {
    // Loop body - executed while condition is true
}

int i = 1;
while (i <= 5) {
    printf("%d ", i);
    i++;
}
// Output: 1 2 3 4 5
```

## do-while Loop
```c
do {
    // Loop body - always executed at least once
} while (condition);

int i = 1;
do {
    printf("%d ", i);
    i++;
} while (i <= 5);
// Output: 1 2 3 4 5
```

## Key Differences
- **while**: Condition checked BEFORE execution
- **do-while**: Condition checked AFTER execution
- **do-while**: Always runs at least once

## Common Use Cases

### Input Validation
```c
int age;
printf("Enter age (1-120): ");
scanf("%d", &age);

while (age < 1 || age > 120) {
    printf("Invalid age. Enter again: ");
    scanf("%d", &age);
}
```

### Processing Unknown Amount of Data
```c
char ch;
while ((ch = getchar()) != EOF) {
    // Process character
}
```

### Game Loops
```c
int game_running = 1;
while (game_running) {
    // Game logic
    char input = get_user_input();
    if (input == 'q') {
        game_running = 0;
    }
}
```

## Loop Control

### break in while
```c
int i = 0;
while (i < 10) {
    if (i == 5) {
        break;
    }
    printf("%d ", i);
    i++;
}
// Output: 0 1 2 3 4
```

### continue in while
```c
int i = 0;
while (i < 5) {
    i++;
    if (i == 3) {
        continue;  // Skip printing 3
    }
    printf("%d ", i);
}
// Output: 1 2 4 5
```

## Infinite Loops
```c
// Common infinite loop patterns
while (1) { }           // Always true
while (true) { }        // If <stdbool.h> included
for (;;) { }            // Equivalent infinite loop
```

## Converting Between Loop Types

### for to while
```c
// for (int i = 0; i < 5; i++)
int i = 0;
while (i < 5) {
    // loop body
    i++;
}
```

### while to for
```c
// int i = 0; while (i < 5) { i++; }
for (int i = 0; i < 5; i++) {
    // loop body
}
```

## Best Practices
- Use while for unknown iterations
- Use do-while when loop must run once
- Ensure condition eventually becomes false
- Keep loop body focused
- Consider for loops for counters

## Common Mistakes
- Infinite loops (forgot to update condition)
- Off-by-one errors
- Missing braces
- Using wrong loop type for the task