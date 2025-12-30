# Bitwise Operations Cheatsheet

## Basic Operators

| Operator | Name | Description | Example |
|----------|------|-------------|---------|
| `&` | AND | Sets bit to 1 if both bits are 1 | `a & b` |
| `\|` | OR | Sets bit to 1 if either bit is 1 | `a \| b` |
| `^` | XOR | Sets bit to 1 if bits are different | `a ^ b` |
| `~` | NOT | Inverts all bits | `~a` |
| `<<` | Left Shift | Shifts bits left by n positions | `a << n` |
| `>>` | Right Shift | Shifts bits right by n positions | `a >> n` |

## Common Patterns

### Setting a Bit
```c
// Set bit n in x
x |= (1 << n);
```

### Clearing a Bit
```c
// Clear bit n in x
x &= ~(1 << n);
```

### Toggling a Bit
```c
// Toggle bit n in x
x ^= (1 << n);
```

### Checking a Bit
```c
// Check if bit n is set in x
if (x & (1 << n)) {
    // Bit is set
}
```

### Bit Masks
```c
#define MASK_BIT_0 0x01  // 00000001
#define MASK_BIT_1 0x02  // 00000010
#define MASK_LOWER_4 0x0F // 00001111
#define MASK_UPPER_4 0xF0 // 11110000
```

### Extracting Bits
```c
// Get lower 4 bits
uint8_t lower = value & 0x0F;

// Get bits 4-7
uint8_t middle = (value >> 4) & 0x0F;
```

### Setting Multiple Bits
```c
// Set bits 1 and 3
x |= (1 << 1) | (1 << 3);

// Clear bits 0, 2, 4
x &= ~((1 << 0) | (1 << 2) | (1 << 4));
```

## Bit Fields (Structs)

```c
struct {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int value : 6;  // 6-bit value
    unsigned int reserved : 24;
} bitfield;
```

## Common Embedded Uses

- **Register Manipulation:** Control hardware registers
- **Flag Management:** Status bits, configuration options
- **Memory Efficiency:** Pack multiple boolean values
- **Communication Protocols:** Bit-level data parsing
- **Interrupt Masks:** Enable/disable interrupts

## Examples

### RGB Color Packing
```c
// Pack RGB values into 16-bit color (5-6-5 format)
uint16_t pack_rgb(uint8_t r, uint8_t g, uint8_t b) {
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

// Unpack RGB values
void unpack_rgb(uint16_t color, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = (color >> 11) & 0x1F;
    *g = (color >> 5) & 0x3F;
    *b = color & 0x1F;
}
```

### Permission Flags
```c
#define PERM_READ    0x01
#define PERM_WRITE   0x02
#define PERM_EXECUTE 0x04

uint8_t permissions = 0;

// Grant read and write
permissions |= PERM_READ | PERM_WRITE;

// Check execute permission
if (permissions & PERM_EXECUTE) {
    // Can execute
}
```

## Performance Notes

- Bitwise operations are very fast (single CPU instructions)
- Use for performance-critical code
- Avoid when readability is more important than performance
- Consider using enums or defines for bit positions