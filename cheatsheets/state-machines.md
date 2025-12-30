# State Machines Cheatsheet

## Basic State Machine Concepts

### State Machine Components
```c
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR,
    STATE_FINISHED
} state_t;

typedef struct {
    state_t current_state;
    // State data
    int error_code;
    int data_count;
} state_machine_t;
```

### Simple State Machine
```c
state_t next_state(state_t current, event_t event) {
    switch (current) {
        case STATE_IDLE:
            if (event == START_EVENT) return STATE_RUNNING;
            break;
        case STATE_RUNNING:
            if (event == STOP_EVENT) return STATE_FINISHED;
            if (event == ERROR_EVENT) return STATE_ERROR;
            break;
        case STATE_ERROR:
            if (event == RESET_EVENT) return STATE_IDLE;
            break;
        case STATE_FINISHED:
            // Terminal state
            break;
    }
    return current;  // Stay in current state
}
```

## Table-Driven State Machines

### State Transition Table
```c
typedef struct {
    state_t current_state;
    event_t event;
    state_t next_state;
    void (*action)(void *data);
} transition_t;

const transition_t transitions[] = {
    {STATE_IDLE, START_EVENT, STATE_RUNNING, start_action},
    {STATE_RUNNING, STOP_EVENT, STATE_FINISHED, stop_action},
    {STATE_RUNNING, ERROR_EVENT, STATE_ERROR, error_action},
    {STATE_ERROR, RESET_EVENT, STATE_IDLE, reset_action},
};

#define NUM_TRANSITIONS (sizeof(transitions) / sizeof(transition_t))
```

### Table Lookup Implementation
```c
state_t process_event(state_machine_t *sm, event_t event) {
    for (int i = 0; i < NUM_TRANSITIONS; i++) {
        if (transitions[i].current_state == sm->current_state &&
            transitions[i].event == event) {
            
            sm->current_state = transitions[i].next_state;
            
            if (transitions[i].action) {
                transitions[i].action(sm);
            }
            
            return sm->current_state;
        }
    }
    return sm->current_state;  // No transition found
}
```

## Hierarchical State Machines

### State Hierarchy
```c
typedef enum {
    // Top level states
    TOP_LEVEL,
    
    // Substates of TOP_LEVEL
    SUBSTATE_A,
    SUBSTATE_B,
    
    // Substates of SUBSTATE_A
    SUBSTATE_A1,
    SUBSTATE_A2
} hierarchical_state_t;
```

### Hierarchical Implementation
```c
typedef struct {
    hierarchical_state_t current_state;
    hierarchical_state_t history[10];  // State history stack
    int history_depth;
} hierarchical_sm_t;

void enter_substate(hierarchical_sm_t *sm, hierarchical_state_t substate) {
    sm->history[sm->history_depth++] = sm->current_state;
    sm->current_state = substate;
    // Execute entry actions
}

void exit_substate(hierarchical_sm_t *sm) {
    if (sm->history_depth > 0) {
        sm->current_state = sm->history[--sm->history_depth];
        // Execute exit actions
    }
}
```

## Event-Driven State Machines

### Event Queue
```c
#define EVENT_QUEUE_SIZE 16

typedef struct {
    event_t events[EVENT_QUEUE_SIZE];
    int head;
    int tail;
    int count;
} event_queue_t;

bool queue_event(event_queue_t *queue, event_t event) {
    if (queue->count >= EVENT_QUEUE_SIZE) return false;
    
    queue->events[queue->tail] = event;
    queue->tail = (queue->tail + 1) % EVENT_QUEUE_SIZE;
    queue->count++;
    return true;
}

bool dequeue_event(event_queue_t *queue, event_t *event) {
    if (queue->count == 0) return false;
    
    *event = queue->events[queue->head];
    queue->head = (queue->head + 1) % EVENT_QUEUE_SIZE;
    queue->count--;
    return true;
}
```

### Event Processing Loop
```c
void state_machine_run(state_machine_t *sm, event_queue_t *events) {
    event_t event;
    
    while (dequeue_event(events, &event)) {
        state_t new_state = process_event(sm, event);
        
        // Execute state-specific actions
        switch (new_state) {
            case STATE_RUNNING:
                running_actions(sm);
                break;
            case STATE_ERROR:
                error_handling(sm);
                break;
        }
    }
}
```

## Guard Conditions

### State Transitions with Guards
```c
typedef bool (*guard_condition_t)(void *data);

typedef struct {
    state_t current_state;
    event_t event;
    state_t next_state;
    guard_condition_t guard;
    void (*action)(void *data);
} guarded_transition_t;

bool is_motor_ready(void *data) {
    motor_status_t *status = (motor_status_t *)data;
    return status->temperature < MAX_TEMP && status->voltage > MIN_VOLTAGE;
}

const guarded_transition_t guarded_transitions[] = {
    {STATE_IDLE, START_EVENT, STATE_RUNNING, is_motor_ready, start_motor},
    {STATE_IDLE, START_EVENT, STATE_ERROR, NULL, report_error},
};
```

### Guarded Transition Processing
```c
state_t process_guarded_event(state_machine_t *sm, event_t event, void *data) {
    for (int i = 0; i < NUM_GUARDED_TRANSITIONS; i++) {
        const guarded_transition_t *t = &guarded_transitions[i];
        
        if (t->current_state == sm->current_state && t->event == event) {
            // Check guard condition
            if (t->guard == NULL || t->guard(data)) {
                sm->current_state = t->next_state;
                
                if (t->action) {
                    t->action(data);
                }
                
                return sm->current_state;
            }
        }
    }
    return sm->current_state;
}
```

## Embedded-Specific Patterns

### Timer-Based State Machines
```c
typedef struct {
    state_t current_state;
    uint32_t state_timer;
    uint32_t timeout_ms;
} timed_state_machine_t;

typedef enum {
    TIMER_IDLE,
    TIMER_COUNTING,
    TIMER_EXPIRED
} timer_state_t;

void update_timed_state_machine(timed_state_machine_t *sm, uint32_t current_time) {
    switch (sm->current_state) {
        case TIMER_IDLE:
            if (start_timer_event) {
                sm->current_state = TIMER_COUNTING;
                sm->state_timer = current_time;
            }
            break;
            
        case TIMER_COUNTING:
            if (current_time - sm->state_timer >= sm->timeout_ms) {
                sm->current_state = TIMER_EXPIRED;
                timer_expired_callback();
            }
            break;
            
        case TIMER_EXPIRED:
            // Handle timeout
            break;
    }
}
```

### Interrupt-Driven State Machines
```c
volatile state_t interrupt_state = STATE_IDLE;

void interrupt_handler(void) {
    // Atomic state transition
    state_t current = interrupt_state;
    
    switch (current) {
        case STATE_IDLE:
            if (interrupt_condition) {
                interrupt_state = STATE_PROCESSING;
                // Set up processing
            }
            break;
            
        case STATE_PROCESSING:
            // Handle interrupt data
            interrupt_state = STATE_IDLE;
            break;
    }
}
```

### Communication Protocol State Machine
```c
typedef enum {
    PROTOCOL_IDLE,
    PROTOCOL_WAIT_SYNC,
    PROTOCOL_RECEIVING_HEADER,
    PROTOCOL_RECEIVING_DATA,
    PROTOCOL_PROCESSING,
    PROTOCOL_TRANSMITTING,
    PROTOCOL_ERROR
} protocol_state_t;

typedef struct {
    protocol_state_t state;
    uint8_t buffer[256];
    uint16_t buffer_index;
    uint16_t expected_length;
    uint32_t timeout_timer;
} protocol_sm_t;

void protocol_process_byte(protocol_sm_t *proto, uint8_t byte) {
    switch (proto->state) {
        case PROTOCOL_IDLE:
            if (byte == SYNC_BYTE) {
                proto->state = PROTOCOL_WAIT_SYNC;
                proto->buffer_index = 0;
            }
            break;
            
        case PROTOCOL_WAIT_SYNC:
            if (byte == SYNC_BYTE) {
                proto->state = PROTOCOL_RECEIVING_HEADER;
            } else {
                proto->state = PROTOCOL_IDLE;
            }
            break;
            
        case PROTOCOL_RECEIVING_HEADER:
            proto->buffer[proto->buffer_index++] = byte;
            if (proto->buffer_index >= HEADER_LENGTH) {
                proto->expected_length = parse_header_length(proto->buffer);
                proto->state = PROTOCOL_RECEIVING_DATA;
                proto->buffer_index = 0;
            }
            break;
            
        case PROTOCOL_RECEIVING_DATA:
            proto->buffer[proto->buffer_index++] = byte;
            if (proto->buffer_index >= proto->expected_length) {
                proto->state = PROTOCOL_PROCESSING;
                process_packet(proto->buffer, proto->expected_length);
            }
            break;
    }
}
```

### Motor Control State Machine
```c
typedef enum {
    MOTOR_OFF,
    MOTOR_STARTING,
    MOTOR_RUNNING,
    MOTOR_STOPPING,
    MOTOR_ERROR
} motor_state_t;

typedef struct {
    motor_state_t state;
    uint16_t target_rpm;
    uint16_t current_rpm;
    uint8_t temperature;
    uint32_t error_flags;
} motor_controller_t;

#define MAX_TEMP 80
#define MIN_RPM 100
#define MAX_RPM 5000

void motor_control_update(motor_controller_t *motor) {
    switch (motor->state) {
        case MOTOR_OFF:
            if (motor_start_command) {
                if (motor->temperature < MAX_TEMP) {
                    motor->state = MOTOR_STARTING;
                    start_motor_hardware();
                } else {
                    motor->state = MOTOR_ERROR;
                    motor->error_flags |= TEMP_TOO_HIGH;
                }
            }
            break;
            
        case MOTOR_STARTING:
            if (motor->current_rpm >= MIN_RPM) {
                motor->state = MOTOR_RUNNING;
            } else if (motor->temperature > MAX_TEMP) {
                motor->state = MOTOR_ERROR;
                stop_motor_hardware();
            }
            break;
            
        case MOTOR_RUNNING:
            // PID control for target RPM
            int16_t rpm_error = motor->target_rpm - motor->current_rpm;
            update_motor_speed(rpm_error);
            
            if (motor_stop_command) {
                motor->state = MOTOR_STOPPING;
            } else if (motor->temperature > MAX_TEMP) {
                motor->state = MOTOR_ERROR;
                stop_motor_hardware();
            }
            break;
            
        case MOTOR_STOPPING:
            if (motor->current_rpm == 0) {
                motor->state = MOTOR_OFF;
            }
            break;
            
        case MOTOR_ERROR:
            // Handle error recovery
            if (motor_reset_command && motor->temperature < MAX_TEMP) {
                motor->state = MOTOR_OFF;
                motor->error_flags = 0;
            }
            break;
    }
}
```

## Best Practices

- Keep state machines simple and focused
- Use enums for states and events
- Document state transitions clearly
- Handle all possible state-event combinations
- Use guard conditions for complex transitions
- Consider hierarchical states for complex systems
- Implement proper error handling states
- Use timers for timeout handling
- Test all state transitions
- Document state machine behavior
- Consider using state machine frameworks for complex systems