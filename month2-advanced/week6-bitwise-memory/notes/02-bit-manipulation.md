# 02: Bit Manipulation

## Bit Manipulation Techniques
Advanced techniques for working with individual bits and bit fields.

## Setting Individual Bits
```c
// Set bit at position n
#define SET_BIT(value, n) ((value) | (1U << (n)))

unsigned int flags = 0;
flags = SET_BIT(flags, 3);  // Set bit 3
printf("Flags: 0x%X\n", flags);  // 0x8

// Multiple bits
flags = SET_BIT(flags, 1);  // Set bit 1
printf("Flags: 0x%X\n", flags);  // 0xA
```

## Clearing Individual Bits
```c
// Clear bit at position n
#define CLEAR_BIT(value, n) ((value) & ~(1U << (n)))

unsigned int flags = 0xF;  // 1111
flags = CLEAR_BIT(flags, 1);  // Clear bit 1
printf("Flags: 0x%X\n", flags);  // 0xD (1101)
```

## Toggling Individual Bits
```c
// Toggle bit at position n
#define TOGGLE_BIT(value, n) ((value) ^ (1U << (n)))

unsigned int flags = 0xA;  // 1010
flags = TOGGLE_BIT(flags, 1);  // Toggle bit 1
printf("Flags: 0x%X\n", flags);  // 0x8 (1000)
flags = TOGGLE_BIT(flags, 1);  // Toggle again
printf("Flags: 0x%X\n", flags);  // 0xA (1010)
```

## Testing Individual Bits
```c
// Check if bit n is set
#define IS_BIT_SET(value, n) (((value) >> (n)) & 1U)

unsigned int status = 0x5;  // 0101
printf("Bit 0 set: %d\n", IS_BIT_SET(status, 0));  // 1
printf("Bit 1 set: %d\n", IS_BIT_SET(status, 1));  // 0
printf("Bit 2 set: %d\n", IS_BIT_SET(status, 2));  // 1
```

## Bit Masks
### Creating Masks
```c
// Create mask with bits from start to end set
#define BIT_MASK(start, end) (((1U << ((end) - (start) + 1)) - 1) << (start))

unsigned int mask = BIT_MASK(2, 5);  // Bits 2, 3, 4, 5 set
printf("Mask: 0x%X\n", mask);  // 0x3C (00111100)
```

### Extracting Bit Fields
```c
// Extract bits from position start to end
#define EXTRACT_BITS(value, start, end) \
    (((value) >> (start)) & ((1U << ((end) - (start) + 1)) - 1))

unsigned int data = 0xABCD;  // 1010101111001101
unsigned int field = EXTRACT_BITS(data, 4, 7);
printf("Bits 4-7: 0x%X\n", field);  // 0xC (1100)
```

### Setting Bit Fields
```c
// Set bits from start to end with new value
#define SET_BITS(value, start, end, new_val) \
    (((value) & ~BIT_MASK(start, end)) | \
     (((new_val) << (start)) & BIT_MASK(start, end)))

unsigned int reg = 0xFF;  // 11111111
reg = SET_BITS(reg, 2, 5, 0xA);  // Set bits 2-5 to 1010
printf("Result: 0x%X\n", reg);  // 0xEB (11101011)
```

## Bit Rotation
### Left Rotation
```c
unsigned int rotate_left(unsigned int value, int n, int width) {
    n %= width;  // Handle large rotations
    return (value << n) | (value >> (width - n));
}

unsigned int val = 0x12345678;
unsigned int rotated = rotate_left(val, 8, 32);
printf("0x%X rotated left by 8: 0x%X\n", val, rotated);
```

### Right Rotation
```c
unsigned int rotate_right(unsigned int value, int n, int width) {
    n %= width;
    return (value >> n) | (value << (width - n));
}

unsigned int val = 0x12345678;
unsigned int rotated = rotate_right(val, 8, 32);
printf("0x%X rotated right by 8: 0x%X\n", val, rotated);
```

## Bit Reversal
```c
unsigned int reverse_bits(unsigned int n) {
    unsigned int result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

unsigned int val = 0x12345678;
unsigned int reversed = reverse_bits(val);
printf("0x%X reversed: 0x%X\n", val, reversed);
```

## Bit Counting
### Count Set Bits (Hamming Weight)
```c
int count_set_bits(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// More efficient version
int count_set_bits_fast(unsigned int n) {
    int count = 0;
    while (n) {
        n &= n - 1;  // Clear least significant set bit
        count++;
    }
    return count;
}

printf("Bits in 0xABCD: %d\n", count_set_bits_fast(0xABCD));
```

### Find First Set Bit
```c
int find_first_set_bit(unsigned int n) {
    if (n == 0) return -1;  // No bits set

    int position = 0;
    while ((n & 1) == 0) {
        n >>= 1;
        position++;
    }
    return position;
}

printf("First set bit in 0x10: %d\n", find_first_set_bit(0x10));  // 4
```

## Gray Code
```c
// Convert binary to Gray code
unsigned int binary_to_gray(unsigned int n) {
    return n ^ (n >> 1);
}

// Convert Gray code to binary
unsigned int gray_to_binary(unsigned int n) {
    unsigned int result = n;
    while (n >>= 1) {
        result ^= n;
    }
    return result;
}

unsigned int binary = 5;  // 0101
unsigned int gray = binary_to_gray(binary);  // 0111
unsigned int back = gray_to_binary(gray);    // 0101
printf("Binary: %u -> Gray: %u -> Binary: %u\n", binary, gray, back);
```

## Bit Interleaving
```c
// Interleave bits of two 16-bit numbers into 32-bit result
unsigned int interleave_bits(unsigned short x, unsigned short y) {
    unsigned int result = 0;
    for (int i = 0; i < 16; i++) {
        result |= ((x >> i) & 1) << (2 * i);
        result |= ((y >> i) & 1) << (2 * i + 1);
    }
    return result;
}

unsigned short a = 0xAAAA;  // 1010101010101010
unsigned short b = 0x5555;  // 0101010101010101
unsigned int interleaved = interleave_bits(a, b);
printf("Interleaved: 0x%08X\n", interleaved);
```

## Best Practices
- Use unsigned types for bit operations
- Define bit positions as named constants
- Create helper functions for complex operations
- Document bit field layouts clearly
- Test edge cases (all bits set/clear, boundary conditions)
- Consider portability across different architectures

## Common Mistakes
- Shifting by amounts >= type width (undefined)
- Assuming bit field order (endianness)
- Mixing signed/unsigned in bit operations
- Not handling overflow in rotations
- Confusing bit positions (0-based vs 1-based)
- Using wrong mask sizes for bit fields