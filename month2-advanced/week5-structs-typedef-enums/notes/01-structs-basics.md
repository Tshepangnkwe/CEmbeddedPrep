# 01: Structs Basics

## What is a Struct?
A struct is a user-defined data type that groups related variables of different types together.

## Defining Structs
### Basic Syntax
```c
struct Person {
    char name[50];
    int age;
    float height;
};
```

### Creating Struct Variables
```c
// Method 1: Declare and define separately
struct Person person1;

// Method 2: Declare with initialization
struct Person person2 = {"Alice", 25, 5.6};

// Method 3: Designated initializers (C99)
struct Person person3 = {
    .name = "Bob",
    .age = 30,
    .height = 5.8
};
```

## Accessing Struct Members
### Using Dot Operator
```c
struct Person p = {"Charlie", 35, 5.9};

printf("Name: %s\n", p.name);
printf("Age: %d\n", p.age);
printf("Height: %.1f\n", p.height);

// Modify members
p.age = 36;
strcpy(p.name, "Charles");
```

## Struct Size and Memory Layout
```c
struct Example {
    char c;      // 1 byte
    int i;       // 4 bytes
    char c2;     // 1 byte
};

printf("Size: %zu bytes\n", sizeof(struct Example));
// Output: 12 bytes (due to padding)
```

### Memory Alignment
- Struct members are aligned to memory boundaries
- Padding bytes are added for efficient access
- Total size may be larger than sum of member sizes

## Nested Structs
```c
struct Address {
    char street[50];
    char city[30];
    int zip_code;
};

struct Person {
    char name[50];
    int age;
    struct Address address;
};

// Usage
struct Person p = {
    "Alice",
    25,
    {"123 Main St", "Anytown", 12345}
};

printf("City: %s\n", p.address.city);
```

## Arrays of Structs
```c
struct Student {
    char name[50];
    int id;
    float gpa;
};

struct Student class[30];  // Array of 30 students

// Initialize
class[0] = (struct Student){"Alice", 1001, 3.8};
class[1] = (struct Student){"Bob", 1002, 3.5};

// Access
for (int i = 0; i < 2; i++) {
    printf("Student %d: %s (ID: %d, GPA: %.1f)\n",
           i+1, class[i].name, class[i].id, class[i].gpa);
}
```

## Struct Assignment
```c
struct Point {
    int x, y;
};

struct Point p1 = {10, 20};
struct Point p2;

// Struct assignment (copies all members)
p2 = p1;

printf("p2.x = %d, p2.y = %d\n", p2.x, p2.y);  // 10, 20
```

## Structs in Functions
### Pass by Value
```c
void print_person(struct Person p) {
    printf("Name: %s, Age: %d\n", p.name, p.age);
    // Modifying p here doesn't affect original
}

int main() {
    struct Person p = {"Alice", 25};
    print_person(p);  // Passes copy
}
```

### Pass by Reference
```c
void update_age(struct Person* p, int new_age) {
    p->age = new_age;  // Modifies original
}

int main() {
    struct Person p = {"Alice", 25};
    update_age(&p, 26);
    printf("New age: %d\n", p.age);  // 26
}
```

## The Arrow Operator (->)
Used to access members of struct pointers:
```c
struct Person* p_ptr = &person;

// Equivalent to (*p_ptr).age
p_ptr->age = 30;

// Also equivalent to:
(*p_ptr).age = 30;
```

## Incomplete Struct Declarations
```c
// Forward declaration
struct Node;

// Now we can use pointers to Node
struct List {
    int data;
    struct Node* next;
};

// Complete definition
struct Node {
    int data;
    struct Node* next;
};
```

## Best Practices
- Use meaningful names for structs and members
- Initialize structs when declaring
- Use const for structs that shouldn't be modified
- Prefer pass by reference for large structs
- Document struct purposes and member meanings
- Consider padding when memory is critical

## Common Mistakes
- Forgetting struct keyword in declarations
- Using dot operator on pointers (use arrow instead)
- Not accounting for struct padding in memory calculations
- Modifying structs passed by value (won't affect original)
- Circular dependencies without forward declarations
- Assuming struct size equals sum of member sizes