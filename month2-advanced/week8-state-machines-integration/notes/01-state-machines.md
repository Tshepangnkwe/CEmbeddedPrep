# 01: State Machines

## State Machines
A state machine is a computational model that can be in exactly one of a finite number of states at any given time.

## Basic State Machine Concepts
```c
#include <stdio.h>
#include <stdbool.h>

// States
typedef enum {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED
} SystemState;

// Events
typedef enum {
    EVENT_START,
    EVENT_PAUSE,
    EVENT_RESUME,
    EVENT_STOP,
    EVENT_RESET
} SystemEvent;

// State machine structure
typedef struct {
    SystemState current_state;
    int data_value;
    bool is_initialized;
} StateMachine;

// Initialize state machine
void state_machine_init(StateMachine* sm) {
    sm->current_state = STATE_IDLE;
    sm->data_value = 0;
    sm->is_initialized = true;
    printf("State machine initialized to IDLE state\n");
}

// Process events and transition states
void state_machine_process_event(StateMachine* sm, SystemEvent event) {
    switch (sm->current_state) {
        case STATE_IDLE:
            switch (event) {
                case EVENT_START:
                    sm->current_state = STATE_RUNNING;
                    sm->data_value = 100;
                    printf("Transition: IDLE -> RUNNING, data = %d\n", sm->data_value);
                    break;
                case EVENT_RESET:
                    printf("Already in IDLE state\n");
                    break;
                default:
                    printf("Invalid event %d in IDLE state\n", event);
                    break;
            }
            break;

        case STATE_RUNNING:
            switch (event) {
                case EVENT_PAUSE:
                    sm->current_state = STATE_PAUSED;
                    printf("Transition: RUNNING -> PAUSED\n");
                    break;
                case EVENT_STOP:
                    sm->current_state = STATE_STOPPED;
                    sm->data_value = 0;
                    printf("Transition: RUNNING -> STOPPED, data reset\n");
                    break;
                default:
                    printf("Invalid event %d in RUNNING state\n", event);
                    break;
            }
            break;

        case STATE_PAUSED:
            switch (event) {
                case EVENT_RESUME:
                    sm->current_state = STATE_RUNNING;
                    printf("Transition: PAUSED -> RUNNING\n");
                    break;
                case EVENT_STOP:
                    sm->current_state = STATE_STOPPED;
                    sm->data_value = 0;
                    printf("Transition: PAUSED -> STOPPED, data reset\n");
                    break;
                default:
                    printf("Invalid event %d in PAUSED state\n", event);
                    break;
            }
            break;

        case STATE_STOPPED:
            switch (event) {
                case EVENT_RESET:
                    sm->current_state = STATE_IDLE;
                    printf("Transition: STOPPED -> IDLE\n");
                    break;
                default:
                    printf("Invalid event %d in STOPPED state\n", event);
                    break;
            }
            break;
    }
}

int main() {
    StateMachine sm;
    state_machine_init(&sm);

    // Test state transitions
    state_machine_process_event(&sm, EVENT_START);
    state_machine_process_event(&sm, EVENT_PAUSE);
    state_machine_process_event(&sm, EVENT_RESUME);
    state_machine_process_event(&sm, EVENT_STOP);
    state_machine_process_event(&sm, EVENT_RESET);

    return 0;
}
```

## State Machine with Actions
```c
#include <stdio.h>
#include <stdlib.h>

// Enhanced state machine with entry/exit actions
typedef enum {
    STATE_OFF,
    STATE_STARTING,
    STATE_ON,
    STATE_SHUTTING_DOWN
} DeviceState;

typedef enum {
    EVENT_TURN_ON,
    EVENT_STARTUP_COMPLETE,
    EVENT_TURN_OFF,
    EVENT_SHUTDOWN_COMPLETE,
    EVENT_ERROR
} DeviceEvent;

typedef struct {
    DeviceState state;
    int temperature;
    int power_level;
} Device;

// Action functions
void enter_off(Device* dev) {
    printf("Device entering OFF state\n");
    dev->temperature = 25;  // Room temperature
    dev->power_level = 0;
}

void enter_starting(Device* dev) {
    printf("Device entering STARTING state - warming up...\n");
    dev->power_level = 50;
}

void enter_on(Device* dev) {
    printf("Device entering ON state - ready for operation\n");
    dev->power_level = 100;
    dev->temperature = 40;  // Operating temperature
}

void enter_shutting_down(Device* dev) {
    printf("Device entering SHUTTING DOWN state - cooling down...\n");
    dev->power_level = 25;
}

void exit_off(Device* dev) {
    printf("Device exiting OFF state\n");
}

void exit_starting(Device* dev) {
    printf("Device exiting STARTING state\n");
}

void exit_on(Device* dev) {
    printf("Device exiting ON state\n");
}

void exit_shutting_down(Device* dev) {
    printf("Device exiting SHUTTING DOWN state\n");
}

// State transition table
typedef struct {
    DeviceState current_state;
    DeviceEvent event;
    DeviceState next_state;
    void (*exit_action)(Device*);
    void (*entry_action)(Device*);
} Transition;

Transition transitions[] = {
    {STATE_OFF, EVENT_TURN_ON, STATE_STARTING, exit_off, enter_starting},
    {STATE_STARTING, EVENT_STARTUP_COMPLETE, STATE_ON, exit_starting, enter_on},
    {STATE_STARTING, EVENT_ERROR, STATE_OFF, exit_starting, enter_off},
    {STATE_ON, EVENT_TURN_OFF, STATE_SHUTTING_DOWN, exit_on, enter_shutting_down},
    {STATE_SHUTTING_DOWN, EVENT_SHUTDOWN_COMPLETE, STATE_OFF, exit_shutting_down, enter_off},
    {STATE_SHUTTING_DOWN, EVENT_ERROR, STATE_OFF, exit_shutting_down, enter_off}
};

#define NUM_TRANSITIONS (sizeof(transitions) / sizeof(transitions[0]))

void device_init(Device* dev) {
    dev->state = STATE_OFF;
    enter_off(dev);
}

bool device_process_event(Device* dev, DeviceEvent event) {
    for (size_t i = 0; i < NUM_TRANSITIONS; i++) {
        if (transitions[i].current_state == dev->state &&
            transitions[i].event == event) {

            // Execute exit action
            if (transitions[i].exit_action) {
                transitions[i].exit_action(dev);
            }

            // Change state
            dev->state = transitions[i].next_state;

            // Execute entry action
            if (transitions[i].entry_action) {
                transitions[i].entry_action(dev);
            }

            return true;
        }
    }

    printf("Invalid event %d in state %d\n", event, dev->state);
    return false;
}

int main() {
    Device dev;
    device_init(&dev);

    // Simulate device operation
    device_process_event(&dev, EVENT_TURN_ON);
    sleep(2);  // Simulate startup time
    device_process_event(&dev, EVENT_STARTUP_COMPLETE);

    sleep(5);  // Device operating
    device_process_event(&dev, EVENT_TURN_OFF);
    sleep(1);  // Simulate shutdown time
    device_process_event(&dev, EVENT_SHUTDOWN_COMPLETE);

    return 0;
}
```

## Hierarchical State Machines
```c
typedef enum {
    // Top level states
    STATE_TOP,

    // Motor states
    STATE_MOTOR_OFF,
    STATE_MOTOR_STARTING,
    STATE_MOTOR_RUNNING,
    STATE_MOTOR_ERROR,

    // Running substates
    STATE_MOTOR_RUNNING_NORMAL,
    STATE_MOTOR_RUNNING_OVERLOAD
} MotorState;

typedef enum {
    EVENT_POWER_ON,
    EVENT_POWER_OFF,
    EVENT_START_MOTOR,
    EVENT_STOP_MOTOR,
    EVENT_OVERLOAD_DETECTED,
    EVENT_OVERLOAD_CLEARED,
    EVENT_ERROR_CLEARED
} MotorEvent;

typedef struct {
    MotorState state;
    int speed;
    int temperature;
    bool overload_detected;
} MotorController;

// Check if state is a substate of running
bool is_running_substate(MotorState state) {
    return state == STATE_MOTOR_RUNNING_NORMAL ||
           state == STATE_MOTOR_RUNNING_OVERLOAD;
}

// Get parent state
MotorState get_parent_state(MotorState state) {
    if (is_running_substate(state)) {
        return STATE_MOTOR_RUNNING;
    }
    return STATE_TOP;
}

void motor_process_event(MotorController* motor, MotorEvent event) {
    MotorState current = motor->state;

    switch (current) {
        case STATE_MOTOR_OFF:
            if (event == EVENT_POWER_ON) {
                motor->state = STATE_MOTOR_OFF;  // Stay in OFF, but powered
                printf("Motor powered on (still off)\n");
            }
            break;

        case STATE_MOTOR_STARTING:
            if (event == EVENT_START_MOTOR) {
                motor->state = STATE_MOTOR_RUNNING_NORMAL;
                motor->speed = 1500;  // RPM
                printf("Motor started, speed = %d RPM\n", motor->speed);
            }
            break;

        case STATE_MOTOR_RUNNING_NORMAL:
            if (event == EVENT_OVERLOAD_DETECTED) {
                motor->state = STATE_MOTOR_RUNNING_OVERLOAD;
                motor->overload_detected = true;
                printf("Overload detected!\n");
            } else if (event == EVENT_STOP_MOTOR) {
                motor->state = STATE_MOTOR_OFF;
                motor->speed = 0;
                printf("Motor stopped\n");
            }
            break;

        case STATE_MOTOR_RUNNING_OVERLOAD:
            if (event == EVENT_OVERLOAD_CLEARED) {
                motor->state = STATE_MOTOR_RUNNING_NORMAL;
                motor->overload_detected = false;
                printf("Overload cleared\n");
            } else if (event == EVENT_STOP_MOTOR) {
                motor->state = STATE_MOTOR_OFF;
                motor->speed = 0;
                printf("Motor emergency stop\n");
            }
            break;

        case STATE_MOTOR_ERROR:
            if (event == EVENT_ERROR_CLEARED) {
                motor->state = STATE_MOTOR_OFF;
                printf("Error cleared, motor off\n");
            }
            break;
    }

    if (current != motor->state) {
        printf("State changed: %d -> %d\n", current, motor->state);
    }
}

int main() {
    MotorController motor = {STATE_MOTOR_OFF, 0, 25, false};

    motor_process_event(&motor, EVENT_POWER_ON);
    motor_process_event(&motor, EVENT_START_MOTOR);
    motor_process_event(&motor, EVENT_OVERLOAD_DETECTED);
    motor_process_event(&motor, EVENT_OVERLOAD_CLEARED);
    motor_process_event(&motor, EVENT_STOP_MOTOR);

    return 0;
}
```

## State Machine with Guards
```c
#include <stdbool.h>

typedef enum {
    STATE_LOCKED,
    STATE_UNLOCKED
} DoorState;

typedef enum {
    EVENT_COIN,
    EVENT_PUSH,
    EVENT_PULL
} DoorEvent;

typedef struct {
    DoorState state;
    int coins_inserted;
    bool door_open;
} Turnstile;

// Guard conditions
bool has_enough_coins(Turnstile* turnstile) {
    return turnstile->coins_inserted >= 1;
}

bool door_is_closed(Turnstile* turnstile) {
    return !turnstile->door_open;
}

void turnstile_process_event(Turnstile* turnstile, DoorEvent event) {
    switch (turnstile->state) {
        case STATE_LOCKED:
            if (event == EVENT_COIN) {
                turnstile->coins_inserted++;
                if (has_enough_coins(turnstile)) {
                    turnstile->state = STATE_UNLOCKED;
                    printf("Coin inserted, door unlocked\n");
                } else {
                    printf("Coin inserted, need more coins\n");
                }
            } else if (event == EVENT_PUSH && door_is_closed(turnstile)) {
                printf("Door is locked, cannot push\n");
            }
            break;

        case STATE_UNLOCKED:
            if (event == EVENT_PUSH && door_is_closed(turnstile)) {
                turnstile->door_open = true;
                turnstile->state = STATE_LOCKED;
                turnstile->coins_inserted = 0;  // Reset for next user
                printf("Door pushed open, now locked again\n");
            } else if (event == EVENT_COIN) {
                printf("Already unlocked, coin returned\n");
            }
            break;
    }
}

int main() {
    Turnstile turnstile = {STATE_LOCKED, 0, false};

    turnstile_process_event(&turnstile, EVENT_PUSH);    // Should fail
    turnstile_process_event(&turnstile, EVENT_COIN);    // Unlock
    turnstile_process_event(&turnstile, EVENT_COIN);    // Extra coin
    turnstile_process_event(&turnstile, EVENT_PUSH);    // Open door

    return 0;
}
```

## State Machine Best Practices
- Keep states and events clearly defined
- Use meaningful names for states and events
- Document state transition diagrams
- Implement entry/exit actions consistently
- Use guard conditions for complex transitions
- Test all possible state transitions
- Avoid unreachable states
- Consider hierarchical states for complex systems
- Document preconditions and postconditions

## Common State Machine Patterns
### Command Processor
```c
typedef enum {
    STATE_READY,
    STATE_PROCESSING_COMMAND,
    STATE_WAITING_RESPONSE
} CommandState;

typedef enum {
    EVENT_COMMAND_RECEIVED,
    EVENT_PROCESSING_COMPLETE,
    EVENT_RESPONSE_RECEIVED,
    EVENT_TIMEOUT
} CommandEvent;
```

### Network Connection
```c
typedef enum {
    STATE_DISCONNECTED,
    STATE_CONNECTING,
    STATE_CONNECTED,
    STATE_DISCONNECTING
} ConnectionState;

typedef enum {
    EVENT_CONNECT_REQUEST,
    EVENT_CONNECTION_ESTABLISHED,
    EVENT_CONNECTION_LOST,
    EVENT_DISCONNECT_REQUEST
} ConnectionEvent;
```

### Device Control
```c
typedef enum {
    STATE_UNINITIALIZED,
    STATE_INITIALIZING,
    STATE_READY,
    STATE_OPERATING,
    STATE_ERROR,
    STATE_MAINTENANCE
} DeviceState;

typedef enum {
    EVENT_INIT,
    EVENT_INIT_COMPLETE,
    EVENT_START_OPERATION,
    EVENT_STOP_OPERATION,
    EVENT_ERROR_DETECTED,
    EVENT_ERROR_CLEARED,
    EVENT_MAINTENANCE_MODE
} DeviceEvent;
```

## Embedded Systems Applications
### Traffic Light Controller
```c
typedef enum {
    STATE_RED,
    STATE_RED_YELLOW,
    STATE_GREEN,
    STATE_YELLOW
} TrafficLightState;

typedef enum {
    EVENT_TIMER_EXPIRED,
    EVENT_PEDESTRIAN_BUTTON,
    EVENT_EMERGENCY_VEHICLE
} TrafficLightEvent;

// State machine controls traffic lights with pedestrian crossing
```

### Motor Speed Controller
```c
typedef enum {
    STATE_STOPPED,
    STATE_ACCELERATING,
    STATE_AT_SPEED,
    STATE_DECELERATING,
    STATE_BRAKING
} MotorState;

typedef enum {
    EVENT_START_REQUEST,
    EVENT_SPEED_REACHED,
    EVENT_STOP_REQUEST,
    EVENT_OVERLOAD,
    EVENT_EMERGENCY_STOP
} MotorEvent;

// Controls motor startup, speed regulation, and emergency stopping
```

### Communication Protocol Handler
```c
typedef enum {
    STATE_IDLE,
    STATE_WAITING_ACK,
    STATE_TRANSMITTING,
    STATE_RECEIVING,
    STATE_ERROR_RECOVERY
} ProtocolState;

typedef enum {
    EVENT_DATA_TO_SEND,
    EVENT_ACK_RECEIVED,
    EVENT_NACK_RECEIVED,
    EVENT_TIMEOUT,
    EVENT_TRANSMIT_COMPLETE
} ProtocolEvent;

// Manages reliable data transmission with acknowledgments
```

## Testing State Machines
```c
// State machine test framework
typedef struct {
    SystemState initial_state;
    SystemEvent event;
    SystemState expected_state;
    const char* description;
} StateTransitionTest;

StateTransitionTest tests[] = {
    {STATE_IDLE, EVENT_START, STATE_RUNNING, "Start from idle"},
    {STATE_RUNNING, EVENT_PAUSE, STATE_PAUSED, "Pause while running"},
    {STATE_PAUSED, EVENT_RESUME, STATE_RUNNING, "Resume from pause"},
    {STATE_RUNNING, EVENT_STOP, STATE_STOPPED, "Stop from running"},
    {STATE_STOPPED, EVENT_RESET, STATE_IDLE, "Reset from stopped"}
};

void run_state_machine_tests() {
    StateMachine sm;

    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        state_machine_init(&sm);
        // Set initial state if needed

        state_machine_process_event(&sm, tests[i].event);

        if (sm.current_state == tests[i].expected_state) {
            printf("PASS: %s\n", tests[i].description);
        } else {
            printf("FAIL: %s (expected %d, got %d)\n",
                   tests[i].description, tests[i].expected_state, sm.current_state);
        }
    }
}
```