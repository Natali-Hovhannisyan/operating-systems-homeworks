# Pointer Assignments Report

## Assignment 1
Used a pointer to store the address of an integer and modify its value through dereferencing.

**Observation:** `ptr` stores the address, while `*ptr` gives the value at that address.

## Assignment 2
Used pointer arithmetic to traverse and modify an integer array.

**Observation:** `*(ptr + i)` accesses the same element as `arr[i]`.

## Assignment 3
Passed the addresses of two integers to a `swap()` function.

**Observation:** Using pointers in functions allows modifying the original variables.

## Assignment 4
Used a pointer to a pointer (`int **`) to access an integer through two levels of indirection.

**Observation:** `**ptr2` gives the original integer value.

## Assignment 5
Used a character pointer to traverse the string `"Hello"` and count its characters until `'\0'`.

**Observation:** I initially used `(*ptr + i)` instead of `*(ptr + i)`, which changed the character value instead of moving through the string.

