# 03: File IO

## File Input/Output
File I/O operations allow programs to read from and write to files on disk, enabling data persistence and configuration management.

## Basic File Operations
```c
#include <stdio.h>
#include <stdlib.h>

// Writing to a file
void write_to_file(const char* filename) {
    FILE* file = fopen(filename, "w");  // Open for writing

    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    // Write text to file
    fprintf(file, "Hello, World!\n");
    fprintf(file, "This is a test file.\n");
    fprintf(file, "Number: %d\n", 42);

    fclose(file);  // Always close the file
    printf("Data written to %s\n", filename);
}

// Reading from a file
void read_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");  // Open for reading

    if (file == NULL) {
        printf("Error opening file for reading\n");
        return;
    }

    char buffer[256];
    printf("Contents of %s:\n", filename);

    // Read line by line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main() {
    const char* filename = "test.txt";

    write_to_file(filename);
    read_from_file(filename);

    return 0;
}
```

## File Open Modes
```c
#include <stdio.h>

void demonstrate_file_modes() {
    // Write mode - creates new file or truncates existing
    FILE* f1 = fopen("write_mode.txt", "w");
    fprintf(f1, "Write mode content\n");
    fclose(f1);

    // Read mode - opens existing file for reading
    FILE* f2 = fopen("write_mode.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), f2);
    printf("Read: %s", buffer);
    fclose(f2);

    // Append mode - adds to end of file
    FILE* f3 = fopen("write_mode.txt", "a");
    fprintf(f3, "Appended content\n");
    fclose(f3);

    // Read + Write mode
    FILE* f4 = fopen("read_write.txt", "w+");
    fprintf(f4, "Initial content\n");
    rewind(f4);  // Go back to beginning
    fgets(buffer, sizeof(buffer), f4);
    printf("Read back: %s", buffer);
    fclose(f4);

    // Binary modes
    FILE* f5 = fopen("binary.dat", "wb");  // Write binary
    int data[] = {1, 2, 3, 4, 5};
    fwrite(data, sizeof(int), 5, f5);
    fclose(f5);

    FILE* f6 = fopen("binary.dat", "rb");  // Read binary
    int read_data[5];
    fread(read_data, sizeof(int), 5, f6);
    fclose(f6);

    printf("Binary data read: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", read_data[i]);
    }
    printf("\n");
}

int main() {
    demonstrate_file_modes();
    return 0;
}
```

## Binary File I/O
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to save/load
typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

void save_employee(const char* filename, Employee* emp) {
    FILE* file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    // Write entire structure
    fwrite(emp, sizeof(Employee), 1, file);
    fclose(file);
    printf("Employee saved to %s\n", filename);
}

void load_employee(const char* filename, Employee* emp) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Error opening file for reading\n");
        return;
    }

    // Read entire structure
    fread(emp, sizeof(Employee), 1, file);
    fclose(file);
    printf("Employee loaded from %s\n", filename);
}

void save_employee_array(const char* filename, Employee* employees, int count) {
    FILE* file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    // Write count first, then array
    fwrite(&count, sizeof(int), 1, file);
    fwrite(employees, sizeof(Employee), count, file);
    fclose(file);
    printf("%d employees saved to %s\n", count, filename);
}

Employee* load_employee_array(const char* filename, int* count) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Error opening file for reading\n");
        return NULL;
    }

    // Read count first
    fread(count, sizeof(int), 1, file);

    // Allocate memory for array
    Employee* employees = malloc(*count * sizeof(Employee));
    if (employees == NULL) {
        fclose(file);
        return NULL;
    }

    // Read array
    fread(employees, sizeof(Employee), *count, file);
    fclose(file);

    printf("%d employees loaded from %s\n", *count, filename);
    return employees;
}

int main() {
    // Single employee
    Employee emp1 = {"John Doe", 30, 50000.0f};
    save_employee("employee.dat", &emp1);

    Employee emp2 = {0};
    load_employee("employee.dat", &emp2);
    printf("Name: %s, Age: %d, Salary: %.2f\n", emp2.name, emp2.age, emp2.salary);

    // Array of employees
    Employee employees[] = {
        {"Alice", 25, 45000.0f},
        {"Bob", 35, 55000.0f},
        {"Charlie", 28, 48000.0f}
    };

    save_employee_array("employees.dat", employees, 3);

    int count;
    Employee* loaded = load_employee_array("employees.dat", &count);

    if (loaded) {
        for (int i = 0; i < count; i++) {
            printf("Employee %d: %s, %d, %.2f\n", i+1,
                   loaded[i].name, loaded[i].age, loaded[i].salary);
        }
        free(loaded);
    }

    return 0;
}
```

## Text File Processing
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Count words, lines, and characters in a file
typedef struct {
    int lines;
    int words;
    int characters;
} FileStats;

FileStats analyze_text_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    FileStats stats = {0, 0, 0};

    if (file == NULL) {
        printf("Error opening file\n");
        return stats;
    }

    char ch;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        stats.characters++;

        if (ch == '\n') {
            stats.lines++;
        }

        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            stats.words++;
        }
    }

    // Count the last line if file doesn't end with newline
    if (stats.characters > 0 && ch != '\n') {
        stats.lines++;
    }

    fclose(file);
    return stats;
}

// Find and replace text in file
void find_replace_in_file(const char* filename, const char* find, const char* replace) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Read entire file into memory
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* content = malloc(file_size + 1);
    fread(content, 1, file_size, content);
    content[file_size] = '\0';
    fclose(file);

    // Perform find and replace
    char* result = malloc(file_size * 2);  // Allocate extra space
    char* pos = content;
    char* result_pos = result;
    size_t find_len = strlen(find);
    size_t replace_len = strlen(replace);

    while ((pos = strstr(pos, find)) != NULL) {
        // Copy text before match
        size_t before_len = pos - content;
        memcpy(result_pos, content, before_len);
        result_pos += before_len;

        // Copy replacement
        memcpy(result_pos, replace, replace_len);
        result_pos += replace_len;

        // Move past the match
        pos += find_len;
        content = pos;
    }

    // Copy remaining text
    strcpy(result_pos, content);

    // Write back to file
    file = fopen(filename, "w");
    fprintf(file, "%s", result);
    fclose(file);

    free(content);
    free(result);
    printf("Find and replace completed\n");
}

// Read CSV file
typedef struct {
    char name[50];
    int age;
    char city[50];
} Person;

Person* read_csv_file(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *count = 0;
        return NULL;
    }

    // Count lines first
    *count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        (*count)++;
    }
    (*count)--;  // Subtract header line

    rewind(file);

    Person* people = malloc(*count * sizeof(Person));

    // Skip header
    fgets(buffer, sizeof(buffer), file);

    // Read data
    for (int i = 0; i < *count; i++) {
        if (fgets(buffer, sizeof(buffer), file)) {
            sscanf(buffer, "%[^,],%d,%[^\n]",
                   people[i].name, &people[i].age, people[i].city);
        }
    }

    fclose(file);
    return people;
}

int main() {
    // Create a test file
    FILE* test_file = fopen("test.txt", "w");
    fprintf(test_file, "Hello world\nThis is a test file\nWith multiple lines\n");
    fclose(test_file);

    // Analyze file
    FileStats stats = analyze_text_file("test.txt");
    printf("Lines: %d, Words: %d, Characters: %d\n",
           stats.lines, stats.words, stats.characters);

    // Find and replace
    find_replace_in_file("test.txt", "world", "universe");

    // Read modified file
    FILE* file = fopen("test.txt", "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);

    return 0;
}
```

## Error Handling and File Operations
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Safe file operations with error handling
FILE* safe_fopen(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file '%s': %s\n", filename, strerror(errno));
        return NULL;
    }
    return file;
}

size_t safe_fread(void* buffer, size_t size, size_t count, FILE* file) {
    size_t result = fread(buffer, size, count, file);
    if (result != count && !feof(file)) {
        fprintf(stderr, "Error reading from file: %s\n", strerror(errno));
    }
    return result;
}

size_t safe_fwrite(const void* buffer, size_t size, size_t count, FILE* file) {
    size_t result = fwrite(buffer, size, count, file);
    if (result != count) {
        fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
    }
    return result;
}

int safe_fclose(FILE* file) {
    if (fclose(file) != 0) {
        fprintf(stderr, "Error closing file: %s\n", strerror(errno));
        return EOF;
    }
    return 0;
}

// File copy function with error handling
int copy_file(const char* source, const char* destination) {
    FILE* src_file = safe_fopen(source, "rb");
    if (src_file == NULL) return -1;

    FILE* dest_file = safe_fopen(destination, "wb");
    if (dest_file == NULL) {
        fclose(src_file);
        return -1;
    }

    char buffer[8192];
    size_t bytes_read;

    while ((bytes_read = safe_fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        if (safe_fwrite(buffer, 1, bytes_read, dest_file) != bytes_read) {
            safe_fclose(src_file);
            safe_fclose(dest_file);
            return -1;
        }
    }

    safe_fclose(src_file);
    safe_fclose(dest_file);

    if (ferror(src_file)) {
        fprintf(stderr, "Error occurred during file copy\n");
        return -1;
    }

    return 0;
}

// Check if file exists
int file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Get file size
long get_file_size(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) return -1;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return size;
}

int main() {
    // Test file operations
    const char* source = "source.txt";
    const char* dest = "destination.txt";

    // Create source file
    FILE* f = safe_fopen(source, "w");
    if (f) {
        fprintf(f, "This is test content for file copying.\n");
        safe_fclose(f);
    }

    // Copy file
    if (copy_file(source, dest) == 0) {
        printf("File copied successfully\n");

        printf("Source file size: %ld bytes\n", get_file_size(source));
        printf("Destination file size: %ld bytes\n", get_file_size(dest));
    } else {
        printf("File copy failed\n");
    }

    return 0;
}
```

## Random Access Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student record for random access file
typedef struct {
    int id;
    char name[50];
    float gpa;
} StudentRecord;

#define RECORD_SIZE sizeof(StudentRecord)

// Create database file with fixed-size records
void create_student_database(const char* filename, int num_records) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error creating database\n");
        return;
    }

    // Initialize with empty records
    StudentRecord empty_record = {0, "", 0.0f};
    for (int i = 0; i < num_records; i++) {
        fwrite(&empty_record, RECORD_SIZE, 1, file);
    }

    fclose(file);
    printf("Database created with %d records\n", num_records);
}

// Add student at specific position
void add_student(const char* filename, int position, StudentRecord* student) {
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        printf("Error opening database\n");
        return;
    }

    // Seek to record position
    fseek(file, position * RECORD_SIZE, SEEK_SET);
    fwrite(student, RECORD_SIZE, 1, file);
    fclose(file);

    printf("Student added at position %d\n", position);
}

// Read student from specific position
void read_student(const char* filename, int position) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening database\n");
        return;
    }

    // Seek to record position
    fseek(file, position * RECORD_SIZE, SEEK_SET);

    StudentRecord student;
    fread(&student, RECORD_SIZE, 1, file);
    fclose(file);

    if (student.id != 0) {
        printf("Student at position %d: ID=%d, Name=%s, GPA=%.2f\n",
               position, student.id, student.name, student.gpa);
    } else {
        printf("No student at position %d\n", position);
    }
}

// Update student GPA
void update_student_gpa(const char* filename, int position, float new_gpa) {
    FILE* file = fopen(filename, "r+b");
    if (file == NULL) {
        printf("Error opening database\n");
        return;
    }

    // Seek to record position
    fseek(file, position * RECORD_SIZE, SEEK_SET);

    StudentRecord student;
    fread(&student, RECORD_SIZE, 1, file);

    if (student.id != 0) {
        student.gpa = new_gpa;

        // Seek back and write updated record
        fseek(file, position * RECORD_SIZE, SEEK_SET);
        fwrite(&student, RECORD_SIZE, 1, file);

        printf("Updated GPA for student at position %d to %.2f\n", position, new_gpa);
    } else {
        printf("No student at position %d\n", position);
    }

    fclose(file);
}

int main() {
    const char* db_file = "students.db";

    // Create database
    create_student_database(db_file, 10);

    // Add students
    StudentRecord s1 = {101, "Alice Johnson", 3.8f};
    StudentRecord s2 = {102, "Bob Smith", 3.2f};
    StudentRecord s3 = {103, "Charlie Brown", 3.9f};

    add_student(db_file, 0, &s1);
    add_student(db_file, 5, &s2);
    add_student(db_file, 9, &s3);

    // Read students
    read_student(db_file, 0);
    read_student(db_file, 5);
    read_student(db_file, 9);
    read_student(db_file, 3);  // Empty record

    // Update GPA
    update_student_gpa(db_file, 5, 3.5f);
    read_student(db_file, 5);

    return 0;
}
```

## Memory-Mapped Files (Platform Specific)
```c
#ifdef _WIN32
#include <windows.h>

void* memory_map_file(const char* filename, size_t* size) {
    HANDLE file_handle = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ,
                                   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) return NULL;

    HANDLE mapping_handle = CreateFileMapping(file_handle, NULL, PAGE_READONLY, 0, 0, NULL);
    if (mapping_handle == NULL) {
        CloseHandle(file_handle);
        return NULL;
    }

    void* mapped_data = MapViewOfFile(mapping_handle, FILE_MAP_READ, 0, 0, 0);
    CloseHandle(mapping_handle);
    CloseHandle(file_handle);

    // Get file size
    DWORD file_size = GetFileSize(file_handle, NULL);
    *size = file_size;

    return mapped_data;
}

void unmap_file(void* data) {
    UnmapViewOfFile(data);
}

#else  // Unix-like systems
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void* memory_map_file(const char* filename, size_t* size) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) return NULL;

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        close(fd);
        return NULL;
    }

    *size = sb.st_size;
    void* mapped_data = mmap(NULL, *size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    if (mapped_data == MAP_FAILED) return NULL;
    return mapped_data;
}

void unmap_file(void* data, size_t size) {
    munmap(data, size);
}
#endif

// Usage example
int main() {
    const char* filename = "large_file.txt";
    size_t file_size;
    void* data = memory_map_file(filename, &file_size);

    if (data) {
        // Access file data directly in memory
        char* text = (char*)data;
        printf("First 100 characters: %.100s\n", text);

        unmap_file(data
#ifdef __unix__
                   , file_size
#endif
                  );
    }

    return 0;
}
```

## Best Practices
- Always check return values of file operations
- Close files when done to prevent resource leaks
- Use appropriate file modes for your needs
- Handle errors gracefully with proper error messages
- Use binary mode for non-text data
- Consider file locking for concurrent access
- Validate file paths and permissions
- Use absolute paths when necessary
- Document file formats and structures

## Common Mistakes
- Forgetting to close files
- Not checking for NULL file pointers
- Using wrong file modes
- Buffer overflows when reading
- Not handling end-of-file correctly
- Race conditions in multi-threaded programs
- Assuming file operations are atomic
- Not checking available disk space

## Performance Considerations
- Use buffered I/O for small, frequent operations
- Use unbuffered I/O for large, sequential operations
- Consider memory mapping for random access
- Minimize seeks in random access files
- Use appropriate buffer sizes
- Profile I/O intensive code
- Consider asynchronous I/O for high performance

## Embedded Systems Considerations
- Limited file system support
- Flash memory wear considerations
- Power loss during writes
- Real-time constraints
- Memory constraints for buffers
- Use of volatile vs persistent storage
- Atomic write operations
- File system journaling