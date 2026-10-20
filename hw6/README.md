# Homework 6: Data Alignment and Struct Padding in C

## Assignment 1: Understanding Data Alignment

In this assignment, I created variables of types `int`, `char`, `double`, and `short`. I used `sizeof()` to find their sizes and the `&` operator to print their memory addresses.

<img width="658" height="231" alt="image" src="https://github.com/user-attachments/assets/60558281-d193-4f2b-ad16-c44bef8b6666" />

The results showed that `int` occupies 4 bytes, `char` occupies 1 byte, `double` occupies 8 bytes, and `short` occupies 2 bytes.

The memory addresses were:

- int: `0x7ffd3b8e184c`
- char: `0x7ffd3b8e1849`
- double: `0x7ffd3b8e1850`
- short: `0x7ffd3b8e184a`

From these results, I observed that different data types have different alignment requirements. The `int` variable is stored at an address divisible by 4, the `double` at an address divisible by 8, and the `short` at an address divisible by 2. The `char` variable can be stored at any byte address because it only requires 1 byte.

This demonstrates that the compiler places variables at memory addresses that satisfy their alignment requirements. The exact addresses may change between program executions.

## Assignment 2: Struct Padding

In this assignment, I created three structs containing the same fields (`char`, `int`, and `double`) but arranged in different orders. I printed the size of each struct and the addresses of its fields to observe how padding affects memory usage.

<img width="658" height="281" alt="image" src="https://github.com/user-attachments/assets/5ac155b5-1902-4c65-a541-11ac116b8c91" />

The first struct had the field order `char`, `int`, `double` and occupied 16 bytes. Its field addresses were `0x7fff9469fcf0`, `0x7fff9469fcf4`, and `0x7fff9469fcf8`. Although the fields require only 13 bytes in total, the compiler added 3 padding bytes after `char` so that `int` starts at a properly aligned address.

The second struct had the field order `double`, `int`, `char` and also occupied 16 bytes. Its field addresses were `0x7fff9469fd00`, `0x7fff9469fd08`, and `0x7fff9469fd0c`. In this case, the compiler added 3 padding bytes at the end of the struct to make its total size a multiple of its alignment requirement.

The third struct had the field order `char`, `double`, `int` and occupied 24 bytes. Its field addresses were `0x7fff9469fd10`, `0x7fff9469fd18`, and `0x7fff9469fd20`. Here, the compiler added 7 padding bytes after `char` and 4 padding bytes at the end, increasing the total size.

These results show that changing the order of fields can affect the size of a struct. The first two arrangements used 16 bytes, while the third used 24 bytes. Padding is added to satisfy alignment requirements, and arranging fields differently can reduce or increase the amount of unused memory.

## Assignment 3: Data Alignment with #pragma pack

In this assignment, I compared a normal struct with structs using `#pragma pack(1)`, `#pragma pack(2)`, and `#pragma pack(4)`. Each struct contained the same fields: `char a`, `int b`, and `double c`.

<img width="658" height="383" alt="image" src="https://github.com/user-attachments/assets/0c5cc3ca-22d8-4d4f-b21c-5e539ae71dce" />

The normal struct occupied 16 bytes. Its field addresses were `0x7ffca3213c50`, `0x7ffca3213c54`, and `0x7ffca3213c58`. The compiler added 3 padding bytes between `char` and `int` to satisfy the normal alignment requirements.

With `#pragma pack(1)`, the struct size decreased to 13 bytes. The field addresses were `0x7ffca3213c35`, `0x7ffca3213c36`, and `0x7ffca3213c3a`. The fields were placed directly next to each other without padding.

With `#pragma pack(2)`, the struct occupied 14 bytes. The field addresses were `0x7ffca3213c42`, `0x7ffca3213c44`, and `0x7ffca3213c48`. Only 1 padding byte was added between `char` and `int`.

With `#pragma pack(4)`, the struct occupied 16 bytes. The field addresses were `0x7ffca3213c60`, `0x7ffca3213c64`, and `0x7ffca3213c68`. The compiler added 3 padding bytes, resulting in the same total size as the normal struct.

The results demonstrate that `#pragma pack` changes the alignment requirements of struct fields. Smaller packing values reduce padding and can save memory. However, packed structs may be less efficient to access on some systems because their fields may not be naturally aligned.

## Conclusion

These assignments helped me understand how data alignment and padding work in C. Different data types have different sizes and alignment requirements. When multiple fields are placed inside a struct, the compiler may add padding bytes to align them correctly.

I also observed that changing the order of struct fields can affect memory usage. Using `#pragma pack` allows us to control alignment and reduce padding.

Overall, data alignment is important because it affects how efficiently memory is organized and accessed.
