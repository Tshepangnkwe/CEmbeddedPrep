# 01: Bitwise Operators

## What are Bitwise Operators?
Bitwise operators manipulate individual bits within integer values. Essential for embedded programming, low-level operations, and performance optimization.

## Bitwise AND (&)
Performs AND operation on each bit pair:
```c
//  1010 (10 in decimal)
//& 1100 (12 in decimal)
//  ----
//  1000 (8 in decimal)

int result = 10 & 12;  // result = 8
printf("%d & %d = %d\n", 10, 12, result);

// Common uses:
// Clear bits: value & ~mask
// Test bits: value & mask
int flags = 0b1011;  // 11 in decimal
int mask = 0b1000;   // 8 in decimal
if (flags & mask) {  // Test if bit 3 is set
    printf("Bit 3 is set\n");
}
```

## Bitwise OR (|)
Performs OR operation on each bit pair:
```c
//  1010 (10)
//| 1100 (12)
//  ----
//  1110 (14)

int result = 10 | 12;  // result = 14
printf("%d | %d = %d\n", 10, 12, result);

// Common uses:
// Set bits: value | mask
int flags = 0b0010;  // 2
flags = flags | 0b1000;  // Set bit 3
printf("Flags: 0x%X\n", flags);  // 0xA (10)
```

## Bitwise XOR (^)
Performs XOR operation on each bit pair:
```c
//  1010 (10)
//^ 1100 (12)
//  ----
//  0110 (6)

int result = 10 ^ 12;  // result = 6
printf("%d ^ %d = %d\n", 10, 12, result);

// Common uses:
// Toggle bits: value ^ mask
// Swap values without temp variable
void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
```

## Bitwise NOT (~)
Flips all bits:
```c
// ~1010 = 0101 (in 4 bits, but actually depends on int size)

int x = 10;
int result = ~x;
printf("~%d = %d\n", x, result);

// For 32-bit int:
// ~10 = -11 (two's complement)

// Common uses:
// Create masks: ~(mask)
int mask = 0x0F;  // 00001111
int inverted = ~mask;  // 11110000
```

## Left Shift (<<)
Shifts bits to the left, filling with zeros:
```c
// 1010 << 1 = 10100 (20)
// 1010 << 2 = 101000 (40)

int x = 10;  // 1010
printf("%d << 1 = %d\n", x, x << 1);  // 20
printf("%d << 2 = %d\n", x, x << 2);  // 40

// Common uses:
// Multiply by powers of 2: x << n is x * (2^n)
// Set bit at position: 1 << position
int bit_mask = 1 << 3;  // 0b1000 (8)
```

## Right Shift (>>)
Shifts bits to the right:
```c
// For unsigned: fills with zeros
// 10100 >> 1 = 01010 (10)
// 10100 >> 2 = 00101 (5)

// For signed: may fill with sign bit (implementation defined)
int x = 20;  // 10100
printf("%d >> 1 = %d\n", x, x >> 1);  // 10
printf("%d >> 2 = %d\n", x, x >> 2);  // 5

// Common uses:
// Divide by powers of 2: x >> n is x / (2^n)
// Extract bits: (value >> position) & mask
int value = 0b110110;
int bit2 = (value >> 2) & 1;  // Extract bit 2
```

## Operator Precedence
Bitwise operators have lower precedence than arithmetic:
```c
int x = 5;
int result = x & 3 + 2;  // (x & 3) + 2 = 0 + 2 = 2
// Not: x & (3 + 2) = 5 & 5 = 5

// Use parentheses for clarity:
int clear_low_bits = value & ~( (1 << n) - 1 );
```

## Practical Examples
### Check if number is power of 2
```c
int is_power_of_two(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

printf("8 is power of 2: %d\n", is_power_of_two(8));   // 1
printf("6 is power of 2: %d\n", is_power_of_two(6));   // 0
```

### Count set bits (population count)
```c
int count_bits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

printf("Bits in 13 (1101): %d\n", count_bits(13));  // 3
```

### Reverse bits
```c
unsigned int reverse_bits(unsigned int n) {
    unsigned int result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

printf("Reverse of 13 (1101): %u\n", reverse_bits(13));  // 2952790016 (in 32-bit)
```

## Best Practices
- Use unsigned types for bit operations when possible
- Be careful with right shift on signed numbers
- Use parentheses to clarify precedence
- Comment complex bit operations
- Consider endianness in cross-platform code
- Use named constants for bit positions

## Common Mistakes
- Confusing bitwise and logical operators (& vs &&, | vs ||)
- Shifting by more than type width (undefined behavior)
- Assuming right shift fills with zeros for signed types
- Not considering operator precedence
- Using bitwise ops on floating point (doesn't work)
- Forgetting two's complement representation