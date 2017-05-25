#include <stdio.h>
#include <stdlib.h>


int compare_uint(const void* a, const void* b) {
  unsigned int a1 = *(const unsigned int*) a;
  unsigned int a2 = *(const unsigned int*) b;
  
  if (a1 < a2) return -1;
  if (a1 > a2) return 1;
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3)
    return -1;
  
  
  unsigned int* vector;
  size_t size;
  
  FILE* input = fopen(argv[1], "r"); {
    if (input == NULL)
      return -2;
  }
  
  FILE* output = fopen(argv[2], "w"); {
    if (input == NULL || output == NULL) {
      fclose(input);
      return -2;
    }
  }
  
  
  if (fscanf(input, "%zu", &size) != 1) {
    fclose(input);
    fclose(output);
    return -3;
  }
  
  
  vector = malloc(size * sizeof(unsigned int));
  
  if (vector == NULL) {
    fclose(input);
    fclose(output);
    return -4;
  }
  
  
  for (size_t i = 0; i < size; i++)
    if (fscanf(input, "%u", &vector[i]) != 1) {
      free(vector);
      fclose(input);
      fclose(output);
      return -3;
    }
  
  
  qsort(vector, size, sizeof(unsigned int), compare_uint);
  
  
  for (size_t i = 0; i < size; i++)
    if (fprintf(output, "%u ", vector[i]) < 0) {
      free(vector);
      fclose(input);
      fclose(output);
      return -5;
    }
  
  
  free(vector);
  
  if (fclose(input) != 0) {
    fclose(output);
    return -6;
  }
  
  if (fclose(output) != 0)
    return -6;
  
  
  return 0;
}
