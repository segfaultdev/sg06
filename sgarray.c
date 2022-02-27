#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char **argv) {
  if (argc != 2) return 1;
  
  FILE *file = fopen(argv[1], "rb");
  if (!file) return 1;
  
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  uint8_t *buffer = malloc(size);
  fread(buffer, 1, size, file);
  
  printf("int user_rom[] = {\n");
  
  for (int i = 0; i < size; i++) {
    if (i % 128 == 0) printf("  ");
    printf("0x%02X, ", buffer[i]);
    
    if (i % 128 == 127) printf("\n");
  }
  
  printf("};");
  
  fclose(file);
  return 0;
}
