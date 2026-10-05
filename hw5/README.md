# Dynamic Memory Allocation in C

## Introduction

The goal of this lab was to practice dynamic memory allocation in C.

In these tasks, I used the main dynamic memory functions:

- `malloc()`
- `calloc()`
- `realloc()`
- `free()`

The main idea was to create arrays dynamically while the program is running instead of using fixed-size arrays. Another important part of the lab was making sure that all dynamically allocated memory was freed after it was no longer needed.

---

## Task 1: Dynamic Integer Array and Sum

### Explanation

In the first program, the user enters the number of elements they want to store.

Then memory is allocated using `malloc()`:

```c
array = malloc(n * sizeof(int));
```

This creates enough memory for `n` integers.

After that, the user enters the values, and a loop goes through the array and adds all the numbers together.

At the end, the program prints the sum.

The memory is released using:

```c
free(array);
```

### How the Program Works

1. The user enters the size of the array.
2. Memory is allocated using `malloc()`.
3. The user enters the integer values.
4. The program adds all values together.
5. The sum is printed.
6. The allocated memory is freed.

### Observation

This task showed that the size of an array does not have to be fixed before the program starts.

The amount of memory depends on the value entered by the user.

It also showed why `free()` is important. If the allocated memory is not freed, the program can cause a memory leak.

---

## Task 2: Using `calloc()` and Finding the Average

### Explanation

In this program, memory is allocated using `calloc()`:

```c
array = calloc(n, sizeof(int));
```

The main difference between `malloc()` and `calloc()` is that `calloc()` initializes all allocated values to zero.

Because of this, when the program prints the array immediately after allocation, all elements are `0`.

Then the user enters new values.

The program calculates the sum of the numbers and then calculates the average.

### How the Program Works

1. The user enters the number of elements.
2. `calloc()` allocates memory.
3. The program prints the initial array containing only zeroes.
4. The user enters the new values.
5. The updated array is printed.
6. The average is calculated and displayed.
7. The memory is freed.

### Observation

The most important thing in this task was seeing the difference between `malloc()` and `calloc()`.

`calloc()` automatically sets the allocated memory to zero, while `malloc()` does not guarantee this.

This can be useful when the program needs initialized values from the beginning.

---

## Task 3: Resizing an Array Using `realloc()`

### Explanation

This program first allocates memory for 10 integers using `malloc()`.

After the user enters 10 values, the array is resized so that it can only store 5 integers.

This is done using:

```c
temp = realloc(array, 5 * sizeof(int));
```

A temporary pointer is used instead of directly writing:

```c
array = realloc(...);
```

This is safer because if `realloc()` fails, the original pointer is not lost.

### How the Program Works

1. Memory for 10 integers is allocated.
2. The user enters 10 numbers.
3. The array is resized to 5 integers using `realloc()`.
4. The first 5 values are printed.
5. The allocated memory is freed.

### Observation

This task showed that `realloc()` can be used to change the size of memory that was already allocated.

When the array is made smaller, the first elements are still available, but the elements outside the new size should not be used anymore.

I also learned that using a temporary pointer with `realloc()` is a safer way to resize memory.

---

## Task 4: Dynamic Array of Strings

### Explanation

This task was slightly more complicated because the program uses dynamic memory in two levels.

First, memory is allocated for an array of three character pointers:

```c
strings = malloc(3 * sizeof(char *));
```

Then memory is allocated separately for every string:

```c
strings[i] = malloc(51 * sizeof(char));
```

The value `51` is used because each string can contain up to 50 characters, and one extra character is needed for the null terminator `\0`.

After entering the first three strings, the pointer array is resized using `realloc()` so it can store five strings.

Then memory is allocated for the two new strings.

### How the Program Works

1. Memory for 3 string pointers is allocated.
2. Memory for each individual string is allocated.
3. The user enters 3 strings.
4. The strings are printed.
5. The pointer array is resized from 3 elements to 5.
6. Memory is allocated for the two additional strings.
7. The user enters the extra strings.
8. All 5 strings are printed.
9. Every individual string is freed.
10. The main pointer array is also freed.

### Observation

This task showed that when dynamic memory contains other dynamically allocated memory, everything must be freed separately.

First, each string has to be freed:

```c
free(strings[i]);
```

After that, the array of pointers can be freed:

```c
free(strings);
```

If only the pointer array was freed, the memory used by the individual strings would still stay allocated.

This would cause a memory leak.

---

## Task 5: Student Grades

### Explanation

In this program, the user enters the number of students in the class.

The program then allocates enough memory to store all student grades using `malloc()`.

After the grades are entered, the program finds the highest and lowest grade.

The first grade is used as the starting value for both the highest and lowest variables.

Then the program compares the other grades one by one.

### How the Program Works

1. The user enters the number of students.
2. Memory is allocated for the grades.
3. The user enters the grades.
4. The first grade becomes the initial highest and lowest value.
5. The program compares all other grades.
6. The highest and lowest grades are printed.
7. The memory is freed.

### Observation

This task showed another useful example of dynamic arrays.

The program does not need to know the number of students before it starts.

It can allocate exactly the amount of memory that is needed.

The program also finds the maximum and minimum values using a simple loop.

---

## Conclusion

These programs helped me understand how dynamic memory works in C.

I learned that:

- `malloc()` allocates memory.
- `calloc()` allocates memory and initializes it to zero.
- `realloc()` changes the size of previously allocated memory.
- `free()` releases memory when it is no longer needed.

The most important part of these exercises was memory management.

Every successful memory allocation should eventually be followed by `free()`.

I also learned that when there are several levels of dynamically allocated memory, like in the string array task, each allocated part must be freed separately.

Overall, dynamic memory makes programs more flexible because the required amount of memory can be decided while the program is running.
