#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Array_struct {
  int *data;
  int len;
  int* orig_data;
} Array;

Array *create_array(int len) {
  Array *tmp;
  tmp = malloc(sizeof(Array));
  tmp->data = (int*) malloc(sizeof(int) * len);
  tmp->len = len;
  tmp->orig_data = tmp->data;
  return tmp;
}

void print_array(Array *array) {
  printf("[ ");
  for(int i = 0; i < array->len; i++) {
    printf("%d ", array->data[i]);
  }
  printf("] \n");
}

void delete_array(Array* array) {
  free(array->orig_data);
  free(array);
}

void process(Array *array, int n) {
  int left_len = array->len / 2;
  int right_len = array->len - left_len;
  int diff = left_len - right_len;
  int *left_ptr = array->data + diff;
  int *right_ptr = array->data + left_len;
  int *cur_left_item;
  int zero = 0;

  if((array->len == 1) || (n == 0)) return;

  for(int i = right_len - 1; i >= 0; i--) {
    cur_left_item = left_ptr + i;
    cur_left_item = (cur_left_item < array->data)? &zero : cur_left_item;
    *(right_ptr + i) += *cur_left_item;
  }

  array->data = right_ptr;
  array->len = right_len;
  process(array, n - 1);
}

int main(int argc, char **argv) {
  const int in_array_offset = 2;
  int iterations;

  if(argc < 3) {
    printf("Usage: %s iterations [values...]\n", argv[0]);
    return -1;
  }

  Array* new_array = create_array(argc - in_array_offset);
  for(int i = 0; i < argc - in_array_offset; i++) {
    new_array->data[i] = atoi(argv[i + in_array_offset]);
  }
  iterations = atoi(argv[1]);

  printf("Input array:\t");
  print_array(new_array);
  process(new_array, iterations);
  printf("Output array:\t");
  print_array(new_array);
  delete_array(new_array);
  return 0;
}
