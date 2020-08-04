#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define START_BLOCK(name) printf("--- %s ---\n", name)
#define END_BLOCK printf("---\n")

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// We can do sizeof this way.
typedef int arr10[10];

// Check struct-array wrapper as well.
struct arr10_s {
  int a[10];
};

/**
 * Because structs are copied on stack,
 * arr will be coppied as well with it.
 * NOTE: we are returning stack address, meaning
 * it will not be usable outside (We just want to compare).
 */
struct arr10_s stack_copy(struct arr10_s arr) {
  printf("Ptr from stack_copy: %p\n", &arr);
  // Here this is local copy that wont exist after this function.
  return arr;
}

int
main() {
  {
    START_BLOCK("Some sizeofs.");
    printf("sizeof(arr10): %lu\n", sizeof(arr10));
    printf("sizeof(struct arr10_s): %lu\n", sizeof(struct arr10_s));
    printf("sizeof(sizeof(int[10])): %lu\n", sizeof(int[10]));
    END_BLOCK;
  }

  {
    START_BLOCK("Staff we can't do with arrays.");
    // We can NOT assign arrays.
    // We can NOT initialize arrays w/o dynamically ?
    int arr[10] = {};
    // Next line is ILLEGAL.
    // You need to memcopy it.
    //int arr2[10] = arr[10];

    // We can of course take pointer to an array
    // either this way:
    int *arr1 = arr;

    // or this more specific way:
    int(*arr2)[10] = &arr;

    // NOTE THE DIFFERENCE ???
    printf("Original: %p\n", &arr);
    printf("Pointer to original: %p\n", arr1);
    printf("Specific pointer to original: %p\n", arr2);

    printf("Data: %lu, ptr: %lu, ptr: %lu\n", sizeof(arr), sizeof(arr1), sizeof(arr2));
    // Here we can see that just pointer does not contain
    // information about the structure whereas specific one
    // does as it should. :)
    printf("Sizeof derefenced: %lu, %lu\n", sizeof(*arr1), sizeof(*arr2));

    END_BLOCK;
  }

  {
    START_BLOCK("Pointers and Array, nasty..");

    int arr[10] = {};
    int *arr1 = arr;
    int (*arr2)[3] = (void *)arr1;

    printf("This is some magic done wrong.\n");
    printf("But sizeof second one: %lu\n", sizeof(*arr2));

    END_BLOCK;
  }

  {
    START_BLOCK("Nasty stuff we can do with arrays.");
    // WE can tell compiler to interpret
    // some allocated memory as SIZED array
    // even if it is not.
    int arr[10] = {};

    // Here let's try to shrink arr to size 2.
    // We tell compiler that we have a pointer that
    // is an array to 2 pointers.
    // This will give us a WARNING.
    // -Wincompatible-pointer-types
    //int (*arr2)[2] = &arr;

    // BUT We can do with the same size:
    // Basically we have created an PTR to an array.
    int (*arr3)[10] = &arr;

    // But anyhow, it will be passed to a function as
    // next line:
    // This will give us WARNING here though.
    //  -Wincompatible-pointer-types.
    //int *arr4 = &arr;

    // BUT if we take heap allocated, (compiler wont statically
    // analyze the code) it wont be able to complain
    // and I believe it's a gray area for the C lang.
    int(*arr5)[3] = malloc(sizeof(int[10]));

    // Here if we try to sizeof it:
    // Even though it is malloced as 10 * 4.
    printf("Allocated as [10], but instructed as [3]:\n");
    printf("sizeof: %lu, elements: %lu\n", sizeof(*arr5), ARRAY_SIZE(*arr5));
    END_BLOCK;
  }

  {
    START_BLOCK("If we have arrays we can always get the size of it.");

    // Not metter if it's malloced or stack initialized
    // if we type cast, compiler will treat it as sized array.
    // (just as any other cast) 
    int (*ints)[10] = malloc(sizeof(int[10]));
    int ints1[10] = {};

    for (int i = 0; i < 10; i++) {
      // write to it
      // We first dereference to an actual memory
      // and then use it as an array.
      (*ints)[i] = 10 - i;

      // print
      printf("(*ints)[%d] = %d,\n", i, (*ints)[i]);
    }
    printf("\n");

    printf("Array Size: %lu, Array size of ptr derefed to data.\n", ARRAY_SIZE(*ints));
    printf("Array size of normal array: %lu\n", ARRAY_SIZE(ints1));
    printf(" Or PTR arithmetics:\n");
    // TODO: Create PTR arithmetics test.
    // NOTE: See PTR arithmetics test.
    printf("array len with ptr arithmetics: %lu\n", *(ints + 1) - *ints);
    printf("array len with ptr arithmetics: %lu\n", *(&ints1 + 1) - ints1);
    printf("\n");

    printf("Size of pointer: %lu\n", sizeof(ints));
    printf("Size of value: %lu\n", sizeof(*ints));
    printf("Pointers: \n");
    printf("Local stack PTR to a PTR to an malloced array: %p\n", &ints);
    printf("ints variable (Actual pointer gotten from malloc): %p\n", ints);
    printf("First element: %p\n", ints[0]);
    END_BLOCK;
  }

  {
    START_BLOCK("We can initialize array with \"dynamic\" values.");

    printf("Please enter to chars: ");
    char arr[3] = {
      getchar(),
      getchar(),
      0
    };

    printf("%s\n", arr);

    END_BLOCK;
  }

  {
    START_BLOCK("Variable Length Arrays(VLA in short) in C are different !");

    printf("Input number of elements in array: ");
    unsigned char size = getchar();
    printf("\n");
    printf("Dynamic size: %d\n", size);

    int ints1[] = {};
    int ints2[] = {1};
    int ints3[] = {1, 2};
    int ints4[size];

    printf("Sizeof: %lu, Size: %lu \n", sizeof(ints1), ARRAY_SIZE(ints1));
    printf("Sizeof: %lu, Size: %lu \n", sizeof(ints2), ARRAY_SIZE(ints2));
    printf("Sizeof: %lu, Size: %lu \n", sizeof(ints3), ARRAY_SIZE(ints3));
    printf("Sizeof: %lu, Size: %lu \n", sizeof(ints4), ARRAY_SIZE(ints4));

    END_BLOCK;
  }

  // NOTE: More tests in struct.c probably.
  {
    START_BLOCK("Stack copy and stack/arr equality in memory size.");
    // Beginning of the struct is
    // the beginning of the array !
    struct arr10_s arr_s = { .a = {} };
    printf("%p, %p\n", &arr_s, &arr_s);

    // NOTE: Pointer to returned
    // is again different.
    // SO: This WILL copy arr_s 3 times.
    struct arr10_s arr2_s = stack_copy(arr_s);
    printf("Returned ptr: %p\n", &arr2_s);
    END_BLOCK;
  }

  return 0;
}
