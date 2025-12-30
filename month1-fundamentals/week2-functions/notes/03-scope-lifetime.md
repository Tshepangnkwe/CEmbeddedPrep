# 03: Scope and Lifetime

## Variable Scope
Scope determines where a variable can be accessed in the program.

### Global Scope
Variables declared outside all functions are global:
```c
#include <stdio.h>

int global_var = 10;  // Global variable

void func() {
    printf("%d\n", global_var);  // Accessible
}

int main() {
    printf("%d\n", global_var);  // Accessible
    func();
    return 0;
}
```

### Local Scope
Variables declared inside functions are local:
```c
void func() {
    int local_var = 5;  // Local to func
    printf("%d\n", local_var);
}

int main() {
    // printf("%d\n", local_var);  // Error: local_var not accessible
    return 0;
}
```

### Block Scope
Variables declared inside blocks (between {}) have block scope:
```c
int main() {
    int x = 10;

    if (x > 5) {
        int y = 20;  // Block scope
        printf("%d %d\n", x, y);  // OK
    }

    // printf("%d\n", y);  // Error: y not accessible
    return 0;
}
```

## Variable Lifetime
Lifetime determines how long a variable exists in memory.

### Static Lifetime
- Global variables: exist for entire program
- Static local variables: exist for entire program but accessible only in function

```c
void counter() {
    static int count = 0;  // Initialized once
    count++;
    printf("Count: %d\n", count);
}

int main() {
    counter();  // Count: 1
    counter();  // Count: 2
    counter();  // Count: 3
    return 0;
}
```

### Automatic Lifetime
Local variables without `static` have automatic lifetime:
```c
void func() {
    int auto_var = 10;  // Created when func called
    // ... use auto_var ...
}  // auto_var destroyed when func returns

int main() {
    func();  // auto_var created and destroyed
    func();  // auto_var created again
    return 0;
}
```

## Storage Classes
### auto
- Default for local variables
- Automatic lifetime
- Local scope

```c
int main() {
    auto int x = 5;  // Same as: int x = 5;
    return 0;
}
```

### static
- Preserves value between function calls
- Internal linkage for global static
- External linkage for global non-static

```c
// File scope static
static int file_var = 10;  // Only accessible in this file

void func() {
    static int count = 0;  // Function scope static
    count++;
    printf("%d\n", count);
}
```

### extern
- Declares variable defined elsewhere
- Used for global variables across files

```c
// file1.c
int global_var = 100;

// file2.c
extern int global_var;  // Declaration, not definition

void func() {
    printf("%d\n", global_var);
}
```

### register
- Hint to compiler to store in register
- Faster access but limited
- Cannot take address

```c
void func() {
    register int fast_var = 5;
    // int* ptr = &fast_var;  // Error: cannot take address
}
```

## Scope Rules
### Shadowing
Inner scope variables can shadow outer scope:
```c
int x = 10;

int main() {
    int x = 20;  // Shadows global x
    printf("%d\n", x);  // Prints 20

    {
        int x = 30;  // Shadows local x
        printf("%d\n", x);  // Prints 30
    }

    printf("%d\n", x);  // Prints 20
    return 0;
}
```

### No Cross-Function Access
Functions cannot access each other's local variables:
```c
void func1() {
    int a = 5;
}

void func2() {
    // printf("%d\n", a);  // Error: a not accessible
}
```

## Best Practices
- Minimize global variables
- Use static for variables that need to persist
- Declare variables in smallest possible scope
- Use meaningful names to avoid shadowing
- Initialize static variables to zero if needed

## Common Mistakes
- Using global variables when local would work
- Forgetting static variables retain values
- Shadowing important variables
- Trying to access variables outside scope
- Not initializing static variables properly