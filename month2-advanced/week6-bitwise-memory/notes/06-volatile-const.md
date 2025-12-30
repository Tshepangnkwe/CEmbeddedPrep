# 06: Volatile and Const

## The const Qualifier
Prevents modification of variables, providing compile-time protection against accidental changes.

## const Variables
```c
const int MAX_SIZE = 100;        // Constant integer
const double PI = 3.14159;       // Constant double
const char* MESSAGE = "Hello";   // Pointer to constant string

// Cannot modify
// MAX_SIZE = 200;  // Error
// PI = 3.14;       // Error
```

## const Pointers
### Pointer to const
```c
int x = 10;
const int* ptr = &x;  // Pointer to constant int

// Cannot modify value through pointer
// *ptr = 20;  // Error

// But can change what pointer points to
int y = 30;
ptr = &y;  // OK

printf("Value: %d\n", *ptr);  // 30
```

### const Pointer
```c
int x = 10, y = 20;
int* const ptr = &x;  // Constant pointer to int

// Can modify value through pointer
*ptr = 15;  // OK, x becomes 15

// But cannot change what pointer points to
// ptr = &y;  // Error

printf("x = %d\n", x);  // 15
```

### const Pointer to const
```c
int x = 10, y = 20;
const int* const ptr = &x;  // Constant pointer to constant int

// Cannot modify value
// *ptr = 15;  // Error

// Cannot change pointer
// ptr = &y;   // Error
```

## const in Function Parameters
```c
// Function won't modify the string
void print_string(const char* str) {
    // str[0] = 'h';  // Error: cannot modify
    printf("%s\n", str);
}

// Function returns const pointer
const char* get_message() {
    return "Hello World";  // String literal is const
}

int main() {
    const char* msg = get_message();
    print_string(msg);
    return 0;
}
```

## const in Arrays
```c
const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Cannot modify array elements
// days_in_month[0] = 32;  // Error

// But can use in expressions
int feb_days = days_in_month[1];
```

## The volatile Qualifier
Prevents compiler optimizations that assume variable values don't change unexpectedly. Essential for hardware registers and multi-threaded code.

## volatile Variables
```c
volatile int hardware_register;  // Hardware register that can change anytime

void poll_hardware() {
    while (hardware_register == 0) {
        // Wait for hardware to set register
        // Compiler won't optimize away this loop
    }
    printf("Hardware ready\n");
}
```

## volatile Pointers
```c
volatile int* ptr;           // Pointer to volatile int
int* volatile ptr2;          // Volatile pointer to int
volatile int* volatile ptr3; // Volatile pointer to volatile int
```

## Common volatile Use Cases
### Hardware Registers
```c
#define UART_STATUS_REG (*(volatile unsigned char*)0x40001000)
#define UART_DATA_REG   (*(volatile unsigned char*)0x40001004)

void uart_write(char data) {
    while (!(UART_STATUS_REG & 0x20)) {
        // Wait for transmit buffer empty
    }
    UART_DATA_REG = data;
}
```

### Interrupt Handlers
```c
volatile int interrupt_flag = 0;

void interrupt_handler() {
    interrupt_flag = 1;
}

void main_loop() {
    while (1) {
        if (interrupt_flag) {
            interrupt_flag = 0;
            // Handle interrupt
        }
        // Do other work
    }
}
```

### Multi-threaded Variables
```c
volatile int shared_counter = 0;

// Thread 1
void thread1() {
    for (int i = 0; i < 1000000; i++) {
        shared_counter++;
    }
}

// Thread 2
void thread2() {
    while (shared_counter < 1000000) {
        // Wait for counter to reach limit
    }
    printf("Counter reached: %d\n", shared_counter);
}
```

## const volatile
Variables that cannot be modified by program but can change externally:
```c
const volatile int* sensor_reading;  // Read-only hardware register

int get_sensor_value() {
    return *sensor_reading;  // OK to read
    // *sensor_reading = 10;  // Error: const
    // But value can change due to hardware
}
```

## Compiler Optimizations and volatile
### Without volatile
```c
int flag = 0;

void set_flag() {
    flag = 1;
}

int check_flag() {
    if (flag) {        // Compiler might optimize to always false
        return 1;      // if it thinks flag never changes
    }
    return 0;
}
```

### With volatile
```c
volatile int flag = 0;

void set_flag() {
    flag = 1;
}

int check_flag() {
    if (flag) {        // Compiler cannot optimize
        return 1;      // Must check flag each time
    }
    return 0;
}
```

## const and volatile Together
```c
// Read-only status register
const volatile unsigned int* const STATUS_REG = (const volatile unsigned int*)0x40000000;

unsigned int read_status() {
    return *STATUS_REG;  // OK: reading volatile const
}

void bad_write() {
    // *STATUS_REG = 0x1234;  // Error: const
}
```

## Best Practices
- Use const for values that shouldn't change
- Use volatile for variables that can change unexpectedly
- Combine const volatile for read-only hardware registers
- Document why variables are const or volatile
- Be careful with volatile in performance-critical code
- Use const in function parameters when appropriate

## Common Mistakes
- Thinking const makes variables immutable at runtime
- Forgetting volatile for hardware registers
- Using volatile when not needed (hurts performance)
- Incorrect const placement in pointer declarations
- Assuming volatile prevents race conditions (it doesn't)
- Using const on function parameters that need to be modified

## Performance Considerations
```c
// Without volatile, compiler might optimize
int sum = 0;
for (volatile int i = 0; i < 1000000; i++) {
    sum += i;  // Each access goes to memory
}

// With volatile, prevents some optimizations
// Use only when necessary!
```

## Embedded Systems Examples
### GPIO Registers
```c
#define GPIO_PORTA_DATA   (*(volatile unsigned int*)0x40004000)
#define GPIO_PORTA_DIR    (*(volatile unsigned int*)0x40004004)

void gpio_init() {
    GPIO_PORTA_DIR = 0xFF;  // Set all pins as output
}

void gpio_set_pin(int pin) {
    GPIO_PORTA_DATA |= (1 << pin);
}
```

### Timer Registers
```c
typedef struct {
    volatile unsigned int control;
    volatile unsigned int counter;
    volatile unsigned int compare;
    const volatile unsigned int status;
} TimerRegisters_t;

#define TIMER0 ((TimerRegisters_t*)0x40001000)

void start_timer() {
    TIMER0->control = 0x01;  // Start timer
    TIMER0->compare = 1000;  // Set compare value
}

int timer_expired() {
    return TIMER0->status & 0x01;  // Check status bit
}
```