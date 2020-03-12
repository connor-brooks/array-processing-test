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
  /* For freeing array at end */
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
  /* Calculate split sizes and difference*/
  int left_len = array->len / 2;
  int right_len = array->len - left_len;
  int diff = left_len - right_len;

  /* Create split pointers*/
  int *left_ptr = array->data + diff;
  int *right_ptr = array->data + left_len;

  /* Pointer for the item in the left split we're looking at*/
  int *cur_left_item;

  /* For use as padding when splits aren't the same size*/
  int zero = 0;

  /* Base case, do we have one number or is n equal to 0, if so, stop */
  if((array->len == 1) || (n == 0)) return;

  /* Go backwards because if we went forwards we'd end up overwriting
   * data we need if the arrays were different size (due to the splits being
   * aligned to the right */
  for(int i = right_len - 1; i >= 0; i--) {
    /* Set pointer for item in left split we're looking at, taking 
     * into account diff of two split's lengths, so they're right
     * aligned*/
    cur_left_item = left_ptr + i;

    /* If we're out of bounds, set cur_a to point to a zero (left padding) 
     * &zero isn't 100% needed, and NULL could be used instead, and then 
     * checked for when the left item is added to the right, however that
     * would require an additional check */
    cur_left_item = (cur_left_item < array->data)? &zero : cur_left_item;

    /* Use space in the right split to save new values by adding the
     * corresponding item from the left split. */
    *(right_ptr + i) += *cur_left_item;
  }

  /* Push main array pointer to the start of the b split, and set the length
   * of the main array to the length of the b split */
  array->data = right_ptr;
  array->len = right_len;

  /* Recursively call this function (may not be as space efficient as decrementing 
   * the iteration (n) in a for loop in main() and recalling the function, but
   * still works nicely */
  process(array, n - 1);
}

int main(int argc, char **argv) {

  const int in_array_offset = 2;
  int iterations;

  if(argc < 3) {
    printf("Usage: %s iterations [values...]\n", argv[0]);
    return -1;
  }

  /* Create array strut and copy values from input */
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
