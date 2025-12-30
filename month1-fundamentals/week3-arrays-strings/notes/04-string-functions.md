# 04: String Functions

## Standard String Functions (string.h)

## strlen() - String Length
```c
#include <string.h>

size_t strlen(const char* str);
// Returns the length of str (excluding null terminator)

char str[] = "Hello";
size_t len = strlen(str);  // 5

// Manual implementation
size_t my_strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
```

## strcpy() - String Copy
```c
#include <string.h>

char* strcpy(char* dest, const char* src);
// Copies src to dest, returns dest

char dest[20];
strcpy(dest, "Hello World");
// dest now contains "Hello World"

// Manual implementation
char* my_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
```

## strncpy() - Bounded String Copy
```c
char* strncpy(char* dest, const char* src, size_t n);
// Copies at most n characters from src to dest

char dest[10];
strncpy(dest, "Hello World", 9);  // Copies "Hello Wor"
dest[9] = '\0';  // Ensure null termination
```

## strcat() - String Concatenation
```c
char* strcat(char* dest, const char* src);
// Appends src to dest, returns dest

char str[20] = "Hello";
strcat(str, " World");  // str becomes "Hello World"

// Manual implementation
char* my_strcat(char* dest, const char* src) {
    int dest_len = strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}
```

## strncat() - Bounded Concatenation
```c
char* strncat(char* dest, const char* src, size_t n);
// Appends at most n characters from src to dest

char str[20] = "Hello";
strncat(str, " World Program", 6);  // Appends " World"
```

## strcmp() - String Comparison
```c
int strcmp(const char* str1, const char* str2);
// Returns: 0 if equal, negative if str1 < str2, positive if str1 > str2

strcmp("apple", "apple");  // 0
strcmp("apple", "banana"); // negative
strcmp("banana", "apple"); // positive

// Manual implementation
int my_strcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}
```

## strncmp() - Bounded Comparison
```c
int strncmp(const char* str1, const char* str2, size_t n);
// Compares at most n characters

strncmp("Hello", "Help", 3);  // 0 (first 3 chars equal)
```

## strchr() - Find Character
```c
char* strchr(const char* str, int c);
// Returns pointer to first occurrence of c in str, or NULL

char str[] = "Hello World";
char* ptr = strchr(str, 'o');  // Points to first 'o'
if (ptr != NULL) {
    printf("Found at position: %ld\n", ptr - str);
}
```

## strrchr() - Find Last Character
```c
char* strrchr(const char* str, int c);
// Returns pointer to last occurrence of c in str

char str[] = "Hello World";
char* ptr = strrchr(str, 'o');  // Points to second 'o'
```

## strstr() - Find Substring
```c
char* strstr(const char* haystack, const char* needle);
// Returns pointer to first occurrence of needle in haystack

char text[] = "Hello World";
char* ptr = strstr(text, "World");  // Points to "World"
```

## strtok() - String Tokenization
```c
char* strtok(char* str, const char* delimiters);
// Splits string into tokens based on delimiters

char str[] = "apple,banana,cherry";
char* token = strtok(str, ",");
while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
}
// Output: apple, banana, cherry
```

## Memory Functions (string.h)
### memcpy() - Memory Copy
```c
void* memcpy(void* dest, const void* src, size_t n);
// Copies n bytes from src to dest

int src[] = {1, 2, 3, 4, 5};
int dest[5];
memcpy(dest, src, sizeof(src));  // Copy entire array
```

### memcmp() - Memory Comparison
```c
int memcmp(const void* ptr1, const void* ptr2, size_t n);
// Compares n bytes

int arr1[] = {1, 2, 3};
int arr2[] = {1, 2, 4};
memcmp(arr1, arr2, sizeof(arr1));  // Negative (arr1 < arr2)
```

### memset() - Memory Set
```c
void* memset(void* ptr, int value, size_t n);
// Sets n bytes starting at ptr to value

char str[10];
memset(str, 'A', 9);  // Fill with 'A's
str[9] = '\0';        // Null terminate
// str = "AAAAAAAAA"
```

## Character Functions (ctype.h)
### isalpha(), isdigit(), etc.
```c
#include <ctype.h>

char c = 'A';
isalpha(c);   // 1 (true) - alphabetic
isdigit(c);   // 0 (false) - not digit
isupper(c);   // 1 (true) - uppercase
islower(c);   // 0 (false) - not lowercase

// Case conversion
toupper('a');  // 'A'
tolower('Z');  // 'z'
```

## Common String Processing Tasks
### Count Words
```c
int count_words(char str[]) {
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace(str[i])) {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            count++;
        }
    }
    return count;
}
```

### Reverse String
```c
void reverse_string(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Usage
char str[] = "Hello";
reverse_string(str);  // "olleH"
```

### Check Palindrome
```c
int is_palindrome(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - 1 - i]) {
            return 0;
        }
    }
    return 1;
}
```

## Best Practices
- Always check return values for NULL
- Ensure destination buffers are large enough
- Use bounded functions (strncpy, strncat) to prevent overflow
- Include null terminator in buffer size calculations
- Use const for source strings when not modifying

## Common Mistakes
- Buffer overflow with strcpy/strcat
- Forgetting null termination
- Using wrong return type comparisons
- Modifying string literals
- Not checking for NULL pointers
- Off-by-one errors in buffer sizes