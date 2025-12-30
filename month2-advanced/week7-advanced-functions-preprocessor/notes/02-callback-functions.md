# 02: Callback Functions

## Callback Functions
Functions passed as arguments to other functions, called when specific events occur or conditions are met.

## Basic Callback Pattern
```c
#include <stdio.h>

// Callback function type
typedef void (*Callback)(int);

// Function that accepts a callback
void process_numbers(int arr[], int size, Callback callback) {
    for (int i = 0; i < size; i++) {
        callback(arr[i]);  // Call the callback function
    }
}

// Callback implementations
void print_number(int num) {
    printf("%d ", num);
}

void print_square(int num) {
    printf("%d ", num * num);
}

void print_cube(int num) {
    printf("%d ", num * num * num);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};

    printf("Numbers: ");
    process_numbers(numbers, 5, print_number);

    printf("\nSquares: ");
    process_numbers(numbers, 5, print_square);

    printf("\nCubes: ");
    process_numbers(numbers, 5, print_cube);

    printf("\n");
    return 0;
}
```

## Callback with Context
```c
// Callback with user data
typedef void (*CallbackWithContext)(int, void*);

// Function that accepts callback with context
void for_each(int arr[], int size, CallbackWithContext callback, void* context) {
    for (int i = 0; i < size; i++) {
        callback(arr[i], context);
    }
}

// Callback that uses context
void multiply_and_print(int num, void* context) {
    int multiplier = *(int*)context;
    printf("%d ", num * multiplier);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int multiplier = 3;

    printf("Numbers multiplied by %d: ", multiplier);
    for_each(numbers, 5, multiply_and_print, &multiplier);
    printf("\n");

    return 0;
}
```

## Event-Driven Callbacks
```c
typedef void (*EventHandler)(const char* event, void* data);

// Simple event system
typedef struct {
    EventHandler handler;
    void* context;
} EventListener;

EventListener listeners[10];
int listener_count = 0;

void register_listener(EventHandler handler, void* context) {
    if (listener_count < 10) {
        listeners[listener_count].handler = handler;
        listeners[listener_count].context = context;
        listener_count++;
    }
}

void trigger_event(const char* event, void* data) {
    for (int i = 0; i < listener_count; i++) {
        if (listeners[i].handler) {
            listeners[i].handler(event, data);
        }
    }
}

// Event handlers
void button_press_handler(const char* event, void* data) {
    printf("Button pressed: %s\n", (char*)data);
}

void temperature_handler(const char* event, void* data) {
    double temp = *(double*)data;
    printf("Temperature changed: %.1f°C\n", temp);
}

int main() {
    // Register event handlers
    register_listener(button_press_handler, NULL);
    register_listener(temperature_handler, NULL);

    // Simulate events
    char button_id[] = "BUTTON_A";
    trigger_event("button_press", button_id);

    double temperature = 25.5;
    trigger_event("temperature_change", &temperature);

    return 0;
}
```

## Timer Callbacks
```c
#include <time.h>

typedef void (*TimerCallback)(void* context);

// Simple timer structure
typedef struct {
    time_t trigger_time;
    TimerCallback callback;
    void* context;
    int active;
} Timer;

Timer timers[5];
int timer_count = 0;

void add_timer(int delay_seconds, TimerCallback callback, void* context) {
    if (timer_count < 5) {
        timers[timer_count].trigger_time = time(NULL) + delay_seconds;
        timers[timer_count].callback = callback;
        timers[timer_count].context = context;
        timers[timer_count].active = 1;
        timer_count++;
    }
}

void check_timers() {
    time_t now = time(NULL);
    for (int i = 0; i < timer_count; i++) {
        if (timers[i].active && now >= timers[i].trigger_time) {
            timers[i].callback(timers[i].context);
            timers[i].active = 0;  // One-shot timer
        }
    }
}

// Timer callback functions
void alarm_callback(void* context) {
    printf("Alarm triggered: %s\n", (char*)context);
}

void reminder_callback(void* context) {
    printf("Reminder: %s\n", (char*)context);
}

int main() {
    add_timer(2, alarm_callback, "Wake up!");
    add_timer(3, reminder_callback, "Meeting in 5 minutes");

    // Simulate timer checking (in real app, this would be in a loop)
    for (int i = 0; i < 5; i++) {
        check_timers();
        sleep(1);  // Sleep for 1 second
    }

    return 0;
}
```

## Comparator Callbacks
```c
// Generic comparison function
typedef int (*Comparator)(const void*, const void*);

// Generic sort function
void bubble_sort(void* arr, int n, size_t elem_size, Comparator compare) {
    char* array = (char*)arr;

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            char* elem1 = array + j * elem_size;
            char* elem2 = array + (j + 1) * elem_size;

            if (compare(elem1, elem2) > 0) {
                // Swap elements
                for (size_t k = 0; k < elem_size; k++) {
                    char temp = elem1[k];
                    elem1[k] = elem2[k];
                    elem2[k] = temp;
                }
            }
        }
    }
}

// Integer comparison
int compare_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

// String comparison
int compare_string(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

int main() {
    // Sort integers
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    bubble_sort(numbers, 7, sizeof(int), compare_int);

    printf("Sorted numbers: ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Sort strings
    char* strings[] = {"zebra", "apple", "banana", "cherry"};
    bubble_sort(strings, 4, sizeof(char*), compare_string);

    printf("Sorted strings: ");
    for (int i = 0; i < 4; i++) {
        printf("%s ", strings[i]);
    }
    printf("\n");

    return 0;
}
```

## Asynchronous Callbacks
```c
typedef void (*AsyncCallback)(void* result, void* context);

// Simulate asynchronous operation
typedef struct {
    AsyncCallback callback;
    void* context;
    int completed;
    int result;
} AsyncOperation;

AsyncOperation* create_async_operation(AsyncCallback cb, void* ctx) {
    AsyncOperation* op = malloc(sizeof(AsyncOperation));
    op->callback = cb;
    op->context = ctx;
    op->completed = 0;
    op->result = 0;
    return op;
}

void process_async_operation(AsyncOperation* op) {
    // Simulate some work
    sleep(1);
    op->result = 42;
    op->completed = 1;

    // Call the callback
    if (op->callback) {
        op->callback(&op->result, op->context);
    }
}

// Callback function
void operation_complete(void* result, void* context) {
    int value = *(int*)result;
    printf("Async operation completed with result: %d\n", value);
    printf("Context: %s\n", (char*)context);
}

int main() {
    char context[] = "Operation 1";
    AsyncOperation* op = create_async_operation(operation_complete, context);

    // Start async operation (in real app, this would be in a thread)
    process_async_operation(op);

    free(op);
    return 0;
}
```

## Callback Chains
```c
typedef void (*ChainCallback)(void* data);

// Chain of callbacks
typedef struct CallbackNode {
    ChainCallback callback;
    void* context;
    struct CallbackNode* next;
} CallbackNode;

CallbackNode* callback_chain = NULL;

void add_to_chain(ChainCallback cb, void* context) {
    CallbackNode* node = malloc(sizeof(CallbackNode));
    node->callback = cb;
    node->context = context;
    node->next = callback_chain;
    callback_chain = node;
}

void execute_chain(void* data) {
    CallbackNode* current = callback_chain;
    while (current) {
        current->callback(data);
        current = current->next;
    }
}

// Chain callbacks
void log_callback(void* data) {
    printf("Log: Processing data\n");
}

void validate_callback(void* data) {
    printf("Validate: Data is valid\n");
}

void process_callback(void* data) {
    printf("Process: Data processed\n");
}

int main() {
    // Build callback chain
    add_to_chain(process_callback, NULL);
    add_to_chain(validate_callback, NULL);
    add_to_chain(log_callback, NULL);

    // Execute chain
    int data = 123;
    execute_chain(&data);

    // Cleanup
    CallbackNode* current = callback_chain;
    while (current) {
        CallbackNode* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
```

## Error Handling Callbacks
```c
typedef void (*SuccessCallback)(void* result);
typedef void (*ErrorCallback)(const char* error);

// Operation result
typedef struct {
    int success;
    void* result;
    const char* error;
} OperationResult;

// Function with success/error callbacks
void async_operation(SuccessCallback on_success, ErrorCallback on_error) {
    // Simulate operation
    int success = rand() % 2;  // Random success/failure

    if (success) {
        int result = 42;
        on_success(&result);
    } else {
        on_error("Operation failed randomly");
    }
}

// Callback implementations
void on_operation_success(void* result) {
    printf("Success! Result: %d\n", *(int*)result);
}

void on_operation_error(const char* error) {
    printf("Error: %s\n", error);
}

int main() {
    srand(time(NULL));

    printf("Attempting operation...\n");
    async_operation(on_operation_success, on_operation_error);

    return 0;
}
```

## Best Practices
- Use typedef for callback function types
- Document callback function signatures clearly
- Check for NULL callbacks before calling
- Pass context data when needed
- Keep callbacks simple and focused
- Handle errors appropriately in callbacks
- Avoid blocking operations in callbacks
- Consider thread safety for shared data

## Common Mistakes
- Calling NULL callback pointers
- Incorrect function signatures
- Memory leaks in callback context
- Blocking operations in event callbacks
- Race conditions in multi-threaded callbacks
- Not handling callback errors
- Overly complex callback chains
- Forgetting to unregister callbacks

## Performance Considerations
```c
// Direct function call (fastest)
void direct_call() {
    printf("Direct call\n");
}

// Callback through function pointer (overhead)
typedef void (*Callback)(void);

void callback_call(Callback cb) {
    if (cb) cb();  // Null check overhead
}

// Virtual function call (similar overhead)
typedef struct {
    Callback method;
} Object;

void method_call(Object* obj) {
    if (obj->method) obj->method();  // Indirection overhead
}
```

## Embedded Systems Applications
### Interrupt Handlers
```c
typedef void (*InterruptHandler)(void);

InterruptHandler uart_rx_handler = NULL;

void register_uart_rx_handler(InterruptHandler handler) {
    uart_rx_handler = handler;
}

void UART_RX_Interrupt() {
    if (uart_rx_handler) {
        uart_rx_handler();
    }
}
```

### Device Drivers
```c
typedef struct {
    void (*init)(void);
    void (*read)(uint8_t* buffer, size_t size);
    void (*write)(const uint8_t* buffer, size_t size);
    void (*close)(void);
} DeviceDriver;

void use_device(DeviceDriver* driver) {
    driver->init();
    uint8_t data[10];
    driver->read(data, 10);
    driver->close();
}
```

### State Machine Events
```c
typedef void (*StateEventHandler)(int event, void* data);

typedef struct {
    int current_state;
    StateEventHandler event_handler;
} StateMachine;

void process_event(StateMachine* sm, int event, void* data) {
    if (sm->event_handler) {
        sm->event_handler(event, data);
    }
}
```