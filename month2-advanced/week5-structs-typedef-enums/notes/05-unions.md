# 05: Unions

## What is a Union?
A union is a special data type that allows storing different data types in the same memory location. Only one member can contain a value at any given time.

## Basic Union Declaration
```c
union Data {
    int i;
    float f;
    char c;
};

int main() {
    union Data data;

    data.i = 42;
    printf("Integer: %d\n", data.i);

    data.f = 3.14;
    printf("Float: %.2f\n", data.f);  // Integer value lost

    data.c = 'A';
    printf("Char: %c\n", data.c);     // Float value lost
}
```

## Union Size
```c
union Mixed {
    char c;         // 1 byte
    int i;          // 4 bytes
    double d;       // 8 bytes
};

printf("Union size: %zu bytes\n", sizeof(union Mixed));
// Output: 8 bytes (size of largest member)
```

## Union with Struct
```c
typedef struct {
    int type;  // Indicates which union member is valid
    union {
        int int_value;
        float float_value;
        char string_value[20];
    } data;
} Variant_t;

void print_variant(Variant_t* v) {
    switch (v->type) {
        case 0:
            printf("Integer: %d\n", v->data.int_value);
            break;
        case 1:
            printf("Float: %.2f\n", v->data.float_value);
            break;
        case 2:
            printf("String: %s\n", v->data.string_value);
            break;
    }
}

int main() {
    Variant_t v1 = {0, .data.int_value = 42};
    Variant_t v2 = {1, .data.float_value = 3.14};
    Variant_t v3 = {2};
    strcpy(v3.data.string_value, "Hello");

    print_variant(&v1);
    print_variant(&v2);
    print_variant(&v3);
}
```

## Bit Fields with Unions
```c
typedef union {
    struct {
        unsigned int ready : 1;    // 1 bit
        unsigned int error : 1;    // 1 bit
        unsigned int mode : 2;     // 2 bits
        unsigned int value : 12;   // 12 bits
    } bits;
    unsigned int raw;  // Access all 16 bits as one value
} StatusRegister_t;

int main() {
    StatusRegister_t status = {0};

    status.bits.ready = 1;
    status.bits.mode = 2;
    status.bits.value = 123;

    printf("Raw value: 0x%04X\n", status.raw);
    printf("Ready: %d, Mode: %d, Value: %d\n",
           status.bits.ready, status.bits.mode, status.bits.value);
}
```

## Type Pun with Unions
```c
union FloatInt {
    float f;
    int i;
};

void print_float_bits(float value) {
    union FloatInt fi;
    fi.f = value;

    printf("Float: %.6f\n", fi.f);
    printf("Bits:  0x%08X\n", fi.i);

    // Extract sign, exponent, mantissa
    int sign = (fi.i >> 31) & 1;
    int exponent = (fi.i >> 23) & 0xFF;
    int mantissa = fi.i & 0x7FFFFF;

    printf("Sign: %d, Exponent: %d, Mantissa: 0x%06X\n",
           sign, exponent, mantissa);
}

int main() {
    print_float_bits(3.14159);
}
```

## Memory Efficient Data Structures
```c
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType_t;

typedef union {
    int int_val;
    float float_val;
    char* string_val;
} DataValue_t;

typedef struct {
    DataType_t type;
    DataValue_t value;
} GenericData_t;

// Array that can hold different types efficiently
GenericData_t data_array[100];

void set_int(GenericData_t* data, int value) {
    data->type = TYPE_INT;
    data->value.int_val = value;
}

void set_string(GenericData_t* data, const char* str) {
    data->type = TYPE_STRING;
    data->value.string_val = strdup(str);  // Allocate copy
}
```

## Serialization with Unions
```c
typedef union {
    struct {
        uint8_t header;
        uint8_t length;
        uint8_t data[10];
        uint8_t checksum;
    } packet;
    uint8_t bytes[12];  // Raw byte access
} SerialPacket_t;

uint8_t calculate_checksum(SerialPacket_t* packet) {
    uint8_t sum = 0;
    for (int i = 0; i < sizeof(packet->packet) - 1; i++) {
        sum += packet->bytes[i];
    }
    return sum;
}

void send_packet(SerialPacket_t* packet) {
    packet->packet.checksum = calculate_checksum(packet);

    // Send raw bytes
    for (int i = 0; i < sizeof(SerialPacket_t); i++) {
        send_byte(packet->bytes[i]);
    }
}
```

## Anonymous Unions (C11)
```c
typedef struct {
    char* name;
    union {  // Anonymous union
        int employee_id;
        char* department;
    };  // No union name
} Person_t;

int main() {
    Person_t person;
    person.name = "Alice";
    person.employee_id = 12345;  // Direct access

    printf("Name: %s, ID: %d\n", person.name, person.employee_id);
}
```

## Best Practices
- Always track which union member is currently valid
- Use unions for memory efficiency when appropriate
- Combine unions with enums for type safety
- Be careful with type punning (implementation defined)
- Document union usage clearly
- Consider struct padding effects

## Common Mistakes
- Accessing wrong union member
- Assuming union size is sum of members
- Memory corruption from improper type punning
- Not initializing union properly
- Using unions when structs would be clearer
- Forgetting union member scope