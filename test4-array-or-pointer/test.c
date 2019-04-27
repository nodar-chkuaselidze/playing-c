#include <stdio.h>
#include <stdlib.h>

static void print_arr(int numbers[]);
static void print_arr_ptr(const int *numbers);
static void print_arr_ptr2(const int *numbers);

int
main(void) {
  int arr1[] = { 1, 2, 3, 4 };
  int arr2[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  int *arr3 = malloc(sizeof(int) * 10);

  for (int i = 0; i < 10; i++)
    arr3[i] = 100 + i * 2;

  print_arr(arr1);
  print_arr_ptr(arr1);
  print_arr_ptr2(arr1);
  printf("....\n");

  print_arr(arr2);
  print_arr_ptr(arr2);
  print_arr_ptr2(arr2);
  printf("....\n");

  print_arr(arr3);
  print_arr_ptr(arr3);
  print_arr_ptr2(arr3);
  printf("....\n");

  free(arr3);

  return 0;
}

static void print_arr(int numbers[]) {
  printf("arr: %p\n", (void *)&numbers);
  printf("arr[0]: %p\n", (void *)&numbers[0]);
  printf("arr[1]: %p\n", (void *)&numbers[1]);
  printf("...\n");
}

static void print_arr_ptr(const int *numbers) {
  printf("arr ptr: %p\n", (void *)numbers);
  printf("arr ptr[0]: %p\n", (void *)(numbers));
  printf("arr ptr[1]: %p\n", (void *)(numbers + 1));
  printf("...\n");
}

static void print_arr_ptr2(const int *numbers) {
  printf("arr ptr: %p\n", (void *)numbers);
  printf("arr ptr[0]: %p\n", (void *)&numbers[0]);
  printf("arr ptr[1]: %p\n", (void *)&numbers[1]);
  printf("...\n");
}
