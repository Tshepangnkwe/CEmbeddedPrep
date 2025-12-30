# 02: Operators

## Arithmetic Operators
```c
int a = 10, b = 3;
int sum = a + b;      // 13
int diff = a - b;     // 7
int prod = a * b;     // 30
int quot = a / b;     // 3 (integer division)
int rem = a % b;      // 1 (modulo)
```

## Assignment Operators
```c
int x = 5;    // Simple assignment
x += 3;       // x = x + 3 → 8
x -= 2;       // x = x - 2 → 6
x *= 4;       // x = x * 4 → 24
x /= 2;       // x = x / 2 → 12
x %= 5;       // x = x % 5 → 2
```

## Comparison Operators
```c
// Return 1 (true) or 0 (false)
int result;
result = (5 == 5);    // 1 (equal to)
result = (5 != 3);    // 1 (not equal to)
result = (5 > 3);     // 1 (greater than)
result = (5 < 3);     // 0 (less than)
result = (5 >= 5);    // 1 (greater than or equal)
result = (5 <= 3);    // 0 (less than or equal)
```

## Logical Operators
```c
int a = 1, b = 0;
int result;

result = a && b;      // 0 (AND: both true → true)
result = a || b;      // 1 (OR: either true → true)
result = !a;          // 0 (NOT: invert)
```

## Increment/Decrement
```c
int x = 5;
int y = x++;    // y = 5, x = 6 (post-increment)
int z = ++x;    // z = 7, x = 7 (pre-increment)

x = 5;
y = x--;        // y = 5, x = 4 (post-decrement)
z = --x;        // z = 3, x = 3 (pre-decrement)
```

## Bitwise Operators
```c
int a = 5;  // 0101 in binary
int b = 3;  // 0011 in binary

int and = a & b;   // 0001 (1) - AND
int or = a | b;    // 0111 (7) - OR
int xor = a ^ b;   // 0110 (6) - XOR
int not = ~a;      // Inverts all bits
int left = a << 1; // 1010 (10) - Left shift
int right = a >> 1;// 0010 (2) - Right shift
```

## Operator Precedence
1. `()` (parentheses)
2. `++ --` (postfix)
3. `++ -- ! ~` (prefix)
4. `* / %` (multiplicative)
5. `+ -` (additive)
6. `<< >>` (bitwise shift)
7. `< <= > >=` (relational)
8. `== !=` (equality)
9. `&` (bitwise AND)
10. `^` (bitwise XOR)
11. `|` (bitwise OR)
12. `&&` (logical AND)
13. `||` (logical OR)
14. `?:` (conditional)
15. `= += -= *= /= %=` (assignment)

## Common Pitfalls
- Division by zero
- Integer overflow
- Operator precedence confusion
- Mixing signed/unsigned types