#include <stdio.h>
#include <stdlib.h>

/**
 * Even though arrays decay to pointers when passed as arguments
 * if we wrap it in a struct we can tell compiler to stack copy
 * it into those functions.
 * Why, How,... whatever man that's how it is.
 *
 * p.s. VLA will be covered in vla.c
 */

#define START_BLOCK(name) printf("--- %s ---\n", name)
#define END_BLOCK printf("---\n")

// Nice thing is, structs don't take any extra space, or have an
// overhead (Well it does, but anyway).
struct arr10 {
  int arr[10];
};

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

int sumPtr(int *arr);
int sumArr(int arr[10]);
int sum(int (*arr)[10]);

int main() {
  printf("sizeof(struct arr10_s): %lu\n", sizeof(struct arr10_s));

  {
    START_BLOCK("Stack copy and stack/arr equality in memory size.");
    // Beginning of the struct is
    // the beginning of the array !
    struct arr10_s arr_s = { .a = {} };
    printf("%p, %p\n", &arr_s, &arr_s.a);

    // NOTE: Pointer to returned
    // is again different.
    // SO: This WILL copy arr_s 3 times.
    struct arr10_s arr2_s = stack_copy(arr_s);
    printf("Returned ptr: %p\n", &arr2_s);
    END_BLOCK;
  }

  {
    START_BLOCK("If we pass to the function, it to same transforms.");

    struct arr10_s arr_s = { .a = {} };

    printf("%p, %p\n", &arr_s, &arr_s.a);
    sumPtr(arr_s.a);
    sumArr(arr_s.a);
    sum(&arr_s.a);

    END_BLOCK;
  }

  {
    START_BLOCK("We can of course malloc this as well.");

    struct arr10_s *arr10_p = calloc(
      sizeof(struct arr10_s),
      sizeof(struct arr10_s)
    );

    for (int i = 0; i < 10; i++)
      printf("%d ", arr10_p->a[i]);
    printf("\n");

    // this will copy data into stack.
    struct arr10_s arr10_s = *arr10_p;

    printf("Heap PTR: %p\n", arr10_p);
    printf("Stack PTR: %p\n", &arr10_s);

    free(arr10_p);
    END_BLOCK;
  }
}

/**
 * If you grab the array, you can devolve to standard rules
 * of array.
 */

int sumPtr(int *arr) {
  printf("Pointer of array: %p\n", arr);
  return 0;
}

int sumArr(int arr[10]) {
  printf("Pointer of arr10: %p\n", arr);
  return 0;
}

int sum(int (*arr)[10]) {
  printf("Array of 10 instead of ptr: %p\n", arr);
  printf("Sizeof: %lu\n", sizeof(*arr));
  return 0;
}
