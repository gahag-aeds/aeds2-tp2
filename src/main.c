#include <stdio.h>
#include <stdlib.h>

#include <libaeds/data/array.h>
#include <libaeds/data/resources/file.h>
#include <libaeds/data/resources/memory.h>
#include <libaeds/data/resources/resource.h>
#include <libaeds/memory/allocator.h>


#define distribution_range_size 100


unsigned long distribution_counting[distribution_range_size] = { 0 };

unsigned long column_key(void* column) {
  unsigned char* value = column;
  return *value - 1;
}


int main(int argc, char* argv[]) {
  if (argc != 3)
    return -1;
  
  Allocator allocator = std_allocator(abort);
  Resources res = new_resources(&allocator);
  
  unsigned char* array;
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
  
  array = rs_register_alloc(
    allocator, size, sizeof(*array),
    rs_disposer_al(&allocator),
    &res
  );
  
  
  foreach_ix (i, 0, size) {
    unsigned int tmp;
    
    if (fscanf(input, "%u", &tmp) != 1)
      return delete_resources(&res), -3;
    
    array[i] = tmp;
  }
  
  
  count_occurrences( // O(n)
    array, size, sizeof(*array),
    column_key, distribution_counting
  );
  
  
  for (unsigned char i = 0; i < distribution_range_size; i++) // O(n)
    while (distribution_counting[i]-- > 0)
      if (fprintf(output, "%u ", i + 1) < 0)
        return delete_resources(&res), -5;
  
  
  return delete_resources(&res), 0;
}
