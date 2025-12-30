# 01: Variables and Data Types

## Variables
Variables are named storage locations in memory that hold data values.

### Declaration
```c
int age;           // Declaration
int age = 25;      // Declaration with initialization
```

### Naming Rules
- Start with letter or underscore
- Contain letters, digits, underscores
- Case sensitive
- No reserved keywords

## Data Types

### Integer Types
```c
char    c = 'A';     // 1 byte, -128 to 127 (signed) or 0-255 (unsigned)
short   s = 100;     // 2 bytes, -32,768 to 32,767
int     i = 42;      // 4 bytes (typically), platform dependent
long    l = 123456;  // 4-8 bytes, depends on system
```

### Floating Point
```c
float   f = 3.14f;   // 4 bytes, ~6-7 decimal digits
double  d = 3.14159; // 8 bytes, ~15 decimal digits
```

### Qualifiers
```c
signed int x;     // Explicitly signed (default for int)
unsigned int y;   // Only positive values
const int z = 5;  // Cannot be modified
```

## Type Conversion

### Implicit (Automatic)
```c
int i = 5;
double d = i;  // int promoted to double
```

### Explicit (Casting)
```c
double d = 3.14;
int i = (int)d;  // Truncates to 3
```

## sizeof Operator
```c
printf("Size of int: %zu bytes\n", sizeof(int));
printf("Size of double: %zu bytes\n", sizeof(double));
```

## Best Practices
- Use meaningful variable names
- Initialize variables before use
- Choose appropriate data types for memory efficiency
- Use const for values that shouldn't change

## Common Mistakes
- Using uninitialized variables
- Integer overflow
- Type mismatch in assignments