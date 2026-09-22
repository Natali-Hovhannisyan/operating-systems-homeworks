# Report on Homework4: Exploring Compilation Units in C Using nm, objdump, and readelf

## 1. Objective

The purpose of this assignment was to understand how a C program with multiple source files is compiled and linked.

I also used `nm`, `objdump`, and `readelf` to examine the symbols, assembly code, and ELF structure of the object files and the final executable.

---

## 2. Program Structure

The program consists of three files:

### `main.c`

```c
#include <stdio.h>
#include "math_utils.h"

int main()
{
    int number = 5;
    int result = square(number);

    printf("Square of %d is %d\n", number, result);

    return 0;
}
```

### `math_utils.c`

```c
#include "math_utils.h"

int square(int number)
{
    return number * number;
}
```

### `math_utils.h`

```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int square(int number);

#endif
```

The `main.c` file calls the `square()` function.

The function is implemented in `math_utils.c`, while its declaration is placed in `math_utils.h`.

---

## 3. Separate Compilation and Linking

The two source files were compiled separately:

```bash
gcc -c main.c
gcc -c math_utils.c
```

This created:

```text
main.o
math_utils.o
```

The object files were then linked together:

```bash
gcc main.o math_utils.o -o square_prog
```

The files in the directory were:

```text
main.c  main.o  math_utils.c  math_utils.h  math_utils.o  square_prog
```

Running the executable:

```bash
./square_prog
```

produced:

```text
Square of 5 is 25
```

This shows that each source file can first be compiled independently and then combined by the linker to create the final program.

---

## 4. Symbol Analysis Using `nm`

### `main.o`

Command:

```bash
nm main.o
```

Output:

```text
0000000000000000 T main
                 U printf
                 U square
```

The symbol `main` has the type `T`, meaning that it is defined in the code section of `main.o`.

The symbols `printf` and `square` have the type `U`, meaning that they are used by `main.o` but are not defined inside it.

`square` is implemented in another object file, while `printf` comes from the C standard library.

### `math_utils.o`

Command:

```bash
nm math_utils.o
```

Output:

```text
0000000000000000 T square
```

The `square` symbol has the type `T`, meaning it is defined in `math_utils.o`.

This matches what was seen in `main.o`: `main.o` needs the `square` function, and `math_utils.o` provides it.

### `square_prog`

Command:

```bash
nm square_prog
```

The final executable contained many more symbols.

Some important ones were:

```text
0000000000001149 T main
000000000000118c T square
                 U printf@GLIBC_2.2.5
0000000000001060 T _start
```

After linking, both `main` and `square` are defined in the final executable.

`printf` is still shown as undefined because it is provided by the shared C library when the program runs.

The executable also contains additional symbols such as `_start`, `_init`, and `_fini`.

---

## 5. Assembly Analysis Using `objdump`

The object files and executable were disassembled using:

```bash
objdump -d main.o
objdump -d math_utils.o
objdump -d square_prog
```

### `main.o`

The assembly contained the `main` function:

```text
0000000000000000 <main>:
```

The function call appeared similar to:

```text
18: e8 00 00 00 00    call   1d <main+0x1d>
```

At this stage, the address of `square()` has not been fully resolved because `main.o` has not yet been linked with `math_utils.o`.

### `math_utils.o`

The object file contained the `square` function:

```text
0000000000000000 <square>:
```

An important instruction was:

```text
0f af c0    imul %eax,%eax
```

The `imul` instruction performs multiplication.

It corresponds to the C statement:

```c
return number * number;
```

### `square_prog`

In the final executable, the call from `main` to `square` was resolved:

```text
1161: e8 26 00 00 00    call   118c <square>
```

The `square` function now had a real location:

```text
000000000000118c <square>:
```

The call to `printf` was also connected through:

```text
1180: e8 cb fe ff ff    call   1050 <printf@plt>
```

The executable contained much more assembly than the individual object files.

It included additional functions such as:

```text
_start
_init
_fini
register_tm_clones
deregister_tm_clones
```

This happens because the final executable needs extra code for program startup, shutdown, and shared libraries.

---

## 6. ELF Header Analysis Using `readelf`

The ELF headers were examined using:

```bash
readelf -h main.o
readelf -h math_utils.o
readelf -h square_prog
```

### `main.o`

Important values were:

```text
Class:                             ELF64
Type:                              REL (Relocatable file)
Machine:                           Advanced Micro Devices X86-64
Entry point address:               0x0
Number of program headers:         0
Number of section headers:         14
```

### `math_utils.o`

Important values were:

```text
Class:                             ELF64
Type:                              REL (Relocatable file)
Machine:                           Advanced Micro Devices X86-64
Entry point address:               0x0
Number of program headers:         0
Number of section headers:         12
```

Both object files have the type `REL`, meaning they are relocatable files.

They are not complete executable programs, so their entry point is `0x0`.

### `square_prog`

The final executable contained:

```text
Class:                             ELF64
Type:                              DYN (Position-Independent Executable file)
Machine:                           Advanced Micro Devices X86-64
Entry point address:               0x1060
Number of program headers:         13
Number of section headers:         31
```

Unlike the object files, the executable has an actual entry point and program headers.

This is because it is a complete program that can be loaded and executed.

---

## 7. Section Analysis

The sections were examined using:

```bash
readelf -S main.o
readelf -S math_utils.o
readelf -S square_prog
```

### Sections in `main.o`

`main.o` contained 14 sections.

Some important sections were:

```text
.text
.rela.text
.data
.bss
.rodata
.symtab
.strtab
```

Their main purposes are:

- `.text` contains compiled program instructions.
- `.data` contains initialized data.
- `.bss` is used for uninitialized data.
- `.rodata` contains read-only data such as strings.
- `.symtab` contains the symbol table.
- `.strtab` contains symbol names.
- `.rela.text` contains relocation information used during linking.

The `.rodata` section contains read-only information such as the string:

```text
Square of %d is %d
```

### Sections in `math_utils.o`

`math_utils.o` contained 12 sections.

Some important sections were:

```text
.text
.data
.bss
.symtab
.strtab
```

It has fewer sections than `main.o`.

For example, it does not have a `.rodata` section because the `square()` function does not use a string such as the one used in `printf`.

### Sections in `square_prog`

The final executable contained 31 sections.

It contained familiar sections such as:

```text
.text
.rodata
.data
.bss
.symtab
.strtab
```

It also contained additional sections such as:

```text
.interp
.dynsym
.dynstr
.rela.dyn
.rela.plt
.init
.plt
.fini
.dynamic
.got
```

The executable has more sections because it contains the combined program as well as additional information needed for execution and dynamic linking.

---

## 8. Comparison of the Files

`main.o` contains the compiled version of `main.c`.

It defines `main`, but it does not define `square`, so `square` appears as an undefined symbol.

`math_utils.o` contains the compiled version of `math_utils.c` and defines the `square` function.

The final executable, `square_prog`, combines both object files.

The linker connects the call to `square` in `main.o` with the implementation of `square` in `math_utils.o`.

The object files contain fewer symbols and sections because they represent individual source files.

The final executable contains more symbols, more sections, startup code, and information needed for shared libraries.

---

## 9. Conclusion

This assignment demonstrated the main stages of compiling a multi-file C program.

First, each `.c` file was compiled separately into an `.o` object file.

These object files contained machine code but were not complete executable programs.

The `nm` command showed which symbols were defined and which symbols were still required from other files or libraries.

The `objdump` command showed the assembly instructions generated by the compiler. It also showed that function calls were not completely resolved in the object files but were resolved after linking.

The `readelf` command showed the ELF headers and sections. The object files were relocatable ELF files, while the final `square_prog` file was a position-independent executable with more sections.

Finally, the linking process combined `main.o` and `math_utils.o`, resolved the reference to `square()`, and produced the runnable `square_prog` executable.
