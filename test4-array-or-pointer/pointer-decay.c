/**
 * NOTE: Comments are written from 64-bit system perspective.
 */

#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define SEPARATOR printf("---------\n");

// According to standard:
//   Arrays passed as arguments to a function ALWAYS decay to pointers.
// Lets experiment.

int getSum(int numbers[]);
int getSum2(int numbers[3]);
int getSum3(int (*numbers)[10]);
int getSum4(int *numbers);

int main() {
  // NOTE: We have not even initialized this array !!!
  // We can even pass uninitialized nums array to these functions,
  // it wont complain..
  int nums1[10];

  // Even if we do, nothing will change:
  int nums[10] = {};

  SEPARATOR;
  for (int i = 0; i < 10; i++) {
    nums[i] = 10 - i;
    printf("%d ", nums[i]);
  }
  printf("\n");
  SEPARATOR;

  {
    printf("Pointer to an array: %p\n", nums);
    printf("Pointer to nums (SAME): %p\n", &nums);
    getSum(nums);
  }
  SEPARATOR;
  {
    printf("Pointer to an array: %p\n", nums);
    getSum2(nums);
  }
  SEPARATOR;
  {
    printf("Pointer to an array: %p\n", nums);
    int result = getSum3(&nums);
    printf("--\n");

    int nums2[5] = {};
    // Now we can have type safety over arrays.
    // -Wincompatible-pointer-types
    getSum3(nums2);
  }
  SEPARATOR;
  {
    printf("Pointer to an array: %p\n", nums);
    // Interestingly we can't do this:
    // Even though &nums and nums are the same (Addresswise)
    // NOTICE: Above example is the opposite of this.
    //
    // -Wincompatible-pointer-types
    int result = getSum4(&nums);
    printf("--\n");

    printf("Pass first element??\n");
    getSum4(nums);

    printf("--\n");
    printf("Pass first element !!!\n");
    getSum4(&nums[0]);

    // basically, nums === &nums[0]
  }
  SEPARATOR;

  return 0;
}

int getSum(int numbers[]) {
  printf("This pointer should be the same: %p\n", numbers);
  printf("Pointer of this pointer?: %p\n", &numbers);
  printf("But we can't get the size, because it decayed into a pointer? NO\n");

  // We get a warning from a compiler:
  // -Wsizeof-array-argument
  printf("Numbers sizeof: %lu\n", sizeof(numbers));
  // Result of this will be `8`(PTR size on 64 bit) because we are talking about
  // `int *numbers` instead of `int numbers[]`

  return 0;
}

int getSum2(int numbers[3]) {
  printf("This pointer should be the same: %p\n", numbers);
  printf("Does the cast happen to int numbers[2]? NO\n");

  // We get a warning from a compiler:
  // -Wsizeof-array-argument
  printf("Numbers sizeof: %lu\n", sizeof(numbers));
  // Result of this will be `8`(PTR size on 64 bit) because we are talking about
  // `int *numbers` instead of `int numbers[]`

  // This wont work (even if it compiles fine)
  // Compiler knows the size of the each element (int - 4 bytes)
  // And the pointer size is 8 bytes.
  // Result will be 8 / 4 = 2;
  // -Wsizeof-array-argument
  // -Wsizeof-pointer-div
  printf("Size: %lu\n", sizeof(numbers) / sizeof(numbers[0]));

  // This wont actually show a warning
  // BUT compiler IS NOT actually
  // validating passed parameter size.
  //return numbers[0] + numbers[1];

  return 0;
}

// BUT do we actually get advantage if we are doing this?
// type safety when passing parameters for example.
//  ---> IT DOES.
// AT LEAST one downside is that we wont be able to accept
// just a pointer array unless we cast them.
// --
// Another downside is we do introduce level of indirection.
// Now it will have pointer to an array, instead of having
// stack pointer like `*pointer` case, where we just get
// address to the first element.
int getSum3(int (*numbers)[10]) {
  // This is similar to how we can use pointers,
  // to still get the correct data about 
  printf("This pointer should be the same: %p\n", numbers);
  printf("Pointer to numbers?: %p\n", &numbers);

  printf("Numbers sizeof: %lu\n", sizeof(numbers));
  printf("Size: %lu\n", ARRAY_SIZE(*numbers));

  return 0;
}

// Basically this and above function are opposites in a way.
// This will complain if you pass pointer to the array, instead
// of the first element (Even if they are same)
// But wont complain if you pass first elements pointer.
// P.S. This is almost same as getSum and getSum2.
int getSum4(int *numbers) {
  printf("This pointer should be the same?: %p\n", numbers);
  printf("But we still with this local pointer?: %p\n", &numbers);

  // this wont complain though.
  printf("Numbers sizeof: %lu\n", sizeof(numbers));
  return 0;
}
