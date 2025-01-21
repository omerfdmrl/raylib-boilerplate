## Coding Style

This repository follows the K&R (Kernighan and Ritchie) and Plan 9 coding style. These are well-known styles widely used in the C programming community. The goal is to maintain consistency and readability in the codebase.

Although some minor deviations are acceptable, try to stick to the same style as much as possible. Below are the basic points and examples to follow when writing code.

## Guide

### 1. Braces

Place braces on the same line as control statements (`if`, `else`, `while`, `for`):

```C
if (x == y) {
    s1;
    s2;
} else {
    s3;
    s4;
}
```

Place braces on the same line with following a space after function definitions:

```c
type functionname(args) {
    if (a == b) {
        s1;
        s2;
    }
    else {
        s3;
        s4;
    }
}
```

No braces around single statement blocks, and use new line:

```C
if (a == b)
    s1;
```

### 2. Indention

Indent with TABs. Do not use spaces for indention.

### 3. Function

Function return type should be placed on a same line:

```C
int functionname(int a, int b) {
    return (a - b);
}

functionname(3, 5);
```

- Do not use more then 4 parameters in functions.
- Do not make functions longer than 25 lines.
- Return values must be in parentheses.
- Function calls should be formatted without spaces.
- Provide checks using assert messages in functions.

### 4. Variable Declaration

Group all variable declarations together at the start of the function or block if possible.\
Do not assign variable values ​​on the line where you define them.

```C
int functionname(args) {
    int a, b;

    a = 3;
    b = 5;

    return a * b;
}
```

- Use `int` for integers, `float` for floating-point numbers and `char` for characters.
- Use descriptive types for fixed-width integers such as `uint8_t`, `int64_t`.

### 5. Use of Constants and Magic Number

Avoid **magic numbers** in your code. Instead, use `#define` constants or enum values to represent any numerical values that are used in multiple places.

```C
#define MAX_SIZE 100

for (i = 0; i < MAX_SIZE; i++) {
    // Code
}
```

### 6. Pointer Declaration

Declare pointers with the asterisk (\*) next to the type, not next to the variable name.

```C
int *ptr;
```

### 7. Type Declaration

Declare struct with `s_` prefix and use typedef in external line.

```C
struct s_my_struct {...}

typedef struct s_my_struct my_struct;
```

In the same way, define enums with `e_` prefix.

```C
enum e_my_enum {...}

typedef enum e_my_enum my_enum;
```

### 8. Naming Conventions

- Use snake_case
- Use descriptive variable names: Avoid one-letter variable names except for loop counters.
- Do not use Hungarian notations, it's just ugly.
- Do not use platform-specific types like BYTE, DWORD unless writing platform-specific code (e.g., Win32).

### 9. Avoiding Copy-Pasting

Do not copy-paste code from other sources (e.g., IDA). Always ensure the code is formatted correctly and adheres to the coding standards.

### 10. Code Cleanliness and Organization

- Keep code clean and well-structured: Make sure the code is easy to read and maintain. Avoid long functions or complicated structures when simpler solutions are available.
- Group related functions together: In general, functions that serve similar purposes should be located near each other.
