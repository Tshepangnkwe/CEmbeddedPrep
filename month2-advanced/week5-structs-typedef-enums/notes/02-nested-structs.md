# 02: Nested Structs

## What are Nested Structs?
Nested structs are structs that contain other structs as members, allowing complex data hierarchies.

## Basic Nested Structs
```c
struct Address {
    char street[50];
    char city[30];
    char state[3];
    int zip_code;
};

struct Person {
    char name[50];
    int age;
    struct Address home_address;
    struct Address work_address;
};

// Usage
struct Person employee = {
    "John Doe",
    30,
    {"123 Main St", "Anytown", "CA", 12345},    // home
    {"456 Office Blvd", "Business City", "CA", 67890}  // work
};

printf("Home city: %s\n", employee.home_address.city);
printf("Work zip: %d\n", employee.work_address.zip_code);
```

## Deep Nesting
```c
struct Date {
    int day, month, year;
};

struct Time {
    int hour, minute, second;
};

struct Event {
    char title[100];
    struct Date date;
    struct Time start_time;
    struct Time end_time;
    char location[50];
};

// Initialization
struct Event meeting = {
    "Team Standup",
    {15, 3, 2024},        // date
    {9, 0, 0},           // start_time
    {9, 30, 0},          // end_time
    "Conference Room A"
};

printf("Event: %s on %d/%d/%d at %d:%02d\n",
       meeting.title,
       meeting.date.month, meeting.date.day, meeting.date.year,
       meeting.start_time.hour, meeting.start_time.minute);
```

## Arrays of Nested Structs
```c
struct Student {
    char name[50];
    int id;
    struct {
        int math, science, english;
    } grades;  // Anonymous nested struct
};

struct Student class[] = {
    {"Alice", 1001, {85, 92, 88}},
    {"Bob", 1002, {78, 85, 90}},
    {"Charlie", 1003, {92, 88, 95}}
};

// Calculate averages
for (int i = 0; i < 3; i++) {
    int avg = (class[i].grades.math +
               class[i].grades.science +
               class[i].grades.english) / 3;
    printf("%s: Average = %d\n", class[i].name, avg);
}
```

## Pointers to Nested Structs
```c
struct Company {
    char name[50];
    struct {
        char street[50];
        char city[30];
        int zip;
    } address;
};

void print_company(struct Company* comp) {
    printf("Company: %s\n", comp->name);
    printf("Address: %s, %s %d\n",
           comp->address.street,
           comp->address.city,
           comp->address.zip);
}

int main() {
    struct Company google = {
        "Google",
        {"1600 Amphitheatre Parkway", "Mountain View", 94043}
    };

    print_company(&google);
}
```

## Linked Data Structures
### Simple Linked List
```c
struct Node {
    int data;
    struct Node* next;
};

// Create nodes
struct Node* head = (struct Node*)malloc(sizeof(struct Node));
head->data = 10;
head->next = (struct Node*)malloc(sizeof(struct Node));
head->next->data = 20;
head->next->next = NULL;

// Traverse
struct Node* current = head;
while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
}

// Free memory
current = head;
while (current != NULL) {
    struct Node* temp = current;
    current = current->next;
    free(temp);
}
```

### Binary Tree
```c
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* create_node(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void inorder_traversal(struct TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

int main() {
    struct TreeNode* root = create_node(10);
    root->left = create_node(5);
    root->right = create_node(15);

    inorder_traversal(root);  // 5 10 15
}
```

## Self-Referential Structs
```c
struct Employee {
    char name[50];
    int id;
    struct Employee* manager;  // Points to another Employee
    struct Employee* subordinates[10];  // Array of pointers
    int sub_count;
};

struct Employee* create_employee(char* name, int id) {
    struct Employee* emp = (struct Employee*)malloc(sizeof(struct Employee));
    strcpy(emp->name, name);
    emp->id = id;
    emp->manager = NULL;
    emp->sub_count = 0;
    return emp;
}
```

## Flexible Array Members (C99)
```c
struct String {
    size_t length;
    char data[];  // Flexible array member
};

struct String* create_string(const char* str) {
    size_t len = strlen(str);
    struct String* s = (struct String*)malloc(sizeof(struct String) + len + 1);
    s->length = len;
    strcpy(s->data, str);
    return s;
}

int main() {
    struct String* str = create_string("Hello World");
    printf("Length: %zu, Content: %s\n", str->length, str->data);
    free(str);
}
```

## Best Practices
- Use meaningful names for nested structs
- Consider memory layout and padding
- Initialize nested structs properly
- Use pointers for optional or variable-sized nested data
- Document the structure hierarchy
- Be careful with deep nesting (can become complex)

## Common Mistakes
- Forgetting to initialize nested structs
- Incorrect nesting levels in initialization
- Memory leaks in linked structures
- Circular references causing infinite loops
- Not accounting for pointer validity in nested structures
- Assuming nested structs are contiguous in memory