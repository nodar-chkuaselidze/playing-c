Pointer vs Array
================

Files:
  - Some simple tests - [./test.c](./test.c)
  - Main tests - [./ptr-v-arr.c](./ptr-v-arr.c)
  - Pointer Decay - [./pointer-decay.c](./pointer-decay.c)
  - Array inside a struct - [./struct.c](./struct.c)

## Summury

#### Simple Tests
#### Pointer v Array
  - We can't assign array to another array.
  - We either use `memcpy` or use `pointers`.
  - We can have array pointers with dimensions `int (*numbers_ptr)[10]`.
  - We can only get size when:
    - We have an array
    - We have a pointer to sized array. (pointer with dimensions)
  - Pointer to array is actually pointer to first element.
    - But pointer to an array is actually, one more lookup:
    - Get PTR from stack pointer -> Read PTR from there -> Than get data
    from that PTR.
      - PTR -> PTR -> DATA
    - Where in arrays: You get PTR from stack -> Then get data from PTR.
      - PTR -> DATA
  - General C Note: Pointers can be casted to anything from anything.
    It wont care.
  - C99/C11 supports dynamic declaration/initialization of array size.

#### Pointer Decay
  - Arrays passed to functions decay into pointers, ALWAYS:
    - `void fn(int numbers[10])` -> `void fn(int *numbers)`
    - `void fn(int numbers[])` -> `void fn(int *numbers)`
    - meaning we can't do sizeof or other array operations.
    - NOTE: C wont complain if you try to access array members.
  - If we want to preserve typesafe dimensions of the array,
  we need specific pointer types.
    - `void fn(int (*numbers)[10])` or `void fn(int (*numbers)[SOME_CONST])`
    - This allows us to do type checks before passing arrays as arguments.
    - BUT we can no longer pass different sized or just pointers.
      (not w/o warnings)
    - Pointers in general introduce same level of indirection as described in
    ptr-v-arr.
      - PTR -> PTR -> data
      - p.s. We can copy arrays on stack using structs.

#### Array inside a struct
  - Arrays (Not PTR to ARR) inside struct will get copied like structs
  whenever struct will get copied.
  - We can use this to make arrays stack/copyable.
  - If we access array directly, we still get above behaviour. (PTR decay)
