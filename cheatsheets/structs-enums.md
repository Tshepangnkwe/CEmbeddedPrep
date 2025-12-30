# Structs and Enums Cheatsheet

## Structures

### Basic Declaration
```c
struct point {
    int x;
    int y;
};

struct point p1;  // Declaration
struct point p2 = {10, 20};  // Initialization
```

### Structure Initialization
```c
// Designated initializers (C99)
struct point p = {.x = 5, .y = 10};

// Partial initialization
struct point p = {5};  // x=5, y=0 (or garbage if not global)

// Array of structs
struct point points[3] = {
    {1, 2},
    {3, 4},
    {5, 6}
};
```

### Accessing Members
```c
struct point p = {10, 20};
p.x = 15;           // Direct access
p.y = 25;

struct point *ptr = &p;
ptr->x = 30;        // Pointer access
(*ptr).y = 40;      // Equivalent but ugly
```

## Typedef

### Basic Usage
```c
typedef int my_int_t;
typedef struct point point_t;

// Now we can use point_t instead of struct point
point_t p = {5, 10};
```

### Structure with Typedef
```c
typedef struct {
    int x, y;
} point_t;

// Or named structure
typedef struct point_tag {
    int x, y;
} point_t;
```

### Function Pointers with Typedef
```c
typedef void (*callback_t)(int);
typedef int (*operation_t)(int, int);

void register_callback(callback_t cb) {
    // Store callback
}
```

## Enumerations

### Basic Enum
```c
enum color {
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
};

enum color c = RED;
```

### Explicit Values
```c
enum status {
    OK = 0,
    ERROR = -1,
    PENDING = 1,
    TIMEOUT = 2
};
```

### Typedef with Enum
```c
typedef enum {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2
} priority_t;

priority_t p = HIGH;
```

## Nested Structures

### Basic Nesting
```c
typedef struct {
    int x, y;
} point_t;

typedef struct {
    point_t start;
    point_t end;
} line_t;

line_t line = {
    {0, 0},     // start
    {10, 10}    // end
};
```

### Anonymous Structures
```c
typedef struct {
    int id;
    struct {
        char first[20];
        char last[20];
    } name;  // Anonymous structure
    int age;
} person_t;

person_t p = {
    .id = 1,
    .name = {"John", "Doe"},
    .age = 30
};
```

## Bit Fields

### Basic Bit Fields
```c
typedef struct {
    unsigned int enabled : 1;    // 1 bit
    unsigned int mode : 2;       // 2 bits
    unsigned int priority : 3;   // 3 bits
    unsigned int : 2;            // 2 bits padding
} config_t;

config_t cfg;
cfg.enabled = 1;
cfg.mode = 3;      // 0-3 range
cfg.priority = 5;  // 0-7 range
```

### Memory Layout
```c
// Total: 8 bits (1 byte)
// enabled: bit 0
// mode: bits 1-2
// priority: bits 3-5
// padding: bits 6-7
```

## Unions

### Basic Union
```c
typedef union {
    int i;
    float f;
    char str[4];
} data_t;

data_t d;
d.i = 42;
printf("%f\n", d.f);  // Undefined behavior - wrong interpretation
```

### Tagged Union
```c
typedef enum { INT_TYPE, FLOAT_TYPE, STRING_TYPE } data_type_t;

typedef struct {
    data_type_t type;
    union {
        int i;
        float f;
        char str[20];
    } value;
} variant_t;

variant_t v;
v.type = INT_TYPE;
v.value.i = 42;
```

## Structure Padding and Alignment

### Size Considerations
```c
struct example {
    char c;      // 1 byte
    int i;       // 4 bytes (aligned to 4-byte boundary)
    char d;      // 1 byte, but padded to 4-byte alignment
}; // Total: 12 bytes (not 6!)

#pragma pack(1)  // Disable padding
struct packed_example {
    char c;
    int i;
    char d;
}; // Total: 6 bytes
#pragma pack()   // Restore default
```

### Alignment Control
```c
// Force alignment
typedef struct {
    char c;
    int i __attribute__((aligned(8)));  // Align to 8-byte boundary
} aligned_struct;
```

## Function Pointers in Structures

### Callback Structures
```c
typedef void (*event_handler_t)(void *data);

typedef struct {
    char name[20];
    event_handler_t handler;
    void *user_data;
} event_t;

void button_press_handler(void *data) {
    printf("Button pressed: %s\n", (char *)data);
}

event_t button_event = {
    "button_press",
    button_press_handler,
    "Button 1"
};
```

### Virtual Tables (Simple OOP)
```c
typedef struct shape_vtable {
    float (*area)(void *self);
    void (*draw)(void *self);
} shape_vtable_t;

typedef struct {
    shape_vtable_t *vtable;
    // Common data
} shape_t;

typedef struct {
    shape_t base;
    float radius;
} circle_t;

float circle_area(void *self) {
    circle_t *circle = (circle_t *)self;
    return 3.14159f * circle->radius * circle->radius;
}
```

## Embedded-Specific Patterns

### Peripheral Registers
```c
typedef struct {
    volatile uint32_t CR1;    // Control register 1
    volatile uint32_t CR2;    // Control register 2
    volatile uint32_t SR;     // Status register
    volatile uint32_t DR;     // Data register
} uart_registers_t;

#define UART1_BASE 0x40011000
#define UART1 ((uart_registers_t *)UART1_BASE)

// Usage
UART1->CR1 |= (1 << 13);  // Enable UART
while (!(UART1->SR & (1 << 7))) {}  // Wait for TXE
UART1->DR = 'A';  // Send character
```

### GPIO Configuration
```c
typedef enum {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_ALTERNATE = 2,
    GPIO_MODE_ANALOG = 3
} gpio_mode_t;

typedef enum {
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP = 1,
    GPIO_PULL_DOWN = 2
} gpio_pull_t;

typedef struct {
    uint8_t pin;
    gpio_mode_t mode;
    gpio_pull_t pull;
    uint8_t speed;
} gpio_config_t;

const gpio_config_t led_config = {
    .pin = 5,
    .mode = GPIO_MODE_OUTPUT,
    .pull = GPIO_PULL_NONE,
    .speed = 2
};
```

### State Machines
```c
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR,
    STATE_FINISHED
} system_state_t;

typedef struct {
    system_state_t current_state;
    uint32_t error_code;
    uint32_t data_count;
    struct {
        uint8_t motor_enabled : 1;
        uint8_t sensor_active : 1;
        uint8_t alarm_triggered : 1;
        uint8_t : 5;  // padding
    } flags;
} system_status_t;

system_status_t system = {
    .current_state = STATE_IDLE,
    .flags.motor_enabled = 0
};
```

### Configuration Structures
```c
typedef struct {
    uint32_t baud_rate;
    uint8_t data_bits;
    uint8_t stop_bits;
    uint8_t parity;
} uart_config_t;

typedef struct {
    uart_config_t uart;
    uint32_t timeout_ms;
    uint8_t retries;
} communication_config_t;

const communication_config_t default_config = {
    .uart = {
        .baud_rate = 9600,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 0
    },
    .timeout_ms = 1000,
    .retries = 3
};
```

## Best Practices

- Use typedef for complex types
- Initialize structures completely
- Be aware of structure padding
- Use designated initializers for clarity
- Document bit field layouts
- Use unions carefully with type tags
- Consider alignment requirements for embedded
- Group related data in structures
- Use meaningful names for enum values
- Document structure member purposes