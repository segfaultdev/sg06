#include <sgforth.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static int is_space(char c) {
  return (isspace(c) || c == ',');
}

int sg_token(FILE *file, char *buffer) {
  int in_string = 0;
  
  char c = ' ';
  
  while (c != EOF && is_space(c)) {
    c = fgetc(file);
    
    if (c == ';') {
      while (c != EOF && c != '\n') c = fgetc(file);
    }
  }
  
  if (c == EOF) return 0;
  
  while (c != EOF && (!is_space(c) || in_string)) {
    if (c == '"') {
      in_string = !in_string;
    } else if (!in_string) {
      if (c == ';') {
        while (c != EOF && c != '\n') c = fgetc(file);
        continue;
      }
    }
    
    *(buffer++) = c;
    
    c = fgetc(file);
  }
  
  if (c == EOF) return 0;
  *buffer = '\0';
  
  while (c != EOF && is_space(c)) {
    c = fgetc(file);
    
    if (c == ';') {
      while (c != EOF && c != '\n') c = fgetc(file);
    }
  }
  
  if (c != EOF) ungetc(c, file);
  return 1;
}

void sg_parse(const char *path, FILE *output) {
  FILE *file = fopen(path, "r");
  
  if (!file) {
    printf("error: cannot open file: '%s'\n", path);
    exit(1);
  }
  
  char buffer[64];
  
  while (sg_token(file, buffer)) {
    fprintf(output, "  ; TOKEN: '%s'\n", buffer);
    
    if (!strcmp(buffer, "+") || !strcmp(buffer, "^")) {
      // load, decrease and save stack pointer
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // get stack pointer into x
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // read value at stack pointer to b
      fprintf(output, "  mov b, [x]\n");
      
      // save b to 0x20FD
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov [x], b\n");
      
      // decrease and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
      
      // get stack pointer into x
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // read value at stack pointer to b
      fprintf(output, "  mov b, [x]\n");
      
      // load a with the value at 0x20FD
      fprintf(output, "  mov l, 0xFD\n");
      fprintf(output, "  mov a, [x]\n");
      
      // store sum/xor into b(by using 0x20FD already set in x)
      fprintf(output, "  mov [x], (a %c b)\n", *buffer);
      fprintf(output, "  mov b, [x]\n");
      
      // get stack pointer into x
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov l, a\n");
      
      // store b at stack pointer
      fprintf(output, "  mov [x], b\n");
      
      // increase and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0x01\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "@")) {
      
    } else if (!strcmp(buffer, "!")) {
      
    } else if (!strcmp(buffer, "drop")) {
      // load, decrease and save stack pointer
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "halt")) {
      // halt
      fprintf(output, "  hlt\n");
    } else if (!strcmp(buffer, "dup")) {
      // get stack pointer minus 1 into x
      fprintf(output, "  mov x, 0x20FC\n");
      fprintf(output, "  mov a, [x]\n");
      fprintf(output, "  mov b, 0xFF\n");
      fprintf(output, "  mov l, (a + b)\n");
      
      // read value at stack pointer to b
      fprintf(output, "  mov b, [x]\n");
      
      // get stack pointer into x
      fprintf(output, "  mov l, a\n");
        
      // store value in b at stack pointer
      fprintf(output, "  mov [x], b\n");
      
      // increase and save new stack pointer
      fprintf(output, "  mov l, 0xFC\n");
      fprintf(output, "  mov b, 0x01\n");
      fprintf(output, "  mov [x], (a + b)\n");
    } else if (!strcmp(buffer, "if")) {
      
    } else {
      char *end;
      uint8_t value = strtol(buffer, &end, 0);
      
      if (end == buffer + strlen(buffer)) {
        // get stack pointer into x
        fprintf(output, "  mov x, 0x20FC\n");
        fprintf(output, "  mov a, [x]\n");
        fprintf(output, "  mov l, a\n");
        
        // store value at stack pointer
        fprintf(output, "  mov b, %d\n", value);
        fprintf(output, "  mov [x], b\n");
        
        // increase and save new stack pointer
        fprintf(output, "  mov l, 0xFC\n");
        fprintf(output, "  mov b, 0x01\n");
        fprintf(output, "  mov [x], (a + b)\n");
      }
    }
  }
  
  fclose(file);
}

int main(void) {
  sg_parse("test.fth", stdout);
  return 0;
}
