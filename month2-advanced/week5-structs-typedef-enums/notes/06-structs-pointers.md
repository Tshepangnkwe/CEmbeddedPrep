# 06: Structs and Pointers

## Pointers to Structs
```c
typedef struct {
    char name[50];
    int age;
    float salary;
} Employee_t;

// Pointer to struct
Employee_t* emp_ptr;

// Allocate memory
emp_ptr = (Employee_t*)malloc(sizeof(Employee_t));

// Initialize
strcpy(emp_ptr->name, "Alice");
emp_ptr->age = 30;
emp_ptr->salary = 50000.0;

// Access members
printf("Name: %s, Age: %d, Salary: %.2f\n",
       emp_ptr->name, emp_ptr->age, emp_ptr->salary);

// Free memory
free(emp_ptr);
emp_ptr = NULL;
```

## Arrow Operator (->)
The arrow operator accesses struct members through pointers:
```c
struct Point {
    int x, y;
};

struct Point* p = (struct Point*)malloc(sizeof(struct Point));
p->x = 10;  // Equivalent to (*p).x = 10;
p->y = 20;  // Equivalent to (*p).y = 20;

printf("Point: (%d, %d)\n", p->x, p->y);

free(p);
```

## Structs Containing Pointers
```c
typedef struct {
    char* name;
    int* scores;
    int num_scores;
} Student_t;

Student_t* create_student(const char* name, int num_scores) {
    Student_t* student = (Student_t*)malloc(sizeof(Student_t));

    // Allocate and copy name
    student->name = (char*)malloc(strlen(name) + 1);
    strcpy(student->name, name);

    // Allocate scores array
    student->scores = (int*)malloc(num_scores * sizeof(int));
    student->num_scores = num_scores;

    return student;
}

void destroy_student(Student_t* student) {
    free(student->name);
    free(student->scores);
    free(student);
}

int main() {
    Student_t* alice = create_student("Alice", 3);
    alice->scores[0] = 85;
    alice->scores[1] = 92;
    alice->scores[2] = 88;

    printf("%s's average: %.1f\n", alice->name,
           (alice->scores[0] + alice->scores[1] + alice->scores[2]) / 3.0);

    destroy_student(alice);
}
```

## Arrays of Struct Pointers
```c
typedef struct {
    char title[100];
    char author[50];
    int year;
} Book_t;

Book_t** create_library(int capacity) {
    Book_t** library = (Book_t**)malloc(capacity * sizeof(Book_t*));
    for (int i = 0; i < capacity; i++) {
        library[i] = NULL;  // Initialize to NULL
    }
    return library;
}

void add_book(Book_t** library, int index, const char* title,
              const char* author, int year) {
    library[index] = (Book_t*)malloc(sizeof(Book_t));
    strcpy(library[index]->title, title);
    strcpy(library[index]->author, author);
    library[index]->year = year;
}

void print_library(Book_t** library, int size) {
    for (int i = 0; i < size; i++) {
        if (library[i] != NULL) {
            printf("%s by %s (%d)\n",
                   library[i]->title,
                   library[i]->author,
                   library[i]->year);
        }
    }
}
```

## Linked Lists with Struct Pointers
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node_t;

Node_t* create_node(int data) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->data = data;
    node->next = NULL;
    return node;
}

void append_node(Node_t** head, int data) {
    Node_t* new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node_t* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void print_list(Node_t* head) {
    Node_t* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node_t* head) {
    Node_t* current = head;
    while (current != NULL) {
        Node_t* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node_t* head = NULL;

    append_node(&head, 10);
    append_node(&head, 20);
    append_node(&head, 30);

    print_list(head);  // 10 20 30

    free_list(head);
}
```

## Function Pointers in Structs
```c
typedef struct {
    char name[50];
    int (*compare)(const void*, const void*);  // Comparison function
    void (*print)(const void*);                // Print function
} Comparator_t;

int int_compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

void int_print(const void* data) {
    printf("%d", *(int*)data);
}

int str_compare(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

void str_print(const void* data) {
    printf("%s", *(char**)data);
}

int main() {
    Comparator_t int_comp = {"Integer", int_compare, int_print};
    Comparator_t str_comp = {"String", str_compare, str_print};

    int x = 5, y = 10;
    printf("Comparing %d and %d: %d\n", x, y,
           int_comp.compare(&x, &y));

    char* s1 = "apple", *s2 = "banana";
    printf("Comparing %s and %s: %d\n", s1, s2,
           str_comp.compare(&s1, &s2));
}
```

## Self-Referential Structs
```c
typedef struct Person {
    char name[50];
    int age;
    struct Person* spouse;    // Pointer to another Person
    struct Person* children;  // Linked list of children
} Person_t;

Person_t* create_person(const char* name, int age) {
    Person_t* person = (Person_t*)malloc(sizeof(Person_t));
    strcpy(person->name, name);
    person->age = age;
    person->spouse = NULL;
    person->children = NULL;
    return person;
}

void add_child(Person_t* parent, Person_t* child) {
    child->next_sibling = parent->children;
    parent->children = child;
}
```

## Memory Management Best Practices
```c
typedef struct {
    char* buffer;
    size_t size;
    size_t capacity;
} Buffer_t;

Buffer_t* buffer_create(size_t initial_capacity) {
    Buffer_t* buf = (Buffer_t*)malloc(sizeof(Buffer_t));
    if (buf == NULL) return NULL;

    buf->buffer = (char*)malloc(initial_capacity);
    if (buf->buffer == NULL) {
        free(buf);
        return NULL;
    }

    buf->size = 0;
    buf->capacity = initial_capacity;
    return buf;
}

void buffer_destroy(Buffer_t* buf) {
    if (buf != NULL) {
        free(buf->buffer);
        free(buf);
    }
}

// Usage
Buffer_t* buf = buffer_create(1024);
if (buf != NULL) {
    // Use buffer
    buffer_destroy(buf);
}
```

## Best Practices
- Always check malloc return values
- Set pointers to NULL after free
- Use consistent memory management patterns
- Document ownership semantics
- Prefer composition over complex inheritance
- Be careful with circular references

## Common Mistakes
- Memory leaks from not freeing struct pointers
- Dangling pointers after free
- Double free errors
- Not checking NULL before dereferencing
- Incorrect arrow vs dot operator usage
- Shallow copying when deep copy needed