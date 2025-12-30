# 02: Multidimensional Arrays

## What are Multidimensional Arrays?
Arrays with more than one dimension, like matrices or tables.

## 2D Arrays (Matrices)
### Declaration
```c
// type array_name[rows][columns];
int matrix[3][4];     // 3 rows, 4 columns
char board[8][8];     // Chess board
double table[10][5];  // Data table
```

### Initialization
```c
// Method 1: Complete initialization
int matrix[2][3] = {
    {1, 2, 3},      // Row 0
    {4, 5, 6}       // Row 1
};

// Method 2: Partial initialization
int matrix2[2][3] = {
    {1, 2},         // Row 0: {1, 2, 0}
    {4}             // Row 1: {4, 0, 0}
};

// Method 3: All elements zero
int matrix3[2][3] = {0};

// Method 4: Size determined by initializer
int matrix4[][3] = {
    {1, 2, 3},
    {4, 5, 6}
};  // 2 rows, 3 columns
```

### Accessing Elements
```c
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

printf("%d\n", matrix[0][0]);  // 1 (row 0, col 0)
printf("%d\n", matrix[1][2]);  // 7 (row 1, col 2)
printf("%d\n", matrix[2][3]);  // 12 (row 2, col 3)

// Modify elements
matrix[1][1] = 99;
```

## Traversing 2D Arrays
### Row-major Order (Standard)
```c
void print_matrix(int matrix[][4], int rows, int cols) {
    for (int i = 0; i < rows; i++) {        // Rows
        for (int j = 0; j < cols; j++) {    // Columns
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Usage
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};
print_matrix(matrix, 3, 4);
```

### Column-major Order
```c
void print_matrix_cols(int matrix[][4], int rows, int cols) {
    for (int j = 0; j < cols; j++) {        // Columns first
        for (int i = 0; i < rows; i++) {    // Then rows
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
```

## 3D Arrays
### Declaration and Initialization
```c
// type array_name[depth][rows][columns];
int cube[2][3][4];  // 2 layers, 3 rows, 4 columns

// Initialization
int cube[2][3][4] = {
    {   // Layer 0
        {1, 2, 3, 4},      // Row 0
        {5, 6, 7, 8},      // Row 1
        {9, 10, 11, 12}    // Row 2
    },
    {   // Layer 1
        {13, 14, 15, 16},  // Row 0
        {17, 18, 19, 20},  // Row 1
        {21, 22, 23, 24}   // Row 2
    }
};
```

### Accessing 3D Array Elements
```c
cube[0][1][2] = 42;  // Layer 0, Row 1, Column 2
printf("%d\n", cube[1][0][3]);  // 16
```

## Arrays as Function Parameters
### 2D Arrays
```c
// Method 1: Fixed column size
void process_matrix(int matrix[][4], int rows) {
    // Can only work with 4-column matrices
}

// Method 2: Using pointer to array
void process_matrix_ptr(int (*matrix)[4], int rows) {
    // Same as above
}

// Method 3: Flattened approach (recommended)
void process_matrix_flat(int* matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value = matrix[i * cols + j];
            // Process value
        }
    }
}

// Usage
int matrix[3][4] = {...};
process_matrix_flat(&matrix[0][0], 3, 4);
```

### 3D Arrays
```c
void process_cube(int cube[][3][4], int depth) {
    // Fixed dimensions for rows and columns
}

void process_cube_flat(int* cube, int depth, int rows, int cols) {
    for (int d = 0; d < depth; d++) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int index = d * rows * cols + r * cols + c;
                int value = cube[index];
            }
        }
    }
}
```

## Common Operations on 2D Arrays
### Matrix Addition
```c
void add_matrices(int result[][3], int a[][3], int b[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}
```

### Matrix Transpose
```c
void transpose(int result[][3], int matrix[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}
```

### Finding Maximum in Matrix
```c
int find_matrix_max(int matrix[][4], int rows, int cols) {
    int max = matrix[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
    }
    return max;
}
```

## Memory Layout
### Row-major Order
Elements stored row by row in memory:
```
matrix[2][3] = {
    {1, 2, 3},  // Row 0
    {4, 5, 6}   // Row 1
}

// Memory: 1, 2, 3, 4, 5, 6
```

### Calculating Address
For `matrix[i][j]` in row-major order:
```
address = base_address + (i * columns + j) * sizeof(element)
```

## Variable-Length Arrays (VLA)
C99 allows variable dimensions:
```c
void process_vla(int rows, int cols) {
    int matrix[rows][cols];  // VLA
    // Use matrix...
}

// But cannot return VLAs or use in global scope
```

## Best Practices
- Use meaningful names for dimensions
- Document row/column meanings
- Consider using 1D arrays for flexibility
- Be careful with large multidimensional arrays (stack space)
- Use const for read-only matrix parameters

## Common Mistakes
- Forgetting arrays are zero-indexed
- Mixing up row/column indices
- Not specifying column size in function parameters
- Stack overflow with large arrays
- Confusing dimensions when declaring