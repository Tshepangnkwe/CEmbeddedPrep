# 03: Conditionals

## if Statement
```c
if (condition) {
    // Code executed if condition is true
}

int age = 20;
if (age >= 18) {
    printf("You are an adult\n");
}
```

## if-else Statement
```c
if (condition) {
    // True block
} else {
    // False block
}

int score = 85;
if (score >= 90) {
    printf("Grade: A\n");
} else {
    printf("Grade: Not A\n");
}
```

## if-else if-else Chain
```c
if (condition1) {
    // Block 1
} else if (condition2) {
    // Block 2
} else {
    // Default block
}

int score = 75;
if (score >= 90) {
    printf("A\n");
} else if (score >= 80) {
    printf("B\n");
} else if (score >= 70) {
    printf("C\n");
} else {
    printf("F\n");
}
```

## Nested if Statements
```c
if (condition1) {
    if (condition2) {
        // Both conditions true
    }
}

int age = 25;
char gender = 'M';
if (age >= 18) {
    if (gender == 'M') {
        printf("Adult male\n");
    } else {
        printf("Adult female\n");
    }
}
```

## switch Statement
```c
switch (expression) {
    case value1:
        // Code for value1
        break;
    case value2:
        // Code for value2
        break;
    default:
        // Default case
        break;
}

int day = 3;
switch (day) {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    default:
        printf("Other day\n");
        break;
}
```

## Ternary Operator
```c
// condition ? true_expression : false_expression
int max = (a > b) ? a : b;

int x = 5, y = 10;
int larger = (x > y) ? x : y;  // larger = 10
```

## Truthy/Falsy Values
- **False**: 0, NULL, '\0'
- **True**: Any non-zero value

## Best Practices
- Use braces even for single statements
- Keep conditions simple and readable
- Use switch for multiple discrete values
- Consider ternary for simple assignments
- Avoid deep nesting when possible

## Common Mistakes
- Forgetting break in switch
- Assignment (=) instead of comparison (==)
- Missing braces causing logic errors
- Complex conditions in if statements