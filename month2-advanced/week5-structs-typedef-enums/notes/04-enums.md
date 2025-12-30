# 04: Enums

## What is an Enum?
An enum (enumeration) is a user-defined type consisting of named integer constants, improving code readability and maintainability.

## Basic Enum Declaration
```c
enum Color {
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
};

// Usage
enum Color favorite = RED;
printf("Favorite color: %d\n", favorite);  // 0
```

## Explicit Values
```c
enum Status {
    SUCCESS = 0,
    ERROR = 1,
    WARNING = 2,
    CRITICAL = 10
};

enum Color {
    RED = 1,
    GREEN = 2,
    BLUE = 4,    // Powers of 2 for bit flags
    YELLOW = 8
};
```

## Enum with Typedef
```c
typedef enum {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} Day_t;

Day_t today = WEDNESDAY;
```

## Enum in Switch Statements
```c
enum Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

int calculate(int a, int b, enum Operation op) {
    switch (op) {
        case ADD:
            return a + b;
        case SUBTRACT:
            return a - b;
        case MULTIPLY:
            return a * b;
        case DIVIDE:
            return b != 0 ? a / b : 0;
        default:
            return 0;
    }
}

int main() {
    printf("5 + 3 = %d\n", calculate(5, 3, ADD));
    printf("5 * 3 = %d\n", calculate(5, 3, MULTIPLY));
}
```

## Enum Size and Type
```c
enum Small { A, B, C };           // Typically 4 bytes (int)
enum Large { X = 1000, Y, Z };    // Still 4 bytes

printf("Small enum size: %zu\n", sizeof(enum Small));
printf("Large enum size: %zu\n", sizeof(enum Large));
```

## Bit Flags with Enums
```c
typedef enum {
    READ    = 1 << 0,  // 0001
    WRITE   = 1 << 1,  // 0010
    EXECUTE = 1 << 2,  // 0100
    DELETE  = 1 << 3   // 1000
} Permission_t;

void check_permissions(Permission_t perms) {
    if (perms & READ) printf("Can read\n");
    if (perms & WRITE) printf("Can write\n");
    if (perms & EXECUTE) printf("Can execute\n");
    if (perms & DELETE) printf("Can delete\n");
}

int main() {
    Permission_t user_perms = READ | WRITE;  // 0011
    check_permissions(user_perms);

    // Add execute permission
    user_perms |= EXECUTE;
    check_permissions(user_perms);
}
```

## State Machines with Enums
```c
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_ERROR,
    STATE_FINISHED
} SystemState_t;

typedef struct {
    SystemState_t current_state;
    int data;
} System_t;

void handle_event(System_t* system, int event) {
    switch (system->current_state) {
        case STATE_IDLE:
            if (event == START_EVENT) {
                system->current_state = STATE_RUNNING;
            }
            break;

        case STATE_RUNNING:
            if (event == PAUSE_EVENT) {
                system->current_state = STATE_PAUSED;
            } else if (event == STOP_EVENT) {
                system->current_state = STATE_FINISHED;
            }
            break;

        case STATE_PAUSED:
            if (event == RESUME_EVENT) {
                system->current_state = STATE_RUNNING;
            }
            break;

        default:
            system->current_state = STATE_ERROR;
            break;
    }
}
```

## Enum in Structs
```c
typedef enum {
    CIRCLE,
    RECTANGLE,
    TRIANGLE
} ShapeType_t;

typedef struct {
    ShapeType_t type;
    union {
        struct { float radius; } circle;
        struct { float width, height; } rectangle;
        struct { float base, height; } triangle;
    } data;
} Shape_t;

float calculate_area(Shape_t* shape) {
    switch (shape->type) {
        case CIRCLE:
            return 3.14159 * shape->data.circle.radius * shape->data.circle.radius;
        case RECTANGLE:
            return shape->data.rectangle.width * shape->data.rectangle.height;
        case TRIANGLE:
            return 0.5 * shape->data.triangle.base * shape->data.triangle.height;
        default:
            return 0.0;
    }
}
```

## Enum Iteration
```c
typedef enum {
    SPRING,
    SUMMER,
    AUTUMN,
    WINTER,
    SEASON_COUNT  // Used for iteration
} Season_t;

const char* season_names[] = {
    "Spring", "Summer", "Autumn", "Winter"
};

void print_seasons() {
    for (Season_t season = SPRING; season < SEASON_COUNT; season++) {
        printf("%s\n", season_names[season]);
    }
}
```

## Enum Limitations
```c
enum Color { RED, GREEN, BLUE };
enum Status { OK, FAIL };

// This is allowed but confusing
enum Color c = OK;  // Compiles but semantically wrong
```

## Best Practices
- Use enums for related constants
- Start with 0 or explicit values
- Use typedef with enums
- Name enums with _t suffix
- Document enum purposes
- Use enums in switch statements
- Consider enum size for embedded systems

## Common Mistakes
- Mixing different enum types
- Assuming enum values are consecutive
- Using enums as boolean flags without bit operations
- Not handling default cases in switches
- Large enum values wasting memory
- Forgetting enum scope (C++ has scoped enums)