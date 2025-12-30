# 05: Pointers and Strings

## Strings as Character Arrays
Strings in C are arrays of characters terminated by null character ('\0').

## String Pointers
### Pointer to String Literal
```c
char* str_ptr = "Hello World";
// str_ptr points to read-only memory

printf("%s\n", str_ptr);     // "Hello World"
printf("%c\n", str_ptr[0]);  // 'H'
printf("%c\n", *str_ptr);    // 'H'
```

### Modifying String Literals (Dangerous)
```c
char* str = "Hello";
// str[0] = 'h';  // UNDEFINED BEHAVIOR!
// String literals are read-only
```

### Safe String Handling
```c
// Method 1: Character array
char str[] = "Hello";
str[0] = 'h';  // OK - modifiable
printf("%s\n", str);  // "hello"

// Method 2: Dynamic allocation
char* dynamic_str = (char*)malloc(6 * sizeof(char));
strcpy(dynamic_str, "Hello");
dynamic_str[0] = 'h';
printf("%s\n", dynamic_str);  // "hello"
free(dynamic_str);
```

## String Functions with Pointers
### Manual String Copy
```c
char* my_strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while ((*dest++ = *src++) != '\0') {
        // Copy character and advance pointers
    }
    return original_dest;
}

// Usage
char dest[20];
my_strcpy(dest, "Hello World");
printf("%s\n", dest);
```

### Manual String Length
```c
size_t my_strlen(const char* str) {
    const char* start = str;
    while (*str != '\0') {
        str++;
    }
    return str - start;
}

// Usage
printf("Length: %zu\n", my_strlen("Hello"));  // 5
```

### Manual String Comparison
```c
int my_strcmp(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// Usage
printf("Compare: %d\n", my_strcmp("apple", "banana"));  // negative
```

## Array of Strings
### Using Array of Pointers
```c
char* fruits[] = {
    "apple",
    "banana",
    "cherry",
    NULL  // Sentinel value
};

// Print all fruits
for (int i = 0; fruits[i] != NULL; i++) {
    printf("%s\n", fruits[i]);
}
```

### Dynamic Array of Strings
```c
char** create_string_array(int count) {
    char** arr = (char**)malloc(count * sizeof(char*));
    for (int i = 0; i < count; i++) {
        arr[i] = (char*)malloc(50 * sizeof(char));  // Max 49 chars + null
    }
    return arr;
}

void free_string_array(char** arr, int count) {
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

// Usage
char** names = create_string_array(3);
strcpy(names[0], "Alice");
strcpy(names[1], "Bob");
strcpy(names[2], "Charlie");

// Use names...

free_string_array(names, 3);
```

## String Tokenization
### Using Pointers
```c
char* my_strtok(char* str, const char* delimiters) {
    static char* next_token = NULL;

    if (str != NULL) {
        next_token = str;
    }

    if (next_token == NULL) {
        return NULL;
    }

    // Skip leading delimiters
    while (*next_token != '\0' && strchr(delimiters, *next_token) != NULL) {
        next_token++;
    }

    if (*next_token == '\0') {
        return NULL;
    }

    char* token_start = next_token;

    // Find end of token
    while (*next_token != '\0' && strchr(delimiters, *next_token) == NULL) {
        next_token++;
    }

    if (*next_token != '\0') {
        *next_token++ = '\0';  // Null terminate token
    }

    return token_start;
}

// Usage
char str[] = "apple,banana,cherry";
char* token = my_strtok(str, ",");
while (token != NULL) {
    printf("%s\n", token);
    token = my_strtok(NULL, ",");
}
```

## Command Line Arguments
### Using Pointers
```c
int main(int argc, char* argv[]) {
    // argc: argument count
    // argv: array of string pointers

    printf("Program name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc - 1);

    for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}

// Command: ./program hello world 123
// Output:
// Program name: ./program
// Number of arguments: 3
// Argument 1: hello
// Argument 2: world
// Argument 3: 123
```

## String Manipulation Patterns
### Reverse String
```c
void reverse_string(char* str) {
    if (str == NULL) return;

    char* end = str;
    while (*end != '\0') {
        end++;
    }
    end--;  // Point to last character

    while (str < end) {
        char temp = *str;
        *str = *end;
        *end = temp;
        str++;
        end--;
    }
}

// Usage
char str[] = "Hello";
reverse_string(str);
printf("%s\n", str);  // "olleH"
```

### Remove Character
```c
void remove_char(char* str, char target) {
    char* src = str;
    char* dst = str;

    while (*src != '\0') {
        if (*src != target) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

// Usage
char str[] = "Hello World";
remove_char(str, 'l');
printf("%s\n", str);  // "Heo Word"
```

### Count Words
```c
int count_words(const char* str) {
    int count = 0;
    int in_word = 0;

    while (*str != '\0') {
        if (*str == ' ' || *str == '\t' || *str == '\n') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

// Usage
printf("Words: %d\n", count_words("Hello world from C"));
```

## Best Practices
- Always ensure strings are null-terminated
- Use const for string parameters that shouldn't be modified
- Check for NULL pointers before string operations
- Be careful with string literal modification
- Free dynamically allocated strings
- Use bounded string functions to prevent buffer overflow

## Common Mistakes
- Forgetting null terminator
- Buffer overflow in string operations
- Modifying read-only string literals
- Memory leaks from not freeing dynamic strings
- Off-by-one errors in string indexing
- Confusing character pointers with character arrays