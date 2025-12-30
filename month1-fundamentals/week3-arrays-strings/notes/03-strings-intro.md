# 03: Strings Introduction

## What are Strings in C?
Strings in C are arrays of characters terminated by a null character ('\0').

## String Declaration and Initialization
### Character Arrays
```c
// Method 1: Character array with null terminator
char str1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};

// Method 2: String literal (automatic null terminator)
char str2[] = "Hello";

// Method 3: Fixed size with string literal
char str3[20] = "Hello World";

// Method 4: Partial initialization
char str4[10] = "Hi";  // {'H', 'i', '\0', '\0', ...}
```

## String Literals
```c
// String literals are stored in read-only memory
char* ptr = "Hello World";  // Pointer to string literal

// This is dangerous - modifying read-only memory
// ptr[0] = 'h';  // Undefined behavior!

// Safe way: copy to modifiable array
char str[20];
strcpy(str, "Hello World");
str[0] = 'h';  // OK
```

## Accessing String Characters
```c
char str[] = "Hello";

printf("%c\n", str[0]);  // 'H'
printf("%c\n", str[4]);  // 'o'

// Last character (null terminator)
printf("%c\n", str[5]);  // '\0' (null character)
printf("%d\n", str[5]);  // 0 (ASCII value)
```

## String Length
### Manual Length Calculation
```c
int string_length(char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Usage
char str[] = "Hello";
printf("Length: %d\n", string_length(str));  // 5
```

### Using strlen() from string.h
```c
#include <string.h>

char str[] = "Hello World";
size_t length = strlen(str);  // 11
```

## Printing Strings
### Using printf
```c
char name[] = "Alice";
printf("Hello, %s!\n", name);

// Print with width
printf("Name: %-10s Age: %d\n", name, 25);
```

### Character by Character
```c
void print_string(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}
```

## String Input
### Using scanf
```c
char name[50];
printf("Enter your name: ");
scanf("%s", name);  // Reads until whitespace
printf("Hello, %s!\n", name);
```

### Reading Full Lines
```c
#include <stdio.h>

char line[100];
printf("Enter a line: ");
fgets(line, sizeof(line), stdin);  // Reads entire line
printf("You entered: %s", line);
```

### scanf with Width Limit
```c
char name[20];
scanf("%19s", name);  // Prevents buffer overflow
```

## String Modification
### Changing Characters
```c
char str[] = "Hello";
str[0] = 'h';  // "hello"
str[1] = 'E';  // "hEllo"
```

### Building Strings Character by Character
```c
char result[10];
int index = 0;

result[index++] = 'H';
result[index++] = 'i';
result[index++] = '!';
result[index] = '\0';  // Don't forget null terminator!

printf("%s\n", result);  // "Hi!"
```

## Common String Patterns
### Counting Characters
```c
int count_char(char str[], char target) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == target) {
            count++;
        }
    }
    return count;
}

// Usage
char str[] = "Hello World";
printf("Spaces: %d\n", count_char(str, ' '));  // 1
printf("l's: %d\n", count_char(str, 'l'));     // 3
```

### Converting Case
```c
void to_uppercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;  // 'a' - 'A' = 32
        }
    }
}

void to_lowercase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}
```

## String Comparison
### Manual Comparison
```c
int string_compare(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

// Usage
char s1[] = "apple";
char s2[] = "banana";
int result = string_compare(s1, s2);
if (result < 0) {
    printf("s1 < s2\n");
} else if (result > 0) {
    printf("s1 > s2\n");
} else {
    printf("s1 == s2\n");
}
```

### Using strcmp() from string.h
```c
#include <string.h>

int result = strcmp(str1, str2);
if (result == 0) {
    // Strings are equal
} else if (result < 0) {
    // str1 < str2
} else {
    // str1 > str2
}
```

## String Copying
### Manual Copy
```c
void string_copy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // Don't forget null terminator
}

// Usage
char original[] = "Hello";
char copy[20];
string_copy(copy, original);
```

### Using strcpy() from string.h
```c
#include <string.h>

char dest[20];
strcpy(dest, "Hello World");  // Copies string and null terminator
```

## Best Practices
- Always ensure space for null terminator
- Use string.h functions when possible
- Check array bounds to prevent overflow
- Initialize strings when declaring
- Use meaningful variable names

## Common Mistakes
- Forgetting null terminator
- Buffer overflow when copying strings
- Using scanf without width specifier
- Modifying string literals
- Off-by-one errors in string operations
- Confusing characters and strings