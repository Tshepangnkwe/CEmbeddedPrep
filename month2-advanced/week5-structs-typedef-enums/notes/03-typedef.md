# 03: Typedef

## What is Typedef?
Typedef creates an alias for existing data types, making code more readable and maintainable.

## Basic Typedef Syntax
```c
typedef existing_type new_type_name;
```

## Simple Type Aliases
```c
// Basic types
typedef int Age;
typedef float Temperature;
typedef char* String;

// Usage
Age person_age = 25;
Temperature room_temp = 22.5;
String name = "Alice";

printf("Age: %d, Temp: %.1f, Name: %s\n", person_age, room_temp, name);
```

## Struct Typedef
### Method 1: Separate typedef
```c
struct Person {
    char name[50];
    int age;
    float height;
};

typedef struct Person Person_t;

// Now we can use Person_t instead of struct Person
Person_t person1 = {"Alice", 25, 5.6};
```

### Method 2: Combined typedef
```c
typedef struct {
    char name[50];
    int age;
    float height;
} Person_t;

// Anonymous struct with typedef
Person_t person1 = {"Bob", 30, 5.8};
```

### Method 3: Self-referential typedef
```c
typedef struct Node {
    int data;
    struct Node* next;  // Still need struct Node here
} Node_t;

// Usage
Node_t* head = (Node_t*)malloc(sizeof(Node_t));
head->data = 10;
head->next = NULL;
```

## Function Pointer Typedef
```c
// Without typedef
int (*operation)(int, int);

// With typedef
typedef int (*OperationFunc)(int, int);

// Usage
OperationFunc add = &some_add_function;
OperationFunc multiply = &some_multiply_function;

int result = add(5, 3);  // 8
```

## Array Typedef
```c
typedef int IntArray[10];
typedef char String[50];

// Usage
IntArray numbers = {1, 2, 3, 4, 5};
String name = "Hello";

printf("First number: %d\n", numbers[0]);
printf("Name: %s\n", name);
```

## Complex Typedef Examples
### Callback System
```c
typedef void (*CallbackFunc)(void* data);

typedef struct {
    char event_name[50];
    CallbackFunc callback;
    void* user_data;
} EventHandler;

void button_click_handler(void* data) {
    printf("Button clicked! Data: %s\n", (char*)data);
}

int main() {
    EventHandler handler = {
        "button_click",
        button_click_handler,
        "Button 1"
    };

    // Simulate event
    handler.callback(handler.user_data);
}
```

### State Machine
```c
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR
} State_t;

typedef struct {
    State_t current_state;
    int data;
} StateMachine_t;

typedef State_t (*StateTransitionFunc)(StateMachine_t*);

typedef struct {
    State_t from_state;
    StateTransitionFunc transition;
} Transition_t;
```

## Typedef for Portability
```c
// Platform-independent types
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;

// Usage in embedded systems
uint8_t port_value;
int16_t sensor_reading;
```

## Typedef Best Practices
### Naming Conventions
```c
// Use _t suffix for typedef names
typedef struct {
    int x, y;
} Point_t;

typedef int (*CompareFunc_t)(const void*, const void*);

// Avoid generic names
typedef int Integer;  // Too generic, not recommended
```

### When to Use Typedef
- For complex types (function pointers, structs)
- To hide implementation details
- For platform abstraction
- To improve code readability
- For self-documenting code

### When NOT to Use Typedef
- For simple types (int, char)
- When it obscures meaning
- For every struct (sometimes struct keyword is clearer)

## Advanced Typedef Patterns
### Opaque Types
```c
// In header file (.h)
typedef struct Database Database_t;

// Client code only sees the typedef
Database_t* db_create();
void db_destroy(Database_t* db);
int db_insert(Database_t* db, int data);

// In implementation file (.c)
struct Database {
    int* data;
    size_t size;
    size_t capacity;
};

Database_t* db_create() {
    return (Database_t*)malloc(sizeof(struct Database));
}
```

### Generic Containers
```c
typedef void* GenericData_t;

typedef struct {
    GenericData_t data;
    size_t size;
} Container_t;

typedef void (*CleanupFunc_t)(GenericData_t);

void container_destroy(Container_t* container, CleanupFunc_t cleanup) {
    if (cleanup && container->data) {
        cleanup(container->data);
    }
    free(container);
}
```

## Common Mistakes
### Multiple typedef of same type
```c
typedef int Length;
typedef int Size;  // OK, but confusing

Length len = 10;
Size sz = 20;
// Both are int, but different semantics
```

### Hiding pointers
```c
typedef int* IntPtr;

// This can be confusing
IntPtr ptr1, ptr2;  // ptr1 is int*, ptr2 is int* - OK

// But this looks like both are pointers:
typedef int* IntPtr;
IntPtr a, b;  // Both are int* - clear
```

### Overusing typedef
```c
typedef int my_int;     // Unnecessary
typedef char* my_string; // Questionable

// Better to use directly:
int counter;
char* name;
```

## Best Practices Summary
- Use typedef for complex types and improved readability
- Follow consistent naming conventions (_t suffix)
- Don't hide simple types unnecessarily
- Document typedef purposes
- Consider code maintainability
- Use typedef for API stability (opaque types)