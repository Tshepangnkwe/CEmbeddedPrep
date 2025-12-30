# 04: Recursion

## What is Recursion?
Recursion is when a function calls itself. It solves problems by breaking them into smaller, similar subproblems.

## Basic Structure
Every recursive function needs:
1. Base case: stops recursion
2. Recursive case: calls itself with smaller problem

```c
void recursive_function(parameters) {
    if (base_case_condition) {
        // Base case: do something simple
        return;
    } else {
        // Recursive case: call self with smaller problem
        recursive_function(smaller_parameters);
    }
}
```

## Simple Example: Factorial
```c
#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) {  // Base case
        return 1;
    } else {
        return n * factorial(n - 1);  // Recursive case
    }
}

int main() {
    printf("5! = %d\n", factorial(5));  // 120
    return 0;
}
```

## Tracing Factorial(5)
```
factorial(5) = 5 * factorial(4)
factorial(4) = 4 * factorial(3)
factorial(3) = 3 * factorial(2)
factorial(2) = 2 * factorial(1)
factorial(1) = 1
factorial(2) = 2 * 1 = 2
factorial(3) = 3 * 2 = 6
factorial(4) = 4 * 6 = 24
factorial(5) = 5 * 24 = 120
```

## Fibonacci Sequence
```c
int fibonacci(int n) {
    if (n == 0) return 0;      // Base case 1
    if (n == 1) return 1;      // Base case 2
    return fibonacci(n-1) + fibonacci(n-2);  // Recursive case
}

int main() {
    printf("Fib(6) = %d\n", fibonacci(6));  // 8
    return 0;
}
```

## Recursion vs Iteration
### Recursive Solution
```c
int sum_recursive(int n) {
    if (n == 0) return 0;
    return n + sum_recursive(n - 1);
}
```

### Iterative Solution
```c
int sum_iterative(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}
```

## Types of Recursion
### Direct Recursion
Function calls itself directly:
```c
void direct_recursion(int n) {
    if (n > 0) {
        printf("%d ", n);
        direct_recursion(n - 1);
    }
}
```

### Indirect Recursion
Function A calls function B, which calls function A:
```c
void function_a(int n) {
    if (n > 0) {
        printf("A: %d\n", n);
        function_b(n - 1);
    }
}

void function_b(int n) {
    if (n > 0) {
        printf("B: %d\n", n);
        function_a(n - 1);
    }
}
```

### Tail Recursion
Recursive call is the last operation:
```c
void tail_recursion(int n) {
    if (n > 0) {
        printf("%d ", n);
        tail_recursion(n - 1);  // Last operation
    }
}
```

### Head Recursion
Recursive call is the first operation:
```c
void head_recursion(int n) {
    if (n > 0) {
        head_recursion(n - 1);  // First operation
        printf("%d ", n);
    }
}
```

## Common Problems Solved with Recursion
### Tree Traversal
```c
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
```

### Tower of Hanoi
```c
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    hanoi(n-1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    hanoi(n-1, aux, to, from);
}
```

## Recursion Limitations
### Stack Overflow
Each recursive call uses stack space:
```c
void infinite_recursion() {
    infinite_recursion();  // Stack overflow!
}
```

### Maximum Recursion Depth
Depends on system, typically 1000-10000 calls.

## Best Practices
- Always have a base case
- Ensure progress toward base case
- Consider stack space limits
- Use iteration when possible for deep recursion
- Tail recursion can be optimized by compilers

## Common Mistakes
- Missing base case (infinite recursion)
- Wrong base case condition
- Not reducing problem size properly
- Stack overflow in deep recursion
- Forgetting return values in recursive functions