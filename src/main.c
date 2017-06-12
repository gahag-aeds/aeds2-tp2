#include <stdio.h>
#include <stdlib.h>

#include <libaeds/array.h>
#include <libaeds/ordering.h>
#include <libaeds/sorting.h>
#include <libaeds/resources/file.h>
#include <libaeds/resources/memory.h>
#include <libaeds/resources/resource.h>


int main(int argc, char *argv[]) {
  if (argc != 3)
    return -1;
  
  
  Allocator allocator = std_allocator(abort);
  Resources res = new_resources(&allocator);
  
  unsigned int* vector;
  size_t size;
  
  FILE* input; {
    if (!rs_register_file(&input, argv[1], "r", rs_disposer_file(fclose_stderr), &res))
      return delete_resources(&res), -2;
  }
  
  FILE* output; {
    if (!rs_register_file(&output, argv[2], "w", rs_disposer_file(fclose_stderr), &res))
      return delete_resources(&res), -2;
  }
  
  
  if (fscanf(input, "%zu", &size) != 1)
    return delete_resources(&res), -3;
  
  vector = rs_register_alloc(
    allocator, size, sizeof(unsigned int),
    rs_disposer_al(&allocator),
    &res
  );
  
  
  foreach_ix (i, 0, size)
    if (fscanf(input, "%u", &vector[i]) != 1)
      return delete_resources(&res), -3;
  
  
  array_intro_sort(vector, size, sizeof(unsigned int), compare_uint);
  
  
  foreach_ix (i, 0, size)
    if (fprintf(output, "%u ", vector[i]) < 0)
      return delete_resources(&res), -5;
  
  
  return delete_resources(&res), 0;
}
