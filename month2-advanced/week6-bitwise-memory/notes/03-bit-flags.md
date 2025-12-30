# 03: Bit Flags

## What are Bit Flags?
Bit flags use individual bits to represent boolean states, allowing multiple flags in a single integer. Efficient for embedded systems with limited memory.

## Basic Bit Flag Operations
```c
typedef enum {
    FLAG_READ    = 1 << 0,  // 0001 (1)
    FLAG_WRITE   = 1 << 1,  // 0010 (2)
    FLAG_EXECUTE = 1 << 2,  // 0100 (4)
    FLAG_DELETE  = 1 << 3   // 1000 (8)
} FilePermission_t;

unsigned int permissions = 0;

// Set flags
permissions |= FLAG_READ | FLAG_WRITE;
printf("Permissions: 0x%X\n", permissions);  // 0x3

// Test flags
if (permissions & FLAG_READ) {
    printf("Can read\n");
}

if (permissions & FLAG_DELETE) {
    printf("Can delete\n");
} else {
    printf("Cannot delete\n");
}

// Clear flags
permissions &= ~FLAG_WRITE;
printf("After clearing write: 0x%X\n", permissions);  // 0x1

// Toggle flags
permissions ^= FLAG_EXECUTE;
printf("After toggling execute: 0x%X\n", permissions);  // 0x5
```

## Flag Sets and Combinations
```c
#define PERM_NONE     0x00
#define PERM_READ     0x01
#define PERM_WRITE    0x02
#define PERM_EXECUTE  0x04
#define PERM_DELETE   0x08
#define PERM_ALL      0x0F

// Check multiple flags
unsigned int user_perms = PERM_READ | PERM_WRITE;

if ((user_perms & (PERM_READ | PERM_WRITE)) == (PERM_READ | PERM_WRITE)) {
    printf("User has read and write permissions\n");
}

// Check if any flag is set
if (user_perms & (PERM_EXECUTE | PERM_DELETE)) {
    printf("User has some advanced permissions\n");
}
```

## Flag Macros
```c
#define SET_FLAG(flags, flag)    ((flags) |= (flag))
#define CLEAR_FLAG(flags, flag)  ((flags) &= ~(flag))
#define TOGGLE_FLAG(flags, flag) ((flags) ^= (flag))
#define CHECK_FLAG(flags, flag)  ((flags) & (flag))

#define SET_FLAGS(flags, mask)   ((flags) |= (mask))
#define CLEAR_FLAGS(flags, mask) ((flags) &= ~(mask))
#define CHECK_FLAGS(flags, mask) ((flags) & (mask))

// Usage
unsigned int status = 0;

SET_FLAG(status, FLAG_READ);
if (CHECK_FLAG(status, FLAG_READ)) {
    printf("Read flag is set\n");
}

SET_FLAGS(status, FLAG_WRITE | FLAG_EXECUTE);
printf("Status: 0x%X\n", status);
```

## State Machines with Bit Flags
```c
typedef enum {
    STATE_IDLE      = 1 << 0,
    STATE_RUNNING   = 1 << 1,
    STATE_PAUSED    = 1 << 2,
    STATE_ERROR     = 1 << 3,
    STATE_FINISHED  = 1 << 4
} SystemState_t;

typedef enum {
    EVENT_START     = 1 << 0,
    EVENT_STOP      = 1 << 1,
    EVENT_PAUSE     = 1 << 2,
    EVENT_RESUME    = 1 << 3,
    EVENT_ERROR     = 1 << 4
} SystemEvent_t;

void handle_event(SystemState_t* state, SystemEvent_t event) {
    switch (*state) {
        case STATE_IDLE:
            if (event == EVENT_START) {
                *state = STATE_RUNNING;
            }
            break;

        case STATE_RUNNING:
            if (event == EVENT_PAUSE) {
                *state = STATE_PAUSED;
            } else if (event == EVENT_STOP) {
                *state = STATE_FINISHED;
            } else if (event == EVENT_ERROR) {
                *state = STATE_ERROR;
            }
            break;

        case STATE_PAUSED:
            if (event == EVENT_RESUME) {
                *state = STATE_RUNNING;
            } else if (event == EVENT_STOP) {
                *state = STATE_FINISHED;
            }
            break;

        default:
            // Handle error states
            break;
    }
}
```

## Configuration Flags
```c
typedef enum {
    CONFIG_DEBUG        = 1 << 0,
    CONFIG_VERBOSE      = 1 << 1,
    CONFIG_AUTO_SAVE    = 1 << 2,
    CONFIG_SOUND        = 1 << 3,
    CONFIG_FULLSCREEN   = 1 << 4,
    CONFIG_VSYNC        = 1 << 5
} ConfigFlag_t;

typedef struct {
    const char* name;
    ConfigFlag_t flag;
} ConfigOption_t;

ConfigOption_t options[] = {
    {"debug", CONFIG_DEBUG},
    {"verbose", CONFIG_VERBOSE},
    {"auto-save", CONFIG_AUTO_SAVE},
    {"sound", CONFIG_SOUND},
    {"fullscreen", CONFIG_FULLSCREEN},
    {"vsync", CONFIG_VSYNC}
};

unsigned int load_config(const char* filename) {
    unsigned int config = 0;
    // Load from file and set appropriate flags
    config |= CONFIG_DEBUG | CONFIG_SOUND;
    return config;
}

void print_config(unsigned int config) {
    printf("Configuration:\n");
    for (size_t i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
        if (config & options[i].flag) {
            printf("  %s: enabled\n", options[i].name);
        } else {
            printf("  %s: disabled\n", options[i].name);
        }
    }
}
```

## Hardware Register Simulation
```c
typedef struct {
    unsigned int control;
    unsigned int status;
    unsigned int data;
} DeviceRegisters_t;

// Control register flags
#define CTRL_ENABLE     (1 << 0)
#define CTRL_RESET      (1 << 1)
#define CTRL_INTERRUPT  (1 << 2)
#define CTRL_MODE_MASK  (0x3 << 3)  // Bits 3-4
#define CTRL_MODE_0     (0x0 << 3)
#define CTRL_MODE_1     (0x1 << 3)
#define CTRL_MODE_2     (0x2 << 3)

// Status register flags
#define STATUS_READY    (1 << 0)
#define STATUS_ERROR    (1 << 1)
#define STATUS_BUSY     (1 << 2)

void device_init(DeviceRegisters_t* dev) {
    dev->control = 0;
    dev->status = STATUS_READY;
}

void device_start(DeviceRegisters_t* dev) {
    // Set enable and mode
    dev->control |= CTRL_ENABLE | CTRL_MODE_1;

    // Clear reset if set
    dev->control &= ~CTRL_RESET;

    // Set busy status
    dev->status |= STATUS_BUSY;
    dev->status &= ~STATUS_READY;
}

int device_is_ready(DeviceRegisters_t* dev) {
    return (dev->status & STATUS_READY) && !(dev->status & STATUS_BUSY);
}
```

## Flag Validation
```c
// Check if flags are valid (no extra bits set)
int validate_flags(unsigned int flags, unsigned int valid_mask) {
    return (flags & ~valid_mask) == 0;
}

// Check if exactly one flag is set
int is_single_flag(unsigned int flags) {
    return flags != 0 && (flags & (flags - 1)) == 0;
}

// Count set flags
int count_flags(unsigned int flags) {
    int count = 0;
    while (flags) {
        flags &= flags - 1;  // Clear least significant set bit
        count++;
    }
    return count;
}

int main() {
    unsigned int perms = FLAG_READ | FLAG_WRITE;

    if (validate_flags(perms, PERM_ALL)) {
        printf("Valid permissions\n");
    }

    printf("Number of permissions: %d\n", count_flags(perms));

    if (is_single_flag(FLAG_READ)) {
        printf("Single permission set\n");
    }
}
```

## Best Practices
- Define flag constants with meaningful names
- Use hex or binary literals for clarity
- Document flag meanings and bit positions
- Group related flags together
- Validate flag combinations when necessary
- Use unsigned integers for flag variables
- Consider using structs with bit fields for complex flags

## Common Mistakes
- Using overlapping flag values
- Not initializing flag variables to 0
- Confusing flag setting with testing
- Using wrong operators (& vs &&, | vs ||)
- Assuming flag order in memory
- Not handling invalid flag combinations